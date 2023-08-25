#ifndef ROLLING_BUFFER_H_
#define ROLLING_BUFFER_H_

#include <stdint.h>
#include <stdlib.h>

#define NULL ((void *)0)
// Use an opaque type to prevent direct access to members
typedef struct RollingBuffer RollingBuffer;

/**
 * @brief Construct a new rolling buffer on the heap.
 *
 * @warning The allocated memory must be freed with a call to `RollingBuffer_destroy()`.
 *
 * @param array The array to use for the rolling buffer.
 * @param length The length of the array.
 * @return RollingBuffer* A pointer to the created rolling buffer, or `NULL` if there was an error.
 */
RollingBuffer *RollingBuffer_construct(void **array, uint16_t length);
/**
 * @brief Free the memory allocated to a rolling buffer.
 *
 * @param buffer The pointer to the rolling buffer to free.
 */
void RollingBuffer_destroy(RollingBuffer *buffer);

/**
 * @brief Get the element at a specified index.
 *
 * @note The index is relative to the current head of the rolling buffer.
 *
 * @param buffer The pointer to the rolling buffer.
 * @param index The index (relative to the head of the buffer) of the element.
 * @return void* The pointer to the element.
 */
void *RollingBuffer_get_element(RollingBuffer *buffer, uint16_t index);

/**
 * @brief Push an element to the tail of the rolling buffer.
 *
 * @param buffer The pointer to the rolling buffer.
 * @param data The pointer to the element to push.
 */
void RollingBuffer_push(RollingBuffer *buffer, void *data);

// /**
//  * @brief Calculate the average of all elements in the rolling buffer.
//  *
//  * @param buffer The pointer to the rolling buffer.
//  * @return uint16_t The average value of the rolling buffer.
//  */
// uint16_t RollingBuffer_get_average(RollingBuffer *buffer);

/**
 * @brief Check if the rolling buffer is full.
 *
 * @param buffer The pointer to the rolling buffer.
 * @return 1 If the rolling buffer is full.
 */
uint8_t RollingBuffer_is_full(RollingBuffer *buffer);

#endif