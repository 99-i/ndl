#include "ast/dims.h"
#include <stdlib.h>

struct dims dims_create(void)
{
	struct dims dims;

	dims.dims_capacity = 4;
	dims.dims_size = 0;
	dims.dims = malloc(dims.dims_capacity * sizeof(*dims.dims));

	return dims;
}

void dims_add_dim(struct dims *dims, uint32_t dim)
{
	if (dims->dims_size == dims->dims_capacity)
	{
		dims->dims_capacity *= 2;
		dims->dims = realloc(dims->dims, dims->dims_capacity * sizeof(*dims->dims));
	}
	dims->dims_size++;
	dims->dims[dims->dims_size - 1] = dim;
}
