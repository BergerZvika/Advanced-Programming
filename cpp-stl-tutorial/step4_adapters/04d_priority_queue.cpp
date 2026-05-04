// Concept: std::priority_queue — binary heap exposed as an adapter.
// top() is the LARGEST element by default. Pass std::greater<T> for a min-heap.
#include <functional>     // std::greater
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int> max_pq;
    for (int x : {5, 3, 8, 1, 9, 4}) max_pq.push(x);
    std::cout << "max-heap pop order:";
    while (!max_pq.empty()) { std::cout << " " << max_pq.top(); max_pq.pop(); }
    std::cout << "\n";

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    for (int x : {5, 3, 8, 1, 9, 4}) min_pq.push(x);
    std::cout << "min-heap pop order:";
    while (!min_pq.empty()) { std::cout << " " << min_pq.top(); min_pq.pop(); }
    std::cout << "\n";

    // Custom comparator (lambda) — pop strings by length, shortest first
    auto by_len = [](const std::string& a, const std::string& b){
        return a.size() > b.size();        // greater = MIN heap
    };
    std::priority_queue<std::string, std::vector<std::string>, decltype(by_len)> short_first(by_len);
    for (auto s : {"hippopotamus", "cat", "elephant", "ox"}) short_first.push(s);
    std::cout << "shortest first:";
    while (!short_first.empty()) { std::cout << " " << short_first.top(); short_first.pop(); }
    std::cout << "\n";
}
