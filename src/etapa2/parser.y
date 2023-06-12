%{
// Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
#include <stdio.h>

int yylex(void);
void yyerror (char const *s);
%}

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
/* x | ; -> means x OR empty

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

corpo: cmd_block ';' ; /*tirar essa duvida com professor!!*/



/*7 - Um bloco de comandos é definido entre chaves, e consiste em uma sequência, possivelmente vazia, de comandos 
simples cada um terminado por ponto-e-vírgula. Um bloco de comandos é considerado como um comando único simples, recursivamente, 
e pode ser utilizado em qualquer construção que aceite um comando simples.*/

cmd_block: '{' cmd_simples '}' | '{' '}' ; 

/*cmd_simples: cmd_block | cmd_line;
cmd_line: cmd_line ';' | cmd_block | var_local | atrib | flow_ctrl | return | fun_call*/



/*8 - Os comandos simples da linguagem podem ser: declaração de variável local, atribuição, construções de fluxo de controle, 
operação de retorno, um bloco de comandos, e chamadas de função.*/

cmd_simples: cmd_line | cmd_block ';'
cmd_line: cmd_line ';' | var_local | atrib | flow_ctrl | return | fun_call


/*9 - Declaração de Variável Local: Consiste no tipo da variável seguido de uma lista composta de pelo menos um nome 
de variável (identificador) separadas por vírgula. Os tipos podem ser aqueles descritos na seção sobre variáveis globais. 
Uma variável local pode ser opcionalmente inicializada caso sua declaração seja seguida do operador composto TK_OC_LE e de um 
literal.*/

var_local: tipo lista_local_var ;
lista_local_var: lista_local_var ',' TK_IDENTIFICADOR | lista_local_var ',' init | TK_IDENTIFICADOR | init ;
init: TK_IDENTIFICADOR TK_OC_LE literais ;



/*10 - Comando de Atribuição: O comando de atribuição consiste em um identificador seguido pelo caractere de igualdade seguido 
por uma expressão*/

atrib: TK_IDENTIFICADOR TK_OC_EQ expressao  | TK_IDENTIFICADOR TK_OC_EQ literais ;



/*11 - Chamada de Função: Uma chamada de função consiste no nome da função, seguida de argumentos entre parênteses separados 
por vírgula. Um argumento pode ser uma expressão.*/

fun_call: TK_IDENTIFICADOR '(' lista_args ')' ;
lista_args: lista_args ',' | literais | expressao ;



/*12 - Comando de Retorno: Trata-se do token return seguido de uma expressão. */

return: TK_PR_RETURN expressao



/*13 - Comandos de Controle de Fluxo: A linguagem possui uma construção condicional e uma iterativa para controle estruturado de 
fluxo. A condicional consiste no token if seguido de uma expressão entre parênteses e então por um bloco de comandos 
obrigatório. O else, sendo opcional, é seguido de um bloco de comandos, obrigatório caso o else seja empregado. Temos apenas 
uma construção de repetição que é o token while seguida de uma expressão entre parênteses e de um bloco de comandos.*/

flow_ctrl: condicional | iterativa ;
condicional: if_head corpo | if_head cmd_block TK_PR_ELSE corpo ;
if_head: TK_PR_IF '(' expressao ')' ;
iterativa: TK_PR_WHILE '(' expressao ')' corpo ;
/* ponto virgula no bloco ou chamada de flow ctrl? ou ambos?


/*14 - As variáveis globais são declaradas pelo tipo seguido de uma lista composta de pelo menos um nome de variável (identificador) 
separadas por vírgula. O tipo pode ser int, float e bool. As declarações de variáveis são terminadas por ponto-e-vírgula.*/

declaracao_variavel_global: tipo lista_var ';' ;
lista_var: lista_var ',' TK_IDENTIFICADOR | TK_IDENTIFICADOR ;



/*Uso Geral*/

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL ;
literais: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_TRUE | TK_LIT_FALSE ;
/* temp */ 
expressao: TK_IDENTIFICADOR ;


%%

void yyerror (char const *s) {
    printf("error\n");
}
