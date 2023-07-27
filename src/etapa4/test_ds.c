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


    SymbolKey* key = mallocAndSetKeyName("var1");
    SymbolKey* key2 = mallocAndSetKeyName("vaaaa2");
    SymbolKey* key4 = mallocAndSetKeyName("vaar4");
    SymbolKey* key3 = mallocAndSetKeyName("7");
    // algo aqui invertendo key3 com key4 e malloc nao retornando mas setando internamente a key (passada como ponteiro) tava dando seg fault

    printf("Criei Keys\n");
    

    printf("Will create lines\n");
    TableContent* content = newContent(key, "2", 0, ID_SYMBOL, TYPE_INT); 
    TableContent* content2 = newContent(key2, "3", 0, ID_SYMBOL, TYPE_INT); 
    TableContent* content3 = newContent(key3, "7", 0, LIT_SYMBOL, TYPE_INT);  // se for FUN_SYMBOL, o TYPE vai ser determinado pelo o q ele retorna
    // lista para atribuicao/declaracao
    // sla
    printf("line created\n");

    //addToCurrentTable(content);

    addInTable(content, scope_stack);
    
    addInTable(content2, scope_stack);

    scope_stack = createTable(scope_stack);

    addInTable(content, scope_stack);

    addInTable(content3, scope_stack); // tirar a key dos parametros

    TableContent* get;

    get = findInTableStack(key2, scope_stack, TYPE_INT);
    printf("key2 content: %s\n", get->value);

    get = findInTableStack(key3, scope_stack, TYPE_INT);
    printf("key3 content: %s\n", get->value);

    get = findInTableStack(key, scope_stack, TYPE_INT);
    printf("key content: %s\n", get->value); // como sei q eh a key q ta no topo e nao na base?

    get = findInTableStack(key4, scope_stack, TYPE_INT);
    printf("key4 content: %s\n", get->value);


    return 0;

}