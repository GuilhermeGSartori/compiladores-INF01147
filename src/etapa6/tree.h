#include "lextype.h"
#include "tac.h"

enum semantic_type {
    TYPE_UNDEFINED,
    TYPE_INT, 
    TYPE_FLOAT, 
    TYPE_BOOL
};

typedef struct astNode {
    char label[LABEL_MAX_SIZE];
	char temp[10];
    CmdILOC* code;
    LexType* lexical_value;
    enum semantic_type type;
    int n_sons;
    struct astNode** sons; // Dynamic array(first *) made of pointers to other nodes (second *)
} Node;

Node* createLexTypeNode(LexType* lex_value);
Node* createNode(char* label);

void addSon(Node* father, Node* son);
int getType(Node* node);
void setType(Node* node, enum semantic_type type);
int inferType(enum semantic_type type1, enum semantic_type type2);
void updateLabel(Node* node);
int isAttr(Node* node);

void printEdges(Node* father);
void printNodes(Node* father);
void printILOC(Node* father);
void printKids(Node* father, int height);

char* labelGenerator();
char* tempGenerator();

void setTemp(Node* node, char* temp);
void setTempString(char* temp, char* tempGenerated);
void setCode(Node* node, char* code);
void setLabel(char* label, char* labelGenerated);
int hasCode(CmdILOC* code);
int emptyElseOrNull(Node* node);