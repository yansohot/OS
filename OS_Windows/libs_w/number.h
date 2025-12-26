#pragma once

#ifdef NUMBER_EXPORTS
#define NUMBER_API __declspec(dllexport)
#else
#define NUMBER_API __declspec(dllimport)
#endif

class Number {
private:
    double value;

public:
    Number(double val = 0.0);

    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;

    double getValue() const;
    void setValue(double val);
};

extern NUMBER_API Number ZERO;
extern NUMBER_API Number ONE;

extern "C" NUMBER_API Number* createNumber(double value);