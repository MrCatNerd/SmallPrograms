#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "impl.h"

int main(void) {
    // Initialize
    unsigned int hashmap_size = pow(2, 3); // needs to be a power of 2
    HashMap hashmap = newHashMap(hashmap_size);

    // Test
    add_value(string_to_int("meow"), 11, &hashmap);
    int result = get_value(string_to_int("meow"), &hashmap);
    printf("%d\n", result);

    remove_value(string_to_int("meow"), &hashmap);

    // Heap cleanup
    cleanHashMap(&hashmap);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
