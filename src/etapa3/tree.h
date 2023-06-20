/* Árvore eh ponteiro para primeiro filho (main) */

enum tk_type{literal, identificador};

struct LexType {
    int line;
    enum tk_type token;
    char* value;
}

struct Node {
    /* endereço de memória do nó */
//    char* label;
//    Node* sons; /* 1 Node vai apontar para vários outros nodes (como se fosse um array)
//		        ou fazer uma lista de adjnacencia? */  	
    int dummy;
};

LexType createLexType(int line, enum tk_type token, char* value);

// Node createTerinalNode();
// Node createMidNode();
// int removeNode();
// int updateTree();
// void printTree();
