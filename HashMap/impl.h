#pragma once

typedef struct HashedNode {
        int key_hash;
        int value;
        struct HashedNode *next;
} HashedNode;

unsigned int string_to_int(char *string);
unsigned int hashkey(int key, const unsigned int hashmap_size);

void add_value(int key, int value, HashedNode **buckets,
               const unsigned int hashmap_size);

int get_value(int key, HashedNode *buckets, const unsigned int hashmap_size);
