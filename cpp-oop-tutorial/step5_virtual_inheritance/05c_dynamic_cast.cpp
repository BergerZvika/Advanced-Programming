// Concept: dynamic_cast — safe runtime downcast.
//   - Returns the cast pointer if the object IS the requested type
//   - Returns nullptr if it is NOT  (and so guards against bad casts)
// Requires at least one virtual function in the base (a polymorphic class).
#include <iostream>

class Base {
public:
    virtual ~Base() = default;     // makes Base polymorphic
};

class Derived : public Base {
public:
    void only_in_derived() const { std::cout << "  Derived::only_in_derived\n"; }
};

class Other : public Base {};

int main() {
    Base* p1 = new Derived();
    Base* p2 = new Other();

    // Cast that should succeed
    if (auto* d = dynamic_cast<Derived*>(p1)) {
        std::cout << "p1 is Derived  — dynamic_cast succeeded\n";
        d->only_in_derived();
    }

    // Cast that should fail → nullptr (no UB, no exception)
    if (auto* d = dynamic_cast<Derived*>(p2)) {
        d->only_in_derived();
    } else {
        std::cout << "p2 is NOT Derived — dynamic_cast returned nullptr (safe)\n";
    }

    delete p1; delete p2;
}
