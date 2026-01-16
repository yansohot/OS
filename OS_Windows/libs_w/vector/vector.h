#pragma once

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

#include "number.h"

class VECTOR_API Vector {
private:
    Number x;
    Number y;

public:
    Vector(Number x_val = ZERO, Number y_val = ZERO);

    Number getR() const;
    Number getPhi() const;

    Vector operator+(const Vector& other) const;

    Number getX() const;
    Number getY() const;

    void setX(Number x_val);
    void setY(Number y_val);
};

extern VECTOR_API Vector ZERO_VECTOR;
extern VECTOR_API Vector ONE_ONE_VECTOR;