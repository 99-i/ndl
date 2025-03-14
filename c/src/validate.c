#include "validate.h"
#include "args.h"
#include "ast/ast.h"
#include "ast/program.h"
#include <stdio.h>

static void usage(void);

int validate(int argc, char **argv)
{
	struct program *prog;

	if (!argc)
	{
		usage();
		return 1;
	}

	const char *file = shift(&argc, &argv);

	printf("%s\n", file);

	ast_create_from_file(&prog, "");

	return 0;
}

static void usage(void)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage: ndl validate <file> \n");

	fprintf(stderr, "\n");
}
