// Concept: polymorphic collection.
// A vector of unique_ptr<Base> owns derived objects; virtual dispatch routes
// each call to the right override; unique_ptr cleans up via virtual dtor.
#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual const char* name() const = 0;
};

class Circle : public Shape {
public:
    Circle(double r) : r_(r) {}
    double area() const override { return 3.14159265 * r_ * r_; }
    const char* name() const override { return "Circle"; }
private:
    double r_;
};

class Square : public Shape {
public:
    Square(double s) : s_(s) {}
    double area() const override { return s_ * s_; }
    const char* name() const override { return "Square"; }
private:
    double s_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> canvas;
    canvas.push_back(std::make_unique<Circle>(2.0));
    canvas.push_back(std::make_unique<Square>(3.0));
    canvas.push_back(std::make_unique<Circle>(1.0));

    double total = 0;
    for (const auto& s : canvas) {
        std::cout << "  " << s->name() << " area=" << s->area() << "\n";
        total += s->area();
    }
    std::cout << "total area = " << total << "\n";
    // unique_ptr destroys each shape at end of scope (virtual dtor in Shape)
}
