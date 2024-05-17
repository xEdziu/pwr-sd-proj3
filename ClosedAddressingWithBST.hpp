#pragma once
#include <iostream>
#include "./HashTable.hpp"
#include "./BST.hpp"

template <typename K, typename V>
class ClosedAddressingWithBST : public HashTable<K, V> {
 private:
    BST<K, V>** table;
    size_t tableSize;
    size_t numElements;

    /*
        * Hash function
        * @param key key to hash
        * @return hashed key
    */
    size_t hash(const K& key) const {
        return key % tableSize;
    }

 public:
    /*
        * Constructor
        * @param size size of hash table
    */
    explicit ClosedAddressingWithBST(size_t size = 101)
        : tableSize(size), numElements(0) {
        table = new BST<K, V>*[tableSize];
        for (size_t i = 0; i < tableSize; ++i) {
            table[i] = nullptr;
        }
    }

    /*
        * Insert key-value pair
        * @param key key to insert
        * @param value value to insert
    */
    void insert(const K& key, const V& value) override {
        size_t index = hash(key);
        if (!table[index]) {
            table[index] = new BST<K, V>();
        }
        table[index]->insert(key, value);
        ++numElements;
    }

    /*
        * Search for key in hash table
        * @param key key to search for
        * @return value associated with key
        * @throws std::out_of_range if key not found
    */
    V search(const K& key) override {
        size_t index = hash(key);
        if (!table[index]) {
            throw std::out_of_range("Key not found");
        }
        return table[index]->search(key);
    }

    /*
        * Remove key from hash table
        * @param key key to remove
    */
    void remove(const K& key) override {
        size_t index = hash(key);
        if (table[index]) {
            table[index]->remove(key);
            --numElements;
        }
    }

    /*
        * Check if key exists in hash table
        * @param key key to search for
        * @return true if key exists, false otherwise
    */
    bool exists(const K& key) override {
        size_t index = hash(key);
        return table[index] && table[index]->exists(key);
    }

    /*
        * Get number of elements in hash table
        * @return number of elements
    */
    size_t size() override {
        return numElements;
    }

    /*
        * Check if hash table is empty
        * @return true if hash table is empty, false otherwise
    */
    bool empty() override {
        return numElements == 0;
    }

    /*
        * Print all keys in hash table
    */
    void keys() override {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table[i]) {
                table[i]->inorder([](BSTNode<K, V>* node) {
                    std::cout << node->key << " ";
                });
            }
        }
        std::cout << std::endl;
    }

    /*
        * Print all values in hash table
    */
    void values() override {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table[i]) {
                table[i]->inorder([](BSTNode<K, V>* node) {
                    std::cout << node->value << " ";
                });
            }
        }
        std::cout << std::endl;
    }

    /*
        * Print hash table
    */
    void print() override {
        for (size_t i = 0; i < tableSize; ++i) {
            std::cout << "Bucket " << i << ": ";
            if (table[i]) {
                table[i]->inorder([](BSTNode<K, V>* node) {
                    std::cout << "(" << node->key <<
                     ", " << node->value << ") ";
                });
            }
            std::cout << std::endl;
        }
    }

    /*
        * Get load factor of hash table
        * @return load factor
    */
    float getLoadFactor() override {
        return static_cast<float>(numElements)
         / static_cast<float>(tableSize);
    }

    /*
        * Destructor
    */
    ~ClosedAddressingWithBST() {
        for (size_t i = 0; i < tableSize; ++i) {
            delete table[i];
        }
        delete[] table;
    }
};
