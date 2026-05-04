// Concept: 'noexcept' — a promise that a function will NOT throw.
//
//   void f() noexcept;
//
// If a noexcept function ever DOES throw, the program calls std::terminate
// immediately — there's no propagation up the stack.
//
// Why mark functions noexcept?
//   - The compiler can sometimes generate better code (no unwind tables needed).
//   - STL containers prefer move ctors / move assignments that are noexcept;
//     std::vector reallocation will COPY instead of MOVE if the move can throw,
//     because it must leave a valid container if a move halfway through fails.
//
// Always mark MOVE constructors and MOVE assignments noexcept (see
// cpp-oop-tutorial/step10_rule_of_five for the full Rule of 5 treatment).
#include <iostream>
#include <utility>
#include <vector>

class Buffer {
public:
    Buffer() : data_(new int[64]) {}
    ~Buffer() { delete[] data_; }

    // Move constructor — marked noexcept so std::vector's grow path will
    // MOVE existing elements instead of copying them.
    Buffer(Buffer&& o) noexcept : data_(o.data_) { o.data_ = nullptr; }
    Buffer& operator=(Buffer&& o) noexcept {
        delete[] data_;
        data_ = o.data_; o.data_ = nullptr;
        return *this;
    }

    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;
private:
    int* data_;
};

// Compile-time test: is_nothrow_move_constructible
#include <type_traits>

int main() {
    static_assert(std::is_nothrow_move_constructible_v<Buffer>,
                  "Buffer's move constructor must be noexcept");

    std::vector<Buffer> v;
    v.reserve(4);
    v.emplace_back();
    v.emplace_back();
    v.emplace_back();
    v.emplace_back();
    // When the vector grows, it will move (not copy) Buffers because the
    // move ctor is noexcept. If the noexcept were missing, vector would have
    // to fall back to deep-copying — for a delete-only-copy class like Buffer
    // that would be a compile error.

    std::cout << "vector grew successfully — moves used the noexcept ctor\n";
}
