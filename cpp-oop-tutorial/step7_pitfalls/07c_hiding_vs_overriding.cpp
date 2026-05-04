// Pitfall 3: hiding vs overriding.
// Without 'virtual', a same-named method in the derived class HIDES rather than
// overrides — the dispatch via base pointer goes to the BASE.
// 'override' (C++11) tells the compiler "this MUST override a virtual" — typos
// are caught at compile time.
#include <iostream>

class Base {
public:
    void hidden() const           { std::cout << "  Base::hidden\n"; }      // not virtual
    virtual void overridden() const { std::cout << "  Base::overridden\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void hidden() const           { std::cout << "  Derived::hidden\n"; }            // hides
    void overridden() const override { std::cout << "  Derived::overridden\n"; }     // overrides
};

int main() {
    Derived d;
    Base* p = &d;
    std::cout << "via Derived directly:\n";
    d.hidden(); d.overridden();
    std::cout << "via Base*:\n";
    p->hidden();      // Base version  ← hidden, not overridden
    p->overridden();  // Derived version ← virtual → polymorphic
}
