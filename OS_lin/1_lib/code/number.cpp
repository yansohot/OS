#include "number.h"
#include <cstdlib>

Number* number_create(double value) {
    Number* num = (Number*)malloc(sizeof(Number));
    if (num) {
        num->value = value;
    }
    return num;
}

void number_destroy(Number* num) {
    if (num) {
        free(num);
    }
}

double number_get_value(const Number* num) {
    return num ? num->value : 0.0;
}

void number_set_value(Number* num, double value) {
    if (num) {
        num->value = value;
    }
}

Number* number_add(const Number* a, const Number* b) {
    if (!a || !b) return number_create(0.0);
    return number_create(a->value + b->value);
}

Number* number_subtract(const Number* a, const Number* b) {
    if (!a || !b) return number_create(0.0);
    return number_create(a->value - b->value);
}

Number* number_multiply(const Number* a, const Number* b) {
    if (!a || !b) return number_create(0.0);
    return number_create(a->value * b->value);
}

Number* number_divide(const Number* a, const Number* b) {
    if (!a || !b) return number_create(0.0);
    return number_create(a->value / b->value);
}

Number NUMBER_ZERO = {0.0};
Number NUMBER_ONE = {1.0};
