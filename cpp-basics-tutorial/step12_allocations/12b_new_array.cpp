// Concept: 'new[]' / 'delete[]' for dynamic arrays.
//
//   new T[n]        — allocates an array of n T's, default-constructs each.
//   delete[] p      — destroys each element in REVERSE order, then frees.
//
// CRITICAL: a 'new[]' result MUST be freed with 'delete[]'. Mixing
//   'delete' (singular) and 'new[]' is UB. Same applies between malloc/free.
//
// Modern advice: prefer std::vector or std::unique_ptr<T[]> over raw new[].
#include <iostream>

int main() {
    int n = 5;
    int* a = new int[n]{};      // value-init → all zeros
    for (int i = 0; i < n; ++i) a[i] = i * i;

    std::cout << "array contents:";
    for (int i = 0; i < n; ++i) std::cout << " " << a[i];
    std::cout << "\n";

    delete[] a;                 // matches new[] — calls dtor on each, then frees

    // delete a;                // ← UB: must use delete[] for array allocations
}
