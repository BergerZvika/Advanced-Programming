// Pitfall 2: non-virtual destructor leaks derived resources when deleting
// through a base pointer. ~Base alone runs; ~Derived is NEVER called.
#include <iostream>

class LeakyBase {                      // ⚠ no virtual dtor
public:
    ~LeakyBase() { std::cout << "  ~LeakyBase (non-virtual)\n"; }
};

class LeakyDerived : public LeakyBase {
public:
    LeakyDerived()  { std::cout << "  LeakyDerived ctor — allocated 256 bytes\n"; }
    ~LeakyDerived() { std::cout << "  ~LeakyDerived — freed buffer\n"; }
};

int main() {
    std::cout << "── delete LeakyDerived through LeakyBase* (non-virtual dtor) ──\n";
    LeakyBase* p = new LeakyDerived();
    delete p;       // ~LeakyDerived NEVER runs → buffer leaked
    std::cout << "  ⇧ ~LeakyDerived was skipped — leak!\n";
    std::cout << "Rule: declare the base destructor virtual when deleting via base*.\n";
}
