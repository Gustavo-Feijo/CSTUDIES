#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <stdbool.h> // A single node of the Binary Search Tree.

/// @brief Single Tree Node.
typedef struct Node {
  int val;
  struct Node *left;
  struct Node *right;
} bst_node;

bst_node *createBstNode(int val);
bst_node *findMinBst(bst_node *root);
bst_node *findMaxBst(bst_node *root);
bst_node *searchBstNode(bst_node *root, int val);

bool removeBstNode(bst_node **root, int val);
bool insertBstNode(bst_node **root, int val);

void cleanupBst(bst_node **root);
void inorderBstTraverse(bst_node *root);
void preBstTraverse(bst_node *root);

#endif
