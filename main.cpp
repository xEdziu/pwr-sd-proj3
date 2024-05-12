#include <iostream>
#include "./OpenAddressing.hpp"

int main(int argc, char** argv) {
    OpenAddressing<int, std::string> ht =
     OpenAddressing<int, std::string>(6);
    ht.insert(9, "one");
    ht.insert(10, "two");
    ht.insert(14, "three");
    ht.insert(21, "four");
    ht.insert(26, "five");
    std::cout << "Load factor: " << ht.getLoadFactor() <<
    " for size: " << ht.size() << std::endl;

    ht.print();

    try {
        std::cout << "\n\nSearch for key 9: "
        << ht.search(9) << std::endl;
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "\n\nRemove key 9\n";
        ht.remove(9);
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "\n\nSearch for key 9: "
        << ht.search(9) << std::endl;
    } catch (const std::range_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
