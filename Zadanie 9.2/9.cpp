#include <iostream>
#include "mypriorityqueue.h"
#include <cassert>

int main() {
    // Test 1: Destruktor
    {
        MyPriorityQueue<int> pq;
        pq.push(10);
        pq.push(20);
    } // Jesli destruktor dziala poprawnie, to nie bedzie wycieku pamieci

    // Test 2: Konstruktor kopiujacy
    MyPriorityQueue<int> pq1;
    pq1.push(10);
    pq1.push(20);
    MyPriorityQueue<int> pq2(pq1);
    assert(pq2.size() == 2);
    assert(pq2.top() == 20);

    // Test 3: Konstruktor przenoszacy
    MyPriorityQueue<int> pq3(std::move(pq1));
    assert(pq1.empty());
    assert(pq3.size() == 2);

    // Test 4: Operator przypisania kopiujacy
    MyPriorityQueue<int> pq4;
    pq4 = pq3;
    assert(pq4.size() == 2);
    assert(pq4.top() == 20);

    // Test 5: Operator przypisania przenoszacy
    MyPriorityQueue<int> pq5;
    pq5 = std::move(pq4);
    assert(pq4.empty());
    assert(pq5.size() == 2);

    // Test 6: push(const T&)
    pq5.push(30);
    assert(pq5.top() == 30);
    assert(pq5.size() == 3);

    // Test 7: push(T&&)
    int val = 40;
    pq5.push(std::move(val));
    assert(pq5.top() == 40);
    assert(pq5.size() == 4);

    // Test 8: pop()
    pq5.pop();
    assert(pq5.top() == 30);
    assert(pq5.size() == 3);

    // Test 9: empty()
    assert(pq5.empty() == false);
    pq5.pop();
    pq5.pop();
    pq5.pop();
    assert(pq5.empty() == true);

    // Test 10: size()
    pq5.push(50);
    pq5.push(60);
    assert(pq5.size() == 2);

    // Test 11: clear()
    pq5.clear();
    assert(pq5.empty());

    // Test 12: display()
    MyPriorityQueue<int> pq6;
    pq6.push(15);
    pq6.push(25);
    pq6.push(5);
    std::cout << "Zawartosc kolejki pq6: ";
    pq6.display(); // Oczekiwany wynik: 25 15 5

    // Test 13: top()
    assert(pq6.top() == 25);
    pq6.pop();
    assert(pq6.top() == 15);
    pq6.push(8);
    pq6.push(20);
    pq6.push(10);
    assert(pq6.top() == 20);

    std::cout << "Wszystko dziala" << std::endl;
    return 0;
}
