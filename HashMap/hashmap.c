#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#define GOLDEN_RATIO 0.6180339887
inline unsigned int hashkey(int key, const unsigned int hashamp_size) {
    float product = key * GOLDEN_RATIO;
    float fraction = product - (int)product; // Fractional part
    return (unsigned int)(hashamp_size * fraction);
}

unsigned int string_to_int(char *string) {
    unsigned int sum = 0;
    for (int i = 0; i < (int)strlen(string); i++) {
        sum += (int)string[i];
    }

    return sum;
}

HashMap newHashMap(unsigned int hashmap_size) {
    HashMap hm;

    hm.buckets = calloc(hashmap_size, sizeof(Item));
    hm.size = hashmap_size;
    hm.nodes = 0;

    return hm;
}

void cleanHashMap(HashMap *hm) {
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
    HashMap temp = newHashMap(hashmap_size);

    // transfer items
    for (unsigned int i = 0; i < hm->size; i++) {
        Item *node = &(hm->buckets[i]);
        while (node->next != NULL) {
            addItemHashmap(node->key, node->value, &temp);
            node = node->next;
        }
    }

    cleanHashMap(hm);
    hm->buckets = temp.buckets;
    hm->size = temp.size;
}

void removeItemHashmap(int key, HashMap *hm) {

    --hm->nodes; // :)

    // 75% load factor
    if (hm->nodes < hm->size * 0.25) {
        resizeHashMap(hm, hm->size / 2);
    }

    const int hash = hashkey(key, hm->size);

    Item *node = &(hm->buckets[hash]);
    Item *prev = NULL;

    while (node->key != key) { // find the node
        if (key == node->key) {
            prev->next = node->next; // link prev to next
            free(node);              // free node from heap
        }

        prev = node;
        node = node->next;
    }
}

int getValueHashmap(int key, HashMap *hm) {
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

    // Create new node on heap
    Item *prev = node;
    node = calloc(sizeof(Item), 1);
    node->next = prev->next; // ik its NULL but just in case
    prev->next = node;

    // set values
    node->key = key;
    node->value = value;
}
