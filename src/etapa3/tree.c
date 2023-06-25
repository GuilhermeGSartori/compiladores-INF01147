#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* De cara ja vai existir um nodo raiz criado, vamos criando nodos e colando eles, arvore existe,
 * construimos uma de cima pra baixo e vamos colando */

Node* createTerminalNode(LexType* lex_value) { 
   
    Node* new_node;
    new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->label, lex_value->value);
    new_node->lexical_value = lex_value;
    new_node->n_sons = 0;//tornar constante?
    new_node->sons = NULL;
    
    return new_node;
}

Node* createNode(char* value) {

    Node* new_node;
    new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->label, value);
    new_node->lexical_value = NULL;
    new_node->n_sons = 0;
    new_node->sons = NULL;

    return new_node;
}

void addSon(Node* father, Node* son) {
 
    printf("Num of kids: %d\n", father->n_sons);	
    if(father->n_sons == 0) 
        father->sons = (Node*) calloc(1, sizeof(Node*)); // isso ver, dando warning
    else 
	father->sons = realloc(father->sons, ((father->n_sons)+1) * sizeof(Node*));

    father->sons[(father->n_sons)+1] = son; // isso ver, dando warning

    father->n_sons++;
}

void exportTree() {
    printf("Working on it...\n");
}

void printKids(Node* father) {
    printf("Working on it... Recursive\n");
}
