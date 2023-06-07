%{
// Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703

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


/*1 - Um programa na linguagem é composto por dois elementos, todos opcionais: um conjunto de declarações de variáveis globais e um 
conjunto de funções. Esses elementos podem estar intercalados e em qualquer ordem.*/

programa: lista | ;
lista: lista elemento | elemento ;
elemento: funcao | declaracao_variavel_global ;



/*2 - Cada função é definida por um cabeçalho e um corpo, sendo que esta definição não é terminada
por ponto-e-vírgula.*/

funcao: cabecalho corpo ;



/*3 - O cabeçalho consiste no nome da função, uma lista de parâmetros, o operador composto TK_OC_MAP e o tipo de retorno*/

cabecalho: TK_IDENTIFICADOR lista_params TK_OC_MAP tipo ;



/*4 - A lista de parâmetros é dada entre parênteses e é composta por zero ou mais parâmetros de entrada, separados por vírgula.*/

lista_params: '(' lista_provisoria_de_params  ')' ;
lista_provisoria_de_params: um_ou_mais_param | ;
um_ou_mais_param: um_ou_mais_param ',' param | param ;



/*5 - Cada parâmetro é definido pelo seu tipo e nome.*/

param: tipo TK_IDENTIFICADOR ;



/*6 - O corpo da função é um bloco de comandos.*/

corpo: '{a}' /*temporario*/
/* corpo: bloco_comandos ;
bloco_comandos: '{' comandos '}' ;
comandos: linhas | ;
linhas: linhas ';' linha ;
linha: 'a' */ 



/*7 - As variáveis globais são declaradas pelo tipo seguido de uma lista composta de pelo menos um nome de variável (identificador) 
separadas por vírgula. O tipo pode ser int, float e bool. As declarações de variáveis são terminadas por ponto-e-vírgula.*/

declaracao_variavel_global: tipo lista_var ';' ;
tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL ;
lista_var: lista_var ',' TK_IDENTIFICADOR | TK_IDENTIFICADOR ;


%%
