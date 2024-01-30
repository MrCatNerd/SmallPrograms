#pragma once

typedef struct {
        float x, y, z;
} Vector3;

Vector3 newVector(float x, float y, float z);
Vector3 normalizeVector(Vector3 *v);
Vector3 fastNormalizeVector(Vector3 *v);
