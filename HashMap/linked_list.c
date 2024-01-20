#include "linked_list.h"

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
        HASHMAP_INPUT_TYPE current;
        LinkedNode *next;
};
