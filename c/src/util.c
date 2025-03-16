#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int slurp_file(const char *filename, char **dest)
{
	size_t size;
	FILE *fptr = fopen(filename, "r+");

	if (!fptr)
		return 1;

	fseek(fptr, 0, SEEK_END);

	size = ftell(fptr);

	*dest = malloc(size + 1);

	fseek(fptr, 0, SEEK_SET);

	fread(*dest, size, 1, fptr);

	return 0;
}
