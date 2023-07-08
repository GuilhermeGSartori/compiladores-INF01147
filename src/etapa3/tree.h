#include "lextype.h"

typedef struct astNode {
    char label[LABEL_MAX_SIZE];
    LexType* lexical_value;
    int n_sons;
    struct astNode** sons; // Dynamic array(first *) made of pointers to other nodes (second *)
} Node;

Node* createLexTypeNode(LexType* lex_value);
Node* createNode(char* label);

void addSon(Node* father, Node* son);
void updateLabel(Node* node);

void printEdges(Node* father);
void printNodes(Node* father);
void printKids(Node* father, int height);

Node* invertCmdList(Node* node); // dai tem que ter switch case
Node* invertPrmList(Node* node); // deve ter logica parecida com proximos
Node* invertFunList(Node* node); // se 2 nodos (primeiro comando e proxima funcao), segue, se nao, sei q eh ultimo
Node* invertVarList(Node* node); // sei q eh ultimo se nao tem 3 filhos
