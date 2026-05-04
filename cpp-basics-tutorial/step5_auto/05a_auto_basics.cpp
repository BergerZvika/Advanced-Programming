// Concept: 'auto' — let the compiler deduce the type from the initialiser.
//
// vs C:
//   In C the keyword 'auto' was a (rarely used) storage-class specifier
//   meaning "automatic local variable", which is the default anyway.
//   Since C++11 it has been REPURPOSED to mean "deduce my type". The deduction
//   rules are exactly those of template argument deduction.
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    auto i = 42;                    // → int
    auto d = 3.14;                  // → double
    auto s = std::string{"hi"};     // → std::string

    std::cout << "i=" << i << "  d=" << d << "  s=" << s << "\n";

    // The win: write awful long iterator types ONCE — let auto do the rest.
    std::map<std::string, std::vector<int>> stats{
        {"alice", {1, 2, 3}}, {"bob", {4, 5}}};

    for (auto it = stats.begin(); it != stats.end(); ++it) {     // it: map<...>::iterator
        std::cout << "  " << it->first << " has " << it->second.size() << " entries\n";
    }
}
