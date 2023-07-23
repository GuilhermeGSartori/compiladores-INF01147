#include "table_content.h"
#include <stdlib.h>
#include <string.h>

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