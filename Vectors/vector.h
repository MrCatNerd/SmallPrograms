#pragma once

typedef struct {
        float x, y, z;
} Vector;

Vector newVector(float x, float y, float z);
Vector normalizeVector(Vector *v);
Vector fastNormalizeVector(Vector *v);
