#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include "./HashTable.hpp"

template <typename K, typename V>
class CuckooHashing : public HashTable<K, V>{
 private:
    static constexpr int INSERTION_ATTEMPTS = 50;
    std::vector<std::pair<K, V>> table1, table2;
    size_t size_;

    /*
    * First hash function
    * @param: K key
    * @return: size_t
    */
    size_t hash1(const K& key) {
        return key % table1.size();
    }

    /*
    * Second hash function
    * @param: K key
    * @return: size_t
    */
    size_t hash2(const K& key) {
        return (key / table1.size()) % table2.size();
    }

    /*
        * Helper function to insert key-value pair into hash table
        * @param key key to insert
        * @param value value to insert
        * @param count number of attempts to insert
        * @return true if insertion was successful, error otherwise
        * @throws std::overflow_error if cycle is detected
    */
    bool insertHelper(const K& key, const V& value, int count) {
        if (count > INSERTION_ATTEMPTS)  // Prevent infinite loop
            throw std::overflow_error("Cycle detected");

        size_t index1 = hash1(key);

        if (!table1[index1].first || table1[index1].first == key) {
            std::swap(table1[index1], std::pair<K, V>(key, value));
            return true;
        }

        std::swap(table1[index1], std::pair<K, V>(key, value));
        return insertHelper(table1[index1].first,
         table1[index1].second, count + 1);
    }
};
