#include "tree.h"
#include <stdio.h>

int main() {
    printf("Vou criar Lex Types.. Testar se alocou e valores e tals\n");
    LexType* new_lex1 = createLexType(0, LEX_LIT_INT, "2");
    LexType* new_lex2 = createLexType(1, LEX_LIT_FLOAT, "2.0");
    LexType* new_lex3 = createLexType(2, LEX_LIT_INT, "1");
    LexType* new_lex4 = createLexType(3, LEX_LIT_BOOL, "false");
    LexType* new_lex5 = createLexType(4, LEX_ID, "_meuId");
    LexType* new_lex6 = createLexType(5, LEX_ID, "_meuId");

    printf("Vou criar nodos terminais\n");
    Node* node1 = createTerminalNode(new_lex1);
    Node* node2 = createTerminalNode(new_lex2);
    Node* node3 = createTerminalNode(new_lex3);
    Node* node4 = createTerminalNode(new_lex4);
    Node* node5 = createTerminalNode(new_lex5);
    Node* node6 = createTerminalNode(new_lex6);

    printf("Vou criar nodo pai 1\n");
    Node* father1 = createNode("=");
    addSon(father1, node5);
    addSon(father1, node1);

    printf("Vou criar nodo pai 2\n");
    Node* father2 = createNode("*");
    addSon(father2, node2);
    addSon(father2, node5);

    printf("Vou criar nodo pai 3\n");
    Node* father3 = createNode("=");
    //addSon(node5, father2); tudo errado burrao
    addSon(father3, node6); // NAO EH O MESMO NODO DA PRIMEIRA VEZ Q _meuId APARECEU, CADA APARICAO, 1 NODO
    addSon(father3, father2);

    printf("\nPrimeiro pai (_meuId = 2)\n");
    printKids(father1, 0);

    printf("\nSegundo pai (2.0 * _meuId)\n");
    printKids(father2, 0);

    printf("\nTerceiro pai (_meuId = 2.0 * _ meuId)\n");
    printKids(father3, 0);

    // Arvore Simulada:
    // _meuId = 2
    // _meuId = 2.0 * _meuId
}
