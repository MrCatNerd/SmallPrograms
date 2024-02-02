#pragma once

typedef struct Item {
        int key;
        int value;
        struct Item *next;
} Item;

typedef struct HashMap {      // bucket = node = item
        struct Item *buckets; // The bucket list
        unsigned int size;    // number of bucket pointers
        unsigned int nodes;   // the actual number of USED buckets
} HashMap;

HashMap newHashMap(unsigned int hashmap_size);

void addItemHashmap(int key, int value, HashMap *hm);

int getValueHashmap(int key, HashMap *hm);

void removeItemHashmap(int key, HashMap *hm);

unsigned int hashkey(int key, const unsigned int hashmap_size);
unsigned int string_to_int(const char *string);
void cleanHashMap(HashMap *hm);
unsigned long getHashMapSize(HashMap *hm);
