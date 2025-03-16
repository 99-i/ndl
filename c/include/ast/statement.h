#pragma once
#include <stddef.h>

struct statement
{
	char *name; // NULL if unnamed
	char *layer_type; // ex dense, cnn_block
	struct hyperparams *hypers;
};
