#include <stdio.h>
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
        table->height = current->height + 1;
        table->previous_scope = current;
    }

    table->size = TABLE_SIZE;
    table->count = 0;
    table->lexemes = (HashItem**)calloc(TABLE_SIZE, sizeof(HashItem*)); // tamanho fixo ou dinâmico?

    
    return table;
}

// Function to create a new HashItem and initialize it
HashItem* createHashItem(SymbolKey* key, TableContent* content) {
    HashItem* item = (HashItem*)malloc(sizeof(HashItem));
    item->hash_key = key;
    item->hash_content = content;
    return item;
}

// Function to calculate the hash index using a simple hash function
int hashFunction(SymbolKey* key) {
    // Replace the following line with an appropriate hash function
    // Example: using string length as a basic hash function

    // maybe this is good?
    return strlen(key->key_name) % TABLE_SIZE;
}

// Function to insert an element into the hash table
void addInTable(SymbolKey* key, TableContent* content, Scope* table) {
    int index = hashFunction(key);

    // aqui tem que verificar se table ja nao ta cheia, se ta, usa a proxima (se a proxima eh null, aloca nova)
    // esquece, nao precisa!

    // Traverse the linked list at the calculated index (separate chaining)
    HashItem* current = table->lexemes[index];
    
    // hash nao da a volta
    while (current != NULL) {
        if (strcmp(current->hash_key, key) == 0) {
            printf("Lexeme already exists! Adapt this to report semantic error!\n");
            // Element with the same key already exists; you can handle this case accordingly
            return;
        }
        current = current->next;
    }

    // Create a new HashItem and add it to the linked list
    HashItem* new_item = createHashItem(key, content);
    new_item->next = table->lexemes[index]; // tem sla, 128 slots sequenciaas em memoria, mas tu pula os vazios pq os slots ocupados se apontam
                                            // na verdade nao... eh um bucket! tem o indice 12 dos 128, todos que sao 12, dai fazem parte de uma lista
                                            // referente ao 12! se o 12 ta ocupado o cara nao vira o 13 nao, ele só vira a cabeca da lista do 12
                                            // nao precisa criar uma nova table
                                            // eh infinito, mas dependnedo do tmanho pode ficar meio ineficiente (todos index terem listas grandes, sla)
    table->lexemes[index] = new_item;
    table->count++;
}


// Function to find an element in the hash table
TableContent* findInTable(SymbolKey* key, Scope* table) {
    int index = hashFunction(key);

    // Traverse the linked list at the calculated index (separate chaining)
    HashItem* current = table->lexemes[index];
    while (current != NULL) {
        if (strcmp(current->hash_key, key) == 0) {
            return current->hash_content; // Element found, return its content
        }
        current = current->next;
    }

    return NULL; // Element not found
}

