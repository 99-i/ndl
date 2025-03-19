%{
#include "parser.h"
#include <stdio.h>
#include <string.h>

int lex_column = 1;

#define YY_USER_ACTION						\
{											\
	int orig_line = yylineno;				\
	int orig_col = lex_column;				\
    for (int i = 0; i < yyleng; i++) {		\
        if (yytext[i] == '\n') {			\
            lex_column = 1;					\
            yylineno++;						\
        } else {							\
            lex_column++;					\
        }									\
    }										\
    yylloc->first_line = orig_line;			\
    yylloc->first_column = orig_col;		\
    yylloc->last_line = yylineno;			\
    yylloc->last_column = lex_column - 1;	\
}

%}

%option outfile="gen/lexer.c" header-file="gen/lexer.h"

%option reentrant
%option bison-bridge
%option noyywrap

%option bison-locations

DIGIT      [0-9]+
FLOAT      [0-9]+(\.[0-9]+)?
IDENT      [a-zA-Z_][a-zA-Z0-9_]*
WHITESPACE [ \t\r\n]+

%%

"/*"([^*]|\*+[^*/])*\*+"/"   { } // block comments
"//".*                       { } // line comments

network { return NETWORK; }
tensor { return TENSOR; }
";" { return SEMICOLON; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"[" { return LBRACKET; }
"]" { return RBRACKET; }
"=" { return EQUALS; }
"," { return COMMA; }

{DIGIT}        { yylval->ival = atoi(yytext); return INT; }
{FLOAT}        { yylval->fval = atof(yytext); return FLOAT; }
{IDENT}        { yylval->sval = strdup(yytext); return IDENTIFIER; }
{WHITESPACE}   { }
.              { return INVALID; }

%%

