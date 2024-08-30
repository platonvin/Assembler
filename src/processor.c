#include "processor_functions.h"
#include "stack_functions.h"
#include "string_funcs.h"
#include <stdio.h>
//clang-tidy gets crazy on codegeneration
#include <math.h>
#include <getopt.h>
#include <string.h>

bool detect_logger(int argc, char **argv)
{
    int should_log = 0;

    static struct option long_options[] = {
        {"log", no_argument, 0, 0},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "", long_options, &option_index)) != -1) {
        if (opt == 0) {
            if (long_options[option_index].flag != 0) {
                break;
            }
            if (strcmp(long_options[option_index].name, "log") == 0) {
                should_log = 1;
            }
        }
    }

    return should_log;
}
int main(int argc, char **argv) 
{
    char program_name_orig[256] = {0};
    char program_name[256] = {0};
    bool should_log = detect_logger(argc, argv);

    if( ((argc == 2) && !should_log) || ((argc == 3) && should_log) )
    {
        str_CAT(program_name_orig, argv[argc - 1]);
        printf("program_name_orig %s\n", program_name_orig);
    }
    else 
    {
        printf("No input file\n");
        printf("Usage: processor filename\n");
        printf("Example: processor programs/factor.compiled\n");
        exit(1);
    }  

    FILE* log_file = fopen("log_file.txt", "w");
    //try directly, then try with .compiled
    str_CAT(program_name, program_name_orig);
    str_CAT(program_name, ".compiled");
    FILE *prog_file = fopen(program_name, "rb");
    if(prog_file == 0){
        prog_file = fopen(program_name_orig, "rb");
    }
    assert(prog_file != 0);
    
    fseek(prog_file, 0l, SEEK_END);
    size_t len = ftell(prog_file) + 1;
    fseek(prog_file, 0l, SEEK_SET);
    len /= sizeof(cmd_type);
    
    cmd_type *code = (cmd_type*)calloc(len, sizeof(cmd_type));
    fread(code, sizeof(cmd_type), len, prog_file);
    fclose(prog_file);

    cmd_type cmd_num = 0;
    cmd_type temp = 0;
    bool is_ram = false;
    bool is_reg = false;
    bool is_num = false;
    

    stack_t *stack = stack_new();
    cmd_type ram[MAX_RAM] = {0};
    cmd_type vram[MAX_VRAM] = {0};
    cmd_type reg[MAX_REG] = {0};

    stack->log_file = log_file;
    stack->should_log = should_log;

    for(size_t i = 0; i < len; )
    {   
        is_ram = code[i] & RAM_BIT;
        is_reg = code[i] & REG_BIT;
        is_num = code[i] & NUM_BIT;
        cmd_num = code[i++] & CMD_MASK;
        cmd_type t1 = 0;
        cmd_type t2 = 0;

        if(false) {} //for linter
        #include "defines/commands.h"
    }

    printf(":%d\n", __LINE__);
    stack_del(stack);
    printf(":%d\n", __LINE__);
    free(code);

    return 0;
}