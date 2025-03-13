#pragma once
#include <stdlib.h>

struct hyperparams
{

};

struct statement
{
	char *name; // NULL if unnamed
	char *layer_type; // ex dense, cnn_block
};

struct block
{
};

enum declaration_type 
{
	DEF_NETWORK
};

struct declaration
{
	enum declaration_type type;
};

struct program
{
	// TODO: use capacity
	struct declaration **decs;
	size_t decs_size;
};

struct program *create_program(void);
void program_add_dec(struct program *prog, struct declaration *dec);

struct declaration *create_network_declaration(char *name);
