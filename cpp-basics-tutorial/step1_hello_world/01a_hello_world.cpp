// Concept: the simplest C++ program.
//
// vs C:
//   In C the standard greeting was:
//       #include <stdio.h>
//       int main(void) { printf("Hello, World!\n"); return 0; }
//   In C++ you typically use <iostream> + std::cout, no manual return needed:
//       int main() returns 0 implicitly.
#include <iostream>

int main() {
    std::cout << "Hello, C++!\n";
    // 'return 0;' is OPTIONAL in main() — it is implied if you fall off the end.
}
