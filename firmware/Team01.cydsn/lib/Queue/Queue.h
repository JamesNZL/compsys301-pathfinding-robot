#ifndef QUEUE_H_
#define QUEUE_H_

#include "../Node/Node.h"

#include <stdbool.h>

typedef struct Queue
{
	Node *head;
	Node *tail;
} Queue;

Queue *Queue_construct(void);
void Queue_destroy(Queue *queue);

Node *Queue_pop(Queue *queue);
void Queue_append(Queue *queue, Node *node);

bool Queue_isEmpty(Queue *queue);

#endif