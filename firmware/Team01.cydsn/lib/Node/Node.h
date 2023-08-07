#ifndef NODE_H_
#define NODE_H_

#include <stdint.h>

typedef struct Node
{
	uint32_t value;
	Node *next;
} Node;

Node *Node_create(uint32_t value, Node *next);
void Node_destroy(Node *node);

void Node_setNext(Node *node, Node *next);
Node *Node_getNext(Node *node);

#endif