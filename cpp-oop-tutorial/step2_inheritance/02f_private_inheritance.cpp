// Concept: private inheritance — "implemented-in-terms-of", NOT "is-a".
// All inherited members become private to Derived, so outside code cannot
// treat a Derived as a Base.
#include <iostream>

class Engine {
public:
    void start() const { std::cout << "  Engine: vroom!\n"; }
};

class Car : private Engine {     // private inheritance
public:
    void drive() const {
        start();                 // OK — Car CAN call Engine methods internally
        std::cout << "  Car is moving\n";
    }
};

int main() {
    Car c;
    c.drive();
    // c.start();   // ← compile error: 'Engine::start' is inaccessible due to
    //                  private inheritance. Outside code can't see Engine at all.
    std::cout << "(c.start() from outside would be a compile error)\n";
}
