// Concept: why manual memory management is dangerous.
//
// Common bugs you can hit with raw new/delete (every one of these is UB):
//   - leak               — forget to delete
//   - double free        — delete the same pointer twice
//   - use after free     — keep using a pointer after delete
//   - exception leak     — exception thrown between new and delete
//
// vs C: same bug classes as malloc/free; C++ adds a way out via RAII (smart
// pointers — step 13). Heap-owning classes should follow the Rule of 5
// (see cpp-oop-tutorial step 10).
#include <iostream>

class Tag {
public:
    Tag(int id) : id_(id) { std::cout << "  Tag ctor #" << id_ << "\n"; }
    ~Tag()                { std::cout << "  Tag dtor #" << id_ << "\n"; }
private:
    int id_;
};

void leaky() {
    Tag* t = new Tag(1);
    if (true) return;          // ← early return → 't' is leaked
    delete t;
}

void exception_leak() {
    Tag* t = new Tag(2);
    try {
        throw 99;              // ← exception thrown before delete → leak
        delete t;
    } catch (int) {
        std::cout << "  caught — but Tag #2 was leaked\n";
    }
}

int main() {
    std::cout << "── leaky() — early return ──\n";
    leaky();
    std::cout << "  ⇧ ~Tag never ran → leak\n";

    std::cout << "── exception_leak() ──\n";
    exception_leak();

    std::cout << "Smart pointers (step 13) eliminate all four classes of bug above.\n";
}
