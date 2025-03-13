#include "ast.h"
#include "frontend.h"

int ast_create_from_file(struct program **prog, const char *src)
{
	yyscan_t scanner;
	YY_BUFFER_STATE state;

	if (yylex_init(&scanner))
	{
		printf("failed\n");
		return 1;
	}

	state = yy_scan_string("", scanner);

	if (yyparse(prog, scanner))
	{
		printf("failed\n");
		return 1;
	}

	yy_delete_buffer(state, scanner);

	yylex_destroy(scanner);

	return 0;
}
