int main() {
    int a;
    a = 1;

    //if(a==1){ Isso não importa, meio que tudo pertence ao desvio da main...
        int b;
        b = 2;
    //}

   // if(a==1) { vao existir ambos "a", o primeiro é desvio -12 e esse é desvio -4... Então tudo pertence a main!
   // só contar quantas variaveis locais ocorrem ao analisar a main!
   // sei q to analisando a main?
   // toda declaracao que achar, aumento o tamanho total da quantidade de ints em main!
   // em ILOC é assim também? essa a dentro do if estaria no offset 8? (terceira var), acho q sim..
   // pois em ILOC não importa o abre e fecha escopo, importa O CONTEXTO QUE TO
   // to nao main? tudo que achar é local, gg! vai pro mesmo pacote, nao importa o escopo q tá
   // afianl de contas, o contexto nesses escopos so sobe, o a vai ser o de cima, mas não é uma bolha, tipo,
   // se usar a, vai ser o da main, se declarar dentro, o proprio, em chamada de funcao nao tem escolha a nao ser declarar A
   // pq mudou o escopo total! não tá afundando em um balde, trocou de balde!
        int a;
        a = 3;
    //}

    return 0;
}