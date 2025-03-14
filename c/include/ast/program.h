#pragma once
#include <stdlib.h>

struct program
{
	// TODO: use capacity
	struct declaration **decs;
	size_t decs_size;
};

struct program *program_create(void);
void program_add_dec(struct program *prog, struct declaration *dec);
