%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "program.h"

int yyerror(struct program **prog, yyscan_t scanner, const char *s);

%}


%code requires {
  typedef void* yyscan_t;
}

%output "gen/parser.c"
%defines "gen/parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { struct program **prog }
%parse-param { yyscan_t scanner }

%union {
    int ival;
    float fval;
    char *sval;
	struct program *prog;
	struct declaration *dec;
}

%token SEMICOLON NETWORK
%token LBRACKET RBRACKET

%token <ival> INT
%token <fval> FLOAT
%token <sval> IDENTIFIER

%type <prog> program
%type <dec> statement 
%type <dec> network_declaration

%%

program:
	   { *prog = create_program();
         $$ = *prog; 
	   }
		| program statement { 
			program_add_dec($1, $2);
			$$ = $1;
		}
		;

statement:
		network_declaration { $$ = $1; }

network_declaration:
		NETWORK IDENTIFIER {
			$$ = create_network_declaration($2);
		}


%%

