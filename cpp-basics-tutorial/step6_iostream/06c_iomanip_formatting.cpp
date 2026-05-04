// Concept: <iomanip> — formatted output (precision, width, base, fill, …).
//
// vs C:
//   printf format specifiers like "%8.3f" or "%05d" do the same work, but
//   they are stringly-typed. <iomanip> is verbose but type-safe.
#include <iomanip>
#include <iostream>

int main() {
    double pi = 3.141592653589;

    std::cout << "default:                  " << pi << "\n";
    std::cout << "setprecision(3):          "
              << std::setprecision(3) << pi << "\n";
    std::cout << "fixed setprecision(5):    "
              << std::fixed << std::setprecision(5) << pi << "\n";

    // setw + setfill — like %05d / %-8s in printf
    std::cout << "setw(8) setfill('0'):     "
              << std::setw(8) << std::setfill('0') << 42 << "\n";

    // Number bases
    std::cout << "dec/hex/oct of 255:       "
              << std::dec << 255  << "  "
              << std::hex << 255  << "  "
              << std::oct << 255  << "\n";

    // boolalpha — already met in step 4
    std::cout << std::boolalpha << "true / false:             "
              << true << " / " << false << "\n";
}
