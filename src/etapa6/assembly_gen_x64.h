#include "hash.h"


#define REGS_N 11


enum exp_cmd_type {
    CMD_EQ,
    CMD_NE,
    CMD_ARITH,
    CMD_LE,
    CMD_GE,
    CMD_LT,
    CMD_GT,
    CMD_UNDEFINED
};

void generateAsm();
void translateCode(char* line);
char* searchOffset(int offset);