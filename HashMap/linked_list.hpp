#pragma once

#define HASHMAP_INPUT_TYPE int // I am bad at C
typedef class LinkedNode LinkedNode;
class LinkedNode {
    public:
        HASHMAP_INPUT_TYPE current;
        LinkedNode *next;

        LinkedNode();
        ~LinkedNode();
};
