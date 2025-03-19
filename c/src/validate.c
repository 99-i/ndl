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

	// const char *file = shift(&argc, &argv);
	const char *file = "ex.ndl";

	struct node *node;

	if (ast_create_from_file(&node, file))
	{
		if (node->root.err)
		{
			fprintf(stderr, "%s", node->root.err_str);
			node_free(node);
		}
		return 1;
	}

	postprocess_ast(node);

	node_free(node);

	return 0;
}

static void usage(void)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage: ndl validate <file> \n");

	fprintf(stderr, "\n");
}
