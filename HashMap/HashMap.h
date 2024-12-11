#ifndef HASH_MAP
#define HASH_MAP
#include "DoublyLinkedList.h"

/// @brief Bucket for the hashtable. Each bucket is a doubly linked list with head and tail.
typedef struct HashList
{
    dll_set_node *head;
    dll_set_node *tail;
} bucket;

/// @brief The hashtable and it's data.
typedef struct HashTable
{
    bucket **buckets;
    int size;
    int elementCount;
} hash_table;

hash_table *create_hash_table();
dll_set_node *search_hash_table(hash_table *table, char *key);

int hash_function(char *key, int size);

void cleanup_table(hash_table *table);
void set_entry(hash_table *table, char *key, int val);
void resize_hash_table(hash_table *table, int new_size);
void traverse_hash_table(hash_table *table);

#endif