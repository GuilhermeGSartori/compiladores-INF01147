%{
// Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
#include <stdio.h>

int yylex(void);
void yyerror (char const *s);
extern int get_line_number();
%}
%define parse.error detailed

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
%token TK_IDENTIFICADOR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_ERRO

%%

/* x | ; -> means x OR empty */


/*1 - Um programa na linguagem é composto por dois elementos, todos opcionais: um conjunto de declarações de variáveis globais e um 
conjunto de funções. Esses elementos podem estar intercalados e em qualquer ordem.*/

programa: lista | ;
lista: lista elemento | elemento ;
elemento: funcao | declaracao_variavel_global ;



/*2 - Cada função é definida por um cabeçalho e um corpo, sendo que esta definição não é terminada
por ponto-e-vírgula.*/

funcao: cabecalho corpo ;



/*3 - O cabeçalho consiste no nome da função, uma lista de parâmetros, o operador composto TK_OC_MAP e o tipo de retorno*/

cabecalho: TK_IDENTIFICADOR '(' lista_params ')' TK_OC_MAP tipo ;



/*4 - A lista de parâmetros é dada entre parênteses e é composta por zero ou mais parâmetros de entrada, separados por vírgula.*/

lista_params: um_ou_mais_param | ;
um_ou_mais_param: um_ou_mais_param ',' param | param ;



/*5 - Cada parâmetro é definido pelo seu tipo e nome.*/

param: tipo TK_IDENTIFICADOR ;



/*6 - O corpo da função é um bloco de comandos.*/
/*6.1 - Um bloco de comandos é definido entre chaves, e consiste em uma sequência, possivelmente vazia, de comandos 
simples cada um terminado por ponto-e-vírgula. Um bloco de comandos é considerado como um comando único simples, recursivamente, 
e pode ser utilizado em qualquer construção que aceite um comando simples.*/

corpo: '{' cmd_simples '}' ';' | '{' '}' ';' ; 
internal_block: '{' cmd_simples '}' | '{' '}' ;


/*7 - Os comandos simples da linguagem podem ser: declaração de variável local, atribuição, construções de fluxo de controle, 
operação de retorno, um bloco de comandos, e chamadas de função.*/

cmd_simples: cmd_simples cmd_list | cmd_list ;
cmd_list: internal_block ';' | var_local ';' | atrib ';' | if ';' else | while ';' | return ';' | fun_call ';' ;



/*8 - Declaração de Variável Local: Consiste no tipo da variável seguido de uma lista composta de pelo menos um nome 
de variável (identificador) separadas por vírgula. Os tipos podem ser aqueles descritos na seção sobre variáveis globais. 
Uma variável local pode ser opcionalmente inicializada caso sua declaração seja seguida do operador composto TK_OC_LE e de um 
literal.*/

var_local: tipo lista_local_var ;
lista_local_var: lista_local_var ',' TK_IDENTIFICADOR | lista_local_var ',' init | TK_IDENTIFICADOR | init ;
init: TK_IDENTIFICADOR TK_OC_LE literais ;



/*9 - Comando de Atribuição: O comando de atribuição consiste em um identificador seguido pelo caractere de igualdade seguido 
por uma expressão*/

atrib: TK_IDENTIFICADOR '=' expressao ;



/*10 - Chamada de Função: Uma chamada de função consiste no nome da função, seguida de argumentos entre parênteses separados 
por vírgula. Um argumento pode ser uma expressão.*/

fun_call: TK_IDENTIFICADOR '(' lista_args ')' ;
lista_args: lista_args ',' args | args ;
args: expressao ;



/*11 - Comando de Retorno: Trata-se do token return seguido de uma expressão. */

return: TK_PR_RETURN expressao ;



/*12 - Comandos de Controle de Fluxo: A linguagem possui uma construção condicional e uma iterativa para controle estruturado de 
fluxo. A condicional consiste no token if seguido de uma expressão entre parênteses e então por um bloco de comandos 
obrigatório. O else, sendo opcional, é seguido de um bloco de comandos, obrigatório caso o else seja empregado. Temos apenas 
uma construção de repetição que é o token while seguida de uma expressão entre parênteses e de um bloco de comandos.*/

if: if_head internal_block ; 
if_head: TK_PR_IF '(' expressao ')' ;

else: TK_PR_ELSE internal_block ';' | ; /*o problema eh o ; pelo visto...*/

while: TK_PR_WHILE '(' expressao ')' internal_block ;



/*13 - As variáveis globais são declaradas pelo tipo seguido de uma lista composta de pelo menos um nome de variável (identificador) 
separadas por vírgula. O tipo pode ser int, float e bool. As declarações de variáveis são terminadas por ponto-e-vírgula.*/

declaracao_variavel_global: tipo lista_var ';' ;
lista_var: lista_var ',' TK_IDENTIFICADOR | TK_IDENTIFICADOR ;



/*Uso Geral*/

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL ;
literais: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_TRUE | TK_LIT_FALSE ;




/*14 - Expressões tem operandos e operadores. Os operandos podem ser(a)identificadores,(b)literaise (c)chamada de função. As expressões podem ser formadas recursivamente 
pelo emprego de operadores. Elas também permitem o uso de parênteses para forçar uma associatividade ou precedência diferente daquela tradicional.*/

operandos: literais | TK_IDENTIFICADOR | fun_call ;

operadoresUnarios: '-' | '!' ;

operadoresPrecedencia2: '*' | '/' | '%' ;

operadoresPrecedencia3: '+' | '-' ;

operadoresPrecedencia4: '<' | '>' | TK_OC_LE | TK_OC_GE ;

operadoresPrecedencia5: TK_OC_EQ | TK_OC_NE ;

operadoresPrecedencia6: TK_OC_AND ;

operadoresPrecedencia7: TK_OC_OR ;

expressao: expr1 | expressao operadoresPrecedencia7 expr1 ;
expr1: expr2 | expr1 operadoresPrecedencia6 expr2 ;
expr2: expr3 | expr2 operadoresPrecedencia5 expr3 ;
expr3: expr4 | expr3 operadoresPrecedencia4 expr4 ; 
expr4: expr5 | expr4 operadoresPrecedencia3 expr5 ;
expr5: expr6 | expr5 operadoresPrecedencia2 expr6 ;
expr6: expr7 | operadoresUnarios expr7 ;
expr7: operandos | '(' expressao ')' ; 


%%

void yyerror (char const *s) {
    printf("Erro sintatico na linha %d.\n%s\n", get_line_number(), s);
}
