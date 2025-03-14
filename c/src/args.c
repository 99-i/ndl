#include "args.h"
#include <assert.h>

// https://github.com/tsoding/sowon/blob/master/png2c.c#L9
const char *shift(int *argc, char ***argv)
{
	assert(*argc > 0);
	const char *result = *argv[0];
	*argc -= 1;
	*argv += 1;
	return result;
}
