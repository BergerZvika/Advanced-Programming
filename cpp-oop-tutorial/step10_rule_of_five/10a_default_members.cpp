// Concept: the FIVE special member functions and what the compiler generates.
//   1. destructor              ~T()
//   2. copy constructor        T(const T&)
//   3. copy assignment         T& operator=(const T&)
//   4. move constructor        T(T&&)              [C++11]
//   5. move assignment         T& operator=(T&&)   [C++11]
// If you don't write them, the compiler synthesises shallow / member-wise
// versions for you. You can also force them with '= default' or remove them
// with '= delete'.
#include <iostream>
#include <string>

class Plain {
    // No special members written → the compiler generates all 5,
    // each one performing member-wise copy / move on data_.
    std::string data_;
public:
    Plain(std::string d) : data_(std::move(d)) {}
    const std::string& data() const { return data_; }
};

class Explicit {
    std::string data_;
public:
    Explicit(std::string d) : data_(std::move(d)) {}
    const std::string& data() const { return data_; }

    // '= default' → ask the compiler for the standard implementation.
    ~Explicit()                          = default;
    Explicit(const Explicit&)            = default;
    Explicit& operator=(const Explicit&) = default;
    Explicit(Explicit&&) noexcept        = default;
    Explicit& operator=(Explicit&&)      = default;
};

class NonCopyable {
    int n_;
public:
    NonCopyable(int n) : n_(n) {}
    // '= delete' → forbid the operation. Trying to copy will not compile.
    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    int n() const { return n_; }
};

int main() {
    Plain a("hello"), b = a;                  // copy ctor (compiler-generated)
    Explicit x("world"), y = std::move(x);    // move ctor (= default)
    NonCopyable nc(7);
    // NonCopyable nc2 = nc;   // ← compile error: deleted copy ctor
    std::cout << "Plain    a=" << a.data() << "  b=" << b.data() << "\n";
    std::cout << "Explicit y=" << y.data() << "\n";
    std::cout << "NonCopyable.n() = " << nc.n() << "  (copy was = delete)\n";
}
