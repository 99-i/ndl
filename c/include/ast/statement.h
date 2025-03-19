#pragma once
#include "ast/dims.h"
#include "hyperparams.h"
#include <stddef.h>

struct statement
{
	char *name; // NULL if unnamed
	char *layer_type; // ex dense, cnn_block
	struct hyperparams *hypers;
	struct dims *output_dims; // populated after ast generation.
};
