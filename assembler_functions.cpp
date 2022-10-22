#include "assembler_functions.h"

void devide_in_lines(ass_prog_t *ass_prog)
{
    fseek(ass_prog->prog_file, 0l, SEEK_END);
    ass_prog->prog_size = ftell(ass_prog->prog_file) + 1;
    fseek(ass_prog->prog_file, 0l, SEEK_SET);

    ass_prog->prog_text = (char*)calloc(ass_prog->prog_size, 1);
    fread(ass_prog->prog_text, sizeof(char), ass_prog->prog_size, ass_prog->prog_file);

    ass_prog->prog_lines_size = 1;

    for(size_t i = 0; i < ass_prog->prog_size; i++)
    {
        if(isupper(ass_prog->prog_text[i]))
        {
            ass_prog->prog_text[i] += 32;
        }
        else if(ass_prog->prog_text[i] == '\n') 
        {
            ass_prog->prog_lines_size++;
            ass_prog->prog_text[i] = 0;
        }
        else if(ass_prog->prog_text[i] == '\r')
        {
            ass_prog->prog_text[i] = 0;
        }
    }

    // printf("size %zu lines %zu\n", ass_prog->prog_size, ass_prog->prog_lines_size);

    ass_prog->prog_lines = (char**)calloc(ass_prog->prog_lines_size, sizeof(char*));

    for(size_t i = 0, cur_ch = 0; i < ass_prog->prog_lines_size; i++)
    {
        ass_prog->prog_lines[i] = &ass_prog->prog_text[cur_ch];    
        
        while(ass_prog->prog_text[cur_ch] != 0)
        {
            cur_ch++;
        }

        while(ass_prog->prog_text[cur_ch] == 0)
        {
            cur_ch++;
        }
    }

    for(size_t i = 0; i < ass_prog->prog_size; i++)
    {
        if(ass_prog->prog_text[i] == ';') 
        {
            ass_prog->prog_text[i] = 0;
        }
    }
} 

ass_registers get_reg_num(const char *reg)
{
    // printf("get reg num called\n");

    ass_registers reg_num;

    if(false) {}
    #include "defines/regs.h"

    return reg_num;
}

void compile_args(size_t *i, ass_prog_t *ass_prog, char *line, bool is_jump)
{
    // printf("compile args called\n");

    cut_first_word(line);    
    delete_spaces (line);

    if(!is_jump)
    {
        cmd_type arg_num = 0;
        cmd_type arg_reg_num = 0;
        char arg_reg_name[3] = {0};

        bool is_arg_num = false;
        bool is_arg_reg = false;
        bool is_arg_ram = false;

        if(false) {}
        #include "defines/args.h"

        // printf("cmp args copypast passed\n");

        size_t cmd_i = (*i) - 1;

        if(is_arg_ram)
        {
            ass_prog->code[cmd_i] += RAM_BIT;
        }
        if(is_arg_reg)
        {
            ass_prog->code[cmd_i] += REG_BIT;
            ass_prog->code[(*i)++] = get_reg_num(arg_reg_name);
        }    
        if(is_arg_num)
        {
            ass_prog->code[cmd_i] += NUM_BIT;
            ass_prog->code[(*i)++] = arg_num;
        }
    }
    else
    {
        ass_prog->code[(*i)] = 0;

        bool flag_founded = false;

        for(size_t j = 0; j < MAX_FLAG_NUM; j++)
        {
            if(str_cmpr(&ass_prog->flag_names[MAX_FLAG_NAME_SIZE * j], line))
            {
                ass_prog->code[(*i)] = ass_prog->flags[j];
                flag_founded = true;
            }
        }

        if(!flag_founded)
        {
            ass_prog->error = flag_not_found;
        }

        (*i)++;
    }
}

void compile(ass_prog_t *ass_prog)
{    
    size_t flag_num = 0;

    size_t colon = 0;

    for(size_t n = 0, i = 0; n < ass_prog->prog_lines_size; n++)
    {
        colon = (size_t)str_chr(ass_prog->prog_lines[n], ':');
        if(colon > 0) 
        {
            colon -= (size_t)ass_prog->prog_lines[n];
            for(size_t j = 0; j < colon; j++)
            {
                ass_prog->flag_names[flag_num * MAX_FLAG_NAME_SIZE + j] =  ass_prog->prog_lines[n][j];
            }
            ass_prog->flags[flag_num++] = i;
            continue;
        }

        if(false) {}
        #include "defines/commands.h"
    }

    // for(size_t i = 0; i < flag_num; i++)
    // {
    //     printf("%s\n", &ass_prog->flag_names[i * MAX_FLAG_NAME_SIZE]);
    // }
}