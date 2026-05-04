// Concept: multiple inheritance — a class can have more than one direct base.
// Construction order follows the DECLARATION order of base classes,
// destruction is the reverse.
#include <iostream>

class Flyable {
public:
    Flyable()  { std::cout << "  Flyable ctor\n"; }
    ~Flyable() { std::cout << "  Flyable dtor\n"; }
    void fly() const { std::cout << "  flying\n"; }
};

class Swimmable {
public:
    Swimmable()  { std::cout << "  Swimmable ctor\n"; }
    ~Swimmable() { std::cout << "  Swimmable dtor\n"; }
    void swim() const { std::cout << "  swimming\n"; }
};

class Duck : public Flyable, public Swimmable {     // ← multiple bases
public:
    Duck()  { std::cout << "  Duck ctor\n"; }
    ~Duck() { std::cout << "  Duck dtor\n"; }
    void quack() const { std::cout << "  Quack!\n"; }
};

int main() {
    std::cout << "── creating Duck (ctor order: Flyable, Swimmable, Duck) ──\n";
    Duck d;
    d.fly();
    d.swim();
    d.quack();
    std::cout << "── leaving scope (dtor order is reverse) ──\n";
}
