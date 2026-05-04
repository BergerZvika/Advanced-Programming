// Concept: the std::exception hierarchy.
//
// All standard exceptions inherit from std::exception, which exposes a single
// virtual member: const char* what() const noexcept.
//
//   std::exception
//   ├── std::logic_error      (programmer's fault — should not happen)
//   │   ├── std::invalid_argument
//   │   ├── std::domain_error
//   │   ├── std::length_error
//   │   └── std::out_of_range
//   └── std::runtime_error    (something the program could not predict)
//       ├── std::range_error
//       ├── std::overflow_error
//       └── std::underflow_error
//
// Define your OWN exception types by deriving from std::exception (or, more
// commonly, std::runtime_error) and providing a constructor that takes a
// string message.
#include <iostream>
#include <stdexcept>
#include <string>

class FileError : public std::runtime_error {
public:
    explicit FileError(const std::string& path)
        : std::runtime_error("FileError: cannot open '" + path + "'") {}
};

int main() {
    try {
        // std::stoi throws on garbage input
        int n = std::stoi("hello");
        std::cout << "got " << n << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "  invalid_argument: " << e.what() << "\n";
    }

    try {
        // std::vector::at performs bounds checking
        std::string s = "abc";
        char c = s.at(99);
        std::cout << "got " << c << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "  out_of_range:     " << e.what() << "\n";
    }

    // Custom exception type — re-uses the standard hierarchy
    try {
        throw FileError("/etc/missing");
    } catch (const std::exception& e) {     // catches FileError too
        std::cout << "  custom:           " << e.what() << "\n";
    }
}
