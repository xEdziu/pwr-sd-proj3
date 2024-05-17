#include <iostream>
#include "./BST.hpp"

int main() {
    BST<int, std::string> bst;

    std::cout << "Inserting elements...\n";
    bst.insert(50, "apple");
    bst.insert(30, "banana");
    bst.insert(20, "cherry");
    bst.insert(40, "date");
    bst.insert(70, "elderberry");
    bst.insert(60, "fig");
    bst.insert(80, "grape");
    bst.print();

    std::cout << "\nSearching for elements...\n";
    try{
        std::cout << "Key 30: " << bst.search(30) << "\n";
    } catch (const std::out_of_range& oor) {
        std::cerr << "Key 30 not found\n";
    }

    try {
        std::cout << "Key 70: " << bst.search(70) << "\n";
    } catch (const std::out_of_range& oor) {
        std::cerr << "Key 70 not found\n";
    }
    
    std::cout << "\nRemoving some elements...\n";
    bst.remove(20);
    bst.remove(70);
    bst.print();

    std::cout << "\nSearching for element 70 again...\n";
    try {
        std::cout << "Key 70: " << bst.search(70) << "\n";
    } catch (const std::out_of_range& oor) {
        std::cerr << "Key 70 not found\n";
    }

    std::cout << "\nIn-order traversal...\n";
    bst.inorder([](BSTNode<int, std::string>* node) {
        std::cout << "Key: " << node->key << ", Value: " << node->value << "\n";
    });

    std::cout << "\nFinal state of the tree:\n";
    bst.print();

    return 0;
}