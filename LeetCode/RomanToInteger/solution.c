#include <stdbool.h>
#include <string.h>

#include "solution.h"

unsigned int raw_value(char c);

unsigned int romanToInt(char *s) {
    unsigned int sum = 0;
    bool skip = false;

    for (unsigned int i = 0; i < strlen(s); i++) {
        if (skip) {
            skip = false;
            continue;
        }

        unsigned int value = raw_value(s[i]);
        unsigned int next_value = raw_value(s[(i + 1) % strlen(s)]);

        if (next_value > value && i < strlen(s) - 1) {
            skip = true;

            sum += next_value - value;
        } else {
            sum += value;
        }
    }
    return sum;
}

unsigned int raw_value(char c) { // No hashmaps :(
    unsigned int value = 0;
    switch (c) {
    case 'I':
        value = 1;
        break;
    case 'V':
        value = 5;
        break;
    case 'X':
        value = 10;
        break;
    case 'L':
        value = 50;
        break;
    case 'C':
        value = 100;
        break;
    case 'D':
        value = 500;
        break;
    case 'M':
        value = 1000;
        break;
    default:
        break;
    };

    return value;
}
