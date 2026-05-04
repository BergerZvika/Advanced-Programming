// Concept: public inheritance — Derived "is-a" Base.
// Derived gains all public/protected members of Base.
#include <iostream>
#include <string>

class Animal {
public:
    Animal(const std::string& name) : name_(name) {}
    void breathe() const { std::cout << "  " << name_ << " breathes air\n"; }
    std::string name() const { return name_; }
protected:
    std::string name_;
};

class Dog : public Animal {              // public inheritance
public:
    Dog(const std::string& name) : Animal(name) {}    // chain to base ctor
    void bark() const { std::cout << "  " << name_ << ": Woof!\n"; }
};

int main() {
    Dog rex("Rex");
    rex.breathe();   // inherited from Animal
    rex.bark();      // Dog's own method
    std::cout << "name: " << rex.name() << "\n";
}
