// Concept: CRTP — Curiously Recurring Template Pattern.
// A class derives from a TEMPLATE base parameterised on itself.
// Achieves polymorphism with NO virtual calls (resolved at compile time).
#include <iostream>

template <typename Derived>
class Printable {
public:
    void print() const {
        // Static cast to derived → calls derived's print_impl(), no vtable.
        static_cast<const Derived*>(this)->print_impl();
    }
};

class Hello : public Printable<Hello> {
public:
    void print_impl() const { std::cout << "  Hello!\n"; }
};

class Bye : public Printable<Bye> {
public:
    void print_impl() const { std::cout << "  Goodbye!\n"; }
};

int main() {
    Hello h;  Bye b;
    h.print();   // resolved at compile time → Hello::print_impl
    b.print();   // resolved at compile time → Bye::print_impl
    std::cout << "(no virtual calls — zero runtime overhead)\n";
}
