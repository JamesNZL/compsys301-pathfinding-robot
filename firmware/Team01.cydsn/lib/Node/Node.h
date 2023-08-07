#ifndef NODE_H_
#define NODE_H_

#include <stdint.h>

// Use an opaque type to prevent direct access to members
typedef struct Node Node;

/**
 * @brief Create a new node on the heap.
 *
 * @warning The allocated memory must be freed with a call to `Node_destroy()`.
 *
 * @param value The value of the node to create.
 * @return Node* A pointer to the created node, or `NULL` if there was an error.
 */
Node *Node_create(uint32_t value);
/**
 * @brief Free the memory allocated to a node.
 *
 * @param node The pointer to the node to free.
 */
void Node_destroy(Node *node);

/**
 * @brief Get the value of a node.
 *
 * @param node The pointer to the node.
 * @return uint32_t The value of the node, or `0` if a `NULL` pointer was provided.
 */
uint32_t Node_getValue(Node *node);

/**
 * @brief Create an edge between two nodes.
 *
 * @param node The pointer to the source node.
 * @param next The pointer to the target node.
 */
void Node_setNext(Node *node, Node *next);
/**
 * @brief Get the target node from a source node.
 *
 * @param node The pointer to the source node.
 * @return Node* The pointer to the target node.
 */
Node *Node_getNext(Node *node);

#endif