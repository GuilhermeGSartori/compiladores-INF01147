%{
  // Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
  #include "parser.tab.h"
%}

%option noyywrap
%option yylineno

%x ML_COMMENT

carac_espec [-!*/%+<>{}()=,;]
digito [0-9]
letra [a-z]

%%

int 		{ return TK_PR_INT; }
float 		{ return TK_PR_FLOAT; }
bool 		{ return TK_PR_BOOL; }
if 		{ return TK_PR_IF; }
else 		{ return TK_PR_ELSE; }
while 		{ return TK_PR_WHILE; }
return 		{ return TK_PR_RETURN; }

"<=" 		{ return TK_OC_LE; }
">=" 		{ return TK_OC_GE; }
"==" 		{ return TK_OC_EQ; }
"!=" 		{ return TK_OC_NE; }
"&"  		{ return TK_OC_AND; }
"|"  		{ return TK_OC_OR; }
"->" 		{ return TK_OC_MAP; }
 
 /* Terminais (literal e identificador) que vão efetivamente para a árvore são "empacotados" em LexType */ 
{digito}+ 	{ yylval.valor_lexico = createLexType(yylineno, literal, strdup(yytext)); return TK_LIT_INT; }
{digito}*"."{digito}+ { yylval.valor_lexico = createLexType(yylineno, literal, strdup(yytext)); return TK_LIT_FLOAT; }
"true" 		{ yylval.valor_lexico = createLexType(yylineno, literal, strdup(yytext)); return TK_LIT_TRUE; }
"false" 	{ yylval.valor_lexico = createLexType(yylineno, literal, strdup(yytext)); return TK_LIT_FALSE; }
({letra}|_)+ 	{ yylval.valor_lexico = createLexType(yylineno, identificador, strdup(yytext)); return TK_IDENTIFICADOR; }

{carac_espec}   { return yytext[0]; }

[ \t\r\n]       { }
"//".*          { }

<INITIAL>"/*".*   { BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/"  { BEGIN(INITIAL); }
<ML_COMMENT>.     { }
<ML_COMMENT>[ \t\r\n] {}

.               { return TK_ERRO; }

%%

int get_line_number() {
  return yylineno;
}
