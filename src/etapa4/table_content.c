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

TableContent* newContent(SymbolKey* key, char* lexeme_value, int line, enum symbol_nature nat, enum semantic_type type) {
    TableContent* table_line = (TableContent*)malloc(sizeof(TableContent));
    
    table_line->key = (SymbolKey*)malloc(sizeof(SymbolKey));

    strcpy(table_line->key->key_name, key->key_name);
    strcpy(table_line->value, lexeme_value);
    table_line->line = line;
    table_line->nature = nat;
    table_line->type = type;

    table_line->parameters = NULL;

    return table_line;
}


void updateContent(TableContent* line, char* lexeme_value, int line_num, enum semantic_type type) {
    
    if(line->line != line_num)
        line->line = line_num;
    
    if(strcmp(line->value, lexeme_value) == 1)
        strcpy(line->value, lexeme_value);

    if(line->type != type)
        line->type = type;

}


void updateContentType(TableContent* line, enum semantic_type type) {
    line->type = type;
}


void setParametersList(TableContent* content, KeyList* list) {
    if(list != NULL) {
        content->parameters = list;
    }
}

void addKeyInList(char* name, KeyList** list, int type) {

    KeyList* new_item = (KeyList*)malloc(sizeof(KeyList));
    SymbolKey* key = mallocAndSetKeyName(name);
    strcpy(new_item->key.key_name, key->key_name);
    new_item->next = NULL;
    new_item->type - type;

    if(*list == NULL) {
        //printf("aaa\n");
        *list = new_item;
    }

    else {
        //printf("bbb\n");
        KeyList* current = *list;
        while(current->next != NULL) {
            //printf("current: %d\n", current->type);
            current = current->next;
        }
        current->next = new_item;
    }
}
