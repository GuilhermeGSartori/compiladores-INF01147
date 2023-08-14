%{
// Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703

#include <stdio.h>
#include "hash.h"

int yylex(void);
void yyerror (char const *s);
extern int get_line_number();
extern void *arvore;
Scope* scope_stack_top = NULL;
CmdILOC* command_list = NULL;
KeyList* key_list = NULL;
int local_offset = 0;
int global_offset = 0;
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
%type<node> operadoresUnariosNeg
%type<node> operadoresUnariosNot
%type<node> operadoresPrecedencia2Mult
%type<node> operadoresPrecedencia2Divi
%type<node> operadoresPrecedencia2Rest
%type<node> operadoresPrecedencia3Sum
%type<node> operadoresPrecedencia3Sub
%type<node> operadoresPrecedencia4LS
%type<node> operadoresPrecedencia4GT
%type<node> operadoresPrecedencia4LE
%type<node> operadoresPrecedencia4GE
%type<node> operadoresPrecedencia5EQ
%type<node> operadoresPrecedencia5NE
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
fecha_escopo: { scope_stack_top = popTable(scope_stack_top); }; 

programa: lista   { $1->code = command_list, arvore = $1; }
	|             { arvore = NULL; }
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

funcao: cabecalho TK_OC_MAP TK_PR_FLOAT corpo fecha_escopo { 
                                                                $$ = $1; addSon($$, $4); setType($$, TYPE_FLOAT);
                                                                SymbolKey* key = mallocAndSetKeyName($1->label);
                                                                TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL, get_line_number());
                                                                updateContentType(content, TYPE_FLOAT); 
                                                           } ;

funcao: cabecalho TK_OC_MAP TK_PR_INT corpo fecha_escopo   { 
                                                                $$ = $1; addSon($$, $4); setType($$, TYPE_INT);
                                                                SymbolKey* key = mallocAndSetKeyName($1->label);
                                                                TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL, get_line_number());
                                                                updateContentType(content, TYPE_INT); 
                                                           } ;

funcao: cabecalho TK_OC_MAP TK_PR_BOOL corpo fecha_escopo  { 
                                                                $$ = $1; addSon($$, $4); setType($$, TYPE_BOOL);
                                                                SymbolKey* key = mallocAndSetKeyName($1->label);
                                                                TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL, get_line_number());
                                                                updateContentType(content, TYPE_BOOL); 
                                                           } ;

                                                           

/*3 - O cabeçalho consiste no nome da função, uma lista de parâmetros, o operador composto TK_OC_MAP e o tipo de retorno*/

cabecalho: fun_name abre_escopo parametros { 
                                               $$ = $1;
                                               SymbolKey* key = mallocAndSetKeyName($1->label);
                                               TableContent* content = findInTable(key, scope_stack_top->previous_scope);
                                               setParametersList(content, key_list); 
                                               key_list = NULL;
                                           } ; 
fun_name: TK_IDENTIFICADOR {
                                $$ = createLexTypeNode($1); 
                                SymbolKey* key = mallocAndSetKeyName($1->value);
                                TableContent* content = newContent(key, $1->value, get_line_number(), FUN_SYMBOL, TYPE_UNDEFINED); 
                                addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                           } ;

parametros: '(' lista_params ')' ;



/*4 - A lista de parâmetros é dada entre parênteses e é composta por zero ou mais parâmetros de entrada, separados por vírgula.*/

lista_params: um_ou_mais_param | ;
um_ou_mais_param: um_ou_mais_param ',' param | param ;



/*5 - Cada parâmetro é definido pelo seu tipo e nome.*/

param: TK_PR_BOOL TK_IDENTIFICADOR   { 
                                         SymbolKey* key = mallocAndSetKeyName($2->value);
                                         TableContent* content = newContent(key, $2->value, get_line_number(), ID_SYMBOL, TYPE_BOOL); 
                                         addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                         addKeyInList(key->key_name, &key_list, TYPE_BOOL, NULL);
                                     } ;

param: TK_PR_INT TK_IDENTIFICADOR    { 
                                         SymbolKey* key = mallocAndSetKeyName($2->value);
                                         TableContent* content = newContent(key, $2->value, get_line_number(), ID_SYMBOL, TYPE_INT); 
                                         addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                         addKeyInList(key->key_name, &key_list, TYPE_INT, NULL);
                                     } ;

param: TK_PR_FLOAT TK_IDENTIFICADOR  { 
                                         SymbolKey* key = mallocAndSetKeyName($2->value);
                                         TableContent* content = newContent(key, $2->value, get_line_number(), ID_SYMBOL, TYPE_FLOAT); 
                                         addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                         addKeyInList(key->key_name, &key_list, TYPE_FLOAT, NULL);
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

cmd_list: abre_escopo cmd_block fecha_escopo ';'    { $$ = $2; } ;
cmd_list: var_local ';'                             { $$ = $1; } ; 
cmd_list: atrib ';'                                 { $$ = $1; } ; 
cmd_list: if                                        { $$ = $1; } ;
cmd_list: while ';'                                 { $$ = $1; } ; 
cmd_list: return ';'                                { $$ = $1; } ; 
cmd_list: fun_call ';'                              { $$ = $1; } ;



/*8 - Declaração de Variável Local: Consiste no tipo da variável seguido de uma lista composta de pelo menos um nome 
de variável (identificador) separadas por vírgula. Os tipos podem ser aqueles descritos na seção sobre variáveis globais. 
Uma variável local pode ser opcionalmente inicializada caso sua declaração seja seguida do operador composto TK_OC_LE e de um 
literal.*/

var_local: TK_PR_BOOL lista_local_var	{
                                            $$ = $2; 
                                            if($2 != NULL) {
                                                Node *leaf_attr = $2;
                                                Node *id = $2->sons[0];
                                                setType($$, TYPE_BOOL);
                                                setType(id, TYPE_BOOL);
                                                while(leaf_attr->n_sons == 3) {
                                                    leaf_attr = leaf_attr->sons[2];
                                                    id = leaf_attr->sons[0];
                                                    setType(leaf_attr, TYPE_BOOL);
                                                    setType(id, TYPE_BOOL);
                                                }
                                            }
                                            while(key_list != NULL) {                             
                                                SymbolKey* key = mallocAndSetKeyName(key_list->key.key_name);                                               
                                                TableContent* content = newContent(key, key_list->value, get_line_number(), ID_SYMBOL, TYPE_BOOL); 
                                                addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                                key_list = key_list->next;
                                            }
                                            key_list = NULL;
                                        } ; 

var_local: TK_PR_INT lista_local_var	{
                                            $$ = $2; 
                                            if($2 != NULL) {
                                                Node *leaf_attr = $2;
                                                Node *id = $2->sons[0];
                                                setType($$, TYPE_INT);
                                                setType(id, TYPE_INT);
                                                while(leaf_attr->n_sons == 3) {
                                                    leaf_attr = leaf_attr->sons[2];
                                                    id = leaf_attr->sons[0];
                                                    setType(leaf_attr, TYPE_INT);
                                                    setType(id, TYPE_INT);
                                                }
                                            }
                                            while(key_list != NULL) {                             
                                                SymbolKey* key = mallocAndSetKeyName(key_list->key.key_name);                                                
                                                TableContent* content = newContent(key, key_list->value, get_line_number(), ID_SYMBOL, TYPE_INT); 
                                                addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                                key_list = key_list->next;
                                            }
                                            key_list = NULL;
                                        } ; 

var_local: TK_PR_FLOAT lista_local_var	{
                                            $$ = $2; 
                                            if($2 != NULL) {
                                                Node *leaf_attr = $2;
                                                Node *id = $2->sons[0];
                                                setType($$, TYPE_FLOAT);
                                                setType(id, TYPE_FLOAT);
                                                while(leaf_attr->n_sons == 3) {
                                                    leaf_attr = leaf_attr->sons[2];
                                                    id = leaf_attr->sons[0];
                                                    setType(leaf_attr, TYPE_FLOAT);
                                                    setType(id, TYPE_FLOAT);
                                                }
                                            }
                                            while(key_list != NULL) {                             
                                                SymbolKey* key = mallocAndSetKeyName(key_list->key.key_name);                                                
                                                TableContent* content = newContent(key, key_list->value, get_line_number(), ID_SYMBOL, TYPE_FLOAT); 
                                                addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                                key_list = key_list->next;
                                            }
                                            key_list = NULL;
                                        } ; 


lista_local_var: TK_IDENTIFICADOR ',' lista_local_var	{ 
                                                            if($3 == NULL) { 
                                                                $$ = NULL;
                                                            } else { 
                                                                $$ = $3;
                                                            } 
                                                            addKeyInList($1->value, &key_list, TYPE_UNDEFINED, NULL);
                                                        }

			   | init ',' lista_local_var               { addSon($1, $3); $$ = $1; } 
			   
               | TK_IDENTIFICADOR 	                    { $$ = NULL; addKeyInList($1->value, &key_list, TYPE_UNDEFINED, NULL); }
			   
               | init 			                        { $$ = $1; }
			   
               ;

init: TK_IDENTIFICADOR TK_OC_LE literais {
                                             $$ = createNode("<="); 
                                             addSon($$, createLexTypeNode($1)); 
                                             addSon($$, $3);
                                             addKeyInList($1->value, &key_list, $3->type, $3->lexical_value->value);
                                         } ; 



/*9 - Comando de Atribuição: O comando de atribuição consiste em um identificador seguido pelo caractere de igualdade seguido 
por uma expressão*/

atrib: TK_IDENTIFICADOR '=' expressao {
                                          SymbolKey* key = mallocAndSetKeyName($1->value);
                                          TableContent* content = findInTableStack(key, scope_stack_top, ID_SYMBOL, get_line_number());                                      
                                          $$ = createNode("="); 
                                          if(content->type == TYPE_INT) {
                                              // mais pra frente tem que ver se codigo eh NULL, se for, ignora e pega proximo/tem que ver se exp da direita eh int?
                                              //setTemp($$, tempGenerator()); isso aqui eh usado para algo? tipo if(a = 1) e tals... =  tem temp? avaliacao sla
                                              CmdILOC* cmd = createCmd("storeAI", $3->temp, content->base, content->offset, MOST_RIGHT);
                                              setCode($$, concatCode($3->code, cmd)->cmd);
                                              //printf("\n%s\n", $$->code->cmd); // setar como code

                                              // como vamos subir o codigo ate a raiz?
                                              cmdToList(&command_list, $$->code);
                                          }    
                                          Node* id = createLexTypeNode($1);
                                          setType(id, content->type);
                                          addSon($$, id); 
                                          addSon($$, $3); 
                                          setType($$, content->type);
                                      } ;



/*10 - Chamada de Função: Uma chamada de função consiste no nome da função, seguida de argumentos entre parênteses separados 
por vírgula. Um argumento pode ser uma expressão.*/

fun_call: TK_IDENTIFICADOR '(' lista_args ')' { 
                                                  $$ = createLexTypeNode($1); 
                                                  updateLabel($$); 
                                                  addSon($$, $3); 
                                                  SymbolKey* key = mallocAndSetKeyName($1->value); 
                                                  TableContent* content = findInTableStack(key, scope_stack_top, FUN_SYMBOL, get_line_number());
                                                  setType($$, content->type); 
                                                  //checkParameters(content->parameters, key_list);
                                                  // tem que procurar os parametros na tabela e setar valor?
                                                  // nao precisa, pegar o conteúdo de fato da tabela e setar o valor fica pra depois
                                                  key_list = NULL;
                                              } ; 

lista_args: um_ou_mais_args 	{ $$ = $1; } 
		    | 		            { $$ = NULL; }
		    ;

um_ou_mais_args: args ',' um_ou_mais_args 	{ addSon($1, $3); $$ = $1; }  
                                                                          
			     | args 	                { $$ = $1; }
			     ;

args: expressao 				{
                                    $$ = $1; 
                                    addKeyInList($1->label, &key_list, $1->type, NULL); //so importa tipo!
                                } ;


/*11 - Comando de Retorno: Trata-se do token return seguido de uma expressão. */

return: TK_PR_RETURN expressao  	{ $$ = createNode("return"); addSon($$, $2); int type = getType($2); setType($$, type); } ;



/*12 - Comandos de Controle de Fluxo: A linguagem possui uma construção condicional e uma iterativa para controle estruturado de 
fluxo. A condicional consiste no token if seguido de uma expressão entre parênteses e então por um bloco de comandos 
obrigatório. O else, sendo opcional, é seguido de um bloco de comandos, obrigatório caso o else seja empregado. Temos apenas 
uma construção de repetição que é o token while seguida de uma expressão entre parênteses e de um bloco de comandos.*/

if: TK_PR_IF '(' expressao ')' abre_escopo cmd_block fecha_escopo else  { 
                                                                            $$ = createNode("if"); addSon($$, $3); addSon($$, $6); addSon($$, $8);
                                                                            if($8 != NULL) { updateLabel($$); } 
                                                                            setType($$, getType($3));
																			setTemp($3, tempGenerator());
																			//fazer um load da expressao no R1?
																			//gerar label? se gerar concatenar com :
																			CmdILOC* cmd = createCmd("cbr", $3->temp, label_do_if_true, label_do_else, CBR);
                                                                        } ; 
 
else: TK_PR_ELSE abre_escopo cmd_block fecha_escopo ';'                 { $$ = $3;}
                                                  | ';'                 { $$ = NULL; } ;

while: TK_PR_WHILE '(' expressao ')' abre_escopo cmd_block fecha_escopo { $$ = createNode("while"); addSon($$, $3); addSon($$, $6); setType($$, getType($3)); } ; 



/*13 - As variáveis globais são declaradas pelo tipo seguido de uma lista composta de pelo menos um nome de variável (identificador) 
separadas por vírgula. O tipo pode ser int, float e bool. As declarações de variáveis são terminadas por ponto-e-vírgula.*/

declaracao_variavel_global: TK_PR_BOOL lista_var ';' {   
                                                         while(key_list != NULL) {                             
                                                             SymbolKey* key = mallocAndSetKeyName(key_list->key.key_name);
                                                             TableContent* content = newContent(key, "0", get_line_number(), ID_SYMBOL, TYPE_BOOL); 
                                                             addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                                             key_list = key_list->next;
                                                         }
                                                         key_list = NULL;
                                                     } ;


declaracao_variavel_global: TK_PR_INT lista_var ';' {   
                                                         while(key_list != NULL) {                             
                                                             SymbolKey* key = mallocAndSetKeyName(key_list->key.key_name);
                                                             TableContent* content = newContent(key, "0", get_line_number(), ID_SYMBOL, TYPE_INT); 
                                                             addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                                             key_list = key_list->next;
                                                         }
                                                         key_list = NULL;
                                                     } ;


declaracao_variavel_global: TK_PR_FLOAT lista_var ';' {   
                                                         while(key_list != NULL) {                             
                                                             SymbolKey* key = mallocAndSetKeyName(key_list->key.key_name);
                                                             TableContent* content = newContent(key, "0", get_line_number(), ID_SYMBOL, TYPE_FLOAT); 
                                                             addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
                                                             key_list = key_list->next;                                                              
                                                         }
                                                         key_list = NULL;
                                                      } ;


lista_var: lista_var ',' TK_IDENTIFICADOR { addKeyInList($3->value, &key_list, TYPE_UNDEFINED, NULL); } ;
lista_var: TK_IDENTIFICADOR { addKeyInList($1->value, &key_list, TYPE_UNDEFINED, NULL); } ;




/*Uso Geral*/

literais: TK_LIT_INT 		{ $$ = createLexTypeNode($1);
							  SymbolKey* key = mallocAndSetKeyName($1->value);
							  TableContent* content = newContent(key, $1->value, get_line_number(), LIT_SYMBOL, TYPE_INT);
							  addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
							  setType($$, TYPE_INT); 
                              setTemp($$, tempGenerator()); 
                              //char ILOC[CMD_MAX_SIZE] = "loadI";
                              CmdILOC* cmd = createCmd("loadI", content->value, $$->temp, NULL, MOST_RIGHT);
                              setCode($$, cmd->cmd);
                              /*printf("\n%s\n", $$->code->cmd);*/ } ;


literais: TK_LIT_FLOAT 		{ $$ = createLexTypeNode($1);
							  SymbolKey* key = mallocAndSetKeyName($1->value);
							  TableContent* content = newContent(key, $1->value, get_line_number(), LIT_SYMBOL, TYPE_FLOAT);
							  addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
							  setType($$, TYPE_FLOAT); } ;


literais: TK_LIT_TRUE 		{ $$ = createLexTypeNode($1);
							  SymbolKey* key = mallocAndSetKeyName($1->value);
							  TableContent* content = newContent(key, $1->value, get_line_number(), LIT_SYMBOL, TYPE_BOOL);
							  addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
							  setType($$, TYPE_BOOL); } ;


literais: TK_LIT_FALSE 		{ $$ = createLexTypeNode($1);
							  SymbolKey* key = mallocAndSetKeyName($1->value);
							  TableContent* content = newContent(key, $1->value, get_line_number(), LIT_SYMBOL, TYPE_BOOL);
							  addInTable(content, scope_stack_top, get_line_number(), &local_offset, &global_offset);
							  setType($$, TYPE_BOOL); } ;




/*14 - Expressões tem operandos e operadores. Os operandos podem ser(a)identificadores,(b)literaise (c)chamada de função. As expressões podem ser formadas recursivamente 
pelo emprego de operadores. Elas também permitem o uso de parênteses para forçar uma associatividade ou precedência diferente daquela tradicional.*/

operandos: TK_IDENTIFICADOR 		{
                                        $$ = createLexTypeNode($1); 
                                        SymbolKey* key = mallocAndSetKeyName($1->value); 
                                        TableContent* content = findInTableStack(key, scope_stack_top, ID_SYMBOL, get_line_number());
                                        if(content->type == TYPE_INT) {
                                            // aqui montaria codigo
                                            // mais pra frente tem que ver se codigo eh NULL, se for, ignora e pega proximo
                                            setTemp($$, tempGenerator());
                                            //char ILOC[CMD_MAX_SIZE] = "loadAI";
                                            CmdILOC* cmd = createCmd("loadAI", content->base, content->offset, $$->temp, MOST_LEFT);
                                            setCode($$, cmd->cmd);
                                            //printf("\n%s\n", $$->code->cmd); // setar como code
                                            //printf("\n\n\nOPERANDO:\n");
                                            //printf("Base: %d\n", content->base);
                                            //printf("Offset: %d\n", content->offset);
                                        }
                                        setType($$, content->type); 
                                    } ;

operandos: literais 				{ $$ = $1; } ;

operandos: fun_call  				{ $$ = $1; } ;

/* operadoresUnarios: '-' | '!' ; */
operadoresUnariosNeg: '-'    			{ $$ = createNode("-"); } ;
operadoresUnariosNot: '!' 				{ $$ = createNode("!"); } ;

/* operadoresPrecedencia2: '*' | '/' | '%' ; */
operadoresPrecedencia2Mult: '*' 		{ $$ = createNode("*"); } ;
operadoresPrecedencia2Divi: '/' 		{ $$ = createNode("/"); } ;
operadoresPrecedencia2Rest: '%' 		{ $$ = createNode("%"); } ;

/* operadoresPrecedencia3: '+' | '-' ; */
operadoresPrecedencia3Sum: '+'  		{ $$ = createNode("+"); } ;
operadoresPrecedencia3Sub: '-'  		{ $$ = createNode("-"); } ;

/*operadoresPrecedencia4: '<' | '>' | TK_OC_LE | TK_OC_GE ;*/
operadoresPrecedencia4LS: '<'  		{ $$ = createNode("<"); } ;
operadoresPrecedencia4GT: '>'  		{ $$ = createNode(">"); } ;
operadoresPrecedencia4LE: TK_OC_LE 	{ $$ = createNode("<="); }; 
operadoresPrecedencia4GE: TK_OC_GE 	{ $$ = createNode(">="); } ;

/*operadoresPrecedencia5: TK_OC_EQ | TK_OC_NE ;*/
operadoresPrecedencia5EQ: TK_OC_EQ 	{ $$ = createNode("=="); } ;
operadoresPrecedencia5NE: TK_OC_NE 	{ $$ = createNode("!="); } ;

operadoresPrecedencia6: TK_OC_AND 	{ $$ = createNode("&"); } ;

operadoresPrecedencia7: TK_OC_OR 	{ $$ = createNode("|"); } ;


expressao: expr1                                        { $$ = $1; } ;

expressao: expressao operadoresPrecedencia7 expr1       { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);															
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("or", $1->temp, $3->temp, $2->temp, MOST_LEFT);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd);
                                                            $$ = $2;
                                                        } ;

expr1: expr2                                            { $$ = $1; } ;

expr1: expr1 operadoresPrecedencia6 expr2               { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                              
                                                            setType($2, inferType(type1, type2));
                                                            addSon($2, $1); 
                                                            addSon($2, $3);
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("and", $1->temp, $3->temp, $2->temp, MOST_LEFT);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;
                                                        } ;

expr2: expr3 	                                        { $$ = $1; } ;

expr2: expr2 operadoresPrecedencia5EQ expr3             { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                      
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("cmp_EQ", $1->temp, $3->temp, $2->temp, CONTROL);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;                                                           
                                                        } ;

expr2: expr2 operadoresPrecedencia5NE expr3             { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                      
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("cmp_NE", $1->temp, $3->temp, $2->temp, CONTROL);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;                                                           
                                                        } ;

expr3: expr4 		                                    { $$ = $1; } ;

expr3: expr3 operadoresPrecedencia4LS expr4             { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                               
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("cmp_LT", $1->temp, $3->temp, $2->temp, CONTROL);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;
                                                        } ;

expr3: expr3 operadoresPrecedencia4GT expr4             { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                               
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("cmp_GT", $1->temp, $3->temp, $2->temp, CONTROL);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;
                                                        } ;

expr3: expr3 operadoresPrecedencia4LE expr4             { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                               
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("cmp_LE", $1->temp, $3->temp, $2->temp, CONTROL);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;
                                                        } ;                                                        

expr3: expr3 operadoresPrecedencia4GE expr4             { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);                                                               
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("cmp_GE", $1->temp, $3->temp, $2->temp, CONTROL);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); 
                                                            $$ = $2;
                                                        } ;

expr4: expr5                                            { $$ = $1; } ; 

expr4: expr4 operadoresPrecedencia3Sum expr5            {
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);
                                                            setType($2, inferType(type1, type2));
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            // if $1 and $3 temp are not NULL
                                                            setTemp($2, tempGenerator());
                                                            CmdILOC* cmd = createCmd("add", $1->temp, $3->temp, $2->temp, MOST_LEFT);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd);
                                                            $$ = $2;
                                                        } ;

expr4: expr4 operadoresPrecedencia3Sub expr5            {
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);
                                                            setType($2, inferType(type1, type2));
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            //char ILOC[CMD_MAX_SIZE] = "sub";
                                                            CmdILOC* cmd = createCmd("sub", $1->temp, $3->temp, $2->temp, MOST_LEFT);
                                                            //setCode($2, cmd->cmd);
                                                            //CmdILOC* temporary = concatCode($1->code, $3->code);
                                                            //strcpy(temporary, concatCode($1->code->cmd, $3->code->cmd));
                                                            //temporary = concatCode(concatCode($1->code, $->code), cmd);
                                                            //setCode($2, temporary->cmd);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); // setar como code
                                                            $$ = $2;
                                                        } ;

expr5: expr6 	                                        { $$ = $1; } ;

expr5: expr5 operadoresPrecedencia2Mult expr6           { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            //char ILOC[CMD_MAX_SIZE] = "mult";
                                                            CmdILOC* cmd = createCmd("mult", $1->temp, $3->temp, $2->temp, MOST_LEFT);
                                                            //CmdILOC* temporary = concatCode($1->code, $3->code);
                                                            //strcpy(temporary, concatCode($1->code->cmd, $3->code->cmd));
                                                            //temporary = concatCode(concatCode($1->code, $->code), cmd);
                                                            //setCode($2, temporary->cmd);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); // setar como code
                                                            $$ = $2;
                                                        } ;
                                                
expr5: expr5 operadoresPrecedencia2Divi expr6           { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            setTemp($2, tempGenerator());
                                                            //char ILOC[CMD_MAX_SIZE] = "divi";
                                                            CmdILOC* cmd = createCmd("divi", $1->temp, $3->temp, $2->temp, MOST_LEFT);
                                                            //CmdILOC* temporary = concatCode($1->code, $3->code);
                                                            //strcpy(temporary, concatCode($1->code->cmd, $3->code->cmd));
                                                            //temporary = concatCode(concatCode($1->code, $->code), cmd);
                                                            //setCode($2, temporary->cmd);
                                                            setCode($2, concatCode(concatCode($1->code, $3->code), cmd)->cmd);
                                                            //printf("\n%s\n", $2->code->cmd); // setar como code
                                                            $$ = $2;
                                                        } ;

expr5: expr5 operadoresPrecedencia2Rest expr6           { 
                                                            int type1 = getType($1);
                                                            int type2 = getType($3);
                                                            setType($2, inferType(type1, type2)); 
                                                            addSon($2, $1); 
                                                            addSon($2, $3); 
                                                            $$ = $2;
                                                        } ;

expr6: expr7 	                                        { $$ = $1; } ;

expr6: operadoresUnariosNeg expr7 		                {  // nao precisa traduzir para ILOC
                                                            addSon($1, $2); 
                                                            $$ = $1;
                                                            setType($1, getType($2)); 
                                                        } ; 
                                                        
expr6: operadoresUnariosNot expr7                       { 
                                                            addSon($1, $2); 
                                                            $$ = $1;                                                            
                                                            setType($1, getType($2)); 
                                                        } ; 

expr7: operandos 	                                    { $$ = $1; } ;
expr7: '(' expressao ')'                                { $$ = $2; } ;


%%

void yyerror (char const *s) {
    printf("Erro sintatico na linha %d.\n%s\n", get_line_number(), s);
}
