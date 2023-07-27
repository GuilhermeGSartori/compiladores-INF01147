#include "table_content.h"
#include <stdlib.h>
#include <string.h>


SymbolKey* mallocAndSetKeyName(char* value) {
    SymbolKey* key = malloc(sizeof(SymbolKey));
    strcpy(key->key_name, value);
    return key;
}

void setKeyName(SymbolKey* key, char* value) {
    strcpy(key->key_name, value);
}

char* getKeyName(TableContent* line) {
    return line->key->key_name;
}

TableContent* newContent(SymbolKey* key, char* lexeme_value, int line, enum symbol_nature nat, enum lex_type type) {
    TableContent* table_line = (TableContent*)malloc(sizeof(TableContent));
    
    table_line->key = (SymbolKey*)malloc(sizeof(SymbolKey));

    strcpy(table_line->key->key_name, key->key_name);
    strcpy(table_line->value, lexeme_value);
    table_line->line = line;
    table_line->nature = nat;
    table_line->type = type;
    

    return table_line;
}


void updateContent(TableContent* line, char* lexeme_value, int line_num, enum lex_type type) {
    
    if(line->line != line_num)
        line->line = line_num;
    
    if(strcmp(line->value, lexeme_value) == 1)
        strcpy(line->value, lexeme_value);

    if(line->type != type)
        line->type = type;

}
