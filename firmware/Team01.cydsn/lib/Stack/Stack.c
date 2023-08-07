#include "Stack.h"

#include <stdlib.h>

typedef struct Stack
{
	Node *top;
} Stack;

Stack *Stack_construct(void)
{
	Stack *stack = malloc(sizeof(Stack));
	if (stack == NULL)
	{
		// malloc error
		return NULL;
	}

	stack->top = NULL;

	return stack;
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
		Node *top = Stack_pop(stack);
		Node_destroy(top);
	}

	free(stack);
}

void Stack_clear(Stack *stack)
{
	if (stack == NULL || Stack_isEmpty(stack))
	{
		return;
	}

	stack->top = NULL;
}

Node *Stack_peek(Stack *stack)
{
	if (stack == NULL || Stack_isEmpty(stack))
	{
		return NULL;
	}

	return stack->top;
}

Node *Stack_pop(Stack *stack)
{
	if (stack == NULL || Stack_isEmpty(stack))
	{
		return NULL;
	}

	Node *top = stack->top;
	// Case 1: stack has 1 element
	if (Node_getNext(top) == NULL)
	{
		stack->top = NULL;
	}
	// Case 2: stack has many elements
	else
	{
		stack->top = Node_getNext(top);
	}

	Node_setNext(top, NULL);
	return top;
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
		stack->top = node;
	}
	// Case 2: stack is not empty
	else
	{
		Node_setNext(node, stack->top);
		stack->top = node;
	}
}

bool Stack_isEmpty(Stack *stack)
{
	if (stack == NULL)
	{
		return true;
	}

	return stack->top == NULL;
}