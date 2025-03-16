%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "ast/node.h"

void yyerror(YYLTYPE *yylloc, struct node **node, yyscan_t scanner, const char *msg);

%}

%code requires {
  typedef void* yyscan_t;
}

%output "gen/parser.c"
%defines "gen/parser.h"

%define api.pure
%define parse.error verbose

%locations

%parse-param { struct node **node }
%parse-param { yyscan_t scanner }

%lex-param   { yyscan_t scanner }

%union
{
    int ival;
    float fval;
    char *sval;
	struct node *node;
}

%token SEMICOLON NETWORK
%token LBRACKET RBRACKET
%token LBRACE RBRACE

%token <ival> INT
%token <fval> FLOAT
%token <sval> IDENTIFIER

%type <node> root
%type <node> toplevel_statement 
%type <node> network_definition
%type <node> block
%type <node> block_statements
%type <node> statement

%%

root:
	{
		*node = node_create_root();
		$$ = *node; 
	}
	| root toplevel_statement
	{ 
		node_add_child_node($1, $2);
		$$ = $1;
	}
	| root error toplevel_statement
	{
		yyerrok;
	}
	;

toplevel_statement:
	network_definition
	;

network_definition:
	NETWORK IDENTIFIER block
	{
		$$ = node_create();

		$$->type = NODE_NETWORK_DEFINITION;
		$$->network.network_name = $2;

		$$->children = $3->children;
		$$->children_size = $3->children_size;

		// don't call node_free because we only used the block node as a placeholder to hold children and children_size, which we still need.
		free($3);
	}
	;

block:
	LBRACE block_statements RBRACE
	{
		$$ = $2;
	}
	;

block_statements:
	{
		$$ = node_create();
	}
	| block_statements statement
	{
		node_add_child_node($1, $2);
		$$ = $1;		
	}
	| block_statements error statement
	{
		yyerrok;
	}
	;

statement:
	IDENTIFIER
	{
		$$ = node_create();
		$$->type = NODE_STATEMENT;
		$$->statement.name = $1;
	}
	;
%%

void yyerror(YYLTYPE *yylloc, struct node **node, yyscan_t scanner, const char *msg)
{
	struct location loc;
	loc.line = yylloc->first_line;
	loc.col = yylloc->first_column;

	root_add_err(*node, msg, loc);
}
