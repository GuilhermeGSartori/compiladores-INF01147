#include "lextype.h"

LexType* createLexType(int line, enum data_type type, char* value) {

    LexType *new_lex_value;
    new_lex_value = calloc(1, sizeof(*LexType));
    
    new_lex_value->line = line;
    new_lex_value->type = type;
    strcpy(new_lex_value->value, value);

    return new_lex_value;
}

