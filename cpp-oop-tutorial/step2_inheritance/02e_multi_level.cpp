// Concept: multi-level inheritance.
// Animal → Mammal → Dog.  Dog inherits everything from Animal AND Mammal.
#include <iostream>
#include <string>

class Animal {
public:
    Animal(const std::string& n) : name_(n) {}
    void breathe() const { std::cout << "  " << name_ << " breathes air\n"; }
protected:
    std::string name_;
};

class Mammal : public Animal {
public:
    Mammal(const std::string& n) : Animal(n) {}
    void warm_blooded() const { std::cout << "  " << name_ << " is warm-blooded\n"; }
};

class Dog : public Mammal {
public:
    Dog(const std::string& n, const std::string& breed)
        : Mammal(n), breed_(breed) {}
    void fetch() const { std::cout << "  " << name_ << " (" << breed_ << ") fetches!\n"; }
private:
    std::string breed_;
};

int main() {
    Dog luna("Luna", "Husky");
    luna.breathe();        // from Animal
    luna.warm_blooded();   // from Mammal
    luna.fetch();          // from Dog
}
