// is_BST.h

#ifndef IS_BST_H
#define IS_BST_H

#include <queue>

template <typename T>
struct BSTNode {
    T value;
    BSTNode *left, *right;

    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {
        delete left; delete right;
    }
};

template <typename T>
class BinarySearchTree {
public:
    BSTNode<T> *root;

    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() { delete root; }

    void insert(const T& item) {
        root = insert(root, item);
    }

    BSTNode<T>* insert(BSTNode<T>* node, const T& item) {
        if (node == nullptr) {
            return new BSTNode<T>(item);
        }
        if (item < node->value) {
            node->left = insert(node->left, item);
        } else {
            node->right = insert(node->right, item);
        }
        return node;
    }

    bool is_BST() {
        return is_BST(root, nullptr, nullptr);
    }

    bool is_BST(BSTNode<T> *wezel, T *minimalna, T *maksymalna) {
        if (wezel == nullptr) {
            return true;
        }

        if ((minimalna != nullptr && wezel->value < *minimalna) || (maksymalna != nullptr && wezel->value >= *maksymalna)) {
            return false;
        }

        return is_BST(wezel->left, minimalna, &wezel->value) && is_BST(wezel->right, &wezel->value, maksymalna);
    }
};

#endif
