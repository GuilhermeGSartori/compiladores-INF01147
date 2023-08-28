int a, b, j;
int main() {
    a = 2;
    j = 20;
    int b, c;
    b = 3;
    c = 4;
    int d;
    //d = b + c;
    d = b - c;
	return a;
}

/*
	.file	"c_2.c"
	.text


---> ISSO AQUI SE BASEIA NA TABELA, CONSOME A TABELA GLOBAL E BASEADO NO QUE TEM NELA, SÓ ESCREVE ISSO
------------------------------ int a, b
	.comm	a,4,4
	.comm	b,4,4
    .comm	j,4,4
------------------------------

------------------------------ int main()
	.globl	main
	.type	main, @function
------------------------------

---> ISSO AQUI COLOCA DE CABEÇALHO NO ARQUIVO, SEMPRE
main:
.LFB0:

---> ISSO AQUI COLOCA SEMPRE NO ARQUIVO
----------------------------- Faz de padrão
	pushq	%rbp
	movq	%rsp, %rbp
-----------------------------

---> ISSO AQUI, VAI TER QUE ACHAR O COMANDO ILOC QUE REPRESENTA ISSO...
---> loadI 2 -> x \n load x -> base, offset
-> Como vamos fazer isso..? Se tiver loadI, sei que terei expressao com literal, que é atribuicao ou controle de fluxo
----------------------------- a = 2.. Pelo visto na global vai ter q dar um jeito... 
                                      Ver na tabela global qual a coisa que tá naquela posicao que o ILOC tá salvando na global
                                      pegar o símbolo que tá associado aquela posicao na tabela
                                      e no .s dai escreve o simbolo (a var.), já q nao é posicao!
                                      mesma coisa quando usa uma global AT ALL no código
	movl	$2, a(%rip)
    movl	$20, j(%rip)
-----------------------------
----------------------------- b = 3
	movl	$3, -12(%rbp)
-----------------------------
----------------------------- c = 4
	movl	$4, -8(%rbp)
-----------------------------

----------------------------- d = b + c;
    movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
-----------------------------
como podemos ver, rbp funciona tipo uma pilha

 ---   rbp
|   | -4(%rbp)
|   | -8(%rbp)
|   | -12(%rbp)

ou seja, sempre que declaramos uma variavel, o rbp sobe e a posicao das declaradas ficam pra tras... 
a filosofia do ILOC tem que mudar, em ver de rbp ser o piso, ter que virar o teto... 

----------------------------- return a
	movl	a(%rip), %eax
	popq	%rbp
	ret
-----------------------------

-> para traduzir ILOC para assembly, vamos guardar cada linha em um índice de um vetor de strings
-> vamos avancando no vetor
-> basicamente toda operação começa com "load", ou seja, sempre que achamos um load, guardamos esse índice
-> vamos descendo e tentando ENTENDER o que é
-> eventualmente vamos achar um comando ILOC que deixa claro o que tá acontecendo
-> se é expressao matematica, lógica, if, else, atribuicao, etc...
-> Na real, se é controle de fluxo, vamos saber pq vai ter uma label...
-> no fim, artefatos que temos... Atribuicao, declaracao, inicializacao, controle de fluxo, retorno... E todos eles USAM expressoes de algum jeito
-> expressoes que começam carregando dados em registradores e etc...



---> Complexidade vai ser PODRE e ainda com if else... faz parte... só vamos entregar e deu...

.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
*/