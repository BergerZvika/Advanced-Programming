// Concept: const-correctness flows through inheritance.
// A const Shape* can only call const methods — derived overrides must keep
// the same const-ness for the override to count.
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;        // const — read-only operation
    virtual void   describe() const {       // const default behaviour
        std::cout << "  Shape area=" << area() << "\n";
    }
};

class Circle : public Shape {
public:
    Circle(double r) : r_(r) {}
    double area() const override { return 3.14159265 * r_ * r_; }
    // If we wrote 'double area() override' (no const), it would NOT override.
private:
    double r_;
};

void show(const Shape& s) { s.describe(); }   // works because describe() is const

int main() {
    Circle c(5);
    show(c);
}
