#ifndef ASSEMBLER_FUNCTIONS_H
#define ASSEMBLER_FUNCTIONS_H

#include <stdio.h>
#include <malloc.h>
#include "string_funcs.h"

typedef long cmd_type;

#define RAM_BIT 0x80000000
#define REG_BIT 0x40000000
#define NUM_BIT 0x20000000

#define MAX_ARG_NUM 2
#define MAX_FLAG_NUM 64
#define MAX_FLAG_NAME_SIZE 16

#define _ARG_DEF_(arg_num, format, args, is_ram, is_reg, is_num) \
else if(sscanf(line, #format, args) == arg_num)\
{\
    is_arg_num = is_num;\
    is_arg_reg = is_reg;\
    is_arg_ram = is_ram;\
}

#define _CMD_DEF_(name, num, is_arg, is_jump, ...) \
else if(str_cmpr(#name, ass_prog->prog_lines[n]))\
{\
    ass_prog->code[i++] = num;\
    if(is_arg)\
    {\
        compile_args(&i, ass_prog, ass_prog->prog_lines[n], is_jump);\
    }\
}

#define _REG_DEF_(reg_name, reg_num) \
    reg_name = reg_num,

enum ass_registers
{
    #include "defines/regs.h"
};

#undef _REG_DEF_

#define _REG_DEF_(reg_name, ...) \
else if(str_cmpr(reg, #reg_name))\
{\
    reg_num = reg_name;\
}

enum ass_errors
{
    flag_not_found = 1,
};

struct ass_prog_t
{
    FILE *prog_file;

    char *prog_text;
    char **prog_lines;
    size_t prog_size;
    size_t prog_lines_size;

    cmd_type *code;

    char flag_names[(MAX_FLAG_NAME_SIZE + 1) * MAX_FLAG_NUM] = {0};
    size_t flags[MAX_FLAG_NUM]= {0};
    size_t flag_num = 0;

    ass_errors error;
    FILE *log_file;
};


// ass_prog_t new_ass_prog();

void devide_in_lines(ass_prog_t *ass_prog);

ass_registers get_reg_num(const char *reg);

void compile_args(size_t *i, ass_prog_t *ass_prog, char *line, bool is_jump);

void compile(ass_prog_t *ass_prog);

cmd_type get_cmd_num(char *line);

#endif //ASSEMBLER_FUNCTIONS_H