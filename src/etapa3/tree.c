Node createTerminalNode() { /* arvore criada de baixo para cima, como? */
    if(isEmpty(arvore)) {
        // create tree
    }
    else {
        Node new_node = allocateTerminalNode(terminal);
    }

    return new_node;
} /* terminais cria nodo so e retorna ele */


Node allocateTerminalNode(int terminal) {
    Node allocated_node;
    switch(terminal) {
        //case TK_: allocated_node.mem = *allocated_node; alocated_node.label = TK_;
	// ...
    }

    return allocated_node;
}

Node createMidNode(Node* sons) {
    // cria nodo
    // usa sons e o tamanho do sons para criar e alocar filhos para o Nodo
    // Tu aloca um elemento na lista de nodos (tipo vector) [x]
    // e para aquele elemento tu atribui o nodo, tu aponta para o nodo
    // Eh um vector de ponteiros... Nao eh uma copia, tu aponta para o endereco de 
    // memoria desse son ali
    // os sons vao sendo construindo e usados nessa lista, ate q acha pai e com certeza
    // eles vao ser sons deles?
    // ver na etapa 2! imrpimir as coisas conforme acha e ver qual a ordem q rola
}

// retorna o nodo, o codigo principal aloca um espaço, coloca esse nodo no espaço
// complexidade?
