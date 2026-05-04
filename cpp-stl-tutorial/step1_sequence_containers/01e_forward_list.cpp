// Concept: std::forward_list — singly-linked list (C++11).
//
// Leaner than std::list: only forward links, no size() member (counting would
// be O(n)), and a special insert_after API since there is no back-pointer.
//
// Use only when memory is very tight; otherwise list or vector is more ergonomic.
#include <forward_list>
#include <iostream>

int main() {
    std::forward_list<int> fl{1, 2, 3, 4, 5};

    fl.push_front(0);                  // only push_front exists

    auto it = fl.begin();              // 0
    ++it;                              // 1
    fl.insert_after(it, 99);           // insert 99 between 1 and 2

    std::cout << "forward_list:";
    for (int x : fl) std::cout << " " << x;
    std::cout << "\n";

    int n = 0;
    for (auto p = fl.begin(); p != fl.end(); ++p) ++n;
    std::cout << "manual size = " << n << "  (no .size() member)\n";
}
