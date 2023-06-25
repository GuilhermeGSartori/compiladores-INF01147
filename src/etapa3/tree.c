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
    
    Node** temporary;
    // pegar numero de filhos do pai
    temporary = (Node*) calloc(n_sons+1, sizeof(Node));
    for(int i = 0; i < n_sons+1 < i++) {
	if(i < n_sons)
            temporary[i] = father->sons[i];
        else
	    temporary[i] = son;
    }

    free(father->sons);

    father->sons = (Node*) calloc(n_sons+1, sizeof(Node));
    father->sons = temporary;

}

void exportTree() {
    printf("Working on it...\n");
}


/*Node createMidNode(Node* sons, sons_qtd) {
    Nodo new_node;
    new_node.sons = (Node*)malloc(sons_qtd * sizeof(Node));
    for(int i = 0; i < sons_qtd; i++) {
        new_node.sons[i] = sons[i];
    }
    // cria nodo
    // usa sons e o tamanho do sons para criar e alocar filhos para o Nodo
    // Tu aloca um elemento na lista de nodos (tipo vector) [x]
    // e para aquele elemento tu atribui o nodo, tu aponta para o nodo
    // Eh um vector de ponteiros... Nao eh uma copia, tu aponta para o endereco de 
    // memoria desse son ali
    // os sons vao sendo construindo e usados nessa lista, ate q acha pai e com certeza
    // eles vao ser sons deles?
    // ver na etapa 2! imrpimir as coisas conforme acha e ver qual a ordem q rola
}*/

// retorna o nodo, o codigo principal aloca um espaço, coloca esse nodo no espaço
// complexidade?
