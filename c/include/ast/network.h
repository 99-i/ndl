#pragma once
#include "block.h"

struct network_definition
{
	char *network_name;
	struct block *statements;
};

struct declaration *network_create(char *network_name, struct block *statements);
