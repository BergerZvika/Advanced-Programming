// Concept: destructor — runs when an object goes out of scope.
// Within a scope, destructors fire in REVERSE order of construction (LIFO).
#include <iostream>

struct Tag {
    const char* name;
    Tag(const char* n) : name(n) { std::cout << "  ctor " << name << "\n"; }
    ~Tag()                       { std::cout << "  dtor " << name << "\n"; }
};

int main() {
    std::cout << "── enter scope ──\n";
    {
        Tag a("A");
        Tag b("B");
        Tag c("C");
        std::cout << "  (about to leave inner scope — dtors run C, B, A)\n";
    }
    std::cout << "── after scope ──\n";
}
