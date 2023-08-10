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

	if (Stack_is_empty(stack))
	{
		free(stack);
		return;
	}

	// Destroy the nodes on the stack
	while (!Stack_is_empty(stack))
	{
		Node *top = Stack_pop(stack);
		Node_destroy(top);
	}

	free(stack);
}

void Stack_clear(Stack *stack)
{
	if (stack == NULL || Stack_is_empty(stack))
	{
		return;
	}

	stack->top = NULL;
}

Node *Stack_peek(Stack *stack)
{
	if (stack == NULL || Stack_is_empty(stack))
	{
		return NULL;
	}

	return stack->top;
}

Node *Stack_pop(Stack *stack)
{
	if (stack == NULL || Stack_is_empty(stack))
	{
		return NULL;
	}

	Node *top = stack->top;
	// Case 1: stack has 1 element
	if (Node_get_next(top) == NULL)
	{
		stack->top = NULL;
	}
	// Case 2: stack has many elements
	else
	{
		stack->top = Node_get_next(top);
	}

	Node_set_next(top, NULL);
	return top;
}

void Stack_push(Stack *stack, Node *node)
{
	if (stack == NULL)
	{
		return;
	}

	// Case 1: stack is empty
	if (Stack_is_empty(stack))
	{
		stack->top = node;
	}
	// Case 2: stack is not empty
	else
	{
		Node_set_next(node, stack->top);
		stack->top = node;
	}
}

uint8_t Stack_is_empty(Stack *stack)
{
	if (stack == NULL)
	{
		return 1;
	}

	return stack->top == NULL;
}