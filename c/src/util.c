#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int slurp_file(const char *filename, char **dest)
{
	FILE *fptr = fopen(filename, "r");
	if (!fptr)
	{
		return 1;
	}

	fseek(fptr, 0, SEEK_END);
	long size = ftell(fptr);
	if (size < 0)
	{
		fclose(fptr);
		return 1;
	}

	rewind(fptr);

	*dest = malloc(size + 1);
	if (!*dest)
	{
		fclose(fptr);
		return 1;
	}

	size_t bytes_read = fread(*dest, 1, size, fptr);
	fclose(fptr);

	(*dest)[bytes_read] = '\0';

	return 0;
}
