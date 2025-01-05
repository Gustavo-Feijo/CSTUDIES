#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#define getMax(x, y) ((x) > (y) ? (x) : (y))

/**
 * Allocate and initialize a new avl_node with the passed value.
 * Return the node if allocated, else return NULL;
 * @param val The value of the node entry.
 * @return New node with the malloced value or NULL if fail.
 */
avl_node *createNode(int val) {
  avl_node *new = malloc(sizeof(avl_node));
  if (new == NULL)
    return NULL;

  new->height = 1;
  new->val = val;
  new->left = NULL;
  new->right = NULL;
  return new;
}

/**
 * Find the node with the smallest value on a tree.
 * @param *root The tree to be searched.
 */
avl_node *findMinBst(avl_node *root) {
  while (root && root->left != NULL)
    root = root->left;
  return root;
}

/**
 * Insert a new node in the right position of the BST.
 * Handle duplicates, inicialization and rotation.
 * @param **root A pointer to the address of the root.
 * @param val The value to be inserted.
 * @return True if sucess, else False.
 */
bool insertAVLNode(avl_node **root, int val) {
  // Verifies if  the root is not NULL, if it is, initialize it.
  if (*root == NULL) {
    avl_node *toInsert = createNode(val);
    if (toInsert == NULL)
      return false;
    *root = toInsert;
    return true;
  }

  // Handle the recursive insertion.
  if ((*root)->val > val) {
    // Handle cases where didn't inserted.
    if (!insertAVLNode(&((*root)->left), val)) {
      return false;
    }
  } else if ((*root)->val < val) {
    if (!insertAVLNode(&((*root)->right), val)) {
      return false;
    }
  } else {
    // Duplicate.
    return false;
  }

  // Get the new height for the element.
  // Since we inserted recursively from the Root, will affect all nodes on the
  // subtree.
  (*root)->height =
      1 + getMax(getHeight((*root)->left), getHeight((*root)->right));

  // Get the balance of the current node.
  int balance = getBalance(*root);

  // Left subtree is deeper and the value was inserted to the left of the left
  // subtree.
  if (balance > 1 && (*root)->left->val > val) {
    rotateRight(root);
  }
  // Right subtree is deeper and the value was inserted to the right of the
  // right subtree.
  else if (balance < -1 && (*root)->right->val < val) {
    rotateLeft(root);
  }
  // Left subtree is deeper and the value was inserted at the right of the left
  // subtree.
  else if (balance > 1 && (*root)->left->val < val) {
    // Rotate the left subtree (Which could unbalance it until the next
    // rotation)
    rotateLeft(&((*root)->left));
    // Rotate the root again, balancing everything.
    rotateRight(root);
  }
  // Right subtree is deeper and the value was inserted to the left of the right
  // subtree.
  else if (balance < -1 && (*root)->right->val > val) {
    rotateRight(&((*root)->right));
    rotateLeft(root);
  }
  // Inserted sucessfully.
  return true;
}

/**
 * Remove a node from the AVL based on it's value.
 * Handle the leaf, one child and two child cases.
 * Automatically rotates it to mantain balanced.
 * @param **root A pointer to the address of the root.
 * @param val The value of the node to be deleted.
 * @return True if removed, false otherwise.
 */
bool removeAVLNode(avl_node **root, int val) {
  // Can't remove NULL node.
  if (*root == NULL)
    return false;

  // Node to be removed is to the left.
  if ((*root)->val > val) {
    // Couldn't remove (Doesn't exist).
    if (!removeAVLNode(&((*root)->left), val)) {
      return false;
    }
  }
  // Node to be removed is to the right.
  else if (((*root)->val < val)) {
    if (!removeAVLNode(&((*root)->right), val)) {
      return false;
    }
  } else {
    // No child, just free and set the pointer to NULL.
    if ((*root)->left == NULL && (*root)->right == NULL) {
      free(*root);
      *root = NULL;
    } else if ((*root)->left == NULL) {
      // Just right child, change the current to it and free the old.
      avl_node *temp = *root;
      *root = (*root)->right;
      free(temp);
    } else if ((*root)->right == NULL) {
      avl_node *temp = *root;
      *root = (*root)->left;
      free(temp);
    } else {
      // Found the node to be removed, get the smallest value on the right
      // child.
      avl_node *temp = findMinBst((*root)->right);
      // Copy the value to the current and remove the smallest from the right.
      (*root)->val = temp->val;
      removeAVLNode(&((*root)->right), temp->val);
    }
  }

  // If we just removed the node, just return true.
  if (*root == NULL)
    return true;

  // Get the new height.
  (*root)->height =
      1 + getMax(getHeight((*root)->left), getHeight((*root)->right));

  int balance = getBalance(*root);

  // Left subtree is deeper and isn't unbalanced to the right.
  if (balance > 1 && getBalance((*root)->left) >= 0) {
    // Just rotates to the right to correct the unbalanced left subtree.
    rotateRight(root);
  }
  // Right subtree is deeper and isn't unbalanced to the right.
  else if (balance < -1 && getBalance((*root)->right) <= 0) {
    rotateLeft(root);
  }
  // Left subtree is deeper and unbalanced to the right.
  else if (balance > 1 && getBalance((*root)->left) < 0) {
    // Rotate the left subtree to correct the right unbalance.
    rotateLeft(&((*root)->left));
    rotateRight(root);
  }
  // Right subtree is deeper and unbalanced to the left.
  else if (balance < -1 && getBalance((*root)->right) > 0) {
    // Rotate the right subtree to correct the left unbalance.
    rotateRight(&((*root)->right));
    rotateLeft(root);
  }

  // Sucessfully removed.
  return true;
}

/**
 * Get the current balancement of the node.
 * @param *node Node to verify if the children heights are balanced.
 * @return The difference in height, [0,1,-1] are balanced, only one level of
 * difference, more is unbalanced.
 */
int getBalance(avl_node *node) {
  // Return the difference in height between the left and right node.
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

/**
 * Get the height of a given node.
 * @param *node The node to get the height.
 * @return The height of the node, 0 if NULL.
 */
int getHeight(avl_node *node) { return node ? node->height : 0; }

/**
 * Realize a rotation of the tree to the left.
 * @param **root A pointer to the root of the tree/subtree to be rotated.
 */
void rotateLeft(avl_node **root) {
  // New root.
  avl_node *r = (*root)->right;
  avl_node *rl = r->left;

  r->left = *root;
  (*root)->right = rl;

  // Update the height of the new right.
  (*root)->height =
      1 + getMax(getHeight((*root)->left), getHeight((*root)->right));
  // Update the height of the new root.
  r->height = 1 + getMax(getHeight(r->left), getHeight(r->right));
  *root = r;
}

/**
 * Realize a rotation of the tree to the right.
 * @param **root A pointer to the root of the tree/subtree to be rotated.
 */
void rotateRight(avl_node **root) {
  avl_node *l = (*root)->left;
  avl_node *lr = l->right;

  l->right = *root;
  (*root)->left = lr;

  (*root)->height =
      1 + getMax(getHeight((*root)->left), getHeight((*root)->right));
  l->height = 1 + getMax(getHeight(l->left), getHeight(l->right));
  *root = l;
}

/**
 * Cleanup the Tree.
 * Sets the root to NULL after cleanup.
 * @param **root A pointer to the root of the Tree.
 */
void cleanupAVL(avl_node **root) {
  if (*root == NULL)
    return;
  cleanupAVL(&((*root)->left));
  cleanupAVL(&((*root)->right));
  free(*root);
  *root = NULL;
}

/**
 * Print the Tree in a pre order traversal.
 * @param *root The root of the tree.
 */
void printPreOrder(avl_node *root) {
  if (root) {
    printf("%d ", root->val);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}
