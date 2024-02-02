#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

// TODO: less memory consumption
// FIXME: fix like, everything

int main(void) {
    // Initialize
    HashMap hm = newHashMap(pow(2, 4)); // needs to be a power of 2

    // Test
    addItemHashmap(string_to_int("meow"), 93232, &hm);

    // removeItemHashmap(string_to_int("meow"), &hm);

    unsigned long hm_size_bytes = getHashMapSize(&hm);
    printf("%lu\n", hm_size_bytes);

    // Heap cleanup
    cleanHashMap(&hm);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
