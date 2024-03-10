#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <limits.h> // for INT_MIN constant

#include "hashmap.h"

#define GOLDEN_RATIO 0.6180339887
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

    if (hashmap_size == 0)
        hashmap_size = 16;

    HashMap hm;

    hm.buckets = (Item *)calloc(hashmap_size, sizeof(Item));
    hm.size = hashmap_size;
    hm.used = 0;

    return hm;
}

void hashMapClean(HashMap *hm) {
    // walk through the buckets (not including the first layer)
    for (unsigned int i = 0; i < hm->size; ++i) {
        Item *next = &(hm->buckets[i]);

        while ((next = next->next) != NULL)
            free(next);
    }

    free(hm->buckets); // free first layer
}

void hashMapResize(HashMap *hm, unsigned int hashmap_size) {
    // Create new buckets
    HashMap new_hm = createHashMap(hashmap_size);

    // Recalculate the items
    for (unsigned int i = 0; i < hm->size; ++i) {
        Item *bucket = &(hm->buckets[i]);

        while (bucket->next != NULL) {
            hashMapPut(bucket->key, bucket->value, &new_hm, true);
            bucket = bucket->next;
        }
    }

    hashMapClean(hm); // clean the old buckets

    // Assign new values
    hm->buckets = new_hm.buckets;
    hm->used = new_hm.used;
    hm->size = new_hm.size;
}

void hashMapRemove(int key, HashMap *hm) {
    --hm->used;

    // 75% load factor
    if (hm->used < hm->size * 0.75) {
        hashMapResize(hm, hm->size / 2);
    }

    const int hash = hashkey(key, hm->size);

    Item *node = &(hm->buckets[hash]); // the node to delete
    Item *previous = NULL;

    // find the node
    while (node != NULL && node->key != key) {
        previous = node;
        node = node->next;
    }

    if (node != NULL) {         // if the node is found
        if (previous == NULL) { // if it's the first node
            hm->buckets[hash] =
                *(node->next); // update the bucket to skip the current node
        } else {               // if it's not the first node
            previous->next = node->next; // link the previous node to the next
                                         // node, skipping the current one
        }

        free(node); // free the current node
    }
}

int hashMapGet(int key, HashMap *hm) {
    const int hash = hashkey(key, hm->size);

    // get initial hashed node
    Item *node = &(hm->buckets[hash]);

    // find the node
    while (node != NULL && node->key != key)
        node = node->next;

    // check if the key was found
    if (node != NULL) {
        return node->value;
    } else {
        return INT_MIN;
    }
}

void hashMapPut(int key, int value, HashMap *hm, bool no_resize) {
    ++hm->used;

    // 75% load factor
    if (hm->used > hm->size * 0.75 && !no_resize) {
        hashMapResize(hm, hm->size * 2);
    }

    const unsigned int hash = hashkey(key, hm->size);

    // find free node
    Item *node = &(hm->buckets[hash]);
    bool first = true;

    while (node->next != NULL) {
        first = false;
        node = node->next;
    }

    if (first) {
        node->key = key;
        node->value = value;
    } else {
        node->next = (Item *)calloc(sizeof(Item), 1);
        node = node->next;

        node->key = key;
        node->value = value;
    }
}

unsigned long hashMapSize(HashMap *hm) {
    unsigned long hm_size_bytes = sizeof(*hm);

    for (unsigned int i = 0; i < hm->size; ++i) {
        Item *node = &(hm->buckets[i]);
        while (node != NULL) {
            hm_size_bytes += sizeof(*node);
            node = node->next;
        }
    }

    return hm_size_bytes;
}
