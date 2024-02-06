#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

// TODO: less memory consumption
// FIXME: fix like, everything

int main(void) {
    // Initialize
    HashMap hm = createHashMap(pow(2, 4)); // needs to be a power of 2

    // Test
    int i = 12;
    while (--i) {
        hashMapPut(i, 93232, &hm);
    }

    hashMapPut(stringToInt("meow"), 93232, &hm);

    // removeItemHashmap(stringToInt("meow"), &hm);

    unsigned long hm_size_bytes = hashMapSize(&hm);
    printf("%lu\n", hm_size_bytes);

    hashMapResize(&hm, pow(2, 6));

    hm_size_bytes = hashMapSize(&hm);
    printf("%lu\n", hm_size_bytes);

    // Heap cleanup
    hashMapClean(&hm);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
