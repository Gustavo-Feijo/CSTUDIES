#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Create a double linked list node and return it.
 */
dll_set_node *create_dll_node(char *key, int val)
{
    // Allocate the new node.
    dll_set_node *new_node = malloc(sizeof(dll_set_node));
    if (new_node == NULL)
        return NULL;

    if (key == NULL)
    {
        free(new_node);
        return NULL;
    }

    // Dump the key to preserve the list state.
    new_node->key = strdup(key);
    if (new_node->key == NULL)
    {
        free(new_node);
        return NULL;
    }
    new_node->val = val;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

/**
 * Append a double linked nost at the end of the list.
 */
bool append_dll_set(dll_set_node **head, dll_set_node **tail, char *key, int val)
{
    if (head == NULL || tail == NULL)
    {
        return false;
    }

    // Verify if the key is not in the list already.
    if (search_dll_set(*head, *tail, key) != NULL)
        return false;

    // Create the new node.
    dll_set_node *new_node = create_dll_node(key, val);
    if (new_node == NULL)
        return false;

    // Initialize the list.
    if (*head == NULL && *tail == NULL)
    {
        *head = new_node;
        *tail = new_node;
        return true;
    }

    // Append and return true.
    (*tail)->next = new_node;
    new_node->prev = *tail;
    *tail = new_node;
    return true;
}

/**
 * Cleanup the list.
 */
void cleanup_dll_set(dll_set_node *head)
{
    // Loop through each node, free the key and free the node itself.
    dll_set_node *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->key);
        free(temp);
    }
}

/**
 * Traverse the list and print each element.
 */
void traverse_dll_set(dll_set_node *head)
{
    dll_set_node *cur = head;
    while (cur != NULL)
    {
        printf("(%s,%d) -> ", cur->key, cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}

/**
 * Remove a given node based on it's key.
 */
bool remove_dll_set(dll_set_node **head, dll_set_node **tail, char *key)
{
    // Assure that you can at least search for the key.
    if (head == NULL || tail == NULL || *head == NULL || key == NULL)
    {
        return false;
    }

    dll_set_node *cur = *head;
    while (cur != NULL)
    {
        // Verify if the current element is the one to remove.
        if (strcmp(cur->key, key) == 0)
        {
            // Handle the case that the element to remove is the head.
            if (cur == *head)
            {
                *head = cur->next;
                if (*head != NULL)
                {
                    (*head)->prev = NULL;
                }
            }

            // Handle the case that the element to remove is the tail.
            if (cur == *tail)
            {
                *tail = cur->prev;
                if (*tail != NULL)
                {
                    (*tail)->next = NULL;
                }
            }

            // Set the prev and next if possible.
            if (cur->prev != NULL)
            {
                cur->prev->next = cur->next;
            }
            if (cur->next != NULL)
            {
                cur->next->prev = cur->prev;
            }

            // Clean the memory.
            free(cur->key);
            free(cur);
            return true;
        }
        cur = cur->next;
    }
    // The value is not present.
    return false;
}

/**
 * Search for a element in the list.
 * Returns the node, might return NULL if wrong params provided or result not found.
 */
dll_set_node *search_dll_set(dll_set_node *head, dll_set_node *tail, char *key)
{
    // Verify if everything is provided.
    if (head == NULL || tail == NULL || key == NULL)
    {
        return NULL;
    }

    dll_set_node *start = head;
    dll_set_node *end = tail;

    // Loop through each node.
    while (start != NULL && end != NULL && start != end && start->prev != end)
    {
        // Compare the key with the node content. Return the node if matches.
        if (strcmp(start->key, key) == 0 || strcmp(end->key, key) == 0)
            return strcmp(start->key, key) == 0 ? start : end;

        start = start->next;
        end = end->prev;
    }
    // Handle the edge case of start == end.
    if (strcmp(start->key, key) == 0)
        return start;
    return NULL;
}