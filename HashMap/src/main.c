#include <stdio.h>
#include <stdlib.h>

#include "include/hashmap.h"

int main(void) {
    // Initialize
    HashMap hm = createHashMap(0);

    // Test
    printf("Testing HashMap Implementation\n");

    // Test 1: Insertion, retrieval, and removal
    printf("\nTest 1: Insertion, Retrieval, and Removal\n");
    printf("1st layer buckets size: %lu bytes\n", sizeof(*(hm.buckets)));

    hashMapPut(stringToInt("meow"), 93232, &hm, false);
    int get = hashMapGet(stringToInt("meow"), &hm);
    printf("Retrieved value for key 'meow': %d\n", get);

    hashMapRemove(stringToInt("meow"), &hm);
    printf("Removed key 'meow'\n");

    // Test 2: Resizing
    printf("\nTest 2: Resizing\n");
    printf("Inserting 100 elements to trigger resizing...\n");
    for (int i = 0; i < 100; ++i) {
        hashMapPut(i, i * 10, &hm, false);
    }
    printf("Size of the hashmap after inserting 100 elements: %lu bytes\n",
           hashMapSize(&hm));

    // Test 3: Clean up
    printf("\nTest 3: Clean up\n");
    printf("Cleaning up the hashmap...\n");
    hashMapClean(&hm);

    printf("\nAll tests completed.\n");

    return EXIT_SUCCESS;
}
