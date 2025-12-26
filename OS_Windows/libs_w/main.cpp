#include <iostream>
#include <windows.h>
#include "number.h"
#include "vector.h"

int main() {
    std::cout << "=== Number Library Test ===" << std::endl;

    Number* a = createNumber(5.0);
    Number* b = createNumber(3.0);

    std::cout << "a = " << a->getValue() << std::endl;
    std::cout << "b = " << b->getValue() << std::endl;

    Number sum = *a + *b;
    Number diff = *a - *b;
    Number prod = *a * *b;
    Number quot = *a / *b;

    std::cout << "a + b = " << sum.getValue() << std::endl;
    std::cout << "a - b = " << diff.getValue() << std::endl;
    std::cout << "a * b = " << prod.getValue() << std::endl;
    std::cout << "a / b = " << quot.getValue() << std::endl;

    std::cout << "ZERO = " << ZERO.getValue() << std::endl;
    std::cout << "ONE = " << ONE.getValue() << std::endl;

    delete a;
    delete b;

    std::cout << "\n=== Vector Library Test ===" << std::endl;

    Vector v1(Number(3.0), Number(4.0));
    Vector v2(Number(1.0), Number(2.0));
    Vector v3 = v1 + v2;

    std::cout << "Vector v1: (" << v1.getX().getValue() << ", " << v1.getY().getValue() << ")" << std::endl;
    std::cout << "Vector v2: (" << v2.getX().getValue() << ", " << v2.getY().getValue() << ")" << std::endl;
    std::cout << "Vector v1 + v2: (" << v3.getX().getValue() << ", " << v3.getY().getValue() << ")" << std::endl;

    std::cout << "v1 polar: r=" << v1.getR().getValue() << ", phi=" << v1.getPhi().getValue() << std::endl;
    std::cout << "v2 polar: r=" << v2.getR().getValue() << ", phi=" << v2.getPhi().getValue() << std::endl;

    std::cout << "ZERO_VECTOR: (" << ZERO_VECTOR.getX().getValue() << ", " << ZERO_VECTOR.getY().getValue() << ")" << std::endl;
    std::cout << "ONE_ONE_VECTOR: (" << ONE_ONE_VECTOR.getX().getValue() << ", " << ONE_ONE_VECTOR.getY().getValue() << ")" << std::endl;

    return 0;
}