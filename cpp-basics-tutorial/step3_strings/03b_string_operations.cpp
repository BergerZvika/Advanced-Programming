// Concept: common std::string operations.
//
// vs C:
//   substring → strncpy + null term     vs   s.substr(pos, len)
//   find      → strstr                  vs   s.find("needle")
//   compare   → strcmp                  vs   operator==, operator<
//   replace   → manual                  vs   s.replace(pos, len, new_text)
#include <iostream>
#include <string>

int main() {
    std::string s = "the quick brown fox";

    std::cout << "s.size()           = " << s.size()           << "\n";
    std::cout << "s.substr(4, 5)     = '" << s.substr(4, 5)    << "'\n";

    auto pos = s.find("brown");
    std::cout << "s.find(\"brown\")   = " << pos               << "\n";

    if (s.find("dog") == std::string::npos)
        std::cout << "'dog' not found    (npos == " << std::string::npos << ")\n";

    std::string a = "abc", b = "abc", c = "abd";
    std::cout << "a == b ? " << (a == b ? "yes" : "no") << "\n";
    std::cout << "a <  c ? " << (a <  c ? "yes" : "no") << "\n";

    s.replace(s.find("fox"), 3, "panda");
    std::cout << "after replace:     " << s << "\n";
}
