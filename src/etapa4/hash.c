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
        printf("EH os guri\n");
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
    printf("Was able to malloc\n");

    //table->lexemes = (HashItem**)calloc(TABLE_SIZE, sizeof(HashItem*)); // tamanho fixo ou dinâmico?

    // precisa dar um jeito de alocar internamente o q ta dentro do HashItem como next

    // precisa alocar as estruturas de dentro das estruturas?
    // aloca, dai aloca o q ta dentro e tals...
    // se nao aloca eh null
    
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
    // Replace the following line with an appropriate hash function
    // Example: using string length as a basic hash function

    // maybe this is good?
    return strlen(key->key_name) % TABLE_SIZE;
}

// Function to insert an element into the hash table
void addInTable(TableContent* content, Scope* table) {

    //if(table->lexemes == NULL) { // isso basicamente vai ser se o [0] (o ponteiro) ta apontando pra nada, eh alocado vai estar..
    //    return;
    //}

    int index = hashFunction(content->key);

    // aqui tem que verificar se table ja nao ta cheia, se ta, usa a proxima (se a proxima eh null, aloca nova)
    // esquece, nao precisa!

    // Traverse the linked list at the calculated index (separate chaining)
    printf("Index: %d\n", index);
    HashItem* current = table->lexemes[index];
    // printf("Aqui q da seg fault?\n");
    
    // hash nao da a volta
    while (current != NULL) {
        if (strcmp(current->hash_content->key->key_name, content->key->key_name) == 0) {
            printf("Symbol was already declared!\n");
            exit(ERR_DECLARED);
        }
        current = current->next;
    }

    scanf("%d", &index);
    printf("Achei um espaço\n");

    // Create a new HashItem and add it to the linked list
    HashItem* new_item = createHashItem(content);

    // ver se ta colocando certinho nos buckets da id... essa lista do index e tals
    new_item->next = table->lexemes[index]; // tem sla, 128 slots sequenciaas em memoria, mas tu pula os vazios pq os slots ocupados se apontam
                                            // na verdade nao... eh um bucket! tem o indice 12 dos 128, todos que sao 12, dai fazem parte de uma lista
                                            // referente ao 12! se o 12 ta ocupado o cara nao vira o 13 nao, ele só vira a cabeca da lista do 12
                                            // nao precisa criar uma nova table
                                            // eh infinito, mas dependnedo do tmanho pode ficar meio ineficiente (todos index terem listas grandes, sla)
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
        if (strcmp(current->hash_content->key->key_name, key->key_name) == 0) {
            return current->hash_content; // Element found, return its content
        }
        current = current->next;
    }

    return NULL; // Element not found
}


TableContent* findInTableStack(SymbolKey* key, Scope* stack_top) {

    //int current_height = stack_top->height;
    Scope* stack_run = stack_top;

    TableContent* content = NULL;

    int count = 0;

    while(stack_run != NULL && content == NULL) {
        content = findInTable(key, stack_run);
        if(content != NULL) {
            printf("Jumped %d scopes!\n", count);
            return content;
        }
        count++;
        stack_run = stack_run->previous_scope;
    }

    printf("Symbol was NOT declared!\n");
    exit(ERR_UNDECLARED);
     
}   // vai descendo a stack de hash tables

