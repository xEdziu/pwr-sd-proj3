#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>
#include "./HashTable.hpp"

template <typename K, typename V>
class CuckooHashing : public HashTable<K, V> {
 private:
    std::pair<K, V> *table1, *table2;
    size_t tableSize;
    size_t size_;

    static constexpr K EMPTY_KEY = -1;
    static constexpr int INSERTION_ATTEMPTS = 50;

    /*
    * First hash function
    * @param: K key
    * @return: size_t
    */
    size_t hash1(const K& key) {
        return key % tableSize;
    }

    /*
    * Second hash function
    * @param: K key
    * @return: size_t
    */
    size_t hash2(const K& key) {
        return (key / tableSize) % tableSize;
    }

    /*
    * Helper function to insert key-value pair
    * @param: K key key to insert
    * @param: V value value to insert
    * @param: int iteration count of insertion attempts
    * @return: bool
    * @throws: std::overflow_error if cycle detected
    */
    bool insertHelper(K key, V value, int count) {
        if (count > INSERTION_ATTEMPTS) {
            throw std::overflow_error("Cycle detected");
        }

        size_t index1 = hash1(key);

        if (table1[index1].first == EMPTY_KEY
         || table1[index1].first == key) {
            table1[index1] = std::make_pair(key, value);
            return true;
        }

        std::pair<K, V> temp = std::make_pair(key, value);
        std::swap(table1[index1], temp);

        size_t index2 = hash2(temp.first);

        if (table2[index2].first == EMPTY_KEY
         || table2[index2].first == temp.first) {
            table2[index2] = temp;
            return true;
        }

        std::swap(table2[index2], temp);

        return insertHelper(temp.first, temp.second, count + 1);
    }


 public:
    /*
    * Constructor
    * @param: size_t bucketCount
    */
    explicit CuckooHashing(size_t bucketCount = 101)
     : tableSize(bucketCount), size_(0) {
        table1 = new std::pair<K, V>[tableSize];
        table2 = new std::pair<K, V>[tableSize];
        for (size_t i = 0; i < tableSize; ++i) {
            table1[i].first = EMPTY_KEY;
            table2[i].first = EMPTY_KEY;
        }
    }

    /*
    * Return load factor of the hash table
    * @return float
    */
    float getLoadFactor() override {
        return static_cast<float>(size_) / tableSize;
    }

    /*
    * Insert key-value pair
    * @param: K key
    * @param: V value
    */
    void insert(const K& key, const V& value) override {
        if (!insertHelper(key, value, 0)) {
            throw std::overflow_error("HashTable is full");
        }
        ++size_;
    }

    /*
    * Search for key
    * @param: K key
    * @return: V
    * @throws: std::out_of_range if key not found
    */
    V search(const K& key) override {
        size_t index1 = hash1(key);
        if (table1[index1].first == key) {
            return table1[index1].second;
        }
        size_t index2 = hash2(key);
        if (table2[index2].first == key) {
            return table2[index2].second;
        }
        throw std::out_of_range("Key not found");
    }

    /*
    * Remove key from hash table
    * @param: K key
    * @throws: std::out_of_range if key not found
    */
    void remove(const K& key) override {
        size_t index1 = hash1(key);
        if (table1[index1].first == key) {
            table1[index1].first = EMPTY_KEY;
            --size_;
            table1[index1].second = V();
            return;
        }
        size_t index2 = hash2(key);
        if (table2[index2].first == key) {
            table2[index2].first = EMPTY_KEY;
            --size_;
            table2[index2].second = V();
            return;
        }
        throw std::out_of_range("Key not found");
    }

    /*
    * Check if key exists in hash table
    * @param: K key
    * @return: bool
    */
    bool exists(const K& key) override {
        size_t index1 = hash1(key);
        if (table1[index1].first == key) {
            return true;
        }
        size_t index2 = hash2(key);
        if (table2[index2].first == key) {
            return true;
        }
        return false;
    }

    /*
    * Return size of hash table
    * @return: size_t
    */
    size_t size() override {
        return size_;
    }

    /*
    * Check if hash table is empty
    * @return: bool
    */
    bool empty() override {
        return size_ == 0;
    }

    /*
    * Print all keys in hash table
    */
    void keys() override {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table1[i].first != EMPTY_KEY) {
                std::cout << table1[i].first << " ";
            }
        }
        for (size_t i = 0; i < tableSize; ++i) {
            if (table2[i].first != EMPTY_KEY) {
                std::cout << table2[i].first << " ";
            }
        }
        std::cout << std::endl;
    }

    /*
    * Print all values in hash table
    */
    void values() override {
        for (size_t i = 0; i < tableSize; ++i) {
            if (table1[i].first != EMPTY_KEY) {
                std::cout << table1[i].second << " ";
            }
        }
        for (size_t i = 0; i < tableSize; ++i) {
            if (table2[i].first != EMPTY_KEY) {
                std::cout << table2[i].second << " ";
            }
        }
        std::cout << std::endl;
    }

    /*
    * Print hash table
    */
    void print() override {
        std::cout << "Table 1:" << std::endl;
        for (size_t i = 0; i < tableSize; ++i) {
            std::cout << "  Key: " << table1[i].first <<
                ", Value: " << table1[i].second << std::endl;
        }
        std::cout << "Table 2:" << std::endl;
        for (size_t i = 0; i < tableSize; ++i) {
            std::cout << "  Key: " << table2[i].first <<
                ", Value: " << table2[i].second << std::endl;
        }
    }

    /*
    * Destructor
    */
    ~CuckooHashing() override {
        delete[] table1;
        delete[] table2;
    }
};
