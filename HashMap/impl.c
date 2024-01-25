#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "impl.h"

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
    HashMap map;

    map.buckets = calloc(hashmap_size, sizeof(HashedNode));
    map.size = hashmap_size;

    return map;
}

void cleanHashMap(HashMap *hm) { free(hm->buckets); }

void remove_value(int key, HashMap *hm) {
    const int hash = hashkey(key, hm->size);

    HashedNode node = hm->buckets[hash];

    HashedNode *prev = NULL;
    while (node.key_hash != hash) {
        assert(node.next != NULL);
        node = *node.next;

        if (key == node.key_hash) {
            *prev->next = *node.next;
        }

        prev = &node;
    }
}

int get_value(int key, HashMap *hm) {
    const int hash = hashkey(key, hm->size);

    HashedNode node = hm->buckets[hash];

    while (node.key_hash != hash) {
        assert(node.next != NULL);
        node = *node.next;
    }

    return node.value;
}

void add_value(int key, int value, HashMap *hm) {
    const unsigned int hash = hashkey(key, hm->size);

    // get inital hashed node
    HashedNode *node = &(hm->buckets[hash]);

    // find a free node
    while (node->next != NULL) {
        *node = *node->next;
    }

    // set values
    node->key_hash = hash;
    node->value = value;
}
