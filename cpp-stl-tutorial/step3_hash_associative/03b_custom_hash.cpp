// Concept: to use your OWN type as the key of an unordered_map / unordered_set
// you must provide:
//   1) operator==(const T&, const T&)
//   2) a hasher: a callable Hasher with size_t operator()(const T&) const
//
// Two ways to plug in the hasher:
//   - specialise std::hash<T>
//   - pass a hasher type as the third template parameter
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

// Option A: specialise std::hash for Point
namespace std {
    template<> struct hash<Point> {
        size_t operator()(const Point& p) const noexcept {
            // Combine the two int hashes — a common pattern (boost::hash_combine).
            return hash<int>{}(p.x) ^ (hash<int>{}(p.y) << 1);
        }
    };
}

int main() {
    std::unordered_set<Point> visited;
    visited.insert({1, 2});
    visited.insert({3, 4});
    visited.insert({1, 2});            // duplicate — dropped
    std::cout << "visited.size = " << visited.size() << "  (1,2 was duplicate)\n";

    // Option B: pass a hasher as the third template parameter
    auto hasher = [](const Point& p) {
        return std::hash<long>{}((long(p.x) << 32) | p.y);
    };
    using PointEq = std::equal_to<Point>;
    std::unordered_set<Point, decltype(hasher), PointEq> alt(8, hasher);
    alt.insert({5, 6});
    std::cout << "alt.size     = " << alt.size() << "  (uses lambda hasher)\n";
}
