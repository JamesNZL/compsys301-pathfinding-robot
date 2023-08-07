#include "Queue.h"

#include <stdlib.h>

Queue *Queue_construct(void)
{
	return malloc(sizeof(Queue));
}

void Queue_destroy(Queue *queue)
{
	if (queue == NULL)
	{
		return;
	}

	if (Queue_isEmpty(queue))
	{
		free(queue);
		return;
	}

	// Destroy the nodes in the queue
	while (!Queue_isEmpty(queue))
	{
		Node *head = Queue_pop(queue);
		Node_destroy(head);
	}

	free(queue);
}

Node *Queue_peek(Queue *queue)
{
	if (queue == NULL || Queue_isEmpty(queue))
	{
		return NULL;
	}

	return queue->head;
}

Node *Queue_pop(Queue *queue)
{
	if (queue == NULL || Queue_isEmpty(queue))
	{
		return NULL;
	}

	Node *head = queue->head;
	// Case 1: queue has 1 element
	if (Node_getNext(head) == NULL)
	{
		queue->head = NULL;
		queue->tail = NULL;
	}
	// Case 2: queue has many elements
	else
	{
		queue->head = Node_getNext(head);
	}

	Node_setNext(head, NULL);
	return head;
}

void Queue_append(Queue *queue, Node *node)
{
	if (queue == NULL)
	{
		return;
	}

	// Case 1: queue is empty
	if (Queue_isEmpty(queue))
	{
		queue->head = node;
		queue->tail = node;
	}
	// Case 2: queue is not empty
	else
	{
		Node_setNext(queue->tail, node);
		queue->tail = node;
	}
}

bool Queue_isEmpty(Queue *queue)
{
	if (queue == NULL)
	{
		return true;
	}

	return queue->head == NULL;
}