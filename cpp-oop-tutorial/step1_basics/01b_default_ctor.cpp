// Concept: default constructor (no arguments).
// Called when an object is created without any arguments: Point p;
#include <iostream>

struct Point {
    double x, y;
    Point() : x(0.0), y(0.0) {                       // default ctor
        std::cout << "  Point() default → (" << x << ", " << y << ")\n";
    }
};

int main() {
    Point p1;       // default ctor runs
    Point p2{};     // value-initialisation also calls the default ctor
    std::cout << "p1 = (" << p1.x << ", " << p1.y << ")\n";
    std::cout << "p2 = (" << p2.x << ", " << p2.y << ")\n";
}
