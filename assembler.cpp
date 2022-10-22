#include "assembler_functions.h"

int main()
{
    ass_prog_t ass_prog;
    ass_prog.prog_file = fopen("program.ass", "r");
    ass_prog.log_file = fopen("log_file.txt", "w");

    FILE *prog_compiled = fopen("compiled.ass", "wb");

    devide_in_lines(&ass_prog);

    size_t max_elem_count = ass_prog.prog_lines_size * (MAX_ARG_NUM + 1) + 1;
    ass_prog.code = (cmd_type*)calloc(max_elem_count, sizeof(cmd_type));
    
    compile(&ass_prog);

    devide_in_lines(&ass_prog);
    compile(&ass_prog);

    for(size_t i = 0; i < max_elem_count; i++)
    {
        printf("%02X ", (int)(unsigned char)(ass_prog.code[i]));
        // fprintf(prog_compiled, "%02X ", (int)(unsigned char)(ass_prog.code[i]));
    }
    fwrite(ass_prog.code, sizeof(cmd_type), max_elem_count, prog_compiled);

    free(ass_prog.code);
    free(ass_prog.prog_lines);
    free(ass_prog.prog_text);

    return 0;
}