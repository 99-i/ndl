#pragma once
#include <stdint.h>
#include <stddef.h>

struct dims
{
	uint32_t *dims;
	size_t dims_size;
	size_t dims_capacity;
};

struct dims dims_create(void);

void dims_add_dim(struct dims *dims, uint32_t dim);
