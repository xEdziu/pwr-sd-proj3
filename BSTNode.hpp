#pragma once

template <typename K, typename V>
class BSTNode {
 public:
    K key;
    V value;
    BSTNode* left;
    BSTNode* right;
    int height;

    BSTNode(const K& k, const V& v)
        : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};
