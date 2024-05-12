#include <iostream>
#include "./OpenAddressing.hpp"

int main(int argc, char** argv) {
    OpenAddressing<int, std::string> ht =
     OpenAddressing<int, std::string>(50);
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(3, "three");
    ht.insert(4, "four");
    ht.insert(5, "five");
    ht.insert(6, "six");
    ht.insert(7, "seven");
    ht.insert(8, "eight");
    ht.insert(9, "nine");
    ht.insert(10, "ten");
    std::cout << "Load factor: " << ht.getLoadFactor() <<
    " for size: " << ht.size() << std::endl;

    try {
        std::cout << "\n\nSearch for key 5: "
        << ht.search(5) << std::endl;
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "\n\nRemove key 5\n";
        ht.remove(5);
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "\n\nSearch for key 5: "
        << ht.search(5) << std::endl;
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
