#include "stack_functions.h" 

stack_t *stack_new()
{
    stack_t *stack = (stack_t*)calloc(1, sizeof(stack_t));

    if(stack == nullptr)
    {
        stack->error = failed_to_create_stack;
    }

    return stack;
}

void stack_push(stack_t *stack, STACK_TYPE num)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    if(stack->capacity == 0)
    {
        stack->capacity = 1; 
        stack->data = (STACK_TYPE*)calloc(3, sizeof(STACK_TYPE));

        if(stack->data == nullptr)
        {
            stack->error = failed_to_increase_stack;
        }

        stack->data[0] = DETECTOR;
        stack->data[1] = DETECTOR;
    }  


    stack_check(stack);


    if(stack->size == stack->capacity) 
    {
        stack->capacity = stack->capacity * 2;  
        stack->data = (STACK_TYPE*)realloc(stack->data, (stack->capacity + 2) * sizeof(STACK_TYPE));
        
        if(stack->data == nullptr)
        {
            stack->error = failed_to_increase_stack;
        }  
    }

    stack->size++;

    stack->data[stack->size] = num;
    stack->data[stack->size + 1] = DETECTOR;

    stack->hash += get_hash((HASH_TYPE) stack->data[stack->size]);

    stack_dump(stack, __FUNCTION__, __LINE__);
}

STACK_TYPE stack_pop(stack_t *stack)
{
    stack_check(stack);

    STACK_TYPE temp = 0;
    
    if(stack->size <= stack->capacity / 4)
    {
        stack->capacity = stack->capacity / 2;
        stack->data = (STACK_TYPE*)realloc(stack->data, (stack->capacity + 2) * sizeof(STACK_TYPE));
        
        if(stack->data == nullptr)
        {
            stack->error = failed_to_decrease_stack;
        }
    }

    temp = stack->data[stack->size];

    stack->data[stack->size] = DETECTOR;
    stack->data[stack->size + 1] = POISON;   

    stack->size--;

    stack_dump(stack, __FUNCTION__, __LINE__);

    stack->hash -= get_hash((HASH_TYPE) temp);

    stack_dump(stack, __FUNCTION__, __LINE__);

    return temp;
}

void stack_dump(stack_t *stack, const char *func_name, int line) 
{
    fprintf(stack->log_file, "In func %s, line %d\nsize = %zu, capacity = %zu\n", func_name, line, stack->size, stack->capacity);

    if(stack->data != nullptr)
    {
        for(size_t i = 0; i < stack->size + 2; i++)
        {
            fprintf(stack->log_file, "%d ", stack->data[i]);
        }
        fprintf(stack->log_file, "\nhash = %zu ", stack->hash);
        fprintf(stack->log_file, "get_data_hash = %zu ", get_data_hash(stack));
        fprintf(stack->log_file, "get_hash = %zu (%d)\n\n", get_hash(stack->data[stack->size]), stack->data[stack->size]);
    }
    else 
    {
        fprintf(stack->log_file, "\ndata = nullptr\n\n");
    }

}

void stack_check(stack_t *stack)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    if(stack->data[0] != DETECTOR || stack->data[stack->size + 1] != DETECTOR)
    {
        stack->error = stack_is_side_damaged;
    }

    if(stack->size < 0 || stack->size > stack->capacity)
    {
        stack->error = stack_unreal_size;
    }

    if(stack->hash != get_data_hash(stack))
    {
        stack->error = stack_wrong_hash;
    }
}

HASH_TYPE get_data_hash(stack_t *stack) 
{
    HASH_TYPE hash = 0;

    for(size_t i = 1; i < stack->size + 1; i++)
    {
        for(size_t j = 0; j < 8 * sizeof(HASH_TYPE); j++)
        {
            hash += (((HASH_TYPE)stack->data[i] & (1 << j)) >> j);
        }
    }
    
    return hash;
}

HASH_TYPE get_hash(HASH_TYPE num)
{
    HASH_TYPE hash = 0;

    for(size_t i = 0; i < 8  * sizeof(HASH_TYPE); i++)
    {
        hash += (num & (1 << i)) >> i;
    }

    return hash;
}

void stack_del(stack_t *stack)
{
    stack_dump(stack, __FUNCTION__, __LINE__);

    for(size_t i = 0; i < stack->size + 2; i++)
    {
        stack->data[i] = POISON;
    }

    free(stack->data);
    free(stack->log_file);
    free(stack);
}

/** что нужно сделать:
 * в начале и в конце даты канарейка и проверять не тронули ли их DETECTOR
 * в удалении заливать нелогичные значения
 * calloc вместо malloc
 * проверять всё
 * динамическое изменение размера
 * логи
 * удалять сам стэк и его дату
 * HASH
 * 
 */
