#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

int main(void) {
    // Initialize
    unsigned int hashmap_size = pow(2, 3); // needs to be a power of 2
    HashMap *hashmap = newHashMap(hashmap_size);

    // Test
    // for (int n = 0; n < 100; n++) {
    //     add_value(n, n * 2, &hashmap);
    // }
    // int result = get_value(string_to_int("meow"), &hashmap);
    // int result = get_value(12, &hashmap);
    // printf("%d\n", result);

    // remove_value(string_to_int("meow"), &hashmap);

    // Heap cleanup
    cleanHashMap(hashmap);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
