#define CMD_MAX_SIZE 32

enum cmd_type {
    MOST_LEFT,
    MOST_RIGHT,
    CONTROL
};

typedef struct CmdILOC { char cmd[CMD_MAX_SIZE]; } CmdILOC;

CmdILOC* createCmd(char* ILOC_CMD, char* register1, char* register2, char* register3, enum cmd_type type);