#ifndef NUMBER_H
#define NUMBER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Number {
    double value;
} Number;

Number* number_create(double value);
void number_destroy(Number* num);
double number_get_value(const Number* num);
void number_set_value(Number* num, double value);
Number* number_add(const Number* a, const Number* b);
Number* number_subtract(const Number* a, const Number* b);
Number* number_multiply(const Number* a, const Number* b);
Number* number_divide(const Number* a, const Number* b);

extern Number NUMBER_ZERO;
extern Number NUMBER_ONE;

#ifdef __cplusplus
}
#endif

#endif
