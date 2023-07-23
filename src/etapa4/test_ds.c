#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Scope* scope_stack = NULL;

int main() {

    // uses global variable as the scope, first one should be NULL
    scope_stack = createTable(scope_stack); // adaptar isso pra ser global mesmo, construir em cima da global, nao retornar..
    // global fica no topo
    // isso q tava causando seg fault??

    SymbolKey* key = malloc(sizeof(SymbolKey));
    SymbolKey* key2 = malloc(sizeof(SymbolKey));

    strcpy(key->key_name, "var1");
    printf("Line 1 made\n");
    strcpy(key2->key_name, "vaaaa2");
    

    printf("Will create lines\n");
    TableContent* content = newContent(key, "2", 0, ID_SYMBOL, LEX_LIT_INT); 
    TableContent* content2 = newContent(key2, "2", 0, ID_SYMBOL, LEX_LIT_INT); 
    printf("line created\n");

    //addToCurrentTable(content);

    addInTable(content->key, content, scope_stack);
    
    addInTable(content->key, content, scope_stack);
    
    addInTable(content2->key, content2, scope_stack);
    

}