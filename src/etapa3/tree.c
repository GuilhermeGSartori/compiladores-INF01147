#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* De cara ja vai existir um nodo raiz criado, vamos criando nodos e colando eles, arvore existe,
 * construimos uma de cima pra baixo e vamos colando */

extern void exporta (void *arvore);

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
    if(son != NULL) {
        if(father->n_sons == 0) 
            father->sons = malloc(sizeof(struct astNode)); // isso ver, dando warning
        else 
	    father->sons = realloc(father->sons, ((father->n_sons)+1) * sizeof(struct astNode));

        father->sons[father->n_sons] = son; // isso ver, dando warning
        printf("Added son: %s\n", father->sons[father->n_sons]->label);

        father->n_sons++;
    }
}

void exporta(void *arvore) {
    Node *father = (Node*) arvore;
    printf("\n\n\nWorking on it...\n\n\n");
    int n_kids = father->n_sons;
    int i = 0;
    printf("current node: %s\n\n", father->label);
    while(n_kids > 0) {
        exporta(father->sons[i]);
        i++;
        n_kids--;
    }

}

void printKids(Node* father, int height) {
 
    int n_kids = father->n_sons;
    int i = 0;
    printf("height: %d\n", height);
    height++;
    printf("current node: %s\n\n", father->label);
    while(n_kids > 0) {
        printKids(father->sons[i], height/*height++*/);
	i++;
	n_kids--;
    }
}
