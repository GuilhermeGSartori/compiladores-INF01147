#include "tree.h"
#include "lextype.h"
#include <stdio.h>

int main() {
    LexType* new_lex1 = createLexType(0, LEX_LIT_INT, "2");
    LexType* new_lex2 = createLexType(1, LEX_LIT_FLOAT, "2.0");
    LexType* new_lex3 = createLexType(2, LEX_LIT_INT, "1");
    LexType* new_lex4 = createLexType(3, LEX_LIT_BOOL, "false");
    LexType* new_lex5 = createLexType(4, LEX_ID, "_meuId");

    Node* node1 = createTerminalNode(new_lex1);
    Node* node2 = createTerminalNode(new_lex2);
    Node* node3 = createTerminalNode(new_lex3);
    Node* node4 = createTerminalNode(new_lex4);
    Node* node5 = createTerminalNode(new_lex5);

    Node* father1 = createNode('=');
    addSon(father1, node5);
    addSon(father1, node1);

    Node* father2 = createNode('*');
    addSon(father2, node2);
    addSon(father2, node5);

    Node* father3 = createNode("=");
    addSon(node5, father2);

    // Arvore Simulada:
    // _meuId = 2
    // _meuId = 2.0 * _meuId
}
