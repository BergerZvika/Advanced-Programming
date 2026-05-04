// Concept: construction & destruction order in single inheritance.
//   Construction: BASE first, then DERIVED.
//   Destruction:  DERIVED first, then BASE.   (LIFO)
#include <iostream>

class Base {
public:
    Base()  { std::cout << "  Base()  ctor\n"; }
    ~Base() { std::cout << "  Base()  dtor\n"; }
};

class Derived : public Base {
public:
    Derived()  { std::cout << "  Derived() ctor\n"; }
    ~Derived() { std::cout << "  Derived() dtor\n"; }
};

int main() {
    std::cout << "── creating Derived ──\n";
    {
        Derived d;
        std::cout << "  (about to leave scope)\n";
    }
    std::cout << "── after scope ──\n";
}
