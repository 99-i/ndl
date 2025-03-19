%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast/dims.h"
#include "lexer.h"
#include "ast/node.h"

void yyerror(YYLTYPE *yylloc, struct node **node, yyscan_t scanner, const char *filename, const char *msg);

%}

%code requires {
	typedef void* yyscan_t;
	#include "ast/dims.h"
}

%output "gen/parser.c"
%defines "gen/parser.h"

%define api.pure
%define parse.error verbose

%locations

%parse-param { struct node **node }
%parse-param { yyscan_t scanner }
%parse-param { const char *filename }

%lex-param   { yyscan_t scanner }

%union
{
    int ival;
    float fval;
    char *sval;
	struct node *node;
	struct dims dims;
}

%token NETWORK
%token LBRACKET RBRACKET
%token LBRACE RBRACE
%token SEMICOLON
%token TENSOR
%token EQUALS
%token COMMA
%token INVALID

%token <ival> INT
%token <fval> FLOAT
%token <sval> IDENTIFIER

%type <node> root
%type <node> toplevel_statement 
%type <node> network_definition
%type <node> block
%type <node> block_statements
%type <node> statement
%type <node> layer
%type <node> tensor_statement
%type <dims> tensor_dims;
%type <dims> tensor_inner_dims;
%type <ival> tensor_dim;

%%

root:
	{
		*node = node_create_root();
		$$ = *node; 
		$$->loc.line = 1;
		$$->loc.col = 1;
		$$->root.filename = strdup(filename);
	}
	| root toplevel_statement
	{ 
		node_add_child_node($1, $2);
		$$ = $1;
		$2->loc.line = @2.first_line;
		$2->loc.col = @2.first_column;
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

		free($$->children);
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
		// temporary node that we use to store the statements.
		$$ = node_create();
	}
	| block_statements statement
	{
		node_add_child_node($1, $2);
		$$ = $1;
		$2->loc.line = @2.first_line + 1;
		$2->loc.col = @2.first_column;
	}
	;

statement:
	layer SEMICOLON
	| IDENTIFIER EQUALS layer SEMICOLON
	{
		$$ = $3;
		$$->statement.name = $1;
	}
	| tensor_statement SEMICOLON
	| IDENTIFIER EQUALS tensor_statement SEMICOLON
	{
		$$ = $3;
		$$->tensor.name = $1;
	}
	;

layer:
	IDENTIFIER
	{
		$$ = node_create();
		$$->type = NODE_STATEMENT;
		$$->statement.layer_type = $1;
		$$->statement.name = NULL;
		$$->statement.hypers = NULL;
		$$->statement.output_dims = NULL;
	}
	;

tensor_statement:
	TENSOR tensor_dims
	{
		$$ = node_create();
		$$->type = NODE_TENSOR;
		$$->tensor.dims = $2;
		$$->tensor.name = NULL;
	}
	;

tensor_dims:
	LBRACKET tensor_inner_dims RBRACKET
	{
		$$ = $2;
	}
	;

tensor_inner_dims:
	tensor_dim
	{
		$$ = dims_create();
		dims_add_dim(&$$, $1);
	}
	| tensor_inner_dims COMMA tensor_dim
	{
		dims_add_dim(&$1, $3);
		$$ = $1;
	}

tensor_dim:
	INT
	;

%%

void yyerror(YYLTYPE *yylloc, struct node **node, yyscan_t scanner, const char *filename, const char *msg)
{
	struct location loc;
	loc.line = yylloc->first_line + 1;
	loc.col = yylloc->first_column;

	root_add_err(*node, msg, loc);
}
