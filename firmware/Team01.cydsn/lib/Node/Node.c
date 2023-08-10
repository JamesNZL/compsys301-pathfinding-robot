#include "Node.h"

#include <stdlib.h>

typedef struct Node
{
	void *value;
	struct Node *next;
} Node;

Node *Node_create(void *value)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL)
	{
		// malloc error
		return NULL;
	}

	node->value = value;
	node->next = NULL;

	return node;
}

void Node_destroy(Node *node)
{
	if (node == NULL)
	{
		return;
	}

	free(node);
}

void *Node_get_value(Node *node)
{
	if (node == NULL)
	{
		return 0;
	}

	return node->value;
}

void Node_set_next(Node *node, Node *next)
{
	if (node == NULL)
	{
		return;
	}

	node->next = next;
}

Node *Node_get_next(Node *node)
{
	if (node == NULL)
	{
		return NULL;
	}

	return node->next;
}