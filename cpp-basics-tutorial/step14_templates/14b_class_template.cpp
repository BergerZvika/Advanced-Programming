// Concept: a CLASS TEMPLATE generates a family of classes, one per type
// (or per combination of template arguments).
//
// vs C: in C you'd implement separate Stack_int, Stack_double, Stack_str
// types, each with its own functions. C++ templates let you write the data
// structure ONCE for any element type — std::vector, std::map, std::set
// are all class templates.
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Stack {
public:
    void push(const T& v) { data_.push_back(v); }
    void pop() {
        if (data_.empty()) throw std::out_of_range("pop on empty stack");
        data_.pop_back();
    }
    const T& top() const  {
        if (data_.empty()) throw std::out_of_range("top on empty stack");
        return data_.back();
    }
    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }

private:
    std::vector<T> data_;     // reuse std::vector — itself a class template!
};

int main() {
    Stack<int> ints;
    ints.push(1); ints.push(2); ints.push(3);
    std::cout << "Stack<int> top    = " << ints.top()    << "  size = " << ints.size() << "\n";

    Stack<std::string> words;
    words.push("hello"); words.push("world");
    std::cout << "Stack<string> top = " << words.top()   << "  size = " << words.size() << "\n";

    // Each instantiation is a DIFFERENT type — Stack<int> ≠ Stack<double>.
    Stack<double> doubles;
    doubles.push(3.14);
    std::cout << "Stack<double> top = " << doubles.top() << "\n";
}
