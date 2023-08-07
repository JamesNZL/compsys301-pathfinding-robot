#ifndef QUEUE_H_
#define QUEUE_H_

#include <Node/Node.h>

#include <stdbool.h>

typedef struct Queue
{
	Node *head;
	Node *tail;
} Queue;

/**
 * @brief Construct a new empty queue on the heap.
 *
 * @warning The allocated memory must be freed with a call to `Queue_destroy()`.
 *
 * @return Queue* A pointer to the created queue, or `NULL` if there was an error.
 */
Queue *Queue_construct(void);
/**
 * @brief Free the memory allocated to a queue and any contained `Node`s.
 *
 * @param queue The pointer to the queue to free.
 */
void Queue_destroy(Queue *queue);

/**
 * @brief Peek the node at the front of a queue without removing the node.
 *
 * @param queue The pointer to the queue.
 * @return Node* The pointer to the node, or `NULL` if the queue is empty;
 */
Node *Queue_peek(Queue *queue);

/**
 * @brief Pop the node at the front of a queue.
 *
 * @param queue The pointer to the queue.
 * @return Node* The pointer to the popped node, or `NULL` if the queue is empty.
 */
Node *Queue_pop(Queue *queue);
/**
 * @brief Append a node to the back of a queue.
 *
 * @param queue The pointer to the queue.
 * @param node The pointer to the node to append.
 */
void Queue_append(Queue *queue, Node *node);

/**
 * @brief Check if the queue is empty.
 *
 * @param queue The pointer to the queue.
 * @return true If the queue is empty, or if a `NULL` pointer was provided.
 */
bool Queue_isEmpty(Queue *queue);

#endif