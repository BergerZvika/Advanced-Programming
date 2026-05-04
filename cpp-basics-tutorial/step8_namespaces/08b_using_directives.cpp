// Concept: 'using' brings names from a namespace into the current scope.
//
//   using std::cout;          → import a single name
//   using namespace std;      → import EVERYTHING (avoid in headers!)
//
// In C++17 you can also nest namespace declarations as 'a::b::c':
//   namespace app::module::ui { ... }
#include <iostream>
#include <string>

namespace app::module::ui {        // C++17 nested syntax
    void render() { std::cout << "  ui::render()\n"; }
}

int main() {
    using std::cout;               // import 'cout' only
    using std::string;             // and 'string'

    string s = "no more std::";
    cout << "  " << s << "\n";

    app::module::ui::render();
    // Best practice: NEVER write 'using namespace std;' in a header — it
    // pollutes the global namespace of every TU that includes your header.
}
