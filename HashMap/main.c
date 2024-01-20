#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

typedef struct HashMap HashMap;
struct HashMap {
        const unsigned int size;
        LinkedNode *list;
};

int hashfunction(const int value, const unsigned int size);
int sum_string(char *string);

int main(int argc, char *argv[]) {
    char *hashme = "meow meow meow";
    HashMap hm = {10, malloc(sizeof(int) * 10)};

    /* char chary = 'a';
    printf("%d\n", (int)chary); */

    printf("%d\n", sum_string(hashme));

    printf("Program ended\n");

    free(hm.list);

    return EXIT_SUCCESS;
}

int sum_string(char *string) {
    int sum = 0;

    for (int i = 0; i < sizeof(string); i++) {
        sum += (int)string[i];
    }

    return sum;
}

int hashfunction(const int value, const unsigned int size) {
    return value % size;
}
