// calc_leaves.h

#ifndef CALC_LEAVES_H
#define CALC_LEAVES_H

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
class RandomBinaryTree {
    BSTNode<T> *root;
public:
    //
    //
    //
    // Funkcje potrzebne do implementacji calc_leaves() oraz sprawdzenia, czy dziala poprawnie
    //
    //
    //
    RandomBinaryTree() : root(nullptr) {}
    ~RandomBinaryTree() { delete root; }

    void insert(const T& item) {
        root = insert(root, item);
    }

    int calc_leaves_rekurencyjnie() {
        return calc_leaves_rekurencyjnie(root);
    }

    int calc_leaves_iteracyjnie() {
        return calc_leaves_iteracyjnie(root);
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

    int calc_leaves_rekurencyjnie(BSTNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return calc_leaves_rekurencyjnie(node->left) + calc_leaves_rekurencyjnie(node->right);
    }

    int calc_leaves_iteracyjnie(BSTNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        int ile_lisci = 0;
        std::queue<BSTNode<T>*> q;
        q.push(node);

        while (!q.empty()) {
            BSTNode<T>* obecny = q.front();
            q.pop();

            if (obecny->left == nullptr && obecny->right == nullptr) {
                ile_lisci++;
            } else {
                if (obecny->left != nullptr) {
                    q.push(obecny->left);
                }
                if (obecny->right != nullptr) {
                    q.push(obecny->right);
                }
            }
        }

        return ile_lisci;
    }
};

#endif
