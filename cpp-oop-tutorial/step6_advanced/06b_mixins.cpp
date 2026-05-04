// Concept: mixins — small reusable pieces of behaviour pulled in via
// inheritance (or templates). Each mixin adds one orthogonal capability.
#include <iostream>
#include <string>
#include <vector>

class TimestampMixin {
public:
    void touch_created(const std::string& d) { created_ = d; }
    void touch_updated(const std::string& d) { updated_ = d; }
    void print_timestamps() const {
        std::cout << "  Created: " << created_ << "  Updated: " << updated_ << "\n";
    }
protected:
    std::string created_, updated_;
};

class TagsMixin {
public:
    void add_tag(const std::string& t) { tags_.push_back(t); }
    void print_tags() const {
        std::cout << "  Tags: [";
        for (size_t i=0;i<tags_.size();++i) std::cout << (i? ", " : "") << tags_[i];
        std::cout << "]\n";
    }
protected:
    std::vector<std::string> tags_;
};

class Post : public TimestampMixin, public TagsMixin {
public:
    Post(std::string title) : title_(std::move(title)) {}
    void show() const {
        std::cout << "Post \"" << title_ << "\"\n";
        print_timestamps();
        print_tags();
    }
private:
    std::string title_;
};

int main() {
    Post p("Hello World");
    p.touch_created("2024-01-15");
    p.touch_updated("2024-03-22");
    p.add_tag("C++"); p.add_tag("OOP");
    p.show();
}
