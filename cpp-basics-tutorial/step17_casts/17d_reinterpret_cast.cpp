// Concept: reinterpret_cast<T>(x) — bit-level reinterpretation between
// otherwise-unrelated types. The MOST dangerous of the four C++ casts.
//
// Almost all uses are one of:
//   - low-level systems code (drivers, hardware registers)
//   - serialisation / deserialisation of bytes
//   - inspecting raw bytes for debug printing
//
// When you reach for reinterpret_cast, ask whether static_cast or std::memcpy
// would do the job correctly — they often do.
//
// ⚠ Many uses of reinterpret_cast violate the strict aliasing rule and lead
//    to undefined behaviour. Prefer std::memcpy for type-punning.
#include <cstdint>
#include <cstring>
#include <iostream>

int main() {
    // 1) Inspect the bytes of a float — typical type-punning use case.
    //    The CORRECT way is std::memcpy; reinterpret_cast on a different
    //    type is technically UB under strict aliasing.
    float f = 3.14f;
    std::uint32_t bits;
    std::memcpy(&bits, &f, sizeof bits);                // ← preferred
    std::cout << "  bits of " << f << " = 0x" << std::hex << bits << std::dec << "\n";

    // 2) Pointer ↔ integer — sometimes used for hashing, debugging, mmaps.
    int x = 42;
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(&x);
    std::cout << "  &x as uintptr_t = " << std::hex << addr << std::dec << "\n";

    // 3) Talking to a hardware register / arbitrary-address pointer:
    //    volatile uint32_t* reg = reinterpret_cast<volatile uint32_t*>(0x40000000);
    //    *reg = 1;
    std::cout << "  (real hardware-register casts look like this in driver code)\n";

    // Don't:
    //    int* ip = ...;
    //    double* dp = reinterpret_cast<double*>(ip);   // strict-aliasing UB on access
    //    *dp = 1.0;
}
