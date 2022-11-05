#include <stdio.h>
#include <malloc.h>
#include "string_funcs.h"

#define RAM_BIT 0x80000000
#define REG_BIT 0x40000000
#define NUM_BIT 0x20000000
#define CMD_MASK 0x1FFFFFFF

#define MAX_ARG_NUM 2
#define MAX_FLAG_NUM 64
#define MAX_FLAG_NAME_SIZE 16

typedef long cmd_type;

#define _CMD_DEF_(name, num, isarg, isjmp, ...)  \
    else if(num == cmd_num)\
    {\
        printf(#name);\
        is_arg = isarg;\
        is_jmp = isjmp;\
    }

#define _REG_DEF_(name, regnum)  \
else if(reg_num == regnum)\
{\
    printf("%3s", #name);\
}

int main()
{
    printf("file to decompile?\n\n");
    char program_name[256] = {0};
    scanf("%s", program_name);
    str_CAT(program_name, ".compiled");

    printf("NAME IS %s\n", program_name);

    FILE * program_compiled_file = fopen(program_name, "r");

    fseek(program_compiled_file, 0l, SEEK_END);
    size_t program_len = ftell(program_compiled_file) / sizeof(cmd_type);
    printf("SIZE IS %zu\n", program_len);
    fseek(program_compiled_file, 0l, SEEK_SET);

    cmd_type *code = (cmd_type*)calloc(program_len, sizeof(cmd_type));

    fread(code, sizeof(cmd_type), program_len, program_compiled_file);

    // for(size_t i = 0; i < program_len; i++)
    // {
    //     printf("%08ld ", code[i]);
    // }
    // printf("\n");

    bool is_ram = false;
    bool is_num = false;
    bool is_reg = false;
    bool is_arg = false;
    bool is_jmp = false;

    cmd_type cmd_num = 0;
    cmd_type reg_num = 0;
    cmd_type num = 0;

    for(size_t i = 0; i < program_len;)
    {
        is_ram = code[i] & RAM_BIT;
        is_reg = code[i] & REG_BIT;
        is_num = code[i] & NUM_BIT;
        cmd_num = code[i++] & CMD_MASK;
        is_arg = false;
        is_jmp = false;

        if(is_reg)
        {
            reg_num = code[i++];
        }
        if(is_num)
        {
            num = code[i++];
        }               

        if(false) {}
        #include "defines/commands.h"

        if(is_jmp)
        {
            printf(" %ld", code[i++]);
        }  

        if(is_arg)
        {
            printf(" ");
            if(is_ram)
            {
                printf("[");
            }   
            if(is_reg)
            {
                if(false) {}
                #include "defines/regs.h"
            }
            if(is_num)
            {
                printf("%ld", num);
            }
            if(is_ram)
            {
                printf("]");
            }   
        }

        printf("\n");
    }
}