#include "hashmap.hpp"
#include "linked_list.hpp"

int HmSumString(char *string) {
    int sum = 0;

    for (unsigned int i = 0; i < sizeof(string); i++) {
        sum += (int)string[i];
    }

    return sum;
}

int HmHashFunction(const int value, const unsigned int size) {
    return value % size;
}

HashMap::HashMap(LinkedNode *buckets) { this->buckets = buckets; }

HashMap::~HashMap() { delete (this->buckets); }
