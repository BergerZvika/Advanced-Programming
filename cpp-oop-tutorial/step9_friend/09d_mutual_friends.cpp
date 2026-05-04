// Concept: two classes can be mutual friends — each grants the other private
// access. Useful for tightly-coupled pairs (here Celsius ↔ Fahrenheit).
#include <iostream>

class Fahrenheit;     // forward declaration

class Celsius {
public:
    explicit Celsius(double c) : c_(c) {}
    double value() const { return c_; }
    friend class Fahrenheit;
private:
    double c_;
};

class Fahrenheit {
public:
    explicit Fahrenheit(const Celsius& c) : f_(c.c_ * 9.0/5.0 + 32.0) {}
    double value() const { return f_; }
    Celsius to_celsius() const { return Celsius((f_ - 32.0) * 5.0/9.0); }
    friend class Celsius;
private:
    double f_;
};

int main() {
    Celsius    c(100);
    Fahrenheit f(c);
    Celsius    back = f.to_celsius();
    std::cout << c.value() << " °C → " << f.value() << " °F → "
              << back.value() << " °C\n";
}
