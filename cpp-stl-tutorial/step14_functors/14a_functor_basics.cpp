// Concept: a FUNCTOR is a class with an overloaded operator() — an object
// you can CALL like a function.
//
// vs C: in C the closest tool is a function pointer. A function pointer
// can be passed around but it CANNOT carry per-instance state. A functor
// does both: it is callable AND it can store data members.
//
// "Anywhere a callable is wanted (algorithms, threads, schedulers), a
//  functor instance works."
#include <iostream>

class Greeter {
public:
    Greeter(const char* prefix) : prefix_(prefix) {}
    // operator() — what makes Greeter a "callable" / functor.
    void operator()(const char* who) const {
        std::cout << "  " << prefix_ << ", " << who << "!\n";
    }
private:
    const char* prefix_;
};

int main() {
    Greeter hello("Hello");
    Greeter ola  ("Olá");

    hello("Ada");          // looks like a function call — actually hello.operator()("Ada")
    hello("Linus");
    ola  ("Bjarne");

    // A function pointer cannot hold prefix_ — every function pointer of the
    // same signature is interchangeable. With a functor, EACH INSTANCE carries
    // its own data.
}
