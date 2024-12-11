#include <iostream>
#include "is_BST.h"
#include <cassert>

int main() {

    BinarySearchTree<int> drzewo;

    drzewo.insert(10);
    drzewo.insert(5);
    drzewo.insert(15);
    drzewo.insert(3);
    drzewo.insert(7);
    drzewo.insert(12);

    assert(drzewo.is_BST() == true);

    // celowo niepoprawne BST
    BSTNode<int>* root = new BSTNode<int>(10);
    root->left = new BSTNode<int>(5);
    root->right = new BSTNode<int>(15);
    root->left->right = new BSTNode<int>(12); // 12 jest na zlej pozycji

    BinarySearchTree<int> niepoprawneDrzewo;
    niepoprawneDrzewo.insert(10);
    niepoprawneDrzewo.insert(5);
    niepoprawneDrzewo.insert(15);
    niepoprawneDrzewo.root = root;

    assert(niepoprawneDrzewo.is_BST() == false);

    std::cout << "Funkcja dziala poprawnie" << std::endl;
    return 0;
}
