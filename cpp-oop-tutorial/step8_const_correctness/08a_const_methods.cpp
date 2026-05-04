// Concept: const member functions.
// 'const' after the parameter list promises the method does not modify
// observable object state. A const method may NOT call non-const methods.
#include <iostream>

class Temperature {
public:
    Temperature(double c) : celsius_(c) {}

    double celsius()    const { return celsius_; }                  // const — read only
    double fahrenheit() const { return celsius_ * 9.0/5.0 + 32.0; } // const — read only

    void set_celsius(double c) { celsius_ = c; }                    // NOT const — mutates

private:
    double celsius_;
};

int main() {
    Temperature t(20);
    std::cout << "celsius    = " << t.celsius()    << "\n";
    std::cout << "fahrenheit = " << t.fahrenheit() << "\n";
    t.set_celsius(100);
    std::cout << "celsius    = " << t.celsius()    << " (after set)\n";
}
