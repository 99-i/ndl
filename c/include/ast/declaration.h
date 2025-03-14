#pragma once
#include "network.h"

enum declaration_type 
{
	DEC_NETWORK
};

struct declaration
{
	enum declaration_type type;
	union
	{
		struct network_definition *network;
	};
};
