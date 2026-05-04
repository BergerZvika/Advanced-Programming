// Concept: std::weak_ptr — a non-owning observer for a shared_ptr.
//
//   A weak_ptr does NOT keep its target alive. Use weak_ptr to BREAK cycles
//   of shared_ptrs (parent ↔ child) which would otherwise leak.
//
//   .lock() returns a temporary shared_ptr if the object is still alive,
//   or an empty shared_ptr if it has been destroyed. Always go through .lock().
#include <iostream>
#include <memory>
#include <string>

struct Node {
    std::string                name;
    std::weak_ptr<Node>        parent;     // weak — does not keep parent alive
    std::shared_ptr<Node>      child;      // strong — owns the child

    explicit Node(std::string n) : name(std::move(n)) {
        std::cout << "  Node ctor " << name << "\n";
    }
    ~Node() { std::cout << "  Node dtor " << name << "\n"; }
};

int main() {
    auto root  = std::make_shared<Node>("root");
    auto leaf  = std::make_shared<Node>("leaf");

    root->child  = leaf;        // root owns leaf  (shared_ptr)
    leaf->parent = root;        // leaf observes root (weak_ptr) — no cycle

    if (auto p = leaf->parent.lock()) {
        std::cout << "  leaf's parent is alive: " << p->name << "\n";
    }

    std::cout << "  use_counts before reset:  root=" << root.use_count()
              << "  leaf=" << leaf.use_count() << "\n";

    root.reset();               // root destroyed → leaf->parent now expired

    if (leaf->parent.expired())
        std::cout << "  leaf's weak parent has expired (no leak — cycle was avoided)\n";
}
