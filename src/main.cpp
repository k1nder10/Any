#include <iostream>
#include <string>
#include <vector>
#include <typeindex>
#include <stdexcept>

#include "Any.hpp"

int main() {
    try {
        palkin::Any any;
        int x = 5;
        any = x;
        any = 1.24;
        any = 'c';

        const auto c = palkin::any_cast<char>(any);
        std::cout << c << '\n';

        any = std::string("string");
        std::cout << palkin::any_cast<std::string>(any) << '\n';

        any = std::vector<std::string>{"hello", "world"};
        const auto vec = palkin::any_cast<std::vector<std::string>>(any);
        for (const auto& v: vec) std::cout << v << '\n';

        // TODO: have to workaround with template parameter
        // const char world[] = "world";
        // any = world;
        // std::cout << palkin::any_cast<const char*>(any) << '\n';

        const auto b = palkin::any_cast<const bool>(any);
    }
    catch (const std::exception& e) {
        std::cerr << "Error catched: " << e.what() << '\n';
    }

    return 0;
}