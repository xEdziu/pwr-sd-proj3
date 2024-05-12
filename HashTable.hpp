#pragma once
#include <iostream>

template <typename K, typename V>
class HashTable {
 public:
    virtual void insert(const K& key, const V& value) = 0;
    virtual V search(const K& key) = 0;
    virtual void remove(const K& key) = 0;
    virtual bool exists(const K& key) = 0;
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual void keys() = 0;
    virtual void values() = 0;
    virtual void print() = 0;
    virtual ~HashTable() {}
};
