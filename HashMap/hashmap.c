#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#define GOLDEN_RATIO 0.6180339887
unsigned int hashkey(int key, const unsigned int hashamp_size) {
    /*
     * A hashing function using the multiplication method
     */

    float product = key * GOLDEN_RATIO;
    float fraction = product - (int)product; // Fractional part
    return (unsigned int)(hashamp_size * fraction);
}

unsigned int string_to_int(const char *string) {
    /*
     * Converts a string to an unsigned int by summing up its ASCII values
     */

    unsigned int sum = 1;
    for (int i = 0; i < (int)strlen(string); i++) {
        sum += (int)string[i];
    }

    return sum;
}

HashMap newHashMap(unsigned int hashmap_size) {
    /*
     * Creates a new hashmap
     */

    HashMap hm;

    hm.buckets = calloc(hashmap_size, sizeof(Item));
    hm.size = hashmap_size;
    hm.nodes = 0;

    return hm;
}

void cleanHashMap(HashMap *hm) {
    /*
     * Cleans the hashmap by freeing all heap allocated memory
     */

    for (unsigned int i = 0; i < hm->size; i++) { // free nodes that are linked
        Item *node = hm->buckets[i].next;

        while (node != NULL) {
            Item *next = node->next;
            free(node);
            node = next;
        }
    }

    free(hm->buckets); // free hashmap
}

void resizeHashMap(HashMap *hm, unsigned int hashmap_size) {
    /*
     * Resizes the hashmap by recalculating and reallocating the hashmap values
     * automatically frees the old buckets
     */

    HashMap temp = newHashMap(hashmap_size);

    // transfer items
    for (unsigned int i = 0; i < hm->size; i++) {
        Item *node = &(hm->buckets[i]);
        while (node->next != NULL) {
            addItemHashmap(node->key, node->value, &temp);
            node = node->next;
        }
    }

    cleanHashMap(hm); // cleans only buckets
    hm->buckets = temp.buckets;
    hm->size = temp.size;
    hm->nodes = temp.nodes;
}

void removeItemHashmap(int key, HashMap *hm) {
    /*
     * Remove a specific item from the hashmap
     */

    --hm->nodes; // :)

    printf("%d\n", hm->size);

    // 75% load factor
    if (hm->nodes < hm->size * 0.25) {
        resizeHashMap(hm, hm->size / 2);
    }

    printf("%d\n", hm->size);

    const int hash = hashkey(key, hm->size);

    Item *node = &(hm->buckets[hash]); // the node to delete
    Item *prev = NULL;                 // previous node

    // find the node
    unsigned short int position = 1;
    while (node->key != key) {
        prev = node;
        node = node->next;
        ++position;
    }

    if (prev != NULL) {          // if its first node
        prev->next = node->next; // link prev to next
    }

    if (position != 1) { // if first node
        free(node);      // free node from heap
    } else {
        Item *next = node->next;

        node->key = next->key;
        node->value = next->value;
        node->next = next->next;
        free(next);
    }
}

int getValueHashmap(int key, HashMap *hm) {
    /*
     * Get the value of an item
     */

    const int hash = hashkey(key, hm->size);

    // get inital hashed node
    Item node = hm->buckets[hash];

    // find the node
    while (node.key != key) {
        node = *node.next;
    }

    return node.value;
}

void addItemHashmap(int key, int value, HashMap *hm) {
    /*
     * Add an item to the hashmap
     */

    ++hm->nodes; // :)

    // 75% load factor
    if (hm->nodes > hm->size * 0.75) {
        resizeHashMap(hm, hm->size * 2);
    }

    const unsigned int hash = hashkey(key, hm->size);

    // get inital hashed node
    Item *node = &(hm->buckets[hash]);

    // find a free node
    while (node->next != NULL) {
        node = node->next;
    }

    if (hm->buckets[hash].key != key) { // if not first
        // Create new node on heap
        Item *prev = node;
        node = calloc(sizeof(Item), 1);
        node->next = prev->next; // ik its NULL but just in case
        prev->next = node;
    }

    // set values
    node->key = key;
    node->value = value;
}

unsigned long getHashMapSize(HashMap *hm) {
    /*
     * Calculate the amount of bytes used by the hashmap in memory
     */

    unsigned long hm_size_bytes = sizeof(HashMap) + sizeof(*hm->buckets);
    // unsigned long hm_size_bytes = sizeof(hm);

    for (unsigned int i = 0; i < hm->size; i++) {
        Item *node = &(hm->buckets[i]);

        while (node->next != NULL) {
            hm_size_bytes += sizeof(*node);
            node = node->next;
        }
    }

    return hm_size_bytes;
}
