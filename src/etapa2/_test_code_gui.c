int exemplo;
bool exemplo, _exemplo;

/*fun () -> int {
    int a;
    int a, b, c; //ver se posso atribuir literal
    int b
    //int _a = 1; //-> realmente nao eh assim?
    int _a <= 1;
    //float d = 10.1; //precisa manter a conssitencia? gramaticamente faz sentido, questao de semantica vemos dps
    if(a) {
        int e;
    };

    if(b) {
    };
    else {
        int f;
    };

};*/

main () -> int {
    int a;
    int a, b, c; //ver se posso atribuir literal
    int b;
    int _a <= 1;
    float d <= 10.1; //precisa manter a conssitencia? gramaticamente faz sentido, questao de semantica vemos dps
    {};
    if(a) {};
    if(a) {
        int e;
    };
    
    {
    };

    {
        float w;
    };

    if(b) {
        //int j;
    }; // -> CONSERTAR ISSO
      // DEVIA TER UM PONTO VIRGULA AQUI... ESTOU TENDO PROBLEMA COM SHIFT REDUCE... RESOLVER ISSO DE MANEIRA INTELIGENTE
      // O problema eh que um if pode sim acabar com ponto virgula, e ate onde o bison sabe, o else e o if sao separados
      // logo, eh possivel acontecer um if por ser ele mesmo (com ponto virgula no final) e um if com ponto vigula nao
      // sabendo se veio do else ou nao
    else {
        int f;
    };

    z = y;

    while(a) {
        int x <= 1;
	float z, y <= 2.0, l;
	z = y;
	foo(z, y, x, 1, 2, p, 3, true, 0.3);
	//z = foo(1, 2, 3)  // pode uma chamada ser uma expressao usada na atribuicao?
    };

    // testes de expressao

    return a;

};

//foo (int input) -> bool a

//foo (int input, bool _input) -> bool a

//faa (int input, bool _input) -> bool output a
