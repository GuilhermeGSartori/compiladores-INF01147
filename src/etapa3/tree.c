#include <stdio.h>
#include "tree.h"

/* De cara ja vai existir um nodo raiz criado, vamos criando nodos e colando eles, arvore existe,
 * construimos uma de cima pra baixo e vamos colando */

Node* createTerminalNode(LexType* lex_value) { 
    
    Node* new_node;
    new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->label, lex_value->value);
    new_node->lexical_value = lex_value;
    new_node->sons = NULL;
    
    return new_node;
}

Node* createNode(char* value) {

    Node* new_node;
    new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->label, value);
    new_node->lexical_value = NULL;
    new_node->sons = NULL;

    return new_node;
}

void addSon(Node* father, Node* son) {
    
    if(father->n_sons == 0) 
        father->sons = calloc(1, sizeof(*Node));
    else 
	father->sons = realloc(father->sons, (father->n_sons+1) * sizeof(*Node));

    father->sons[n_sons+1] = son;

    father->n_sons++;
}

void exportTree() {
    printf("Working on it...\n");
}
