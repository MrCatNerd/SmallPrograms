#pragma once

typedef struct BucketNode {
        int key;
        int value;
        struct BucketNode *next;
} BucketNode;

typedef struct HashMap {
        struct BucketNode *buckets;
        unsigned int size;
} HashMap;

HashMap *newHashMap(unsigned int hashmap_size);

void add_value(int key, int value, HashMap *hm);

int get_value(int key, HashMap *hm);

void remove_value(int key, HashMap *hm);

unsigned int hashkey(int key, const unsigned int hashmap_size);
unsigned int string_to_int(char *string);
void cleanHashMap(HashMap *hm);
