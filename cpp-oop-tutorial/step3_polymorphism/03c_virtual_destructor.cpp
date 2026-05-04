// Concept: virtual destructor — REQUIRED when deleting through a base pointer.
// Without 'virtual', only ~Base runs → derived resources leak.
#include <iostream>

class Base {
public:
    virtual ~Base() { std::cout << "  ~Base\n"; }   // virtual!
};

class Derived : public Base {
public:
    Derived()  { std::cout << "  Derived ctor (allocated 256-byte buffer)\n"; }
    ~Derived() { std::cout << "  ~Derived (freed buffer)\n"; }
};

int main() {
    std::cout << "── delete via Base* with virtual dtor ──\n";
    Base* p = new Derived();
    delete p;     // ~Derived runs first (vtable), then ~Base. Correct.
    std::cout << "── done ──\n";
    std::cout << "(if ~Base were non-virtual, ~Derived would not run → leak)\n";
}
