%{
  #include<stdio.h>
  #include "tokens.h"
%}

%option noyywrap
%option yylineno

%s ML_COMMENT

carac_espec [-!*/%+<>{}()=,;]
digito [0-9]
letra [a-z]

%%

int 		{ return TK_PR_INT; }
float 		{ return TK_PR_FLOAT; }
bool 		{ return TK_PR_BOOL; }
if 			{ return TK_PR_IF; }
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

{digito}+ 	{ return TK_LIT_INT; }
{digito}*.{digito}+ { return TK_LIT_FLOAT; }
"true" 		{ return TK_LIT_TRUE; }
"false" 	{ return TK_LIT_FALSE; }
({letra}|_)+ 	{ return TK_IDENTIFICADOR; }
{carac_espec}   { return yytext[0]; }

[ \t\r\n]       { }
"//.*"          { }

<INITIAL>"/*"   { BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/" { BEGIN(INITIAL); }
<ML_COMMENT>[.\n]+ { }

.               { return TK_ERRO; }

%%

int get_line_number() {
  //printf("%d", lineno);
  return yylineno;
}
