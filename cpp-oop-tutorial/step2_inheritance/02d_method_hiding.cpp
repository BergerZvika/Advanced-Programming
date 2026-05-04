// Concept: method hiding — a non-virtual method in the derived class with the
// same name does NOT override the base; a base pointer still calls the BASE.
// (For true polymorphism, see step 3 — virtual functions.)
#include <iostream>
#include <string>

class Animal {
public:
    std::string sound() const { return "<silence>"; }   // NOT virtual
};

class Dog : public Animal {
public:
    std::string sound() const { return "Woof!"; }       // hides, doesn't override
};

int main() {
    Dog d;
    std::cout << "Dog::sound() directly        = " << d.sound() << "\n";

    Animal* p = &d;
    std::cout << "Animal* → sound() (no virt) = " << p->sound()
              << "   ← base version called\n";
}
