#pragma once
#include <stdexcept>
#include "./BSTNode.hpp"

template <typename K, typename V>
class BST {
 private:
    BSTNode<K, V>* root;

    /*
        * Get height of node
        * @param node node to get height of
        * @return height of node
    */
    int height(BSTNode<K, V>* node) const {
        return node ? node->height : 0;
    }

    /*
        * Update height of node
        * @param node node to update height of
    */
    void updateHeight(BSTNode<K, V>* node) {
        node->height =
            (height(node->left) > height(node->right)
         ? height(node->left) : height(node->right)) + 1;
    }

    /*
        * Rotate BST right
        * @param y node to rotate
        * @return rotated node
    */
    BSTNode<K, V>* rotateRight(BSTNode<K, V>* y) {
        BSTNode<K, V>* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    /*
        * Rotate BST left
        * @param x node to rotate
        * @return rotated node
    */
    BSTNode<K, V>* rotateLeft(BSTNode<K, V>* x) {
        BSTNode<K, V>* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    /*
        * Balance BST
        * @param node node to balance
        * @return balanced node
    */
    BSTNode<K, V>* balance(BSTNode<K, V>* node) {
        updateHeight(node);
        int balanceFactor =
         height(node->left) - height(node->right);

        if (balanceFactor > 1) {
            if (height(node->left->left)
             < height(node->left->right)) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (height(node->right->right)
             < height(node->right->left)) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    /*
        * Insert key-value pair into BST
        * @param node node to insert into
        * @param key key to insert
        * @param value value to insert
        * @return node with inserted key-value pair
    */
    BSTNode<K, V>* insert(BSTNode<K, V>* node,
         const K& key, const V& value) {
        if (!node)
            return new BSTNode<K, V>(key, value);

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;  // Update value if key already exists
        }

        return balance(node);
    }

    /*
        * Find minimum node in BST
        * @param node node to start search from
        * @return minimum node
    */
    BSTNode<K, V>* findMin(BSTNode<K, V>* node) const {
        return node->left ? findMin(node->left) : node;
    }

    /*
        * Remove minimum node in BST
        * @param node node to start search from
        * @return node with minimum node removed
    */
    BSTNode<K, V>* removeMin(BSTNode<K, V>* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }

    /*
        * Remove key from BST
        * @param node node to remove key from
        * @param key key to remove
        * @return node with key removed
    */
    BSTNode<K, V>* remove(BSTNode<K, V>* node, const K& key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            BSTNode<K, V>* left = node->left;
            BSTNode<K, V>* right = node->right;
            delete node;
            if (!right) return left;
            BSTNode<K, V>* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }

    /*
        * Search for key in BST
        * @param node node to search from
        * @param key key to search for
        * @return node with key
    */
    BSTNode<K, V>* search(BSTNode<K, V>* node,
     const K& key) const {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    /*
        * Inorder traversal of BST
        * @param node node to start traversal from
        * @param visit function to call on each node
    */
    void inorder(BSTNode<K, V>* node,
     void (*visit)(BSTNode<K, V>*)) const {
        if (!node) return;
        inorder(node->left, visit);
        visit(node);
        inorder(node->right, visit);
    }

 public:
    /*
        * Constructor
    */
    BST() : root(nullptr) {}

    /*
        * Insert key-value pair into BST
        * @param key key to insert
        * @param value value to insert
    */
    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    /*
        * Remove key from BST
        * @param key key to remove
    */
    void remove(const K& key) {
        root = remove(root, key);
    }

    /*
        * Search for key in BST
        * @param key key to search for
        * @return value associated with key
        * @throws std::out_of_range if key not found
    */
    V search(const K& key) const {
        BSTNode<K, V>* result = search(root, key);
        if (!result) throw std::out_of_range("Key not found");
        return result->value;
    }

    /*
        * Check if key exists in BST
        * @param key key to search for
        * @return bool
    */
    bool exists(const K& key) const {
        return search(root, key) != nullptr;
    }

    /*
        * Perform inorder traversal of BST
    */
    void inorder(void (*visit)(BSTNode<K, V>*)) const {
        inorder(root, visit);
    }

    /*
        * Print BST
    */
    void print(
        BSTNode<K, V>* node, int space = 0, int increment = 10)
         const {
        if (node == nullptr)
            return;

        space += increment;

        print(node->right, space);

        std::cout << std::endl;
        for (int i = increment; i < space; i++)
            std::cout << " ";
        std::cout << node->key << "\n";

        print(node->left, space);
    }

    /*
        * Callable Print BST
    */
    void print() const {
        print(root);
    }

    /*
        * Destructor
    */
    ~BST() {
        while (root) {
            remove(root->key);
        }
    }
};
