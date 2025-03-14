#include "args.h"
#include "validate.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void usage(void);

int main(int argc, char **argv)
{
	shift(&argc, &argv);

	if (argc <= 0)
	{
		usage();
		return 1;
	}

	const char *command = shift(&argc, &argv);

	if (!strcmp("validate", command))
	{
		validate(argc, argv);
	}
	else
	{
		usage();
		return 1;
	}

	return 0;
}

static void usage(void)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage: ndl <command> [<args>] \n");
	fprintf(stderr, "This is a list of available commands:\n\n");

	fprintf(stderr, "validate - validate an NDL file for syntax and semantic errors\n");

	fprintf(stderr, "\n");
}
