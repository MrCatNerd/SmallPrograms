#include <stdio.h>
#include <stdlib.h>

#include "impl.h"

int main(void) {
    // Initialize
    unsigned int hashmap_size = 10;
    HashedNode *buckets = malloc(sizeof(HashedNode) * hashmap_size);

    for (unsigned int i = 0; i < hashmap_size; i++) {
        buckets[i].next = NULL;
    }

    // Test
    add_value(string_to_int("meow"), 11, &buckets, hashmap_size);
    int result = get_value(string_to_int("meow"), buckets, hashmap_size);
    printf("%d\n", result);

    // Heap cleanup
    free(buckets);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
