// Concept: user-defined conversion operators.
//
//   operator T() const;            implicit conversion to T
//   explicit operator T() const;   convertible only via static_cast<T>(...) or
//                                   in conditions where bool is expected
//
// Rule of thumb: use 'explicit' UNLESS the conversion is genuinely lossless
// and unsurprising. Implicit conversions can fire in unexpected places and
// quietly change overload resolution.
//
// The classic safe-bool idiom uses 'explicit operator bool()' so that
//   if (obj) { ... }
// works, but
//   int x = obj + 5;        // ← compile error
// does not.
#include <iostream>
#include <string>

class FilePointer {
public:
    explicit FilePointer(const std::string& path)
        : path_(path), valid_(!path.empty() && path != "BAD") {}

    // explicit conversion to bool — used by `if (fp)` but NOT by accidental
    // arithmetic mixing.
    explicit operator bool() const { return valid_; }

    // implicit conversion to std::string — risky, but illustrative
    operator std::string() const { return "FilePointer(" + path_ + ")"; }

private:
    std::string path_;
    bool        valid_;
};

int main() {
    FilePointer ok ("data.txt");
    FilePointer bad("BAD");

    if (ok)  std::cout << "  ok  is truthy (operator bool)\n";
    if (!bad) std::cout << "  bad is falsy\n";

    // explicit means this would be illegal:
    //   bool b = ok;          // ← compile error: explicit conversion required
    bool b = static_cast<bool>(ok);
    std::cout << "  static_cast<bool>(ok) = " << b << "\n";

    // implicit conversion to std::string fires in contexts that expect a string:
    std::string s = ok;        // ← OK because operator string() is implicit
    std::cout << "  implicit to string: " << s << "\n";
}
