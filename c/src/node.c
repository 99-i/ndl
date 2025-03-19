#include "ast/node.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node *node_create_root(void)
{
	struct node *node = malloc(sizeof(*node));
	node->type = NODE_ROOT;
	node->children_size = 0;
	node->children = NULL;

	node->root.err_str = malloc(1);
	node->root.err_str[0] = 0;
	node->root.err = false;

	return node;
}

struct node *node_create(void)
{
	struct node *node = malloc(sizeof(*node));
	node->children_size = 0;
	node->children = NULL;

	return node;
}

void node_add_child_node(struct node *node, struct node *child)
{
	node->children_size++;
	node->children = realloc(node->children, node->children_size * sizeof(struct node *));
	node->children[node->children_size - 1] = child;
}

void root_add_err(struct node *node, const char *err, struct location loc)
{
	assert(node->type == NODE_ROOT);

	char buf[256] = {0};

	snprintf(buf, 256, "\033[0;31mSyntax error:\033[0m %s at line %d:%d", err, loc.line, loc.col);

	size_t old = strlen(node->root.err_str);
	size_t new = old + strlen(buf);

	node->root.err_str = realloc(node->root.err_str, new + 1);

	memcpy(node->root.err_str + old, buf, new - old);

	node->root.err_str[new] = 0;

	node->root.err = true;
}

void node_free(struct node *node)
{
	switch (node->type)
	{
		case NODE_ROOT:
			free(node->root.filename);
			free(node->root.err_str);
			break;
		case NODE_NETWORK_DEFINITION:
			free(node->network.network_name);
			break;
		case NODE_STATEMENT:
			free(node->statement.name);
			free(node->statement.layer_type);
			// todo: hypers_free
			free(node->statement.hypers);
			break;
		case NODE_TENSOR:
			free(node->tensor.dims.dims);
			free(node->tensor.name);
			break;
	}

	for (size_t i = 0; i < node->children_size; i++)
		node_free(node->children[i]);

	free(node->children);
	free(node);
}
