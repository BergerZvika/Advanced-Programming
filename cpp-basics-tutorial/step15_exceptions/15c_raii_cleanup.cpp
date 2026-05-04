// Concept: RAII — Resource Acquisition Is Initialisation.
// In C++, cleanup is the destructor's job, not a finally block.
//
// vs C: in C you'd write
//
//     FILE* f = fopen(...); if (!f) goto err1;
//     int* buf = malloc(...); if (!buf) goto err2;
//     /* work */
//     err2: free(buf);
//     err1: fclose(f);
//
// Every error path has to remember every resource. With RAII, the destructor
// of each owning object runs automatically when the scope exits — INCLUDING
// when the exit is caused by an exception. There is no 'finally' in C++
// because RAII makes one unnecessary.
#include <iostream>
#include <stdexcept>

class Tag {
public:
    explicit Tag(const char* name) : name_(name) {
        std::cout << "  [" << name_ << "] acquired\n";
    }
    ~Tag() {
        std::cout << "  [" << name_ << "] released  (destructor — runs on exception too)\n";
    }
private:
    const char* name_;
};

void risky() {
    Tag a("A");
    Tag b("B");
    Tag c("C");
    throw std::runtime_error("something failed");
    // Even though the exception propagates out, ~C, ~B, ~A run in reverse order
    // automatically as the stack unwinds — no try/finally, no goto.
}

int main() {
    try {
        risky();
    } catch (const std::exception& e) {
        std::cout << "  caught: " << e.what() << "\n";
    }
    std::cout << "  back in main — note all destructors ran on the way out\n";
}
