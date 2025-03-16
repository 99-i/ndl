#pragma once
#include <stddef.h>

enum hyperparam_type
{
	HYPERPARAM_FLOAT,
	HYPERPARAM_INT,
	HYPERPARAM_ATOM
};

struct hyperparam
{
	enum hyperparam_type type;
	union
	{
		float f;
		int i;
		char *atom;
	};
};

// for representing hyperparams in module/network definitions as well as being passed to modules
struct hyperparams
{
	struct hyperparam *params;
	size_t params_size;
	size_t params_capacity;
};

struct hyperparams *hyperparams_create(void);

void hyperparams_add_param(struct hyperparams* hyperparams, struct hyperparam param);
