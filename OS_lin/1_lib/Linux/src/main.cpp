#include <iostream>
#include "number.h"
#include "vector.h"

int main() {
    std::cout << "Number Library Test" << std::endl;
    
    Number* a = number_create(5.0);
    Number* b = number_create(3.0);
    
    std::cout << "a = " << number_get_value(a) << std::endl;
    std::cout << "b = " << number_get_value(b) << std::endl;
    
    Number* sum = number_add(a, b);
    Number* diff = number_subtract(a, b);
    Number* prod = number_multiply(a, b);
    Number* quot = number_divide(a, b);
    
    std::cout << "a + b = " << number_get_value(sum) << std::endl;
    std::cout << "a - b = " << number_get_value(diff) << std::endl;
    std::cout << "a * b = " << number_get_value(prod) << std::endl;
    std::cout << "a / b = " << number_get_value(quot) << std::endl;
    
    std::cout << "NUMBER_ZERO = " << number_get_value(&NUMBER_ZERO) << std::endl;
    std::cout << "NUMBER_ONE = " << number_get_value(&NUMBER_ONE) << std::endl;
    
    number_destroy(a);
    number_destroy(b);
    number_destroy(sum);
    number_destroy(diff);
    number_destroy(prod);
    number_destroy(quot);
    
    std::cout << "\nVector Library Test===" << std::endl;
    
    Number* x1 = number_create(3.0);
    Number* y1 = number_create(4.0);
    Number* x2 = number_create(1.0);
    Number* y2 = number_create(2.0);
    
    Vector* v1 = vector_create(x1, y1);
    Vector* v2 = vector_create(x2, y2);
    Vector* v3 = vector_add(v1, v2);
    
    Number* v1_x = vector_get_x(v1);
    Number* v1_y = vector_get_y(v1);
    Number* v2_x = vector_get_x(v2);
    Number* v2_y = vector_get_y(v2);
    Number* v3_x = vector_get_x(v3);
    Number* v3_y = vector_get_y(v3);
    
    std::cout << "Vector v1: (" << number_get_value(v1_x) << ", " << number_get_value(v1_y) << ")" << std::endl;
    std::cout << "Vector v2: (" << number_get_value(v2_x) << ", " << number_get_value(v2_y) << ")" << std::endl;
    std::cout << "Vector v1 + v2: (" << number_get_value(v3_x) << ", " << number_get_value(v3_y) << ")" << std::endl;
    
    Number* v1_r = vector_get_r(v1);
    Number* v1_phi = vector_get_phi(v1);
    Number* v2_r = vector_get_r(v2);
    Number* v2_phi = vector_get_phi(v2);
    
    std::cout << "v1 polar: r=" << number_get_value(v1_r) << ", phi=" << number_get_value(v1_phi) << std::endl;
    std::cout << "v2 polar: r=" << number_get_value(v2_r) << ", phi=" << number_get_value(v2_phi) << std::endl;
    
    Number* zero_x = vector_get_x(&VECTOR_ZERO);
    Number* zero_y = vector_get_y(&VECTOR_ZERO);
    Number* one_one_x = vector_get_x(&VECTOR_ONE_ONE);
    Number* one_one_y = vector_get_y(&VECTOR_ONE_ONE);
    
    std::cout << "VECTOR_ZERO: (" << number_get_value(zero_x) << ", " << number_get_value(zero_y) << ")" << std::endl;
    std::cout << "VECTOR_ONE_ONE: (" << number_get_value(one_one_x) << ", " << number_get_value(one_one_y) << ")" << std::endl;
    
    number_destroy(x1);
    number_destroy(y1);
    number_destroy(x2);
    number_destroy(y2);
    number_destroy(v1_x);
    number_destroy(v1_y);
    number_destroy(v2_x);
    number_destroy(v2_y);
    number_destroy(v3_x);
    number_destroy(v3_y);
    number_destroy(v1_r);
    number_destroy(v1_phi);
    number_destroy(v2_r);
    number_destroy(v2_phi);
    number_destroy(zero_x);
    number_destroy(zero_y);
    number_destroy(one_one_x);
    number_destroy(one_one_y);
    
    vector_destroy(v1);
    vector_destroy(v2);
    vector_destroy(v3);
    
    return 0;
}
