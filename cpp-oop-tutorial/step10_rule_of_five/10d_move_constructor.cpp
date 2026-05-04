// Concept: move constructor — T(T&& other).
// Steal 'other's resources, leave 'other' in a valid empty state.
// Mark it 'noexcept' so std::vector and friends pick the move path.
#include <cstddef>
#include <cstring>
#include <iostream>

class Buffer {
public:
    explicit Buffer(std::size_t n) : n_(n), data_(new int[n]) {
        std::cout << "  ctor       n=" << n_ << "\n";
    }
    ~Buffer() {
        std::cout << "  dtor       n=" << n_ << "  data=" << static_cast<void*>(data_) << "\n";
        delete[] data_;
    }

    // Copy ctor — deep copy
    Buffer(const Buffer& o) : n_(o.n_), data_(new int[o.n_]) {
        std::memcpy(data_, o.data_, n_ * sizeof(int));
        std::cout << "  copy ctor  n=" << n_ << "\n";
    }

    // Move ctor — STEAL the pointer, NULL the source.
    // 'noexcept' lets STL containers prefer move over copy on reallocation.
    Buffer(Buffer&& o) noexcept
        : n_(o.n_), data_(o.data_)
    {
        o.n_    = 0;
        o.data_ = nullptr;        // ← critical: avoid double-free
        std::cout << "  move ctor  stole " << n_ << " ints\n";
    }

    std::size_t size() const { return n_; }

private:
    std::size_t n_;
    int*        data_;
};

int main() {
    Buffer a(8);
    Buffer b = std::move(a);   // move ctor — a is now empty
    std::cout << "after move: a.size=" << a.size() << "  b.size=" << b.size() << "\n";
    // 'a' is destroyed safely because data_ was nulled in the move.
}
