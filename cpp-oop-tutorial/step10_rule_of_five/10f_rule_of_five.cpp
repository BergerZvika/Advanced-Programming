// Concept: Rule of 5 — for a class that owns a raw resource, define ALL FIVE
// special member functions:
//     1. destructor
//     2. copy constructor      (deep copy)
//     3. copy assignment       (release + deep copy + return *this)
//     4. move constructor      (steal + null source) noexcept
//     5. move assignment       (release + steal + null source) noexcept
#include <cstddef>
#include <cstring>
#include <iostream>

class Buffer {
public:
    explicit Buffer(std::size_t n) : n_(n), data_(new int[n]) {
        std::cout << "  ctor       n=" << n_ << "\n";
    }

    // 1. destructor
    ~Buffer() {
        std::cout << "  dtor       n=" << n_
                  << (data_ ? "" : "  (moved-from)") << "\n";
        delete[] data_;
    }

    // 2. copy constructor
    Buffer(const Buffer& o) : n_(o.n_), data_(new int[o.n_]) {
        std::memcpy(data_, o.data_, n_ * sizeof(int));
        std::cout << "  copy ctor  n=" << n_ << "\n";
    }

    // 3. copy assignment
    Buffer& operator=(const Buffer& o) {
        if (this == &o) return *this;
        delete[] data_;
        n_    = o.n_;
        data_ = new int[o.n_];
        std::memcpy(data_, o.data_, n_ * sizeof(int));
        std::cout << "  copy=      n=" << n_ << "\n";
        return *this;
    }

    // 4. move constructor
    Buffer(Buffer&& o) noexcept : n_(o.n_), data_(o.data_) {
        o.n_ = 0; o.data_ = nullptr;
        std::cout << "  move ctor  stole n=" << n_ << "\n";
    }

    // 5. move assignment
    Buffer& operator=(Buffer&& o) noexcept {
        if (this == &o) return *this;
        delete[] data_;
        n_      = o.n_;    data_   = o.data_;
        o.n_    = 0;       o.data_ = nullptr;
        std::cout << "  move=      now hold n=" << n_ << "\n";
        return *this;
    }

    std::size_t size() const { return n_; }

private:
    std::size_t n_;
    int*        data_;
};

int main() {
    Buffer a(4);
    Buffer b = a;              // copy ctor
    Buffer c(2); c = a;        // copy assignment
    Buffer d = std::move(a);   // move ctor   (a is now empty)
    Buffer e(1); e = std::move(b);   // move assignment (b is now empty)
    std::cout << "sizes  a=" << a.size() << "  b=" << b.size()
              << "  c=" << c.size() << "  d=" << d.size()
              << "  e=" << e.size() << "\n";
}
