// Concept: typeid — runtime type information (RTTI).
// For a polymorphic object accessed via a base pointer/reference, typeid
// returns the type of the actual MOST-DERIVED object.
#include <iostream>
#include <typeinfo>

class Animal { public: virtual ~Animal() = default; };
class Dog : public Animal {};
class Cat : public Animal {};

int main() {
    Dog d;
    Animal& a = d;             // base reference, but actual object is Dog

    std::cout << "typeid(d).name()  = " << typeid(d).name() << "\n";
    std::cout << "typeid(a).name()  = " << typeid(a).name() << "  ← still Dog (polymorphic)\n";

    Animal* p = new Cat();
    std::cout << "typeid(*p).name() = " << typeid(*p).name() << "  ← Cat\n";
    delete p;

    std::cout << "Same type as Dog? "
              << (typeid(a) == typeid(Dog) ? "YES" : "NO") << "\n";
}
