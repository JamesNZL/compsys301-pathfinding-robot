#include "RollingBuffer.h"

#include <stdint.h>

typedef struct RollingBuffer
{
	void **array;
	uint16_t length;

	uint16_t head;
	uint16_t tail;

	// uint32_t sum;
	uint8_t isFull;
} RollingBuffer;

RollingBuffer *RollingBuffer_construct(void **array, uint16_t length)
{
	RollingBuffer *buffer = malloc(sizeof(RollingBuffer));
	if (buffer == NULL)
	{
		// malloc error
		return NULL;
	}

	buffer->array = array;
	buffer->length = length;
	buffer->head = 0;
	buffer->tail = 0;
	buffer->isFull = 0;

	return buffer;
}

void RollingBuffer_destroy(RollingBuffer *buffer)
{
	if (buffer == NULL)
	{
		return;
	}

	free(buffer);
}

void *RollingBuffer_get_element(RollingBuffer *buffer, uint16_t index)
{
	uint16_t arrayIndex = (buffer->head + index) % buffer->length;
	return buffer->array[arrayIndex];
}

void RollingBuffer_push(RollingBuffer *buffer, void *data)
{
	if (is_buffer_full(buffer))
	{
		// buffer->sum -= buffer->array[buffer->head++];
		buffer->head++;
		buffer->head %= buffer->length;
	}
	else if (((buffer->tail - buffer->head) + 1) == buffer->length)
	{
		buffer->isFull = 1;
	}

	// buffer->sum += data;

	// Add the new element to the tail of the array
	buffer->array[buffer->tail++] = data;
	// Wrap the tail around to the beginning of the array if necessary
	buffer->tail %= buffer->length;
}

// uint16_t RollingBuffer_get_average(RollingBuffer *buffer)
// {
// 	if (!is_buffer_full(buffer))
// 	{
// 		return 0;
// 	}

// 	return buffer->sum * ((float)1 / buffer->length);
// }

uint8_t RollingBuffer_is_full(RollingBuffer *buffer)
{
	return buffer->isFull;
}