#include <iostream>
#include <string>
#include <vector>
#include <typeindex>
#include <stdexcept>

#include "Any.hpp"

int main() {
    try {
        palkin::Any any;
        any = 5;
        any = 1.24;
        any = 'c';

        auto c = palkin::any_cast<char>(any);
        std::cout << c << '\n';

        any = std::string("string");
        std::cout << palkin::any_cast<std::string>(any) << '\n';
        
        // any = "world"; // TODO: fix error

        any = std::vector<std::string>{"hello", "world"};
        auto vec = palkin::any_cast<std::vector<std::string>>(any);
        for (const auto& v: vec) std::cout << v << '\n';

        auto b = palkin::any_cast<bool>(any);
    }
    catch (const std::exception& e) {
        std::cerr << "Error catched: " << e.what() << '\n';
    }

    return 0;
}