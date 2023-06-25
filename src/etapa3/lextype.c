#include "lextype.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

LexType* createLexType(int line, int type, char* value) {

    //printf("Vou alocar lex type\n");

    LexType *new_lex_value;
    new_lex_value = (LexType*) calloc(1, sizeof(LexType));
    
    //printf("Aloquei lex type\n");

    new_lex_value->line = line;
    //printf("Setei linha\n");
    new_lex_value->type = type;
    //printf("Setei type\n");
    //char dummy[20];
    strcpy(new_lex_value->value, value);
    //strcpy(dummy, value);
    //printf("Setei valor\n");

    //printf("Setei atributos\n");

    return new_lex_value;
}

