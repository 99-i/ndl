%{
#include "parser.h"
#include "ast/program.h"

#include <stdio.h>

%}

%option outfile="gen/lexer.c" header-file="gen/lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge


DIGIT      [0-9]+
FLOAT      [0-9]+(\.[0-9]+)?
IDENT      [a-zA-Z_][a-zA-Z0-9_]*
WHITESPACE [ \t\r\n]+

%%

network { return NETWORK; }
; { return SEMICOLON; }
{ { return LBRACE; }
} { return RBRACE; }
\[ { return LBRACKET; }
] { return RBRACKET; }

{DIGIT}        { yylval->ival = atoi(yytext); return INT; }
{FLOAT}        { yylval->fval = atof(yytext); return FLOAT; }
{IDENT}        { yylval->sval = strdup(yytext); return IDENTIFIER; }
{WHITESPACE}   { /* Ignore whitespace */ }
.              { printf("Unexpected character: %c\n", yytext[0]); }

%%

int yyerror(struct program **prog, yyscan_t scanner, const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
	return 0;
}
