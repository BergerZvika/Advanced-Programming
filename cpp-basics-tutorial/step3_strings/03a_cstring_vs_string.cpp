// Concept: C-string (char array) vs std::string.
//
// vs C:
//   C strings are null-terminated char arrays — fixed buffer, manual length
//   tracking with strlen, manual concatenation with strcpy/strcat. Buffer
//   overflow is a constant risk.
//   std::string owns its memory, knows its length in O(1), grows
//   automatically, and frees itself when it goes out of scope (RAII).
#include <cstring>     // strlen, strcpy
#include <iostream>
#include <string>      // std::string

int main() {
    // ── C string ────────────────────────────────────────────────
    char  c_buf[32];
    std::strcpy(c_buf, "Hello, ");
    std::strcat(c_buf, "C!");                     // hope c_buf is big enough!
    std::cout << "C string:    " << c_buf
              << "   length=" << std::strlen(c_buf) << "\n";

    // ── C++ string ──────────────────────────────────────────────
    std::string s = "Hello, ";
    s += "C++!";                                  // operator+= grows as needed
    std::cout << "std::string: " << s
              << "  length=" << s.length()
              << "  capacity=" << s.capacity() << "\n";

    // Convert when you need a char* (e.g. for a C API):
    const char* raw = s.c_str();
    std::cout << "as char*:    " << raw << "\n";
}
