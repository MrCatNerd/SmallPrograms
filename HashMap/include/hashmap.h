#pragma once

#include <stdbool.h>

/**
 * @class Item
 * @brief A Bucket / Item implementation for a hashmap
 *
 */
typedef struct Item {
        int key;
        int value;
        struct Item *next;
} Item;

/**
 * @brief HashMap implementation
 */
typedef struct {           // bucket = node = item
        Item *buckets;     // The bucket list
        unsigned int size; // number of bucket pointers
        unsigned int used; // the actual number of USED buckets
} HashMap;

/**
 * @brief Create a new hashmap (Must be cleaned later cuz heap)
 *
 * @see hashMapClean
 *
 * @param hashmap_size
 * @return HashMap
 */
HashMap createHashMap(unsigned int hashmap_size);

/**
 * @brief Put a new item in the hashmap
 *
 * @param key
 * @param value
 * @param hm
 */
void hashMapPut(int key, int value, HashMap *hm, bool no_resize);

/**
 * @brief Get the value of an item
 *
 * @param key
 * @param hm
 * @return The associated value
 */
int hashMapGet(int key, HashMap *hm);

/**
 * @brief Remove a specific item
 *
 * @param key
 * @param hm
 */
void hashMapRemove(int key, HashMap *hm);

/**
 * @brief Resizes the hashmap by recalculating and reallocating the hashmap
 * values automatically frees the old buckets
 * @param hm
 * @param hashmap_size
 */
void hashMapResize(HashMap *hm, unsigned int hashmap_size);

/**
 * @brief Converts a string to an unsigned int by summing up its ASCII values
 *
 * @param string
 * @return The ASCII value sum
 */
unsigned int stringToInt(const char *string);

/**
 * @brief Cleans the hashmap by freeing all heap allocated memory
 *
 * @param hm
 */
void hashMapClean(HashMap *hm);

/**
 * @brief self explanatory
 *
 * @param hm
 */
unsigned long hashMapSize(HashMap *hm);
