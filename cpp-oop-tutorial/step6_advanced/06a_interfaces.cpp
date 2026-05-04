// Concept: an "interface" in C++ is just a class with only pure virtual
// methods (and a virtual destructor). A concrete class can implement many.
#include <iostream>
#include <string>

struct ISerializable {
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
};

struct ILoggable {
    virtual ~ILoggable() = default;
    virtual void log() const = 0;
};

class User : public ISerializable, public ILoggable {
public:
    User(int id, std::string name) : id_(id), name_(std::move(name)) {}

    std::string serialize() const override {
        return "User{id=" + std::to_string(id_) + ",name=" + name_ + "}";
    }
    void log() const override {
        std::cout << "  [LOG] User id=" << id_ << " name=" << name_ << "\n";
    }
private:
    int id_;
    std::string name_;
};

int main() {
    User u(42, "Alice");
    std::cout << "serialize: " << u.serialize() << "\n";
    u.log();

    ILoggable* lp = &u;     // can pass User where any ILoggable is wanted
    lp->log();
}
