#pragma once

#include "linked_list.hpp"

typedef struct HashMap HashMap;
struct HashMap {
    public:
        LinkedNode *buckets;

        HashMap(LinkedNode *buckets);
        ~HashMap();
};

int SumString(const int value, const unsigned int size);
int HashFunction(char *string);
