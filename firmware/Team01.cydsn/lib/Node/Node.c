#include "Node.h"

#include <stdlib.h>

Node *Node_create(uint32_t value, Node *next)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL)
	{
		// malloc error
		return NULL;
	}

	node->value = value;
	node->next = next;

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
	return node->next;
}