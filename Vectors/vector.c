#include <math.h>

#include "vector.h"

float fast_inverse_sqrt(float number);

Vector3 newVector(float x, float y, float z) {
    Vector3 v = {x, y, z};
    return v;
}

Vector3 normalizeVector(Vector3 *v) {
    Vector3 u;

    float inv_magnitude = 1 / sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

    u.x = v->x * inv_magnitude;
    u.y = v->y * inv_magnitude;
    u.z = v->z * inv_magnitude;

    return u;
}

Vector3 fastNormalizeVector(Vector3 *v) {
    Vector3 u;

    float inv_magnitude =
        fast_inverse_sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

    u.x = v->x * inv_magnitude;
    u.y = v->y * inv_magnitude;
    u.z = v->z * inv_magnitude;

    return u;
}

float fast_inverse_sqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(long *)&y;
    i = 0x5f375a86 - (i >> 1);
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));
    return y;
}
