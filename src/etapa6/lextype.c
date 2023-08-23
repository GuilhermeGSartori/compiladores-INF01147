#include "lextype.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

LexType* createLexType(int line, int type, char* value) {


    LexType *new_lex_value;
    new_lex_value = (LexType*) calloc(1, sizeof(LexType));

    new_lex_value->line = line;
    new_lex_value->type = type;
    strcpy(new_lex_value->value, value);

    return new_lex_value;
}

