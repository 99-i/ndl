#include "ast/ast.h"
#include "ast/node.h"
#include "frontend.h"
#include "postprocess.h"
#include "util.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

int ast_create_from_file(struct node **node, const char *file)
{
	yyscan_t scanner;
	YY_BUFFER_STATE state;

	if (yylex_init(&scanner))
	{
		printf("Failed to initialize the lexer.\n");
		return 1;
	}

	char *src;

	if (slurp_file(file, &src))
	{
		printf("File could not be read (%d): %s\n", errno, strerror(errno));
		return 1;
	}

	state = yy_scan_string(src, scanner);

	if (yyparse(node, scanner, file))
	{
		return 1;
	}

	yy_delete_buffer(state, scanner);

	yylex_destroy(scanner);

	free(src);

	return 0;
}
