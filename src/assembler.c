#include "assembler_functions.h"
#include "string_funcs.h"
#include <stdlib.h>
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
    char program_name[256] = {0};
    bool should_log = detect_logger(argc, argv);

    if( ((argc == 2) && !should_log) || ((argc == 3) && should_log) )
    {
        str_CAT(program_name, argv[argc - 1]);
        printf("program_name_orig %s\n", program_name);
    }
    else
    {
        printf("No input file\n");
        printf("Usage: assembler filename\n");
        printf("Example: assembler programs/factor\n");
        exit(1);
    }  
    ass_prog_t ass_prog = {};
    ass_prog.prog_file = fopen(program_name, "r");
    ass_prog.log_file = fopen("log_file.txt", "w");
    // ass_prog.should_log = should_log;

    str_CAT(program_name, ".compiled");

    FILE *prog_compiled = fopen(program_name, "wb");

    devide_in_lines(&ass_prog);

        size_t elem_count = 0;
        for(size_t i = 0; i < ass_prog.prog_lines_size; i++)
        {
            elem_count += count_words(ass_prog.prog_lines[i]);
        }

        printf("elem_c = %zu\n", elem_count);

        size_t max_elem_count = ass_prog.prog_lines_size * (MAX_ARG_NUM + 1) + 1;

        printf("max_elem_c = %d\n", max_elem_count);

    ass_prog.code = (cmd_type*)calloc(elem_count, sizeof(cmd_type));
        
    compile(&ass_prog);

    ass_prog.error = no_errors;

    devide_in_lines(&ass_prog);
    compile(&ass_prog);

    if(ass_prog.error != no_errors)
    {
        printf("ERROR = %d\n", ass_prog.error);
    }

    for(size_t i = 0; i < elem_count; i++)
    {
        printf("%08X ", (long int)(ass_prog.code[i]));
    }
    fwrite(ass_prog.code, sizeof(cmd_type), elem_count, prog_compiled);

    free(ass_prog.code);
    free(ass_prog.prog_lines);
    free(ass_prog.prog_text);

    return 0;
}