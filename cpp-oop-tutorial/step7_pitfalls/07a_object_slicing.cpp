// Pitfall 1: object slicing.
// Passing/copying a polymorphic object BY VALUE truncates it down to the base
// part — the derived data and vtable info are LOST.
// Rule: pass polymorphic objects by reference or pointer, never by value.
#include <iostream>
#include <string>

class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string sound() const { return "<silence>"; }
};

class Dog : public Animal {
public:
    std::string sound() const override { return "Woof!"; }
};

void by_value(Animal a)        { std::cout << "  by value:     " << a.sound() << "  ← sliced!\n"; }
void by_reference(const Animal& a) { std::cout << "  by reference: " << a.sound() << "\n"; }
void by_pointer(const Animal* a)   { std::cout << "  by pointer:   " << a->sound() << "\n"; }

int main() {
    Dog d;
    by_value(d);       // SLICED — only the Animal part is copied
    by_reference(d);   // OK — vtable intact
    by_pointer(&d);    // OK — vtable intact
}
