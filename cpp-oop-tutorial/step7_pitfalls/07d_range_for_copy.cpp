// Pitfall 4: accidental copies in range-for.
// 'for (auto x : container)' COPIES each element. Use 'const auto&' to read
// without copying, or 'auto&' to mutate in place.
#include <iostream>
#include <string>
#include <vector>

struct Widget {
    int id; std::string label;
    Widget(int i, std::string l) : id(i), label(std::move(l)) {
        std::cout << "  ctor   #" << id << "\n";
    }
    Widget(const Widget& other) : id(other.id), label(other.label) {
        std::cout << "  copy   #" << id << "\n";
    }
};

int main() {
    std::vector<Widget> ws;
    ws.reserve(2);
    ws.emplace_back(1, "one");
    ws.emplace_back(2, "two");

    std::cout << "── for (auto w : ws) — each element COPIED ──\n";
    for (auto w : ws) { (void)w; }

    std::cout << "── for (const auto& w : ws) — no copies ──\n";
    for (const auto& w : ws) std::cout << "  read #" << w.id << "\n";
}
