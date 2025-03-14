#pragma once
#include "statement.h"

struct block
{
	struct statement *statements;
	int statements_size;
};

struct block *block_create(void);

void block_add_statement(struct block *block, struct statement *statement);
