#define CMD_MAX_SIZE 2048

enum cmd_type {
    MOST_LEFT,
    MOST_RIGHT,
    CONTROL,
    CBR,
    JUMP,
    RETURN
};

typedef struct CmdILOC { 
    char cmd[CMD_MAX_SIZE]; 
    //struct CmdILOC* next;
} CmdILOC;

CmdILOC* createCmd(char* command, char* register1, char* register2, char* register3, enum cmd_type type);

CmdILOC* concatCode(CmdILOC* code1, CmdILOC* code2);

CmdILOC* concatCodeToString(CmdILOC * code1, char* strng);

//void cmdToList(CmdILOC** list, CmdILOC* command);

CmdILOC* mallocAndSetCmdILOC(char* value);