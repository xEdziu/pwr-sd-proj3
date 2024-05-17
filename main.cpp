#include <iostream>
#include <string>
#include "./CuckooHashing.hpp"

int main() {
    CuckooHashing<int, std::string> ht = CuckooHashing<int, std::string>(7);
    ht.insert(9, "one");
    ht.insert(10, "two");
    ht.insert(14, "three");
    ht.insert(21, "four");
    ht.insert(26, "five");

    std::cout << "Load factor: " << ht.getLoadFactor() << " for size: " << ht.size() << std::endl;

    ht.insert(31, "six");

    std::cout << "Added 31: " << ht.search(31) << std::endl;

    try {
        ht.remove(31);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of range error: " << oor.what() << std::endl;
    }

    std::cout << "Deleted 31" << std::endl;

    try {
        std::cout << "Search 31: " << ht.search(31) << std::endl;
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of range error: " << oor.what() << std::endl;
    }

    ht.print();

    return 0;
}
