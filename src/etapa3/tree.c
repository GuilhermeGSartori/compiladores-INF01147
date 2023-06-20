#include "tree.h"

LexType* createLexType(int line, enum tk_type token, char* value) {
    LexType* new_lex_type;
    
    new_lex_type = (LexType*)malloc(LexType);
    
    *new_lex_type.line = line;
    *new_lex_type.token = token;
    strcpy(*new_lex_type.value, value);

    return new_lex_type;
}


//Node createTerminalNode(terminal_tk, id_fun_name) { /* arvore criada de baixo para cima, como? */
/*    if(isEmpty(arvore)) {
        // create tree
    }
    else {
        Node new_node;
	switch(terminal_tk) {
	    case TK_IDENTIFICADOR:
                new_node.addres = &new_node;
		new_node.label = id_fun_name;
		new_node.sons = NULL;
		break;
	    // ...
	}
    }

    return new_node;
}*/ /* terminais cria nodo so e retorna ele */


/*Node createMidNode(Node* sons, sons_qtd) {
    Nodo new_node;
    new_node.sons = (Node*)malloc(sons_qtd * sizeof(Node));
    for(int i = 0; i < sons_qtd; i++) {
        new_node.sons[i] = sons[i];
    }
    // cria nodo
    // usa sons e o tamanho do sons para criar e alocar filhos para o Nodo
    // Tu aloca um elemento na lista de nodos (tipo vector) [x]
    // e para aquele elemento tu atribui o nodo, tu aponta para o nodo
    // Eh um vector de ponteiros... Nao eh uma copia, tu aponta para o endereco de 
    // memoria desse son ali
    // os sons vao sendo construindo e usados nessa lista, ate q acha pai e com certeza
    // eles vao ser sons deles?
    // ver na etapa 2! imrpimir as coisas conforme acha e ver qual a ordem q rola
}*/

// retorna o nodo, o codigo principal aloca um espaço, coloca esse nodo no espaço
// complexidade?
