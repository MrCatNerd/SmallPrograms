#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

// TODO: less memory consumption

int main(void) {
    // Initialize
    unsigned int hashmap_size = pow(2, 5); // needs to be a power of 2
    HashMap hm = newHashMap(hashmap_size);

    // Test
    // FIXME: oh no removng items from start
    for (int n = 0; n < 100; n++) {
        addItemHashmap(n, n * 2, &hm);
    }
    addItemHashmap(string_to_int("meow"), 123, &hm);
    int result = getValueHashmap(string_to_int("meow"), &hm);
    printf("%d\n", result);

    removeItemHashmap(string_to_int("meow"), &hm);

    unsigned long hm_size_bytes = 0;
    // unsigned long hm_size_bytes = sizeof(hm);

    for (unsigned int i = 0; i < hm.size; i++) {
        Item *node = &(hm.buckets[i]);

        while (node->next != NULL) {
            hm_size_bytes += sizeof(*node);
            node = node->next;
        }
    }

    printf("%lu\n", hm_size_bytes);

    // Heap cleanup
    cleanHashMap(&hm);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
