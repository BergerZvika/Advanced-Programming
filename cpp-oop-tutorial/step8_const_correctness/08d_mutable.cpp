// Concept: 'mutable' lets a member be modified even from a const method.
// Useful for caches, lazy evaluation, or thread-sync primitives — internal
// state changes that don't affect the object's logical/observable value.
#include <cmath>
#include <iostream>

class Sqrt {
public:
    Sqrt(double x) : x_(x) {}

    // const method — but it updates the cache. The cache is mutable.
    double get() const {
        if (!cached_) {
            std::cout << "  [computing sqrt of " << x_ << "...]\n";
            value_  = std::sqrt(x_);
            cached_ = true;
        }
        return value_;
    }
private:
    double x_;
    mutable double value_  = 0;
    mutable bool   cached_ = false;
};

int main() {
    const Sqrt s(49);            // const object — but get() can still cache
    std::cout << "first  call: " << s.get() << "\n";
    std::cout << "second call: " << s.get() << "  (cached — no recompute)\n";
}
