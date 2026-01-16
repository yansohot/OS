#include "vector.h"
#include <cmath>
#include <cstdlib>

Vector* vector_create(Number* x, Number* y) {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec) {
        vec->x = number_create(x ? number_get_value(x) : 0.0);
        vec->y = number_create(y ? number_get_value(y) : 0.0);
    }
    return vec;
}

void vector_destroy(Vector* vec) {
    if (vec) {
        if (vec != &VECTOR_ZERO && vec != &VECTOR_ONE_ONE) {
            if (vec->x != &NUMBER_ZERO && vec->x != &NUMBER_ONE) {
                number_destroy(vec->x);
            }
            if (vec->y != &NUMBER_ZERO && vec->y != &NUMBER_ONE) {
                number_destroy(vec->y);
            }
            free(vec);
        }
    }
}

Number* vector_get_r(const Vector* vec) {
    if (!vec) return number_create(0.0);
    double x_val = number_get_value(vec->x);
    double y_val = number_get_value(vec->y);
    return number_create(sqrt(x_val * x_val + y_val * y_val));
}

Number* vector_get_phi(const Vector* vec) {
    if (!vec) return number_create(0.0);
    double x_val = number_get_value(vec->x);
    double y_val = number_get_value(vec->y);
    return number_create(atan2(y_val, x_val));
}

Vector* vector_add(const Vector* a, const Vector* b) {
    if (!a || !b) return vector_create(NULL, NULL);
    
    Number* x_sum = number_add(a->x, b->x);
    Number* y_sum = number_add(a->y, b->y);
    Vector* result = vector_create(x_sum, y_sum);
    
    number_destroy(x_sum);
    number_destroy(y_sum);
    
    return result;
}

Number* vector_get_x(const Vector* vec) {
    if (!vec) return number_create(0.0);
    return number_create(number_get_value(vec->x));
}

Number* vector_get_y(const Vector* vec) {
    if (!vec) return number_create(0.0);
    return number_create(number_get_value(vec->y));
}

void vector_set_x(Vector* vec, Number* x) {
    if (vec && x) {
        if (vec->x != &NUMBER_ZERO && vec->x != &NUMBER_ONE) {
            number_destroy(vec->x);
        }
        vec->x = number_create(number_get_value(x));
    }
}

void vector_set_y(Vector* vec, Number* y) {
    if (vec && y) {
        if (vec->y != &NUMBER_ZERO && vec->y != &NUMBER_ONE) {
            number_destroy(vec->y);
        }
        vec->y = number_create(number_get_value(y));
    }
}

Vector VECTOR_ZERO = {&NUMBER_ZERO, &NUMBER_ZERO};
Vector VECTOR_ONE_ONE = {&NUMBER_ONE, &NUMBER_ONE};