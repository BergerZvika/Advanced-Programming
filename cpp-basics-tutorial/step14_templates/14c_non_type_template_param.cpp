// Concept: NON-TYPE template parameters — an integral CONSTANT (or pointer,
// reference, enum, …) baked into the type at compile time.
//
// std::array<T, N> is the canonical example: the size N is part of the type,
// not a runtime field.
//
// vs C: a "fixed-size array struct" in C requires either a macro or a wrapped
// type per size. C++ lets the COMPILER bake the constant into the type.
#include <array>
#include <iostream>

template <typename T, size_t N>          // N is a non-type template param
class FixedBuffer {
public:
    constexpr size_t capacity() const { return N; }
    T& operator[](size_t i)           { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

private:
    T data_[N];        // size known at compile time → can live on the stack
};

int main() {
    FixedBuffer<int, 4> small;
    for (size_t i = 0; i < small.capacity(); ++i) small[i] = static_cast<int>(i * 10);

    std::cout << "FixedBuffer<int, 4> capacity = " << small.capacity() << "\n";
    std::cout << "small[2] = " << small[2] << "\n";

    // Different N → different TYPE.
    FixedBuffer<int, 8> bigger;
    std::cout << "FixedBuffer<int, 8> capacity = " << bigger.capacity() << "\n";

    // std::array is just a polished version of the above.
    std::array<double, 3> arr{1.0, 2.5, 3.5};
    std::cout << "std::array<double, 3>[1] = " << arr[1] << "\n";
}
