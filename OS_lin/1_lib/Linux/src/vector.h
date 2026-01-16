#ifndef VECTOR_H
#define VECTOR_H

#include "number.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vector {
    Number* x;
    Number* y;
} Vector;

Vector* vector_create(Number* x, Number* y);
void vector_destroy(Vector* vec);
Number* vector_get_r(const Vector* vec);
Number* vector_get_phi(const Vector* vec);
Vector* vector_add(const Vector* a, const Vector* b);
Number* vector_get_x(const Vector* vec);
Number* vector_get_y(const Vector* vec);
void vector_set_x(Vector* vec, Number* x);
void vector_set_y(Vector* vec, Number* y);

extern Vector VECTOR_ZERO;
extern Vector VECTOR_ONE_ONE;

#ifdef __cplusplus
}
#endif

#endif
