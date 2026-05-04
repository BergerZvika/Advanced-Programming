// Concept: covariant return type — the override may return a derived pointer
// where the base returned a base pointer.
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual Shape* clone() const = 0;        // base returns Shape*
};

class Circle : public Shape {
public:
    Circle(double r) : r_(r) {}
    Circle* clone() const override {         // covariant: returns Circle*
        return new Circle(r_);
    }
    double r() const { return r_; }
private:
    double r_;
};

int main() {
    Circle c(5.0);

    // through a base pointer → Shape*
    Shape*  base_clone = static_cast<const Shape&>(c).clone();
    std::cout << "via Shape*  → got a clone (cleanup via virtual dtor)\n";
    delete base_clone;

    // directly on Circle → Circle* (no cast needed to read r())
    Circle* circle_clone = c.clone();
    std::cout << "via Circle* → cloned r = " << circle_clone->r() << "\n";
    delete circle_clone;
}
