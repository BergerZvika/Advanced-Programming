// Concept: Rule of 0 — prefer to write NONE of the five special members.
// Compose your class out of types that already manage their own resources
// (std::string, std::vector, std::unique_ptr, std::shared_ptr, ...).
// The compiler-synthesised members will then do the right thing for free.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Document {
public:
    Document(std::string title, std::vector<std::string> lines)
        : title_(std::move(title)), lines_(std::move(lines)) {}

    void show() const {
        std::cout << "  " << title_ << "  (" << lines_.size() << " lines)\n";
    }

    // No destructor, no copy ctor, no copy=, no move ctor, no move= written.
    // string and vector each handle their own resource → all 5 are correctly
    // synthesised by the compiler. This is the safest, most maintainable form.

private:
    std::string              title_;
    std::vector<std::string> lines_;
};

class Tree {
public:
    Tree(int v) : value_(v) {}
    void add_left(int v)  { left_  = std::make_unique<Tree>(v); }
    void add_right(int v) { right_ = std::make_unique<Tree>(v); }
    void show(int depth = 0) const {
        for (int i=0;i<depth;++i) std::cout << "  ";
        std::cout << "  Tree(" << value_ << ")\n";
        if (left_)  left_ ->show(depth + 1);
        if (right_) right_->show(depth + 1);
    }

    // unique_ptr destroys child trees automatically — no destructor needed.
    // unique_ptr is move-only, so Tree becomes move-only too. Free of charge.

private:
    int                   value_;
    std::unique_ptr<Tree> left_, right_;
};

int main() {
    Document d("Notes", {"first line", "second", "third"});
    d.show();
    Document e = d;       // compiler-generated copy — string + vector deep-copy
    e.show();

    Tree t(1); t.add_left(2); t.add_right(3);
    Tree u = std::move(t);   // unique_ptr is move-only → Tree is move-only
    u.show();
}
