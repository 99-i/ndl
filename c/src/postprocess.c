#include "ast/node.h"
#include <assert.h>

void postprocess_ast(struct node *root)
{
	assert(root->type == NODE_ROOT);
}
