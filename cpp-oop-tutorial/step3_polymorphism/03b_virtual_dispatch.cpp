// Concept: virtual functions enable RUNTIME dispatch via the vtable.
// A base pointer to a derived object calls the DERIVED override.
// 'override' (C++11) is a compile-time check — typos won't silently miss.
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

class Cat : public Animal {
public:
    std::string sound() const override { return "Meow!"; }
};

int main() {
    Dog d;  Cat c;  Animal a;
    Animal* zoo[] = { &a, &d, &c };
    for (Animal* p : zoo) {
        std::cout << "  " << p->sound() << "   ← dispatched at runtime via vtable\n";
    }
}
