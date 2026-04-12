#include <iostream>
#include "mylib.h"

int main() {
    std::cout << "=== Step 9: Install Rules ===\n\n";

    std::cout << "repeat('ha', 3)             = "
              << MyLib::repeat("ha", 3) << "\n";

    std::cout << "join(['a','b','c'], '-')     = "
              << MyLib::join({"a", "b", "c"}, "-") << "\n";

    std::cout << "starts_with('hello','hel')  = "
              << (MyLib::starts_with("hello", "hel") ? "true" : "false") << "\n";

    std::cout << "to_snake_case('CamelCase')  = "
              << MyLib::to_snake_case("CamelCase") << "\n";

    std::cout << "to_snake_case('MyBigClass') = "
              << MyLib::to_snake_case("MyBigClass") << "\n";

    return 0;
}
