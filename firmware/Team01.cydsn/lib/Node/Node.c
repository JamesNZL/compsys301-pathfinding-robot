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

void *Node_getValue(Node *node)
{
	if (node == NULL)
	{
		return 0;
	}

	return node->value;
}

void Node_setNext(Node *node, Node *next)
{
	if (node == NULL)
	{
		return;
	}

	node->next = next;
}

Node *Node_getNext(Node *node)
{
	if (node == NULL)
	{
		return NULL;
	}

	return node->next;
}