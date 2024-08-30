#ifndef STACK_FUNCTIONS_H
#define STACK_FUNCTIONS_H

#include <stdbool.h>
#define POISON 13
#define DETECTOR 69666420

typedef long STACK_TYPE;
typedef unsigned int HASH_TYPE;

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

enum errors_t
{
    no_errors = 0,
    failed_to_create_stack   = -1,
    failed_to_increase_stack = 1,
    failed_to_decrease_stack = 2,
    stack_is_side_damaged = DETECTOR,
    stack_unreal_size = -2,
    stack_wrong_hash = (1000 - 7),
};

typedef struct stack_t
{
    STACK_TYPE *data;
    size_t size;
    size_t capacity;
    FILE *log_file;
    bool should_log;

    HASH_TYPE hash; 

    enum errors_t error; 
} stack_t;

/**
 * creates a new stack
 * 
 * @return A pointer to a new stack.
 */
stack_t *stack_new();

/**
 * If the stack is empty, allocate memory for it. If the stack is full, double its size. Then pushes the
 * number into the stack
 * 
 * @param stack pointer to the stack
 * @param num the number to be pushed
 */
void stack_push(stack_t *stack, STACK_TYPE num);

/**
 * checks the stack, decreases the capacity if too much, pops the last element, decreases the size,
 * checks the hash, and returns the popped element
 * 
 * @param stack pointer to the stack
 * 
 * @return The value of the element that was deleted from the stack.
 */
STACK_TYPE stack_pop(stack_t *stack);

/**
 * It prints the stack's size, capacity, data, hash, and the hash of the last element in the stack into stack logfile
 * 
 * @param stack pointer to the stack
 * @param func_name the name of the function where the dump is called, __FUNCTION__
 * @param line the line number in the file where the function was called __LINE__
 */
void stack_dump(stack_t *stack, const char *file_name, int line);

/**
 * checks the stack for errors
 * 
 * @param stack pointer to the stack
 */
void stack_check(stack_t *stack);

/**
 * > The function takes a stack and returns a hash value based on the data in the stack
 * 
 * @param stack The stack to get the hash of.
 * 
 * @return The hash of the data in the stack.
 */
HASH_TYPE get_data_hash(stack_t *stack);

/**
 * It takes a number and returns the number (sum) of bits that are set to 1 in that number
 * 
 * @param num The number to hash.
 * 
 * @return The number of bits set to 1 in the input number.
 */
HASH_TYPE get_hash(HASH_TYPE num);

/**
 * deletes the stack and its data
 * 
 * @param stack pointer to the stack
 */
void stack_del(stack_t *stack);

#endif //STACK_FUNCTIONS_H