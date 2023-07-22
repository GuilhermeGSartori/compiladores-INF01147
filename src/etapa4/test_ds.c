#include "hash.h"
#include <stdio.h>

Scope* scope_stack = NULL;

int main() {

    // uses global variable as the scope, first one should be NULL
    createTable(scope_stack);


    TableContent* content = newContent("var1", "2", 0, ID_SYMBOL, LEX_LIT_INT); 

    //addToCurrentTable(content);

    addInTable(content->key->key_name, content, scope_stack);
    
    addInTable(content->key->key_name, content, scope_stack);
    

}