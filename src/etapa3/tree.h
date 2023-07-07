#include "lextype.h"

typedef struct astNode {
    //char* label;
    char label[64];
    LexType* lexical_value;
    int n_sons;
    struct astNode** sons; // Dynamic array(first *) made of pointers to other nodes (second *)
} Node;

Node* createLexTypeNode(LexType* lex_value);
Node* createNode(char* label);
void addSon(Node* father, Node* son);
void exportTree();
void printKids(Node* father, int height);
