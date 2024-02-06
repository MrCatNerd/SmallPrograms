#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#define GOLDEN_RATIO 0.6180339887
/**
 * @brief A hashing function using the multiplication method
 *
 * @param key
 * @param hashamp_size
 * @return unsigned int
 */
unsigned int hashkey(int key, const unsigned int hashamp_size) {
    float product = key * GOLDEN_RATIO;
    float fraction = product - (int)product; // Fractional part
    return (unsigned int)(hashamp_size * fraction);
}

unsigned int stringToInt(const char *string) {

    unsigned int sum = 1;

    unsigned int i = strlen(string);
    while (--i) {
        sum += (int)string[i];
    }

    return sum;
}

HashMap createHashMap(unsigned int hashmap_size) {

    HashMap hm;

    hm.buckets = calloc(hashmap_size, sizeof(Item));
    hm.size = hashmap_size;
    hm.nodes = 0;

    return hm;
}

void hashMapClean(HashMap *hm) {
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

void hashMapResize(HashMap *hm, unsigned int hashmap_size) {
    Item *buckets = calloc(sizeof(Item), hashmap_size);

    for (unsigned int i = 0; i < hm->size; i++) {
        Item *node = &(hm->buckets[i]);
        while (node->next != NULL) {
            Item *next = node->next;

            // recalculate node position
            const unsigned int hash = hashkey(node->key, hashmap_size);

            // find free node
            Item *add_node = &(buckets[hash]);
            bool first = true;

            while (node->next != NULL) {
                node = node->next;
                first = false;
            }

            if (!first) {
                add_node->next = calloc(sizeof(Item), 1);
                add_node->next->key = node->key;
                add_node->next->value = node->value;
            } else {
                add_node->key = node->key;
                add_node->value = node->value;
            }

            free(node);
            node = next;
        }
    }

    // number of nodes stays the same so no need to recalculate

    // clean buckets
    free(hm->buckets);
    hm->buckets = buckets;

    // change size thingy
    hm->size = hashmap_size;
}

void hashMapRemove(int key,
                   HashMap *hm) { // TODO: fix that shitty code
    --hm->nodes;                  // :)

    printf("%d\n", hm->size);

    // 75% load factor
    if (hm->nodes < hm->size * 0.25) {
        hashMapResize(hm, hm->size / 2);
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
    Item *node = &(hm->buckets[hash]);

    // find the node
    while (node->key != key) {
        node = node->next;
    }

    return node->value;
}

void hashMapPut(int key, int value, HashMap *hm) {
    /*
     * Add an item to the hashmap
     */

    ++hm->nodes; // :)

    // 75% load factor
    if (hm->nodes > hm->size * 0.75) {
        hashMapResize(hm, hm->size * 2);
    }

    const unsigned int hash = hashkey(key, hm->size);

    // find free node
    Item *node = &(hm->buckets[hash]);
    bool first = true;

    while (node->next != NULL) {
        node = node->next;
        first = false;
    }

    if (!first) {
        node->next = calloc(sizeof(Item), 1);
        node->next->key = key;
        node->next->value = value;
    } else {
        node->key = key;
        node->value = value;
    }
}

unsigned long hashMapSize(HashMap *hm) {
    /*
     * Calculates the amount of bytes used by the hashmap in memory (both heap
     * and stack)
     */

    unsigned long hm_size_bytes = sizeof(*hm);
    // unsigned long hm_size_bytes = sizeof(hm);

    unsigned int i = hm->size; // looks cleaner
    while (--i) {
        Item *node = &(hm->buckets[i]);

        while (node->next) {
            hm_size_bytes += sizeof(*node);
        }
    }

    return hm_size_bytes;
}
