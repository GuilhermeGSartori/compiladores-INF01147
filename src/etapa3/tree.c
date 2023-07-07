#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* De cara ja vai existir um nodo raiz criado, vamos criando nodos e colando eles, arvore existe,
 * construimos uma de cima pra baixo e vamos colando */

extern void exporta (void *arvore);

Node* createLexTypeNode(LexType* lex_value) { 
   
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
 
    if(son != NULL) {
        if(father->n_sons == 0) 
            father->sons = malloc(sizeof(struct astNode)); 
        else 
	    father->sons = realloc(father->sons, ((father->n_sons)+1) * sizeof(struct astNode));

        father->sons[father->n_sons] = son; 

        father->n_sons++;
    }
}

void printEdges(Node* father) {
    int n_kids = father->n_sons;
    int i = 0;

    while(n_kids > 0) {
        printf("%p, %p\n", father, father->sons[i]);
	i++;
	n_kids--;
    }

    n_kids = father->n_sons;
    i = 0;

    while(n_kids > 0) {
        printEdges(father->sons[i]);
	i++;
	n_kids--;
    }
 
}

void printNodes(Node* father) {
    int n_kids = father->n_sons;
    int i = 0;

    printf("%p [label=\"%s\"];\n", father, father->label);

    while(n_kids > 0) {
        printNodes(father->sons[i]);
        i++;
        n_kids--;
    }
}

void exporta(void *arvore) {
    Node *father = (Node*) arvore;
    
    printEdges(arvore);
    printf("\n\n");
    printNodes(arvore);

    // como fazer o role do call funcionar e INVERTER listas
    // tem que ver se identificador eh chamada de funcao, se sim, colocar call... como diferencias? declaracao de funcao e chamada tem estrutura igual
    // ambos sao "terminais" com filhos, como saber qual eh call? ver outro identificador sla mudar o Terminal para outro nome

}

void printKids(Node* father, int height) {
 
    int n_kids = father->n_sons;
    int i = 0;
    printf("height: %d\n", height);
    height++;
    printf("current node: %s\n\n", father->label);
    while(n_kids > 0) {
        printKids(father->sons[i], height);
	i++;
	n_kids--;
    }
}
