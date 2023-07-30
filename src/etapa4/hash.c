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


    return table;
}

Scope* popTable(Scope* stack_top) {
    for(int i=0; i<TABLE_SIZE;i++) {
        HashItem* item = stack_top->lexemes[i];
        while(item != NULL) {
            free(item->hash_content->key);
            KeyList* parameters = item->hash_content->parameters;
            while(parameters != NULL) {
                KeyList* prev = parameters;
                parameters = parameters->next;
                free(prev);
            }
            free(item->hash_content);
            HashItem* prev = item;
            item = item->next;
            free(prev);
        }
    }
    Scope* new_top = stack_top->previous_scope;
    free(stack_top);
    return new_top; 
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
    }
    return sum_of_chars % TABLE_SIZE;
    
}

// Function to insert an element into the hash table
void addInTable(TableContent* content, Scope* table, int line) {

    int index = hashFunction(content->key);

    HashItem* current = table->lexemes[index];

    // hash nao da a volta
    while (current != NULL) {//se são iguais e for ID ou Função, lança o erro
        if ((strcmp(getKeyName(current->hash_content), getKeyName(content)) == 0) && (content->nature != LIT_SYMBOL)) {
            printf("Semantic Error in Line %d: Symbol \"%s\" was declared in line %d!\n", line, getKeyName(content), current->hash_content->line);
            exit(ERR_DECLARED);
        } else if ((strcmp(getKeyName(current->hash_content), getKeyName(content)) == 0) && (content->nature == LIT_SYMBOL)) {//se são iguais, mas é literal, apenas retorna, não insere novamente e não lança erro
			return;
		}
        current = current->next;
    }


    // Create a new HashItem and add it to the linked list
    HashItem* new_item = createHashItem(content);// se ainda não existir na tabela, adiciona, independente da natureza
    new_item->next = table->lexemes[index];
    table->lexemes[index] = new_item;
    table->count++;

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

void assertContentIsID(int nature, int line) {
    if(nature != ID_SYMBOL && nature == FUN_SYMBOL) {
        printf("Used function symbol as a variable in line %d!\n", line);
        exit(ERR_FUNCTION); // CONFIRMAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    }
}

void assertContentIsFUN(int nature, int line) {
    if(nature != FUN_SYMBOL && nature == ID_SYMBOL) {
        printf("Used variable symbol as a function in line %d!\n", line);
        exit(ERR_VARIABLE); // CONFIRMAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    }
}

TableContent* findInTableStack(SymbolKey* key, Scope* stack_top, int nature, int line) {

    Scope* stack_run = stack_top;

    TableContent* content = NULL;

    int count = 0;

    while(stack_run != NULL && content == NULL) {
        content = findInTable(key, stack_run);
        if(content != NULL) {
            printf("Jumped %d scopes and found \"%s\"!\n", count, content->key->key_name);
            if(nature == ID_SYMBOL)
                assertContentIsID(content->nature, line);
            else if(nature == FUN_SYMBOL)
                assertContentIsFUN(content->nature, line);
            return content;
        }
        count++;
        stack_run = stack_run->previous_scope;
    }

    printf("Symbol \"%s\", used in line %d was NOT declared!\n", key->key_name, line);
    exit(ERR_UNDECLARED);
     
}   // vai descendo a stack de hash tables


void invalidSemanticOperation() {
    printf("Invalid semantic operation!\n");
}