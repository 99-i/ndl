#include "ast/network.h"
#include "ast/declaration.h"
#include <stdlib.h>

struct declaration *network_create(char *network_name, struct block *statements)
{
	struct network_definition *network = malloc(sizeof(*network));

	network->network_name = network_name;
	network->statements = statements;

	struct declaration *dec = malloc(sizeof(*dec));

	dec->type = DEC_NETWORK;
	dec->network = network;

	return dec;
}
