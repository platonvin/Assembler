#ifndef PROCESSOR_FUNCTIONS_H
#define PROCESSOR_FUNCTIONS_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef long cmd_type;

#define _CMD_DEF_(name, num, is_arg, is_jump, ...) \
else if(cmd_num == num)\
{\
    __VA_ARGS__\
}

#define CMD_MASK 0x1FFFFFFF
#define RAM_BIT 0x80000000
#define REG_BIT 0x40000000
#define NUM_BIT 0x20000000

#define MAX_RAM 256
#define MAX_REG 8

#endif //PROCESSOR_FUNCTIONS_H