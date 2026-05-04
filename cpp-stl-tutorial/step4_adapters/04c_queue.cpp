// Concept: std::queue — FIFO container adapter.
// Wraps a sequence container (default std::deque) with: push, pop, front, back.
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;
    for (int x : {1, 2, 3, 4, 5}) q.push(x);

    std::cout << "front=" << q.front() << "  back=" << q.back()
              << "  size=" << q.size() << "\n";

    std::cout << "pop order (FIFO):";
    while (!q.empty()) {
        std::cout << " " << q.front();
        q.pop();
    }
    std::cout << "\n";
}
