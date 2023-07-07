%{
// Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
// To Do: Testar estruturas, parser.y, exportar, gerar arvore
#include <stdio.h>
#include "tree.h"

int yylex(void);
void yyerror (char const *s);
extern int get_line_number();
extern void *arvore;
%}
%define parse.error verbose

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_IF
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_RETURN
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_MAP
%token<valor_lexico> TK_IDENTIFICADOR /*acho que isso ta errado... Nao deveria ser o tipo de yylval assume para esse TK? char*? */
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE
%token TK_ERRO

/* TK_IDENTIFICADOR já é atômico, literais não */
%type<valor_lexico> literais
%type<node> programa
%type<node> lista
%type<node> elemento
%type<node> funcao
%type<node> cabecalho
%type<node> corpo
%type<node> cmd_block
%type<node> cmd_simples
%type<node> cmd_list
%type<node> var_local
%type<node> lista_local_var
%type<node> init
%type<node> fun_call
%type<node> lista_args
%type<node> um_ou_mais_args
%type<node> args
%type<node> if
%type<node> else
%type<node> while
%type<node> operandos
%type<node> operadoresUnarios
%type<node> operadoresPrecedencia2
%type<node> operadoresPrecedencia3
%type<node> operadoresPrecedencia4
%type<node> operadoresPrecedencia5
%type<node> operadoresPrecedencia6
%type<node> operadoresPrecedencia7
%type<node> expr7
%type<node> expr6
%type<node> expr5
%type<node> expr4
%type<node> expr3
%type<node> expr2
%type<node> expr1
%type<node> expressao
%type<node> atrib
%type<node> return

%union {
    struct LexType* valor_lexico;
    struct astNode* node;
}

%%

/* x | ; -> means x OR empty */


/*1 - Um programa na linguagem é composto por dois elementos, todos opcionais: um conjunto de declarações de variáveis globais e um 
conjunto de funções. Esses elementos podem estar intercalados e em qualquer ordem.*/

programa: lista   { arvore = $1; }
	|         { arvore = NULL; }
        ;

lista: lista elemento  {
                                       if($2 == NULL) {
                                           $$ = $1;
                                       }
                                       else {
                                           if($1 != NULL) {
                                               addSon($2, $1);
                                               $$ = $2;
                                           }
                                           else { 
                                               $$ = $2;
                                           }
                                        }
                                    } ;
lista: elemento          { if($1 != NULL) {$$ = $1;} else {$$ = NULL;} } ;

elemento: funcao { $$ = $1; } ; 
elemento: declaracao_variavel_global { $$ = NULL; } ;



/*2 - Cada função é definida por um cabeçalho e um corpo, sendo que esta definição não é terminada
por ponto-e-vírgula.*/

funcao: cabecalho corpo { $$ = $1; addSon($$, $2); } ;



/*3 - O cabeçalho consiste no nome da função, uma lista de parâmetros, o operador composto TK_OC_MAP e o tipo de retorno*/

cabecalho: TK_IDENTIFICADOR '(' lista_params ')' TK_OC_MAP tipo { $$ = createTerminalNode($1); };
/* como diferencia ID de declaracao de funcao vs chmada de funcao? */


/*4 - A lista de parâmetros é dada entre parênteses e é composta por zero ou mais parâmetros de entrada, separados por vírgula.*/

lista_params: um_ou_mais_param | ;
um_ou_mais_param: um_ou_mais_param ',' param | param ;



/*5 - Cada parâmetro é definido pelo seu tipo e nome.*/

param: tipo TK_IDENTIFICADOR ;



/*6 - O corpo da função é um bloco de comandos.*/
/*6.1 - Um bloco de comandos é definido entre chaves, e consiste em uma sequência, possivelmente vazia, de comandos 
simples cada um terminado por ponto-e-vírgula. Um bloco de comandos é considerado como um comando único simples, recursivamente, 
e pode ser utilizado em qualquer construção que aceite um comando simples.*/

corpo: cmd_block { $$ = $1; } ;
cmd_block: '{' cmd_simples '}' { $$ = $2; }; /* se todos os comandos simples forem sequencias de iniciailizacoes sem atribuicoes aqui vai ser null, dai o addSon da funcao vai ver q primeiro comando eh null e vai adicionar nada */
cmd_block: '{' '}' { $$ = NULL; } ; /* e se o if tiver bloco vazio, o q vai acontecer? */


/*7 - Os comandos simples da linguagem podem ser: declaração de variável local, atribuição, construções de fluxo de controle, 
operação de retorno, um bloco de comandos, e chamadas de função.*/

cmd_simples: cmd_simples cmd_list  { 
	                               if($2 == NULL) { 
                                           $$ = $1; 
                                       }
                                       else { 
                                           if($1 != NULL) { 
                                               addSon($2, $1); /* aqui eh se pelo menos algum antes do ultimo nao eh null, como sei q 1 nao vai ser null se direto em cima dele eh? */
                                                               /* ah sim, eh por causa do if mais de cima! se o de cima eh null, ele vai passar o proximo da lista... pq o $1 de agora
                                                                  eh o $$ do futuro que recebe o valor baseado se $2 eh ou nao null */
                                               $$ = $2; 
                                           } 
                                           else { /*aqui eh no caso q o ultimo comando ever (rec esquerda) eh o unico que nao eh atribuicao */
                                               $$ = $2; 
                                           } 
                                        } 
                                    } ; 
/*lista vai pra arvore? sera q filho do cmd nao eh outro cmd? mas dai qual seria o comando em si? outro filho? tipo, o comando seria uma atribuicao, ele teria os filhos de atribuicao + outro comando?*/
/* acho que o role seria tipo pegar esse primeiro cmd_siples e adicionar nele o filho cmd list, isso eh, addSon($1, $2)  e $$ = $1 */
cmd_simples: cmd_list              { if($1 != NULL) {$$ = $1;} else {$$ = NULL;} } ;

cmd_list: cmd_block ';'    { $$ = $1; } ;
cmd_list: var_local ';'    { $$ = $1; } ; 
cmd_list: atrib ';'        { $$ = $1; } ; 
cmd_list: if               { $$ = $1; } ;
cmd_list: while ';'        { $$ = $1; } ; 
cmd_list: return ';'       { $$ = $1; } ; 
cmd_list: fun_call ';'     { $$ = $1; } ;



/*8 - Declaração de Variável Local: Consiste no tipo da variável seguido de uma lista composta de pelo menos um nome 
de variável (identificador) separadas por vírgula. Os tipos podem ser aqueles descritos na seção sobre variáveis globais. 
Uma variável local pode ser opcionalmente inicializada caso sua declaração seja seguida do operador composto TK_OC_LE e de um 
literal.*/

/* aqui so vai pra arvore se tem inicializacao ou nao, acho que aqui vai o if... nao eh lista, eh declaracao filho de declaracao */
/* proximo comando eh ANTES da lista ou eh irmao do primeiro da lista? */


var_local: tipo lista_local_var			{ $$ = $2; } ;

lista_local_var: lista_local_var ',' TK_IDENTIFICADOR 	{ if($1 == NULL) { $$ = NULL;} else { $$ = $1;} } // acho q lista nao se faz assim.. nao tem nodo lista
			   | lista_local_var ',' init   { addSon($3, $1); $$ = $3; } // se o addSon receber o filho como NULL, dai tem q adicionar NADA... isso eh importante... pq dai nao adicionaria filho
                                                                            // tipo, esse init seria um nodo e tals da lista, mas se o lista fosse so outro tk_id, dai o filho sendo NULL nao adiciona!
                                                                            // isso reflete ate la em cima, se o proximo comando eh NULL, ou seja, so declaracao sem inicializacao, dai ele skipa
                                                                            // mas a cabeca tem q assumir um valor
			   | TK_IDENTIFICADOR 	        { $$ = NULL; }
			   | init 			{ $$ = $1; }
			   ;

/* Montar a arvore de comandos simples considerando a atribuicao quando assume NULL e ver indo da esquerda e como o comando da direita pega essa proximo da esquerda depois q um foi NULL, ver como
esses Ifs e passando as coisas */

init: TK_IDENTIFICADOR TK_OC_LE literais { $$ = createNode("<="); addSon($$, createTerminalNode($1)); addSon($$, createTerminalNode($3)); } ; 



/*9 - Comando de Atribuição: O comando de atribuição consiste em um identificador seguido pelo caractere de igualdade seguido 
por uma expressão*/

atrib: TK_IDENTIFICADOR '=' expressao { $$ = createNode("="); addSon($$, createTerminalNode($1)); addSon($$, $3); } ;



/*10 - Chamada de Função: Uma chamada de função consiste no nome da função, seguida de argumentos entre parênteses separados 
por vírgula. Um argumento pode ser uma expressão.*/


/* fun call nao eh um nodo... o nodo pai que representa fun_call via ter o label q eh o identificador, o filho eh a lista de args */

/* AQUI ACHO QUE EH DIFERENTE! ACHO QUE TU CRIA NODO COM TK_IDENTIFICADOR E FILHO DELE EH A LISTA ARGS 
fun_call: TK_IDENTIFICADOR '(' lista_args ')' 		{ char fun[20]; strcpy(fun, "call "); strcat(fun, $1->label); $$ = createNode(fun); addSon($$, createTerminalNode($1)); addSon($$, $3); } ;
/* esse nodo tem um valor lexico */
/* addSOn ver se eh zero ou null para nao adicionar */
fun_call: TK_IDENTIFICADOR '(' lista_args ')' { $$ = createTerminalNode($1); addSon($$, $3); } ; /* O LABEL VAI SER O NOME DA FUNCAO... SE NODO TEM FILHO E LEXICO, EH CHAMADA DE FUNCAO.. tem que ver se o nodo com label de TK_ID tem filho, se sim, ele vira um "call" no export.. nao eh terminal node o nome certo... */

lista_args: um_ou_mais_args 	{ $$ = $1; }
		  | 		{ $$ = NULL; }
		  ;

/* problema eh que aqui paramentros (a, b, c) ficam call fun->c->b->a*/
um_ou_mais_args: um_ou_mais_args ',' args 	{ addSon($3, $1); $$ = $3; } 
			   | args 		{ $$ = $1; }
			   ;

args: expressao 				{ $$ = $1; } ;



/*11 - Comando de Retorno: Trata-se do token return seguido de uma expressão. */

return: TK_PR_RETURN expressao  	{ $$ = createNode("return"); addSon($$, $2); } ;



/*12 - Comandos de Controle de Fluxo: A linguagem possui uma construção condicional e uma iterativa para controle estruturado de 
fluxo. A condicional consiste no token if seguido de uma expressão entre parênteses e então por um bloco de comandos 
obrigatório. O else, sendo opcional, é seguido de um bloco de comandos, obrigatório caso o else seja empregado. Temos apenas 
uma construção de repetição que é o token while seguida de uma expressão entre parênteses e de um bloco de comandos.*/

if: TK_PR_IF '(' expressao ')' cmd_block else  { $$ = createNode("if"); addSon($$, $3); addSon($$, $5); addSon($$, $6); } ; /*else can be null*/
 
else: TK_PR_ELSE cmd_block ';'                 { $$ = $2;}
        | ';'                                  { $$ = 0; } ;

while: TK_PR_WHILE '(' expressao ')' cmd_block { $$ = createNode("while"); addSon($$, $3); addSon($$, $5); } ; 



/*13 - As variáveis globais são declaradas pelo tipo seguido de uma lista composta de pelo menos um nome de variável (identificador) 
separadas por vírgula. O tipo pode ser int, float e bool. As declarações de variáveis são terminadas por ponto-e-vírgula.*/

declaracao_variavel_global: tipo lista_var ';' ;

lista_var: lista_var ',' TK_IDENTIFICADOR | TK_IDENTIFICADOR ;




/*Uso Geral*/

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL ;

/* Faz o token subir para ser convertido em nó com lex no operador*/
literais: TK_LIT_INT 		{ $$ = $1; } ;
literais: TK_LIT_FLOAT 		{ $$ = $1; } ;
literais: TK_LIT_TRUE 		{ $$ = $1; } ;
literais: TK_LIT_FALSE 		{ $$ = $1; } ;
	
/*literais: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_TRUE | TK_LIT_FALSE ; */




/*14 - Expressões tem operandos e operadores. Os operandos podem ser(a)identificadores,(b)literaise (c)chamada de função. As expressões podem ser formadas recursivamente 
pelo emprego de operadores. Elas também permitem o uso de parênteses para forçar uma associatividade ou precedência diferente daquela tradicional.*/

/* operandos: literais | TK_IDENTIFICADOR | fun_call ; */
operandos: TK_IDENTIFICADOR 		{ $$ = createTerminalNode($1); } ;
operandos: literais 				{ $$ = createTerminalNode($1); } ;
operandos: fun_call  				{ $$ = NULL; } ;

/* operadoresUnarios: '-' | '!' ; */
operadoresUnarios: '-'  			{ $$ = createNode("-"); } ;
operadoresUnarios: '!' 				{ $$ = createNode("!"); } ;

/* operadoresPrecedencia2: '*' | '/' | '%' ; */
operadoresPrecedencia2: '*' 		{ $$ = createNode("*"); } ;
operadoresPrecedencia2: '/' 		{ $$ = createNode("/"); } ;
operadoresPrecedencia2: '%' 		{ $$ = createNode("%"); } ;

/* operadoresPrecedencia3: '+' | '-' ; */
operadoresPrecedencia3: '+'  		{ $$ = createNode("+"); } ;
operadoresPrecedencia3: '-'  		{ $$ = createNode("-"); } ;

/*operadoresPrecedencia4: '<' | '>' | TK_OC_LE | TK_OC_GE ;*/
operadoresPrecedencia4: '<'  		{ $$ = createNode("<"); } ;
operadoresPrecedencia4: '>'  		{ $$ = createNode(">"); } ;
operadoresPrecedencia4: TK_OC_LE 	{ $$ = createNode("<="); }; 
operadoresPrecedencia4: TK_OC_GE 	{ $$ = createNode(">="); } ;

/*operadoresPrecedencia5: TK_OC_EQ | TK_OC_NE ;*/
operadoresPrecedencia5: TK_OC_EQ 	{ $$ = createNode("=="); } ;
operadoresPrecedencia5: TK_OC_NE 	{ $$ = createNode("!="); } ;

operadoresPrecedencia6: TK_OC_AND 	{ $$ = createNode("&"); } ;

operadoresPrecedencia7: TK_OC_OR 	{ $$ = createNode("|"); } ;


expressao: expr1                                        { $$ = $1; } ;
expressao: expressao operadoresPrecedencia7 expr1       { addSon($2, $1); addSon($2, $3); $$ = $2; } ;
expr1: expr2                                            { $$ = $1; } ;
expr1: expr1 operadoresPrecedencia6 expr2               { addSon($2, $1); addSon($2, $3); $$ = $2; } ;
expr2: expr3 	                                        { $$ = $1; } ;
expr2: expr2 operadoresPrecedencia5 expr3               { addSon($2, $1); addSon($2, $3); $$ = $2; } ;
expr3: expr4 		                                { $$ = $1; } ;
expr3: expr3 operadoresPrecedencia4 expr4               { addSon($2, $1); addSon($2, $3); $$ = $2; } ;
expr4: expr5                                            { $$ = $1; } ;
expr4: expr4 operadoresPrecedencia3 expr5               { addSon($2, $1); addSon($2, $3); $$ = $2; } ;
expr5: expr6 	                                        { $$ = $1; } ;
expr5: expr5 operadoresPrecedencia2 expr6               { addSon($2, $1); addSon($2, $3); $$ = $2; } ;
expr6: expr7 	                                        { $$ = $1; } ;
expr6: operadoresUnarios expr7 		                { addSon($1, $2); $$ = $1; } ;
expr7: operandos 	                                { $$ = $1; } ;
expr7: '(' expressao ')'                                { $$ = $2; } ;


%%

void yyerror (char const *s) {
    printf("Erro sintatico na linha %d.\n%s\n", get_line_number(), s);
}
