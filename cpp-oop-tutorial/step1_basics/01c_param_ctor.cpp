// Concept: parameterized constructor.
// Initialises members from arguments. Multiple ctors can coexist (overloading).
#include <iostream>

struct Point {
    double x, y;
    Point(double px, double py) : x(px), y(py) {     // parameterized ctor
        std::cout << "  Point(" << x << ", " << y << ") param ctor\n";
    }
};

int main() {
    Point a(3.0, 4.0);
    Point b{1.5, -2.5};   // brace init also calls the parameterized ctor
    std::cout << "a = (" << a.x << ", " << a.y << ")\n";
    std::cout << "b = (" << b.x << ", " << b.y << ")\n";
}
