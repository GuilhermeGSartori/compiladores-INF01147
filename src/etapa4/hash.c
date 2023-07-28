#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Function to create a new hash table (Scope)
Scope* createTable(Scope* current) {
    Scope* table = (Scope*)malloc(sizeof(Scope));
    
    if(current == NULL) {
        // creates global scope
        table->height = 0;
        table->previous_scope = NULL;
        printf("Criei a global\n");
    }
    else {
        table->previous_scope = (Scope*)malloc(sizeof(Scope));
        table->height = current->height + 1;
        table->previous_scope = current;
    }

    table->size = TABLE_SIZE;
    table->count = 0;
    table->lexemes = malloc(TABLE_SIZE * sizeof(HashItem));

    for(int i=0; i<TABLE_SIZE; i++)
        table->lexemes[i] = NULL;

    //table->parameters = NULL;

    printf("Consegui alocar uma nova tabela\n");

    return table;
}

// Function to create a new HashItem and initialize it
HashItem* createHashItem(TableContent* content) {
    HashItem* item = (HashItem*)malloc(sizeof(HashItem));
    item->hash_content = content;
    item->next = NULL;
    return item;
}

// Function to calculate the hash index using a simple hash function
int hashFunction(SymbolKey* key) {

    int sum_of_chars = 0;
    for(int i=0; i<strlen(key->key_name); i++) { // esse loop aqui consome mto recurso?
        sum_of_chars += (int)key->key_name[i];
        printf("Teste: %d\n", sum_of_chars);
    }
    return sum_of_chars % TABLE_SIZE;
    
}

// Function to insert an element into the hash table
void addInTable(TableContent* content, Scope* table) {

    int index = hashFunction(content->key);

    printf("Index: %d\n", index);
    HashItem* current = table->lexemes[index];

    // hash nao da a volta
    while (current != NULL) {
        if (strcmp(getKeyName(current->hash_content), getKeyName(content)) == 0) {
            printf("Symbol was already declared!\n");
            exit(ERR_DECLARED);
        }
        current = current->next;
    }

    scanf("%d", &index);
    printf("Achei um espaço\n");

    // Create a new HashItem and add it to the linked list
    HashItem* new_item = createHashItem(content);

    new_item->next = table->lexemes[index];
    table->lexemes[index] = new_item;
    table->count++;

    int counter = 0;
    HashItem* it = table->lexemes[index];
    while(it != NULL) {
        counter++;
        printf("counter: %d\n", counter);
        it = it->next;
    }

}


// Function to find an element in the hash table
TableContent* findInTable(SymbolKey* key, Scope* table) {
    int index = hashFunction(key);

    // Traverse the linked list at the calculated index (separate chaining)
    HashItem* current = table->lexemes[index];
    while (current != NULL) {
        if (strcmp(getKeyName(current->hash_content), key->key_name) == 0) {
            return current->hash_content; // Element found, return its content
        }
        current = current->next;
    }

    return NULL; // Element not found
}

void assertContentIsID(int nature) {
    if(nature != ID_SYMBOL && nature == FUN_SYMBOL) {
        printf("Used function symbol as a identifier!\n");
        exit(ERR_VARIABLE); // CONFIRMAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    }
}

void assertContentIsFUN(int nature) {
    if(nature != FUN_SYMBOL && nature == ID_SYMBOL) {
        printf("Used identifier symbol as a function!\n");
        exit(ERR_FUNCTION); // CONFIRMAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    }
}

TableContent* findInTableStack(SymbolKey* key, Scope* stack_top, int nature) {

    Scope* stack_run = stack_top;

    TableContent* content = NULL;

    int count = 0;

    while(stack_run != NULL && content == NULL) {
        content = findInTable(key, stack_run);
        if(content != NULL) {
            printf("Jumped %d scopes!\n", count);
            if(nature == ID_SYMBOL)
                assertContentIsID(content->nature);
            else if(nature == FUN_SYMBOL)
                assertContentIsFUN(content->nature);
            return content;
        }
        count++;
        stack_run = stack_run->previous_scope;
    }

    printf("Symbol was NOT declared!\n");
    exit(ERR_UNDECLARED);
     
}   // vai descendo a stack de hash tables

void addParameterInList(int type, ParameterList** list) {

    ParameterList* new_item = (ParameterList*)malloc(sizeof(ParameterList));
    new_item->type = type;
    new_item->next = NULL;

    if(*list == NULL) {
        printf("aaa\n");
        *list = new_item;
    }

    else {
        printf("bbb\n");
        ParameterList* current = *list;
        while(current->next != NULL) {
            printf("current: %d\n", current->type);
            current = current->next;
        }
        current->next = new_item;
    }

}

void invalidSemanticOperation() {
    printf("Invalid semantic operation!\n");
}