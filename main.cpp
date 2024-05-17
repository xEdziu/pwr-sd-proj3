#include <iostream>
#include "./ClosedAddressingWithBST.hpp"

int main() {
    // Create a hash table with size 10
    ClosedAddressingWithBST<int, std::string> hashTable
     = ClosedAddressingWithBST<int, std::string>(11);

    // Insert 10 key-value pairs
    hashTable.insert(1, "One");
    hashTable.insert(2, "Two");
    hashTable.insert(3, "Three");
    hashTable.insert(4, "Four");
    std::cout << "Load factor after 4/11 inserts: " << hashTable.getLoadFactor() << "\n";
    hashTable.insert(5, "Five");
    hashTable.insert(6, "Six");
    hashTable.insert(7, "Seven");
    std::cout << "Load factor after 7/11 inserts: " << hashTable.getLoadFactor() << "\n";
    hashTable.insert(8, "Eight");
    hashTable.insert(9, "Nine");
    hashTable.insert(10, "Ten");
    std::cout << "Load factor after 10/11 inserts: " << hashTable.getLoadFactor() << "\n";

    // Print the hash table
    std::cout << "Hash table after insertion:\n";
    hashTable.print();

    // Check if a key exists
    std::cout << "Key 5 exists: " << (hashTable.exists(5) ? "Yes" : "No") << "\n";

    // Get the size of the hash table
    std::cout << "Size of hash table: " << hashTable.size() << "\n";

    // Check if the hash table is empty
    std::cout << "Hash table is empty: " << (hashTable.empty() ? "Yes" : "No") << "\n";

    // Search for a key
    try {
        std::cout << "Value for key 5: " << hashTable.search(5) << "\n";
    } catch (const std::out_of_range& oor) {
        std::cerr << "Key not found\n";
    }

    // Another 10 insertions
    hashTable.insert(11, "Eleven");
    hashTable.insert(12, "Twelve");
    hashTable.insert(13, "Thirteen");
    hashTable.insert(14, "Fourteen");
    hashTable.insert(15, "Fifteen");
    hashTable.insert(16, "Sixteen");
    hashTable.insert(17, "Seventeen");
    hashTable.insert(18, "Eighteen");
    hashTable.insert(19, "Nineteen");
    hashTable.insert(20, "Twenty");

    // Print the hash table
    std::cout << "Hash table after another 10 insertions:\n";
    hashTable.print();

    std::cout << "\n\n\n\n" << std::endl;

        // Create a hash table with size 10
    ClosedAddressingWithBST<int, std::string> secondHashTable
     = ClosedAddressingWithBST<int, std::string>(5);

    // Insert key-value pairs into the hash table
    secondHashTable.insert(1, "one");
    secondHashTable.insert(3, "three");
    secondHashTable.insert(4, "four");
    secondHashTable.insert(5, "five");
    secondHashTable.insert(6, "six");
    secondHashTable.insert(8, "eight");

    secondHashTable.print();

    return 0;
}