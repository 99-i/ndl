#pragma once
#include "ast/dims.h"

struct tensor
{
	struct dims dims;
	char *name;
};
