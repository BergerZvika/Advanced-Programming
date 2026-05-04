// Concept: std::deque — Double-Ended QUEue.
//
// Internally a sequence of fixed-size blocks linked in an index, so it
// supports O(1) push_front AND push_back, plus random access [i].
// Element addresses are NOT contiguous — pointers/references can be invalidated
// by inserts at either end.
//
// Pick deque when you need fast push at BOTH ends; otherwise prefer vector.
#include <deque>
#include <iostream>

int main() {
    std::deque<int> dq{2, 3};
    dq.push_front(1);          // O(1) — vector cannot do this efficiently
    dq.push_back(4);
    dq.push_back(5);

    std::cout << "deque:";
    for (int x : dq) std::cout << " " << x;
    std::cout << "\n";

    std::cout << "front=" << dq.front()
              << "  back=" << dq.back()
              << "  size=" << dq.size() << "\n";

    dq.pop_front();
    dq.pop_back();
    std::cout << "after pop_front+pop_back:";
    for (int x : dq) std::cout << " " << x;
    std::cout << "\n";
}
