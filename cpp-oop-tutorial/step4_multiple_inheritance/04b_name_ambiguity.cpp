// Concept: name ambiguity in multiple inheritance.
// If both bases have a member with the same name, you must qualify it
// using the class name and the scope-resolution operator (::).
#include <iostream>

class Flyable {
public:
    void describe() const { std::cout << "  Flyable describe\n"; }
};

class Swimmable {
public:
    void describe() const { std::cout << "  Swimmable describe\n"; }
};

class FlyingFish : public Flyable, public Swimmable {};

int main() {
    FlyingFish ff;
    // ff.describe();          // ← ambiguous: which base's describe()?
    ff.Flyable::describe();    // explicit qualification
    ff.Swimmable::describe();
    std::cout << "(unqualified ff.describe() would be a compile error)\n";
}
