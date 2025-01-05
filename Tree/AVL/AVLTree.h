#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>

/// @brief Simple AVL Node definition.
typedef struct node
{
  int val;
  int height;
  struct node *left;
  struct node *right;
} avl_node;

avl_node *createNode(int val);
avl_node *findMinBst(avl_node *root);

bool insertAVLNode(avl_node **root, int val);
bool removeAVLNode(avl_node **root, int val);

int getBalance(avl_node *node);
int getHeight(avl_node *node);

void rotateLeft(avl_node **root);
void rotateRight(avl_node **root);

void cleanupAVL(avl_node **root);
void printPreOrder(avl_node *root);

#endif
