#pragma once
#include <stddef.h>


struct statement
{
	char *name; // NULL if unnamed
	char *layer_type; // ex dense, cnn_block
	struct hyperparams *hypers;
};

struct statement *statement_create(char *name, char *layer_type);

struct hyperparams *hyperparams_create();
