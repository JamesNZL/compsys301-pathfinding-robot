#include "Queue.h"

#include <stdlib.h>

typedef struct Queue
{
	Node *front;
	// Maintain an end pointer to enable O(1) insertions
	Node *end;
} Queue;

Queue *Queue_construct(void)
{
	Queue *queue = malloc(sizeof(Queue));
	if (queue == NULL)
	{
		// malloc error
		return NULL;
	}

	queue->front = NULL;
	queue->end = NULL;

	return queue;
}

void Queue_destroy(Queue *queue)
{
	if (queue == NULL)
	{
		return;
	}

	if (Queue_is_empty(queue))
	{
		free(queue);
		return;
	}

	// Destroy the nodes in the queue
	while (!Queue_is_empty(queue))
	{
		Node *front = Queue_pop(queue);
		Node_destroy(front);
	}

	free(queue);
}

Node *Queue_peek(Queue *queue)
{
	if (queue == NULL || Queue_is_empty(queue))
	{
		return NULL;
	}

	return queue->front;
}

Node *Queue_pop(Queue *queue)
{
	if (queue == NULL || Queue_is_empty(queue))
	{
		return NULL;
	}

	Node *front = queue->front;
	// Case 1: queue has 1 element
	if (Node_get_next(front) == NULL)
	{
		queue->front = NULL;
		queue->end = NULL;
	}
	// Case 2: queue has many elements
	else
	{
		queue->front = Node_get_next(front);
	}

	Node_set_next(front, NULL);
	return front;
}

void Queue_append(Queue *queue, Node *node)
{
	if (queue == NULL)
	{
		return;
	}

	// Case 1: queue is empty
	if (Queue_is_empty(queue))
	{
		queue->front = node;
		queue->end = node;
	}
	// Case 2: queue is not empty
	else
	{
		Node_set_next(queue->end, node);
		queue->end = node;
	}
}

uint8_t Queue_is_empty(Queue *queue)
{
	if (queue == NULL)
	{
		return 1;
	}

	return queue->front == NULL;
}