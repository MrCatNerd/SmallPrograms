#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

int main(void) {
    // Initialize
    unsigned int hashmap_size = pow(2, 5); // needs to be a power of 2
    HashMap hm = newHashMap(hashmap_size);

    // Test
    for (int n = 0; n < 100; n++) {
        addItemHashmap(n, n * 2, &hm);
    }
    addItemHashmap(string_to_int("meow"), 123, &hm);
    int result = getValueHashmap(string_to_int("meow"), &hm);
    printf("%d\n", result);

    removeItemHashmap(string_to_int("meow"), &hm);

    // Heap cleanup
    cleanHashMap(&hm);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
