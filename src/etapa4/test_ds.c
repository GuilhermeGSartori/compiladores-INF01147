#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Scope* scope_stack = NULL;

int main() {

    //extern Scope* scope_stack;
    // uses global variable as the scope, first one should be NULL
    scope_stack = createTable(scope_stack); // adaptar isso pra ser global mesmo, construir em cima da global, nao retornar..
    // global fica no topo
    // isso q tava causando seg fault??

    SymbolKey* key = malloc(sizeof(SymbolKey));
    SymbolKey* key2 = malloc(sizeof(SymbolKey));
    SymbolKey* key3 = malloc(sizeof(SymbolKey));
    SymbolKey* key4 = malloc(sizeof(SymbolKey));

    strcpy(key->key_name, "var1");
    //printf("Line 1 made\n");
    strcpy(key2->key_name, "vaaaa2");
    strcpy(key4->key_name, "vaar3");
    strcpy(key3->key_name, "7");
    

    printf("Will create lines\n");
    TableContent* content = newContent(key, "2", 0, ID_SYMBOL, TYPE_INT); 
    TableContent* content2 = newContent(key2, "3", 0, ID_SYMBOL, TYPE_INT); 
    TableContent* content3 = newContent(key3, "7", 0, LIT_SYMBOL, TYPE_INT); 
    printf("line created\n");

    //addToCurrentTable(content);

    addInTable(content, scope_stack);
    
    addInTable(content2, scope_stack);

    scope_stack = createTable(scope_stack);

    addInTable(content, scope_stack);

    addInTable(content3, scope_stack); // tirar a key dos parametros

    TableContent* get;

    get = findInTableStack(key2, scope_stack);
    printf("key2 content: %s\n", get->value);

    get = findInTableStack(key3, scope_stack);
    printf("key3 content: %s\n", get->value);

    get = findInTableStack(key, scope_stack);
    printf("key content: %s\n", get->value); // como sei q eh a key q ta no topo e nao na base?

    get = findInTableStack(key4, scope_stack);
    printf("key4 content: %s\n", get->value);


    return 0;

}