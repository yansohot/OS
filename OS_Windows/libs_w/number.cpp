#include "number.h"

Number::Number(double val) : value(val) {}

Number Number::operator+(const Number& other) const {
    return Number(value + other.value);
}

Number Number::operator-(const Number& other) const {
    return Number(value - other.value);
}

Number Number::operator*(const Number& other) const {
    return Number(value * other.value);
}

Number Number::operator/(const Number& other) const {
    return Number(value / other.value);
}

double Number::getValue() const {
    return value;
}

void Number::setValue(double val) {
    value = val;
}

NUMBER_API Number ZERO(0.0);
NUMBER_API Number ONE(1.0);

extern "C" NUMBER_API Number* createNumber(double value) {
    return new Number(value);
}