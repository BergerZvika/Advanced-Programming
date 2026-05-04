// Concept: move assignment — T& operator=(T&& other) noexcept.
// Steps: guard against self-move, release current resource, steal from other,
// null the source, return *this.
#include <cstddef>
#include <cstring>
#include <iostream>

class Buffer {
public:
    explicit Buffer(std::size_t n) : n_(n), data_(new int[n]) {
        std::cout << "  ctor   n=" << n_ << "\n";
    }
    ~Buffer() {
        if (data_) std::cout << "  dtor   n=" << n_ << "\n";
        else        std::cout << "  dtor   (moved-from, nothing to release)\n";
        delete[] data_;
    }

    // Move assignment
    Buffer& operator=(Buffer&& o) noexcept {
        if (this == &o) return *this;        // self-move guard
        delete[] data_;                      // release current resource
        n_      = o.n_;                      // steal
        data_   = o.data_;
        o.n_    = 0;                         // null the source
        o.data_ = nullptr;
        std::cout << "  move=  now hold n=" << n_ << "\n";
        return *this;
    }

    // (We rely on the compiler-generated copy ops here for brevity — a real
    // class with the move= above also needs a deep copy ctor and copy=,
    // see step10_rule_of_five/10f for the complete Rule of 5.)
    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& o) noexcept : n_(o.n_), data_(o.data_) {
        o.n_ = 0; o.data_ = nullptr;
    }

    std::size_t size() const { return n_; }

private:
    std::size_t n_;
    int*        data_;
};

int main() {
    Buffer a(4), b(8);
    std::cout << "before: a.size=" << a.size() << "  b.size=" << b.size() << "\n";
    a = std::move(b);     // move assignment
    std::cout << "after : a.size=" << a.size() << "  b.size=" << b.size() << "\n";
}
