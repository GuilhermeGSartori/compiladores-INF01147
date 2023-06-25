#include "lextype.h"

/*enum data_type {
    AST_LIT_INT,
    AST_LIT_FLOAT,
    AST_LIT_BOOL,
    AST_IDENTIFICADOR,
    AST_IF,
    AST_ELSE,
    AST_WHILE,
    AST_RETURN,
    AST_LESSEQ,
    AST_GREATEQ,
    AST_EQ,
    AST_NOTEQ,
    AST_AND,
    AST_OR,
    AST_MAP
}*/

typedef struct astNode {
    char* label;
    LexType* lexical_value;
    Node** sons; // Dynamic array(first *) made of pointers to other nodes (second *)
} Node;

Node* createTerminalNode(LexType* lex_value);
Node* createNode(char* label);
void addSon(Node* father, Node* son);
void exportTree();
