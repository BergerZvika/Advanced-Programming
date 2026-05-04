// Concept: abstract class — has at least one pure virtual function (= 0).
// Cannot be instantiated. Forces derived classes to implement the operation.
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;        // pure virtual → abstract
};

class Square : public Shape {
public:
    Square(double s) : side_(s) {}
    double area() const override { return side_ * side_; }
private:
    double side_;
};

int main() {
    // Shape s;            // ← compile error: cannot instantiate abstract class
    // Shape* s = new Shape();  // same error
    Square sq(4.0);
    std::cout << "Square(4) area = " << sq.area() << "\n";
    std::cout << "(Shape itself is abstract — direct instantiation would not compile)\n";
}
