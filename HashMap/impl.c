#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "impl.h"

unsigned int string_to_int(char *string) {
    unsigned int sum = 0;
    for (int i = 0; i < (int)strlen(string); i++) {
        sum += (int)string[i];
    }

    return sum;
}

inline unsigned int hashkey(int key, const unsigned int hashmap_size) {
    return key % hashmap_size;
}

int get_value(int key, HashedNode *buckets, const unsigned int hashmap_size) {
    const int hash = hashkey(key, hashmap_size);

    HashedNode node = buckets[hash];

    printf("%d\n", node.key_hash);
    printf("%d\n", hash);
    while (node.key_hash != hash) {
        assert(node.next != NULL);
        node = *node.next;
    }

    return node.value;
}

void add_value(int key, int value, HashedNode **buckets,
               const unsigned int hashmap_size) {
    const unsigned int hash = hashkey(key, hashmap_size);

    // get inital hashed node
    HashedNode *node = &(*buckets)[hash];

    // find a free node
    while (node->next != NULL) {
        *node = *node->next;
    }

    // set values
    node->key_hash = hash;
    node->value = value;
}
