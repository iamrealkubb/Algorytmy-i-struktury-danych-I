#include <iostream>
#include "calc_leaves.h"
#include <cassert>

int main() {
    RandomBinaryTree<int> drzewo;

    drzewo.insert(10);
    drzewo.insert(5);
    drzewo.insert(15);
    drzewo.insert(3);
    drzewo.insert(7);
    drzewo.insert(12);

    assert(drzewo.calc_leaves_rekurencyjnie() == 3);
    assert(drzewo.calc_leaves_iteracyjnie() == 3);

    RandomBinaryTree<int> drzewo1;

    drzewo1.insert(3);
    drzewo1.insert(5);
    drzewo1.insert(7);
    drzewo1.insert(10);
    drzewo1.insert(12);
    drzewo1.insert(15);

    assert(drzewo1.calc_leaves_rekurencyjnie() == 1);
    assert(drzewo1.calc_leaves_iteracyjnie() == 1);

    RandomBinaryTree<int> drzewo2;

    drzewo2.insert(10);

    assert(drzewo2.calc_leaves_rekurencyjnie() == 1);
    assert(drzewo2.calc_leaves_iteracyjnie() == 1);

    RandomBinaryTree<int> drzewo3;

    drzewo3.insert(10);
    drzewo3.insert(5);
    drzewo3.insert(15);
    drzewo3.insert(3);
    drzewo3.insert(7);
    drzewo3.insert(12);
    drzewo3.insert(20);

    assert(drzewo3.calc_leaves_rekurencyjnie() == 4);
    assert(drzewo3.calc_leaves_iteracyjnie() == 4);

    RandomBinaryTree<int> drzewo4;

    drzewo4.insert(10);
    drzewo4.insert(15);
    drzewo4.insert(20);
    drzewo4.insert(25);

    assert(drzewo4.calc_leaves_rekurencyjnie() == 1);
    assert(drzewo4.calc_leaves_iteracyjnie() == 1);

    RandomBinaryTree<int> drzewo5;

    drzewo5.insert(10);
    drzewo5.insert(5);
    drzewo5.insert(3);
    drzewo5.insert(1);

    assert(drzewo5.calc_leaves_rekurencyjnie() == 1);
    assert(drzewo5.calc_leaves_iteracyjnie() == 1);

    RandomBinaryTree<int> drzewo6;

    drzewo6.insert(10);
    drzewo6.insert(5);
    drzewo6.insert(15);
    drzewo6.insert(3);
    drzewo6.insert(7);
    drzewo6.insert(6);

    assert(drzewo6.calc_leaves_rekurencyjnie() == 3);
    assert(drzewo6.calc_leaves_iteracyjnie() == 3);

    std::cout << "Funkcje dzialaja poprawnie" << std::endl;
    return 0;
}
