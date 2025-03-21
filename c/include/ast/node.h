#pragma once
#include "ast/dims.h"
#include "ast/network.h"
#include "ast/statement.h"
#include "ast/tensor.h"
#include <stdbool.h>

enum node_type
{
	NODE_ROOT,
	NODE_NETWORK_DEFINITION,
	NODE_STATEMENT,
	NODE_TENSOR // e.g., tensor[10]
};

struct location
{
	int col;
	int line;
};

struct node
{
	enum node_type type;
	struct location loc;
	union
	{
		struct root {
			char *err_str;
			bool err;
			char *filename;
		} root;
		struct network_definition network;
		struct statement statement;
		struct tensor tensor;
	};

	struct node **children;
	size_t children_size;

};

struct node *node_create_root(void);

struct node *node_create(void);

void node_add_child_node(struct node *node, struct node *child);

void root_add_err(struct node *node, const char *err, struct location loc);

void node_free(struct node *node);
