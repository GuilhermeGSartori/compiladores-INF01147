/* Árvore eh ponteiro para primeiro filho (main) */

struct Node {
    /* endereço de memória do nó */
    char* label;
    Node* sons; /* 1 Node vai apontar para vários outros nodes (como se fosse um array)
		        ou fazer uma lista de adjnacencia? */  	
};

Node createTerinalNode();
Node createMidNode();
int removeNode();
int updateTree();
void printTree();
