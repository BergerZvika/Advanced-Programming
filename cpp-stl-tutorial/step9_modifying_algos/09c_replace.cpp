// Concept: in-place substitution.
//
//   std::replace(b, e, old_v, new_v)         every old_v becomes new_v
//   std::replace_if(b, e, pred, new_v)       every element with pred(*it)→true becomes new_v
//   std::replace_copy / std::replace_copy_if write to a separate output
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 2, 4, 2, 5};
    std::replace(v.begin(), v.end(), 2, 99);
    std::cout << "replace 2 → 99:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    std::vector<int> w{1, 2, 3, 4, 5, 6};
    std::replace_if(w.begin(), w.end(),
                    [](int x){ return x % 2 == 0; }, -1);
    std::cout << "replace_if even → -1:";
    for (int x : w) std::cout << " " << x;
    std::cout << "\n";

    // replace_copy — keep the original, write to a new container
    std::vector<int> u{1, 2, 3, 2, 4}, out;
    std::replace_copy(u.begin(), u.end(), std::back_inserter(out), 2, 0);
    std::cout << "u=";
    for (int x : u) std::cout << " " << x;
    std::cout << "  out (2→0):";
    for (int x : out) std::cout << " " << x;
    std::cout << "\n";
}
