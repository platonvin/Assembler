//что делает процессор:
//читает из файла
//номер команды- выполняет

#include "processor_functions.h"
#include "stack_functions.h"
#include "string_funcs.h"

int main()
{
    printf("file to run?\n\n");
    char program_name[256] = {0};
    scanf("%s", program_name);
    str_CAT(program_name, ".compiled");

    FILE* log_file = fopen("log_file.txt", "w");

    FILE *prog_file = fopen(program_name, "rb");
    assert(prog_file != 0);
    
    fseek(prog_file, 0l, SEEK_END);
    size_t len = ftell(prog_file) + 1;
    // printf("len = %zu\n", len);
    fseek(prog_file, 0l, SEEK_SET);
    len /= sizeof(cmd_type);
    // printf("len = %zu\n", len);

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
    cmd_type reg[MAX_REG] = {0};

    stack->log_file = log_file;

    // for(size_t i = 0; i < len; i++)
    // {   
    //     printf("%02X ", (int)(unsigned char)code[i]);
    // }
    // printf("\n\n");

    for(size_t i = 0; i < len; )
    {   
        is_ram = code[i] & RAM_BIT;
        is_reg = code[i] & REG_BIT;
        is_num = code[i] & NUM_BIT;
        cmd_num = code[i++] & CMD_MASK;
        cmd_type t1 = 0;
        cmd_type t2 = 0;

        // printf("%02X ", (int)(unsigned char)cmd_num);

        if(false) {}
        #include "defines/commands.h"
    }

    stack_del(stack);
    free(code);

    return 0;
}