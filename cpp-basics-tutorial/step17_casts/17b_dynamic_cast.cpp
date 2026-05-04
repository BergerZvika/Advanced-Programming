// Concept: dynamic_cast<T*>(p) — runtime-checked downcast in a polymorphic
// hierarchy.
//
//   - p must point to (or reference) a class that has at least one virtual
//     function — i.e. a polymorphic class. Otherwise the cast is rejected
//     at compile time.
//   - For pointers: returns nullptr on mismatch (safe to test).
//   - For references: throws std::bad_cast on mismatch.
//
// vs C: there is no equivalent — C has no runtime type info at all. The
// closest tool is "tagged unions" (a struct with an enum kind + payload).
#include <iostream>
#include <typeinfo>

class Animal {
public:
    virtual ~Animal() = default;     // makes Animal polymorphic
    virtual const char* sound() const { return "<silence>"; }
};

class Dog : public Animal {
public:
    const char* sound() const override { return "Woof!"; }
    void fetch() const { std::cout << "  Dog fetches\n"; }
};

class Cat : public Animal {
public:
    const char* sound() const override { return "Meow!"; }
};

int main() {
    Animal* zoo[] = { new Dog(), new Cat(), new Dog() };

    for (Animal* a : zoo) {
        std::cout << "  " << a->sound();
        if (Dog* d = dynamic_cast<Dog*>(a)) {     // safe downcast
            std::cout << " (is a Dog) → ";
            d->fetch();
        } else {
            std::cout << " (not a Dog)\n";
        }
    }

    // Reference form throws on mismatch
    Animal* a = new Cat();
    try {
        Dog& d = dynamic_cast<Dog&>(*a);          // ← throws std::bad_cast
        d.fetch();
    } catch (const std::bad_cast& e) {
        std::cout << "  caught bad_cast: " << e.what() << "\n";
    }

    for (Animal* a : zoo) delete a;
    delete a;
}
