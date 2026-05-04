// Concept: const objects may only call CONST methods.
// The compiler refuses any call that could mutate a const object.
#include <iostream>

class Counter {
public:
    int  value() const  { return n_; }      // const — OK on const objects
    void inc()          { ++n_; }            // non-const — only on mutable objects
private:
    int n_ = 0;
};

int main() {
    Counter c;
    c.inc(); c.inc();
    std::cout << "c (mutable)  value = " << c.value() << "\n";

    const Counter& cc = c;
    std::cout << "cc (const)   value = " << cc.value() << "\n";
    // cc.inc();   // ← compile error: passing 'const Counter' as 'this' discards const
    std::cout << "(cc.inc() would not compile)\n";
}
