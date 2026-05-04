// Concept: iterator ADAPTERS — wrap something else (a container, a stream,
// another iterator) in an iterator-shaped object.
//
//   std::back_inserter(c)   OutputIterator that calls c.push_back
//   std::front_inserter(c)  OutputIterator that calls c.push_front
//   std::inserter(c, it)    OutputIterator that inserts at position 'it'
//   std::ostream_iterator<T>(os, sep)  writes to a stream
//   std::istream_iterator<T>(is)       reads from a stream
//
// They turn any "place that produces or consumes one item at a time" into
// something STL algorithms can target.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

int main() {
    std::vector<int> src{1, 2, 3, 4, 5};

    // back_inserter — append into an empty vector
    std::vector<int> dst;
    std::copy(src.begin(), src.end(), std::back_inserter(dst));
    std::cout << "back_inserter dst:";
    for (int x : dst) std::cout << " " << x;
    std::cout << "\n";

    // front_inserter — push to a list (vector lacks push_front)
    std::list<int> l;
    std::copy(src.begin(), src.end(), std::front_inserter(l));
    std::cout << "front_inserter list:";
    for (int x : l) std::cout << " " << x;     // reversed: 5 4 3 2 1
    std::cout << "\n";

    // ostream_iterator — pipe directly into std::cout
    std::cout << "via ostream_iterator: ";
    std::copy(src.begin(), src.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // istream_iterator — read ints from a stream
    std::istringstream in("10 20 30 40");
    std::vector<int> nums((std::istream_iterator<int>(in)),
                           std::istream_iterator<int>());
    std::cout << "from istream_iterator:";
    for (int x : nums) std::cout << " " << x;
    std::cout << "\n";
}
