#include "ast/hyperparams.h"
#include <stdlib.h>

struct hyperparams *hyperparams_create(void)
{
	struct hyperparams *hyperparams = malloc(sizeof(*hyperparams));

	hyperparams->params_size = 0;
	hyperparams->params_capacity = 4;
	hyperparams->params = malloc(hyperparams->params_capacity * sizeof(struct hyperparam));

	return hyperparams;
}

void hyperparams_add_param(struct hyperparams *hyperparams, struct hyperparam param)
{
	if (hyperparams->params_size == hyperparams->params_capacity)
	{
		hyperparams->params_capacity *= 2;
		hyperparams->params = realloc(hyperparams->params, hyperparams->params_capacity * sizeof(struct hyperparam));
	}
	hyperparams->params_size += 1;

	hyperparams->params[hyperparams->params_size - 1] = param;
}
