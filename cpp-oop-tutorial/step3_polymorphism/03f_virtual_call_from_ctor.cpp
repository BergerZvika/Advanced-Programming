// Concept: virtual calls from a constructor do NOT dispatch to the derived
// override — the derived part isn't constructed yet, so the base version runs.
// Same caveat applies to destructors. (Full pitfalls walkthrough in step 7.)
#include <iostream>

class Base {
public:
    Base() {
        std::cout << "  Base ctor — calling virtual greet()\n";
        greet();           // dispatches to Base::greet, NOT Derived::greet
    }
    virtual ~Base() = default;
    virtual void greet() const { std::cout << "  Base::greet\n"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "  Derived ctor\n"; }
    void greet() const override { std::cout << "  Derived::greet\n"; }
};

int main() {
    std::cout << "── constructing Derived ──\n";
    Derived d;
    std::cout << "── after construction, calling greet() ──\n";
    d.greet();           // now dispatches to Derived::greet (object fully built)
}
