%{
// Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
/* TO DO:
*         - Create Hash Table (one scope, with basic functions of hash)
*         - Implement the Table Content funcitions
*         - Implement a list of scopes (multiple hashes)
*         - Use the new structs in the parser as defined by the professor
*         - Implement the errors and the "high level stuff" as defined by the professor
*/

#include <stdio.h>
//#include "tree.h"
#include "hash.h"

int yylex(void);
void yyerror (char const *s);
extern int get_line_number();
extern void *arvore;
Scope* scope_stack_top = NULL;
ParameterList* param_list = NULL;
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
%token<valor_lexico> TK_IDENTIFICADOR
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE
%token TK_ERRO

%type<node> literais
%type<node> programa
%type<node> lista
%type<node> elemento
%type<node> funcao
%type<node> cabecalho
%type<node> fun_name
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

inicio: abre_escopo programa fecha_escopo ;

abre_escopo: { scope_stack_top = createTable(scope_stack_top); } ;
fecha_escopo: ; // pop e free e tirar ponteiros

programa: lista   { arvore = $1; }
	|         { arvore = NULL; }
        ;

lista: elemento lista  {
                           if($1 == NULL) {
                               $$ = $2;
                           }
                           else {
                               if($2 != NULL) {
                                   addSon($1, $2);
                                   $$ = $1;
                                }
                                else { 
                                   $$ = $1;
                                }
                            }
                        } ;

lista: elemento         { if($1 != NULL) {$$ = $1;} else {$$ = NULL;} } ;

elemento: funcao { $$ = $1; } ; 
elemento: declaracao_variavel_global { $$ = NULL; } ;



/*2 - Cada função é definida por um cabeçalho e um corpo, sendo que esta definição não é terminada
por ponto-e-vírgula.*/

 //funcao: cabecalho corpo { $$ = $1; addSon($$, $2); } ;

funcao: cabecalho TK_OC_MAP TK_PR_FLOAT corpo fecha_escopo { 
                                                                $$ = $1; addSon($$, $4); setType($$, TYPE_FLOAT);
                                                                SymbolKey* key = mallocAndSetKeyName($1->label);
                                                                TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL);
                                                                updateContentType(content, TYPE_FLOAT); 
                                                           } ;

funcao: cabecalho TK_OC_MAP TK_PR_INT corpo fecha_escopo   { 
                                                                $$ = $1; addSon($$, $4); setType($$, TYPE_INT);
                                                                SymbolKey* key = mallocAndSetKeyName($1->label);
                                                                TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL);
                                                                updateContentType(content, TYPE_INT); 
                                                           } ;

funcao: cabecalho TK_OC_MAP TK_PR_BOOL corpo fecha_escopo  { 
                                                                $$ = $1; addSon($$, $4); setType($$, TYPE_BOOL);
                                                                SymbolKey* key = mallocAndSetKeyName($1->label);
                                                                TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL);
                                                                updateContentType(content, TYPE_BOOL); 
                                                           } ;

 // verificar se tipo de chamada de funcao ta certo?
 // cria um escopo na propria cabeça e dai coloca a lista de param como variaveis

/*3 - O cabeçalho consiste no nome da função, uma lista de parâmetros, o operador composto TK_OC_MAP e o tipo de retorno*/

cabecalho: fun_name abre_escopo parametros { $$ = $1; } ; // pega a label do node do fun_name, procura essa key no escopo anterior
                                                          // adiciona a lista dai no "parameters" do table content dele usando
                                                          // a lista anterior
                                                          // e limpa a lista recursivamente dai

fun_name: TK_IDENTIFICADOR {
                                $$ = createLexTypeNode($1); 
                                SymbolKey* key = mallocAndSetKeyName($1->value);
                                TableContent* content = newContent(key, $1->value, get_line_number(), FUN_SYMBOL, TYPE_UNDEFINED); 
                                addInTable(content, scope_stack_top);
                           } ;

parametros: '(' lista_params ')' ;


/*4 - A lista de parâmetros é dada entre parênteses e é composta por zero ou mais parâmetros de entrada, separados por vírgula.*/

lista_params: um_ou_mais_param | ;
um_ou_mais_param: um_ou_mais_param ',' param | param ;



/*5 - Cada parâmetro é definido pelo seu tipo e nome.*/

/* como defino o valor das variaveis passando as coisas como parametro na chamda de funcao..? aqui adiciono, mas como DEFINO o valor se eh só o valor */

param: TK_PR_BOOL TK_IDENTIFICADOR   { 
                                         SymbolKey* key = mallocAndSetKeyName($2->value);
                                         TableContent* content = newContent(key, $2->value, get_line_number(), ID_SYMBOL, TYPE_BOOL); 
                                         addInTable(content, scope_stack_top);
                                         addParameterInList(TYPE_BOOL, &param_list);
                                     } ;

param: TK_PR_INT TK_IDENTIFICADOR    { 
                                         SymbolKey* key = mallocAndSetKeyName($2->value);
                                         TableContent* content = newContent(key, $2->value, get_line_number(), ID_SYMBOL, TYPE_INT); 
                                         addInTable(content, scope_stack_top);
                                         addParameterInList(TYPE_INT, &param_list);
                                     } ;

param: TK_PR_FLOAT TK_IDENTIFICADOR  { 
                                         SymbolKey* key = mallocAndSetKeyName($2->value);
                                         TableContent* content = newContent(key, $2->value, get_line_number(), ID_SYMBOL, TYPE_FLOAT); 
                                         addInTable(content, scope_stack_top);
                                         addParameterInList(TYPE_FLOAT, &param_list);
                                     } ;

/*6 - O corpo da função é um bloco de comandos.*/
/*6.1 - Um bloco de comandos é definido entre chaves, e consiste em uma sequência, possivelmente vazia, de comandos 
simples cada um terminado por ponto-e-vírgula. Um bloco de comandos é considerado como um comando único simples, recursivamente, 
e pode ser utilizado em qualquer construção que aceite um comando simples.*/

corpo: cmd_block { $$ = $1; } ;
cmd_block: '{' cmd_simples '}' { $$ = $2; }; 
cmd_block: '{' '}' { $$ = NULL; } ; 


/*7 - Os comandos simples da linguagem podem ser: declaração de variável local, atribuição, construções de fluxo de controle, 
operação de retorno, um bloco de comandos, e chamadas de função.*/

cmd_simples: cmd_list cmd_simples  { 
	                               if($1 == NULL) { 
                                           $$ = $2; 
                                       }
                                       else { 
                                           if($2 != NULL) {
                                               if(isAttr($1) == 1) { // if it is <=. Here only attr can be <=
                                                   Node *leaf_attr = $1;
                                                   while(leaf_attr->n_sons == 3)
                                                       leaf_attr = leaf_attr->sons[2];
                                                   addSon(leaf_attr, $2);
                                               }
                                               else {
                                                   addSon($1, $2);
                                               } 
                                               $$ = $1; // point that started the secondary recursion must turn into $$, the head (previous cmd_list in the recursion)
                                           } 
                                           else { 
                                               $$ = $1; 
                                           } 
                                        } 
                                    } ; 

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

var_local: tipo lista_local_var			{ $$ = $2; } ;

lista_local_var: TK_IDENTIFICADOR ',' lista_local_var	{ if($3 == NULL) { $$ = NULL;} else { $$ = $3;} }
			   | init ',' lista_local_var   { addSon($1, $3); $$ = $1; } 
			   | TK_IDENTIFICADOR 	        { $$ = NULL; }
			   | init 			{ $$ = $1; }
			   ;

init: TK_IDENTIFICADOR TK_OC_LE literais { $$ = createNode("<="); addSon($$, createLexTypeNode($1)); addSon($$, $3); } ; 



/*9 - Comando de Atribuição: O comando de atribuição consiste em um identificador seguido pelo caractere de igualdade seguido 
por uma expressão*/

atrib: TK_IDENTIFICADOR '=' expressao { $$ = createNode("="); addSon($$, createLexTypeNode($1)); addSon($$, $3); } ;



/*10 - Chamada de Função: Uma chamada de função consiste no nome da função, seguida de argumentos entre parênteses separados 
por vírgula. Um argumento pode ser uma expressão.*/

/* Coisas acontecem no final, sera que nao tem que quebrar em 2 e herdar e tals? */

fun_call: TK_IDENTIFICADOR '(' lista_args ')' { 
                                                  $$ = createLexTypeNode($1); 
                                                  updateLabel($$); 
                                                  addSon($$, $3); 
                                                  SymbolKey* key = mallocAndSetKeyName($1->value); 
                                                  TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL);
                                                  setType($$, content->type); 
                                              } ; 

lista_args: um_ou_mais_args 	{ $$ = $1; }
		  | 		{ $$ = NULL; }
		  ;

um_ou_mais_args: args ',' um_ou_mais_args 	{ addSon($1, $3); $$ = $1; } 
			   | args 		{ $$ = $1; }
			   ;

args: expressao 				{ $$ = $1; } ;



/*11 - Comando de Retorno: Trata-se do token return seguido de uma expressão. */

return: TK_PR_RETURN expressao  	{ $$ = createNode("return"); addSon($$, $2); int type = getType($2); setType($$, type); } ;



/*12 - Comandos de Controle de Fluxo: A linguagem possui uma construção condicional e uma iterativa para controle estruturado de 
fluxo. A condicional consiste no token if seguido de uma expressão entre parênteses e então por um bloco de comandos 
obrigatório. O else, sendo opcional, é seguido de um bloco de comandos, obrigatório caso o else seja empregado. Temos apenas 
uma construção de repetição que é o token while seguida de uma expressão entre parênteses e de um bloco de comandos.*/

/* como faz tudo no final acho q tem q quebrar em 2 e herdar, if fica como undefined e inter baseado na expressao */
/* expressao nao tem q ser bool? */

if: TK_PR_IF '(' expressao ')' cmd_block else  { 
                                                 $$ = createNode("if"); addSon($$, $3); addSon($$, $5); addSon($$, $6);
                                                 if($6 != NULL) { updateLabel($$); } 
                                               } ; 
 
else: TK_PR_ELSE cmd_block ';'                 { $$ = $2;}
        | ';'                                  { $$ = NULL; } ;

while: TK_PR_WHILE '(' expressao ')' cmd_block { $$ = createNode("while"); addSon($$, $3); addSon($$, $5); } ; 



/*13 - As variáveis globais são declaradas pelo tipo seguido de uma lista composta de pelo menos um nome de variável (identificador) 
separadas por vírgula. O tipo pode ser int, float e bool. As declarações de variáveis são terminadas por ponto-e-vírgula.*/

declaracao_variavel_global: tipo lista_var ';' ;

lista_var: lista_var ',' TK_IDENTIFICADOR | TK_IDENTIFICADOR ;




/*Uso Geral*/

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL ;

literais: TK_LIT_INT 		{ $$ = createLexTypeNode($1); setType($$, TYPE_INT); } ;
literais: TK_LIT_FLOAT 		{ $$ = createLexTypeNode($1); setType($$, TYPE_FLOAT); } ;
literais: TK_LIT_TRUE 		{ $$ = createLexTypeNode($1); setType($$, TYPE_BOOL); } ;
literais: TK_LIT_FALSE 		{ $$ = createLexTypeNode($1); setType($$, TYPE_BOOL); } ;




/*14 - Expressões tem operandos e operadores. Os operandos podem ser(a)identificadores,(b)literaise (c)chamada de função. As expressões podem ser formadas recursivamente 
pelo emprego de operadores. Elas também permitem o uso de parênteses para forçar uma associatividade ou precedência diferente daquela tradicional.*/

/* operandos: literais | TK_IDENTIFICADOR | fun_call ; */
operandos: TK_IDENTIFICADOR 		{
                                        $$ = createLexTypeNode($1); 
                                        SymbolKey* key = mallocAndSetKeyName($1->value); 
                                        TableContent* content = findInTableStack(key, scope_stack_top, ID_SYMBOL);
                                        setType($$, content->type); 
                                    } ;

operandos: literais 				{ $$ = $1; } ;

operandos: fun_call  				{ $$ = $1; 

                                    } ;

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

expr3: expr3 operadoresPrecedencia4 expr4               { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);
                                                            if((type1!=TYPE_FLOAT && type1!=TYPE_INT) || (type2!=TYPE_FLOAT && type2!=TYPE_INT));
                                                                invalidSemanticOperation();   
                                                            setType($2, TYPE_BOOL); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            $$ = $2; 
                                                        } ;

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
