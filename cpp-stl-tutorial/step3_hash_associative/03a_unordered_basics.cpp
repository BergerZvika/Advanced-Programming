// Concept: std::unordered_map / unordered_set — HASH-based associative containers.
//
// vs C: you'd build a hash table by hand. std::unordered_map<K, V> does it for
// you, with average O(1) insert/find/erase.
//
//   std::map               unordered_map
//   ─────────────────      ─────────────────
//   ordered iteration       NO order
//   O(log n)                average O(1), worst O(n)
//   compares with <         hashes with std::hash<K> + ==
//
// Pick unordered when you don't care about order.
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
    // Word counting — quintessential unordered_map use case
    std::unordered_map<std::string, int> word_count;
    for (const char* w : {"the","quick","the","fox","the","quick"})
        ++word_count[w];

    std::cout << "word counts (unordered iteration):\n";
    for (const auto& [w, n] : word_count)
        std::cout << "  " << w << " : " << n << "\n";

    // Rehashing controls
    std::cout << "buckets = " << word_count.bucket_count()
              << "  load factor = " << word_count.load_factor() << "\n";
    word_count.reserve(1000);    // hint: I expect ~1000 entries
    std::cout << "buckets after reserve(1000) = " << word_count.bucket_count() << "\n";

    std::unordered_set<int> seen{1, 2, 3, 2, 1};
    std::cout << "seen.size = " << seen.size()
              << "  (duplicates removed, no order)\n";
}
