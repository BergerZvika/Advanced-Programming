// Concept: enumerate permutations of a range, in lexicographic order.
//
//   std::next_permutation(b, e)   rearrange to the NEXT lex permutation;
//                                  returns false when wrapping around to
//                                  the smallest one. Combined with sort()
//                                  at the start, it iterates ALL n! permutations.
//
//   std::prev_permutation         the reverse direction.
#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string s = "abc";
    std::sort(s.begin(), s.end());        // start at lexicographically smallest

    std::cout << "all permutations of \"abc\":\n";
    do {
        std::cout << "  " << s << "\n";
    } while (std::next_permutation(s.begin(), s.end()));

    // is_permutation — different question: are two ranges permutations of each other?
    int a[] = {1, 2, 3, 4};
    int b[] = {3, 1, 4, 2};
    std::cout << "a is permutation of b? "
              << std::is_permutation(std::begin(a), std::end(a), std::begin(b)) << "\n";
}
