#ifndef STACK_H_
#define STACK_H_

#include <Node/Node.h>

#include <stdbool.h>

typedef struct Stack
{
	Node *top;
} Stack;

/**
 * @brief Construct a new empty stack on the heap.
 *
 * @warning The allocated memory must be freed with a call to `Stack_destroy()`.
 *
 * @return Stack* A pointer to the created stack, or `NULL` if there was an error.
 */
Stack *Stack_construct(void);
/**
 * @brief Free the memory allocated to a stack and any contained `Node`s.
 *
 * @param stack The pointer to the stack to free.
 */
void Stack_destroy(Stack *stack);

/**
 * @brief Empty the stack without deallocating any memory.
 *
 * @param stack The pointer to the stack.
 */
void Stack_empty(Stack *stack);

/**
 * @brief Peek the node at the top of a stack without removing the node.
 *
 * @param stack The pointer to the stack.
 * @return Node* The pointer to the node, or `NULL` if the stack is empty.
 */
Node *Stack_peek(Stack *stack);

/**
 * @brief Pop the node at the top of a stack.
 *
 * @param stack The pointer to the stack.
 * @return Node* The pointer to the popped node, or `NULL` if the stack is empty.
 */
Node *Stack_pop(Stack *stack);
/**
 * @brief Push a node to the top of a stack.
 *
 * @param stack The pointer to the stack.
 * @param node The pointer to the node to push.
 */
void Stack_push(Stack *stack, Node *node);

/**
 * @brief Check if the stack is empty.
 *
 * @param stack The pointer to the stack.
 * @return true If the stack is empty, or if a `NULL` pointer was provided.
 */
bool Stack_isEmpty(Stack *stack);

#endif