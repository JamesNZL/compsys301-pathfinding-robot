#include "Stack.h"

#include <stdlib.h>

Stack *Stack_construct(void)
{
	return malloc(sizeof(Stack));
}

void Stack_destroy(Stack *stack)
{
	if (stack == NULL)
	{
		return;
	}

	if (Stack_isEmpty(stack))
	{
		free(stack);
		return;
	}

	// Destroy the nodes on the stack
	while (!Stack_isEmpty(stack))
	{
		Node *head = Stack_pop(stack);
		Node_destroy(head);
	}

	free(stack);
}

Node *Stack_peek(Stack *stack)
{
	if (stack == NULL || Stack_isEmpty(stack))
	{
		return NULL;
	}

	return stack->head;
}

Node *Stack_pop(Stack *stack)
{
	if (stack == NULL || Stack_isEmpty(stack))
	{
		return NULL;
	}

	Node *head = stack->head;
	stack->head = Node_getNext(head);

	Node_setNext(head, NULL);
	return head;
}

void Stack_push(Stack *stack, Node *node)
{
	if (stack == NULL)
	{
		return;
	}

	// Case 1: stack is empty
	if (Stack_isEmpty(stack))
	{
		stack->head = node;
	}
	// Case 2: stack is not empty
	else
	{
		Node_setNext(node, stack->head);
		stack->head = node;
	}
}

bool Stack_isEmpty(Stack *stack)
{
	if (stack == NULL)
	{
		return true;
	}

	return stack->head == NULL;
}