#include "lextype.h"

enum semantic_type {
    TYPE_INT, 
    TYPE_FLOAT, 
    TYPE_BOOL, 
    TYPE_UNDEFINED
};

typedef struct astNode {
    char label[LABEL_MAX_SIZE];
    LexType* lexical_value;
	enum semantic_type type;
    int n_sons;
    struct astNode** sons; // Dynamic array(first *) made of pointers to other nodes (second *)
} Node;

Node* createLexTypeNode(LexType* lex_value);
Node* createNode(char* label);

void addSon(Node* father, Node* son);
void updateLabel(Node* node);
int isAttr(Node* node);

void printEdges(Node* father);
void printNodes(Node* father);
void printKids(Node* father, int height);
