#pragma once
#include <utility>  // for std::pair
#include "./HashTable.hpp"

template <typename K, typename V>
class OpenAddressing : public HashTable<K, V> {
 private:
    std::pair<K, V>* table;
    size_t tableSize;
    size_t numElements;
    int probingType;

    static constexpr K EMPTY_KEY = -1;
    static constexpr K DELETED_KEY = -2;

    /*
        * Hash function with linear probing for collision resolution
        * @param key key to hash
        * @param i number of iteration
        * @return hashed key
    */
    size_t hash(const K& key, int i) const {
        const int C = 1;  // Adjust this value as needed
        int hashOne = key % tableSize;
        int hashTwo = (key * 2) % tableSize;
        switch (probingType) {
            case 0:
                return (hashOne + i * C) % tableSize;  // Linear probing
            case 1:
                return (hashOne + i * i * C) % tableSize;  // Quadratic probing
            case 2:
                return (hashOne + i * hashTwo) % tableSize;  // Double hashing
            default:
                return (hashOne + i * C) % tableSize;  // Linear probing
        }
    }

    /*
        * Calculate load factor of hash table
        * @return load factor
    */
    float calculateLoadFactor() const {
        return static_cast<float>(numElements) / static_cast<float>(tableSize);
    }

 public:
    /*
        * Constructor
        * @param probingType type of probing to use: 
        * 0 for linear probing, 1 for quadratic probing, 2 for double hashing
        * @param size size of hash table
    */
    explicit OpenAddressing(int probingType, size_t size = 101) :
     probingType(probingType), tableSize(size), numElements(0) {
        table = new std::pair<K, V>[tableSize];
        for (size_t i = 0; i < tableSize; ++i) {
            table[i].first = EMPTY_KEY;
        }
    }

    /*
        * Insert key-value pair into hash table
        * @param key key to insert
        * @param value value to insert
        * @throws std::overflow_error if hash table is full
    */
    void insert(const K& key, const V& value) override {
        int i = 0;
        size_t index;
        do {
            index = hash(key, i);
            if (table[index].first == EMPTY_KEY
                || table[index].first == DELETED_KEY) {
                table[index] = std::make_pair(key, value);
                ++numElements;
                return;
            }
            ++i;
        } while (i < tableSize);
        throw std::overflow_error("HashTable is full");
    }

    /*
        * Search for key in hash table
        * @param key key to search for
        * @return value associated with key
        * @throws std::range_error if key not found
    */
    V search(const K& key) override {
        int i = 0;
        size_t index;
        while (i < tableSize) {
            index = hash(key, i);
            if (table[index].first == key)
                return table[index].second;
            else if (table[index].first == EMPTY_KEY)
                break;
            ++i;
        }
        throw std::range_error("Key not found");
    }

    /*
        * Remove key from hash table
        * @param key key to remove
        * @throws std::range_error if key not found
    */
    void remove(const K& key) override {
        int i = 0;
        size_t index;
        while (i < tableSize) {
            index = hash(key, i);
            if (table[index].first == key) {
                table[index].first = DELETED_KEY;  // Mark as deleted
                --numElements;
                return;
            } else if (table[index].first == EMPTY_KEY) {
                break;
            }
            ++i;
        }
        throw std::range_error("Key not found");
    }

    /*
        * Check if key exists in hash table
        * @param key key to check
        * @return true if key exists, false otherwise
    */
    bool exists(const K& key) override {
        int i = 0;
        size_t index;
        while (i < tableSize) {
            index = hash(key, i);
            if (table[index].first == key)
                return true;
            else if (table[index].first == EMPTY_KEY)
                break;
            ++i;
        }
        return false;
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
            if (table[i].first != EMPTY_KEY
                && table[i].first != DELETED_KEY) {
                std::cout << table[i].first << std::endl;
            }
        }
    }

    /*
        * Print all values in hash table
    */
    void values() override {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table[i].first != EMPTY_KEY
                && table[i].first != DELETED_KEY) {
                std::cout << table[i].second << std::endl;
            }
        }
    }

    /*
        * Get load factor of hash table
        * @return load factor
    */
    float getLoadFactor() override {
        return calculateLoadFactor();
    }

    /*
        * Print all key-value pairs in hash table
    */
    void print() override {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table[i].first != EMPTY_KEY
             && table[i].first != DELETED_KEY) {
                std::cout << "Key: " << table[i].first <<
                 ", Value: " << table[i].second << std::endl;
            } else {
                std::cout << "Key: " << table[i].first << std::endl;
            }
        }
    }

    /*
        * Destructor
    */
    ~OpenAddressing() override = default;
};
