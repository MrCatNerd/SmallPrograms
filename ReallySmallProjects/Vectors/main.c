#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int main(void) {
    Vector3 my_vector = newVector(11.0, 10.0, 10.0);
    Vector3 newv = normalizeVector(&my_vector);
    Vector3 newf = fastNormalizeVector(&my_vector);

    printf("percise:\n\tx: %f\n\ty: %f\n\tz: %f\n\n", newv.x, newv.y, newv.z);
    printf("fast:\n\tx: %f\n\ty: %f\n\tz: %f\n", newf.x, newf.y, newf.z);

    return EXIT_SUCCESS;
}
