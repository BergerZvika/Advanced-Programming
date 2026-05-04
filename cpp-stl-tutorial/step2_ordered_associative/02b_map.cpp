// Concept: std::map — sorted key→value dictionary (red-black tree).
//
// vs C: no standard map; you'd build a hash table or bsearch a sorted array.
// std::map gives O(log n) insert/find/erase, iteration in KEY ORDER, and
// range queries (lower_bound / upper_bound).
//
// Use std::map when you need ordered traversal or range queries.
// Use std::unordered_map (step 3) when you only need fast lookup.
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> ages;
    ages["Alice"] = 30;
    ages["Bob"]   = 25;
    ages.insert({"Carol", 35});

    // Lookup
    if (auto it = ages.find("Alice"); it != ages.end())
        std::cout << "Alice -> " << it->second << "\n";

    // operator[] inserts a default-constructed value if missing — beware:
    int eve = ages["Eve"];
    std::cout << "Eve -> " << eve << "  (operator[] inserted a default)\n";

    // Safer existence check:
    if (ages.count("Frank") == 0) std::cout << "Frank is not in the map\n";

    // Iteration is in KEY ORDER:
    std::cout << "all entries (sorted by key):\n";
    for (const auto& [name, age] : ages)
        std::cout << "  " << name << " -> " << age << "\n";

    // Range query: keys in [B, F)
    auto lo = ages.lower_bound("B");
    auto hi = ages.lower_bound("F");
    std::cout << "keys in [B, F):\n";
    for (auto it = lo; it != hi; ++it) std::cout << "  " << it->first << "\n";
}
