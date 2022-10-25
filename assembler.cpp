#include "assembler_functions.h"

int main()
{
    ass_prog_t ass_prog;

    printf("file to compile?\n\n");
    char program_name[256] = {0};
    scanf("%s", program_name);

    ass_prog.prog_file = fopen(program_name, "w");
    ass_prog.log_file = fopen("log_file.txt", "w");

    str_CAT(program_name, ".compiled");

    FILE *prog_compiled = fopen(program_name, "wb");

    devide_in_lines(&ass_prog);

        size_t max_elem_count = ass_prog.prog_lines_size * (MAX_ARG_NUM + 1) + 1;
        ass_prog.code = (cmd_type*)calloc(max_elem_count, sizeof(cmd_type));
    
    compile(&ass_prog);

    ass_prog.error = no_errors;

    devide_in_lines(&ass_prog);
    compile(&ass_prog);

    if(ass_prog.error != no_errors)
    {
        printf("ERROR = %d\n", ass_prog.error);
    }

    for(size_t i = 0; i < max_elem_count; i++)
    {
        printf("%08X ", (long int)(ass_prog.code[i]));
        // fprintf(prog_compiled, "%02X ", (int)(unsigned char)(ass_prog.code[i]));
    }
    fwrite(ass_prog.code, sizeof(cmd_type), max_elem_count, prog_compiled);

    free(ass_prog.code);
    free(ass_prog.prog_lines);
    free(ass_prog.prog_text);

    return 0;
}