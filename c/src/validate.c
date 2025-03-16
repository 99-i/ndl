#include "validate.h"
#include "args.h"
#include "ast/ast.h"
#include "ast/node.h"
#include "postprocess.h"

#include <stdio.h>

static void usage(void);

int validate(int argc, char **argv)
{
	if (!argc)
	{
		usage();
		return 1;
	}

	const char *file = shift(&argc, &argv);
	struct node *node;

	if (ast_create_from_file(&node, file))
		return 1;

	return 0;
}

static void usage(void)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage: ndl validate <file> \n");

	fprintf(stderr, "\n");
}
