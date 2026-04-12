#include <iostream>
#include <vector>
#include <iomanip>
#include "cmath_bridge.h"   // C functions called from C++
#include "cpp_analysis.h" // C++ class

int main() {
    std::cout << "=== Step 5: Mixed C and C++ ===\n\n";

    // Call C functions from C++
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "C functions:\n";
    std::cout << "  fast_sqrt(2)  = " << fast_sqrt(2.0)  << "\n";
    std::cout << "  fast_sqrt(9)  = " << fast_sqrt(9.0)  << "\n";
    std::cout << "  fast_log2(8)  = " << fast_log2(8.0)  << "\n";
    std::cout << "  fast_log2(1024) = " << fast_log2(1024.0) << "\n";

    // Use C++ Stats class
    std::vector<double> data = {4, 7, 13, 2, 1, 9, 15, 6};
    std::cout << "\nC++ Stats over {4,7,13,2,1,9,15,6}:\n";
    std::cout << "  mean   = " << Stats::mean(data)   << "\n";
    std::cout << "  stddev = " << Stats::stddev(data) << "\n";
    std::cout << "  median = " << Stats::median(data) << "\n";

    return 0;
}
