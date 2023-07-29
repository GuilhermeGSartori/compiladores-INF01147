#include "table_content.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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
    //printf("will copy value \"%s\"!\n", lexeme_value);
    if(lexeme_value == NULL) {
        strcpy(table_line->value, "0");
        //table_line->value = NULL; // confirmar se deixo em NULL ou zero
    }
    else
        strcpy(table_line->value, lexeme_value);
    //printf("copied value!\n");
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

void addKeyInList(char* name, KeyList** list, int type, char* value) {

    KeyList* new_item = (KeyList*)malloc(sizeof(KeyList));
    SymbolKey* key = mallocAndSetKeyName(name);
    strcpy(new_item->key.key_name, key->key_name);
    new_item->next = NULL;
    new_item->type = type;
    if(value != NULL)
        strcpy(new_item->value, value);
    else {
        strcpy(new_item->value, "0");
        //new_item->value = NULL;
    }
    //printf("Criei item novo para lista!\n");

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

void checkParameters(KeyList* parameters, KeyList* list) {

    int list_count = 0;
    int param_count = 0;
    KeyList* heritage = NULL;

    KeyList* it = list;

    while(it != NULL) {
        printf("OG LIST: %s\n", it->key.key_name);
        it = it->next;
    }

    /*while(list != NULL) {
        KeyList* next = list->next;
        if(next == NULL) {
            list->next = heritage;
            break;
        }
        else if(next->next != NULL) {
            KeyList* save_prev_next = next->next;
            //next->next = list;            
            next->next = list;
            KeyList* prev_list = list;
            list = save_prev_next;
            //list->next = next;
            prev_list->next = heritage;
            heritage = next;

        }
        else {
            list->next = heritage;
            heritage = list;
            //heritage = list;
            //KeyList* prev_list = list;
            list = next;
            //prev_list->next = heritage;
        }
    }*/
    
    it = list;
    while(it != NULL) {
        printf("NEW LIST: %s\n", it->key.key_name);
        it = it->next;
        list_count++;
    }
    it = parameters;
    while(it != NULL) {
        it = it->next;
        param_count++;
    }

    if(param_count == list_count) {
        while(list != NULL) {
            if(parameters->type != list->type)
                printf("Wront type passed as parameter!\n");
            list = list->next;
            parameters = parameters->next;
        }
    }
    else {
        printf("Wrong number of parameters\n");        
    }

}
