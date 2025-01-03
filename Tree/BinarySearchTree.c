#include "BinarySearchTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Allocate and initialize a new bst_node with the passed value.
 * Return the node if allocated, else return NULL;
 * @param val The value of the node entry.
 * @return New node with the malloced value or NULL if fail.
 */
bst_node *createBstNode(int val) {
  bst_node *new = malloc(sizeof(bst_node));
  if (new == NULL)
    return NULL;

  new->left = NULL;
  new->right = NULL;
  new->val = val;
  return new;
}

/**
 * Find the node with the smallest value on a tree.
 * @param *root The tree to be searched.
 */
bst_node *findMinBst(bst_node *root) {
  while (root && root->left != NULL)
    root = root->left;
  return root;
}

/**
 * Find the node with the biggest value on a tree.
 * @param *root The tree to be searched.
 */
bst_node *findMaxBst(bst_node *root) {
  while (root && root->right != NULL)
    root = root->right;
  return root;
}

/**
 * Search for a node in the passed tree.
 * @param *root The tree where the search will take place.
 * @param val The value to be searched in the tree.
 * @return The desired Node, NULL if not found.
 */
bst_node *searchBstNode(bst_node *root, int val) {
  // Validate the pointer.
  if (root == NULL) {
    printf("Can't search in NULL Tree.\n");
    return NULL;
  }
  // Loop through the tree.
  while (root != NULL) {
    if (root->val == val)
      return root;
    root = (root->val > val) ? root->left : root->right;
  }
  return NULL;
}

/**
 * Insert a new node in the right position of the BST.
 * Handle duplicates and inicialization.
 * @param **root A pointer to the address of the root.
 * @param val The value to be inserted.
 * @return True if sucess, else False.
 */
bool insertBstNode(bst_node **root, int val) {
  if (root == NULL) {
    printf("Can't insert Node without a valid pointer.\n");
    return false;
  }

  // Create a new node.
  bst_node *toInsert = createBstNode(val);
  if (toInsert == NULL)
    return false;

  // Handle the case to a empty root.
  if (*root == NULL) {
    printf("Initializing Root of the tree.\n");
    *root = toInsert;
    return true;
  }

  // Traveerse the Tree to find where to insert the node.
  bst_node *cur = *root;
  while (true) {
    if (cur->val > val) {
      if (cur->left == NULL) {
        cur->left = toInsert;
        return true;
      }
      cur = cur->left;
    } else if (cur->val < val) {
      if (cur->right == NULL) {
        cur->right = toInsert;
        return true;
      }
      cur = cur->right;
    } else {
      printf("Duplicates are not allowed.\n");
      free(toInsert);
      return false;
    }
  }
  // Shouldn't reach.
  return false;
}

/**
 * Remove a node from the BST based on it's value.
 * Handle the leaf, one child and two child cases.
 * @param **root A pointer to the address of the root.
 * @param val The value of the node to be deleted.
 * @return True if removed, false otherwise.
 */
bool removeBstNode(bst_node **root, int val) {
  // Verify if the node exists.
  if (*root == NULL) {
    return false;
  }

  // Traverse the tree to find the node to remove.
  if ((*root)->val > val) {
    return removeBstNode(&((*root)->left), val);
  } else if ((*root)->val < val) {
    return removeBstNode(&((*root)->right), val);
  } else {
    // Handle leaf case.
    if ((*root)->left == NULL && (*root)->right == NULL) {
      free(*root);
      *root = NULL;
    } else if ((*root)->left == NULL) {
      // Handle right child only.
      bst_node *temp = (*root)->right;
      free(*root);
      *root = temp;
    } else if ((*root)->right == NULL) {
      // Handle left child only.
      bst_node *temp = (*root)->left;
      free(*root);
      *root = temp;
    } else {
      // Handle both child case.
      bst_node *temp = findMinBst((*root)->right);
      (*root)->val = temp->val;
      removeBstNode(&((*root)->right), temp->val);
    }
    return true;
  }
}

/**
 * Cleanup the Tree.
 * Sets the root to NULL after cleanup.
 * @param **root A pointer to the root of the Tree.
 */
void cleanupBst(bst_node **root) {
  if (*root == NULL)
    return;
  cleanupBst(&((*root)->left));
  cleanupBst(&((*root)->right));
  free(*root);
  *root = NULL;
}

/**
 * Traverses the BST in order.
 * New line not included.
 * @param *root The root of the Tree to be traversed.
 */
void inorderBstTraverse(bst_node *root) {
  if (root == NULL)
    return;
  inorderBstTraverse(root->left);
  printf("%d ", root->val);
  inorderBstTraverse(root->right);
}

/**
 * Traverses the BST pre order.
 * New line not included.
 * @param *root The root of the Tree to be traversed.
 */
void preBstTraverse(bst_node *root) {
  if (root == NULL)
    return;
  printf("%d ", root->val);
  preBstTraverse(root->left);
  preBstTraverse(root->right);
}
