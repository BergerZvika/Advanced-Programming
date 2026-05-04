// Concept: std::stack — LIFO container adapter.
//
// Wraps a sequence container (default std::deque) and exposes a restricted API:
//   push, pop, top, empty, size.
//
// vs C: hand-rolled with a vector + index, or a linked list.
#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<int> s;
    for (int x : {1, 2, 3, 4, 5}) s.push(x);

    std::cout << "size=" << s.size() << "  top=" << s.top() << "\n";
    std::cout << "pop order (LIFO):";
    while (!s.empty()) {
        std::cout << " " << s.top();
        s.pop();
    }
    std::cout << "\n";

    // Use case — balanced bracket checker
    auto balanced = [](const std::string& expr){
        std::stack<char> st;
        for (char c : expr) {
            if (c == '(' || c == '[') st.push(c);
            else if (c == ')' || c == ']') {
                if (st.empty()) return false;
                char open = st.top(); st.pop();
                if ((c == ')' && open != '(') || (c == ']' && open != '[')) return false;
            }
        }
        return st.empty();
    };
    std::cout << "(([])) balanced? " << (balanced("(([]))") ? "yes" : "no") << "\n";
    std::cout << "(([)) balanced?  " << (balanced("(([))")  ? "yes" : "no") << "\n";
}
