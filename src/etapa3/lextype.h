enum lex_type {
    LEX_LIT_INT, 
    LEX_LIT_FLOAT, 
    LEX_LIT_BOOL, 
    LEX_ID
};

typedef struct LexType {
    int line;
    enum lex_type type;
    //char* value;
    char value[20]; // Valor de um literal/nome Id no maximo 20 char
} LexType;

LexType* createLexType(int line, int type, char* value);
