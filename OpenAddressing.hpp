#pragma once
#include <vector>
#include <utility>  // for std::pair
#include "./HashTable.hpp"

template <typename K, typename V>
class OpenAddressing : public HashTable<K, V> {
 private:
    std::vector<std::pair<K, V>> table;
    size_t tableSize;
    size_t numElements;

    static constexpr K EMPTY_KEY = -1;
    static constexpr K DELETED_KEY = -2;

    /*
        * Hash function with linear probing for collision resolution
        * @param key key to hash
        * @param i number of iteration
        * @return hashed key
    */
    size_t hash(const K& key, int i) const {
        return (std::hash<K>{}(key) + i) % tableSize;  // Linear probing
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
        * @param size size of hash table
    */
    explicit OpenAddressing(size_t size = 101) :
     tableSize(size), numElements(0) {
        table.resize(tableSize, {EMPTY_KEY, V{}});
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
        for (const auto& slot : table) {
            if (slot.first != EMPTY_KEY
                && slot.first != DELETED_KEY) {
                std::cout << slot.first << std::endl;
            }
        }
    }

    /*
        * Print all values in hash table
    */
    void values() override {
        for (const auto& slot : table) {
            if (slot.first != EMPTY_KEY
                && slot.first != DELETED_KEY) {
                std::cout << slot.second << std::endl;
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
        for (const auto& slot : table) {
            if (slot.first != EMPTY_KEY
                && slot.first != DELETED_KEY) {
                std::cout << "Key: " << slot.first <<
                    ", Value: " << slot.second << std::endl;
            }
        }
    }

    /*
        * Destructor
    */
    ~OpenAddressing() override = default;
};
