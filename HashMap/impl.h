#pragma once

typedef struct HashedNode {
        int key_hash;
        int value;
        struct HashedNode *next;
} HashedNode;

typedef struct HashMap {
        struct HashedNode *buckets;
        unsigned int size;
} HashMap;

HashMap newHashMap(unsigned int hashmap_size);

void add_value(int key, int value, HashMap *hm);

int get_value(int key, HashMap *hm);

void remove_value(int key, HashMap *hm);

unsigned int hashkey(int key, const unsigned int hashmap_size);
unsigned int string_to_int(char *string);
void cleanHashMap(HashMap *hm);
