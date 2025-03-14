%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "ast/program.h"
#include "ast/block.h"
#include "ast/statement.h"
#include "ast/network.h"

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
	struct block *block;
	struct statement *statement;
	struct network *network;
}

%token SEMICOLON NETWORK
%token LBRACKET RBRACKET
%token LBRACE RBRACE

%token <ival> INT
%token <fval> FLOAT
%token <sval> IDENTIFIER

%type <prog> program
%type <dec> declaration 
%type <dec> network_declaration
%type <block> block
%type <block> block_statements
%type <statement> statement



%%

program:
	{
		*prog = program_create();
		$$ = *prog; 
	}
	| program declaration
	{ 
		program_add_dec($1, $2);
		$$ = $1;
	}
	;

declaration:
	network_declaration
	{
		$$ = $1;
	}
	;

network_declaration:
	NETWORK IDENTIFIER block
	{
		$$ = network_create($2, $3);
	}
	;

block:
	LBRACE block_statements RBRACKET
	{
		$$ = $2;
	}
	;

block_statements:
	{
		$$ = block_create();
	}
	| block_statements statement
	{
		block_add_statement($1, $2);
		$$ = $1;		
	}
	;

statement:
	;
%%

