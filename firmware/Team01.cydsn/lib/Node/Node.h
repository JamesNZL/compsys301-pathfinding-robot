#ifndef NODE_H_
#define NODE_H_

// Use an opaque type to prevent direct access to members
typedef struct Node Node;

/**
 * @brief Create a new node on the heap.
 *
 * @warning The allocated memory must be freed with a call to `Node_destroy()`.
 *
 * @param value The pointer to the value of the node to create.
 * @return Node* A pointer to the created node, or `NULL` if there was an error.
 */
Node *Node_create(void *value);
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
 * @return void* The void pointer to the value of the node, or `0` if a `NULL` pointer was provided.
 */
void *Node_get_value(Node *node);

/**
 * @brief Create an edge between two nodes.
 *
 * @param node The pointer to the source node.
 * @param next The pointer to the target node.
 */
void Node_set_next(Node *node, Node *next);
/**
 * @brief Get the target node from a source node.
 *
 * @param node The pointer to the source node.
 * @return Node* The pointer to the target node.
 */
Node *Node_get_next(Node *node);

#endif