#include "lextype.h"

typedef struct astNode {
    char* label;
    LexType* lexical_value;
    int n_sons = 0;
    Node** sons; // Dynamic array(first *) made of pointers to other nodes (second *)
} Node;

Node* createTerminalNode(LexType* lex_value);
Node* createNode(char* label);
void addSon(Node* father, Node* son);
void exportTree();
