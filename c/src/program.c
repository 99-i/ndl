#include "ast/program.h"
#include <stdlib.h>

struct program *program_create(void)
{

	struct program *prog = malloc(sizeof(*prog));
	prog->decs_size = 0;
	prog->decs = malloc(0);

	return prog;
}

void program_add_dec(struct program *prog, struct declaration *dec)
{
	prog->decs_size += 1;

	prog->decs = realloc(prog->decs, prog->decs_size * sizeof(struct declaration *));

	prog->decs[prog->decs_size - 1] = dec;
}

struct declaration *create_network_declaration(char *name)
{
}
