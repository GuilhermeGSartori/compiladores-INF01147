enum lex_type {
    LEX_LIT_INT, 
    LEX_LIT_FLOAT, 
    LEX_LIT_BOOL, 
    LEX_IDENTIFICADOR
};

typedef struct LexType {
    int line;
    //enum lex_type type;
    enum lex_type type;
    char* value;
} LexType;

LexType* createLexType(int line, enum data_type type, char* value);
