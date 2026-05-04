// Concept: 'constexpr' — evaluated at COMPILE time when possible.
// Stronger than const: const just means "don't modify this name", whereas
// constexpr means "computed at compile time, usable in compile-time contexts".
#include <iostream>

constexpr long factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr double area_circle(double r) {
    return 3.14159265 * r * r;
}

int main() {
    constexpr long f5 = factorial(5);            // computed at compile time
    constexpr double a = area_circle(10);        // computed at compile time

    int sz[factorial(4)];                        // 24 ints — array bound is constexpr
    static_assert(factorial(6) == 720);          // checked at compile time

    std::cout << "factorial(5) = " << f5 << "\n";
    std::cout << "area(r=10)   = " << a  << "\n";
    std::cout << "sizeof(sz)   = " << sizeof(sz) / sizeof(int) << " ints\n";
}
