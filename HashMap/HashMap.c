#include "HashMap.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Create and return a hash table.
 */
hash_table *create_hash_table()
{
    // Allocate the new table.
    hash_table *new_table = malloc(sizeof(hash_table));
    if (new_table == NULL)
        return NULL;

    // Set the default size as 11 and allocate the array of buckets.
    new_table->size = 11;
    new_table->buckets = malloc(new_table->size * sizeof(bucket *));
    if (new_table->buckets == NULL)
    {
        free(new_table);
        return NULL;
    }

    // Allocate each bucket and initialize the head and tail.
    for (int i = 0; i < new_table->size; i++)
    {
        new_table->buckets[i] = malloc(sizeof(bucket));
        if (new_table->buckets[i] == NULL)
        {
            // Free the previous buckets in case of failure.
            for (int j = 0; j < i; j++)
                free(new_table->buckets[j]);

            free(new_table->buckets);
            free(new_table);
            return NULL;
        }
        new_table->buckets[i]->head = NULL;
        new_table->buckets[i]->tail = NULL;
    }

    new_table->elementCount = 0;
    return new_table;
}

/**
 * Get the index of the hashmap.
 */
int hash_function(char *key, int size)
{
    unsigned long int hash = 0;
    while (*key != '\0')
        hash = (hash * 31 + *key++);
    return hash % size;
}

/**
 * Cleanup the table.
 */
void cleanup_table(hash_table *table)
{
    if (table == NULL)
        return;
    // Clean up each bucket/linked list.
    for (int i = 0; i < table->size; i++)
    {
        if (table->buckets[i])
        {
            cleanup_dll_set(table->buckets[i]->head);
            free(table->buckets[i]);
        }
    }
    // Free the pointer to the buckets and the table itself.
    free(table->buckets);
    free(table);
}

/**
 * Insert a element in the hash table or update if already exists.
 */
void set_entry(hash_table *table, char *key, int val)
{
    if (table == NULL || key == NULL)
        return;

    // Hash the key.
    int index = hash_function(key, table->size);
    bucket *cur_bucket = table->buckets[index];
    // Append to the respective bucket and increase the element counter if sucessfull.
    if (append_dll_set(&cur_bucket->head, &cur_bucket->tail, key, val))
        table->elementCount++;
    else
    {
        // Update the element if already exists.
        dll_set_node *toUpdate = search_dll_set(cur_bucket->head, cur_bucket->tail, key);
        if (toUpdate == NULL)
        {
            return;
        }
        toUpdate->val = val;
    }

    // Resize the table when the count of elements is 75% of the size.
    if (0.75 < (float)(table->elementCount) / table->size)
        resize_hash_table(table, table->size * 2);
}

/**
 * Resize the hash table.
 */
void resize_hash_table(hash_table *table, int new_size)
{
    if (table == NULL)
        return;

    // Allocate the new buckets.
    bucket **new_buckets = malloc(new_size * sizeof(bucket *));
    if (new_buckets == NULL)
    {
        return;
    }

    // Allocate memory and initialize each bucket.
    for (int i = 0; i < new_size; i++)
    {
        new_buckets[i] = malloc(sizeof(bucket));
        if (new_buckets[i] == NULL)
        {
            // Clean up in case of failure.
            for (int j = 0; j < i; j++)
                free(new_buckets[j]);

            free(new_buckets);
            return;
        }
        new_buckets[i]->head = NULL;
        new_buckets[i]->tail = NULL;
    }

    // Loop through each old bucket.
    for (int i = 0; i < table->size; i++)
    {
        bucket *old_bucket = table->buckets[i];
        dll_set_node *cur = old_bucket->head;
        while (cur != NULL)
        {
            // Re-hash to the new size and append to the new bucket.
            int new_hash = hash_function(cur->key, new_size);
            append_dll_set(&new_buckets[new_hash]->head, &new_buckets[new_hash]->tail, cur->key, cur->val);
            cur = cur->next;
        }
        // Cleanup the old bucket.
        cleanup_dll_set(old_bucket->head);
        free(old_bucket);
    }
    // Free the bucket pointers and set it to the new bucket list.
    free(table->buckets);
    table->buckets = new_buckets;
    table->size = new_size;
}

/**
 * Search for a key and return the respective node.
 * Might return NULL if not found.
 */
dll_set_node *search_hash_table(hash_table *table, char *key)
{
    if (table == NULL)
        return NULL;
    int index = hash_function(key, table->size);
    bucket *cur_bucket = table->buckets[index];
    return search_dll_set(cur_bucket->head, cur_bucket->tail, key);
}

/**
 * Traverse each element on the hash table.
 */
void traverse_hash_table(hash_table *table)
{
    if (table == NULL)
        return;
    for (int i = 0; i < table->size; i++)
    {
        printf("Bucket[%d]: ", i);
        traverse_dll_set(table->buckets[i]->head);
    }
}