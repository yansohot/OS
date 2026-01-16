#include "pch.h"
#include "vector.h"

Vector::Vector(Number x_val, Number y_val) : x(x_val), y(y_val) {}

Number Vector::getR() const {
    Number x_sq = x * x;
    Number y_sq = y * y;
    Number sum = x_sq + y_sq;
    return createNumber(sqrt(sum.getValue()));
}

Number Vector::getPhi() const {
    return createNumber(atan2(y.getValue(), x.getValue()));
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

Number Vector::getX() const {
    return x;
}

Number Vector::getY() const {
    return y;
}

void Vector::setX(Number x_val) {
    x = x_val;
}

void Vector::setY(Number y_val) {
    y = y_val;
}

Vector ZERO_VECTOR(ZERO, ZERO);
Vector ONE_ONE_VECTOR(ONE, ONE);