#include <assert.h>
#include <stdio.h>

// https://github.com/tsoding/sowon/blob/master/png2c.c#L9
const char *shift(int *argc, char ***argv)
{
	assert(*argc > 0);
	const char *result = *argv[0];
	*argc -= 1;
	*argv += 1;
	return result;
}

void usage(void);

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		usage();
		return 1;
	}

	return 0;
}

void usage(void)
{
	fprintf(stderr, "Usage: \n");
}
