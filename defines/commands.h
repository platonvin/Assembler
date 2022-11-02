_CMD_DEF_(hlt, 0x00, 0, 0,
printf("EXIT\n"); exit(0);
)
_CMD_DEF_(push, 0x01, 1, 0,
    if(is_reg) 
    {
        t1 += reg[code[i++]];
    }
    if(is_num) 
    {
        t1 += code[i++];
    }

    if(is_ram)
    {
        stack_push(stack, ram[t1]);
    }
    else
    {
        stack_push(stack, t1);
    }
)
_CMD_DEF_(pop, 0x02, 1, 0,
    if(is_ram)
    {
        if(is_reg) 
        {
            t1 += reg[code[i++]];
        }
        if(is_num)
        {
            t1 += code[i++];
        }
        ram[t1] = stack_pop(stack);
    }
    else
    {
        if(is_reg) 
        {
            reg[code[i++]] = stack_pop(stack);
        }
        else
        {
            stack_pop(stack);
            i++;
        }
    }
)
_CMD_DEF_(add, 0x03, 0, 0,
    t1 += stack_pop(stack);
    t1 += stack_pop(stack);
    stack_push(stack, t1);
)
_CMD_DEF_(sub, 0x04, 0, 0,
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    stack_push(stack, t1 - t2);
)
_CMD_DEF_(imul, 0x05, 0, 0, 
    t1 = stack_pop(stack);
    t1 *= stack_pop(stack);
    stack_push(stack, t1);
)
_CMD_DEF_(mul, 0x06, 0, 0,
    t1 = stack_pop(stack);
    t1 *= stack_pop(stack);
    if(t1 < 0)
    {
        t1 *= -1;
    }
    stack_push(stack, t1);
)
_CMD_DEF_(idiv, 0x07, 0, 0,
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    stack_push(stack, t1 / t2);
)
_CMD_DEF_(div, 0x08, 0, 0,
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    t1 /= t2;
    if(t1 < 0)
    {
        t1 = -t1;
    }
    stack_push(stack, t1);
)
_CMD_DEF_(out, 0x09, 0, 0,
    t1 = stack_pop(stack);
    printf("%ld\n", t1);
)
_CMD_DEF_(in, 0x0a, 0, 0,
    scanf("%ld", &t1);                
    stack_push(stack, t1);
)
_CMD_DEF_(jb, 0x0b, 1, 1, 
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    if(t1 < t2) 
    {
        i = code[i];
    }
    else
    {
        i++;
    }
)
_CMD_DEF_(jbe, 0x0c, 1, 1, 
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    if(t1 <= t2) 
    {
        i = code[i];
    }
    else
    {
        i++;
    }
)
_CMD_DEF_(ja, 0x0d, 1, 1, 
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    if(t1 > t2) 
    {
        i = code[i];
    }
    else
    {
        i++;
    }
)
_CMD_DEF_(jae, 0x0e, 1, 1, 
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    if(t1 >= t2) 
    {
        i = code[i];
    }
    else
    {
        i++;
    }
)
_CMD_DEF_(je, 0x0f, 1, 1, 
    t2 = stack_pop(stack);  
    t1 = stack_pop(stack);
    if(t1 == t2) 
    {
        i = code[i];
    }
    else
    {
        i++;
    }
)
_CMD_DEF_(jne, 0x10, 1, 1, 
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    if(t1 != t2) 
    {
        i = code[i];
    }
    else
    {
        i++;
    }
)
_CMD_DEF_(jmp, 0x11, 1, 1, 
    i = code[i++];
)
_CMD_DEF_(neg, 0x12, 0, 0, 
    stack_push(stack, -stack_pop(stack));
)
_CMD_DEF_(sqrt, 0x13, 0, 0, 
    stack_push(stack, sqrt(stack_pop(stack)));
)
_CMD_DEF_(dup, 0x14, 0, 0, 
    t1 = stack_pop(stack);
    stack_push(stack, t1);
    stack_push(stack, t1);
)
_CMD_DEF_(vpop, 0x15, 0, 0,
    t2 = stack_pop(stack);
    t1 = stack_pop(stack);
    vram[t1] = t2;
)
_CMD_DEF_(vfl, 0x16, 0, 0,
    for(size_t i = 0; (vram[i] != 0) && (i < MAX_VRAM); i++)
    {
        putchar(vram[i]);
        vram[i] = 0;
    }
)