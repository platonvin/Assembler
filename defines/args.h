#define COMMA ,
// _ARG_DEF_(2, %d+%3s, &arg_num COMMA &arg_reg_name,  0, 1, 1)
_ARG_DEF_(2, %3s%d, &arg_reg_name COMMA &arg_num,  0, 1, 1)
// _ARG_DEF_(2, [%d+%3s], &arg_num COMMA &arg_reg_name,  1, 1, 1)
// _ARG_DEF_(2, [%3s%d], &arg_reg_name COMMA &arg_num,  1, 1, 1)
// _ARG_DEF_(1, %d, &arg_num, 0, 0, 1)
// _ARG_DEF_(1, [%d], &arg_num, 1, 0, 1)
// _ARG_DEF_(1, %3s, &arg_reg_name, 0, 1, 0)
// _ARG_DEF_(1, [%3s], &arg_reg_name, 1, 1, 0)