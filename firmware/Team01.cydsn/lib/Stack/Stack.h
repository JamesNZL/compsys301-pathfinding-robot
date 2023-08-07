#ifndef STACK_H_
#define STACK_H_

#include "../Node/Node.h"

#include <stdbool.h>

typedef struct Stack
{
	Node *head;
} Stack;

Stack *Stack_construct(void);
void Stack_destroy(Stack *stack);

Node *Stack_pop(Stack *stack);
void Stack_push(Stack *stack, Node *node);

bool Stack_isEmpty(Stack *stack);

#endif