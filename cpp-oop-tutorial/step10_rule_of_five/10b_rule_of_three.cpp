// Concept: Rule of 3 — if a class manages a raw resource (heap buffer, file
// handle, mutex …) and you write ANY of these, you almost certainly need all
// three:
//     destructor, copy constructor, copy assignment.
// Without them, the compiler-generated SHALLOW copy gives two objects pointing
// at the same buffer → double-free / UB at scope exit.
#include <cstddef>
#include <cstring>
#include <iostream>

class Buffer {
public:
    explicit Buffer(std::size_t n) : n_(n), data_(new int[n]) {
        for (std::size_t i = 0; i < n_; ++i) data_[i] = 0;
        std::cout << "  ctor  buffer of " << n_ << " ints\n";
    }

    // 1. destructor — release the resource
    ~Buffer() {
        std::cout << "  dtor  releasing " << n_ << " ints\n";
        delete[] data_;
    }

    // 2. copy constructor — DEEP copy: allocate a fresh buffer
    Buffer(const Buffer& o) : n_(o.n_), data_(new int[o.n_]) {
        std::memcpy(data_, o.data_, n_ * sizeof(int));
        std::cout << "  copy ctor (deep)\n";
    }

    // 3. copy assignment — release old, deep-copy new
    Buffer& operator=(const Buffer& o) {
        if (this == &o) return *this;             // self-assignment guard
        delete[] data_;
        n_    = o.n_;
        data_ = new int[o.n_];
        std::memcpy(data_, o.data_, n_ * sizeof(int));
        std::cout << "  copy assign (deep)\n";
        return *this;
    }

    void set(std::size_t i, int v) { data_[i] = v; }
    int  get(std::size_t i) const  { return data_[i]; }

private:
    std::size_t n_;
    int*        data_;
};

int main() {
    Buffer a(4); a.set(0, 42);
    Buffer b = a;                  // copy ctor
    Buffer c(2); c = a;            // copy assign
    std::cout << "a[0]=" << a.get(0)
              << "  b[0]=" << b.get(0)
              << "  c[0]=" << c.get(0)
              << "  (each owns its own buffer — no double free)\n";
}
