#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.hpp"
#include "linked_list.hpp"

// TODO: put hashmap in a different file
int main(void) {
    HashMap hm(new LinkedNode[10]);

    printf("Program ended\n");

    return EXIT_SUCCESS;
}
