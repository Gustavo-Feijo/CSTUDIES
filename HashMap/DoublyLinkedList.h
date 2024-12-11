#ifndef DLL_SET
#define DLL_SET
#include <stdbool.h>

/// @brief Double Linked List Node with key-value pair.
typedef struct dllsn
{
    int val;
    char *key;
    struct dllsn *next;
    struct dllsn *prev;
} dll_set_node;

dll_set_node *create_dll_node(char *key, int val);
dll_set_node *search_dll_set(dll_set_node *head, dll_set_node *tail, char *key);

bool append_dll_set(dll_set_node **head, dll_set_node **tail, char *key, int val);
void cleanup_dll_set(dll_set_node *head);
bool remove_dll_set(dll_set_node **head, dll_set_node **tail, char *key);
void traverse_dll_set(dll_set_node *head);

#endif