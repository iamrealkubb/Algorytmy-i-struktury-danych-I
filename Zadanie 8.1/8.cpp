#include <iostream>
#include "myqueue.h"
#include <cassert>

int main() {
    // Test 1: Destruktor
    {
        MyQueue<int> queue;
        queue.push(1);
        queue.push(2);
    } // Jesli destruktor dziala poprwanie, nie bedzie wycieku pamieci

    // Test 2: Konstruktor kopiujacy
    MyQueue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    MyQueue<int> queue2(queue1);
    assert(queue2.size() == 2);
    assert(queue2.front() == 1);
    assert(queue2.back() == 2);

    // Test 3: push(const T&)
    queue1.push(3);
    assert(queue1.back() == 3);
    assert(queue1.size() == 3);

    // Test 4: pop()
    queue1.pop();
    assert(queue1.front() == 2);
    assert(queue1.size() == 2);

    // Test 5: display()
    std::cout << "Zawartosc kolejki queue1: ";
    queue1.display(); // Oczekiwany wynik: 2 3

    // Test 6: empty()
    assert(queue1.empty() == false);
    queue1.pop();
    queue1.pop();
    assert(queue1.empty() == true);

    // Test 7: full()
    MyQueue<int> queue3(2);
    queue3.push(1);
    queue3.push(2);
    assert(queue3.full() == true);

    // Test 8: Konstruktor przenoszacy
    MyQueue<int> queue4(std::move(queue3));
    assert(queue3.empty());
    assert(queue4.size() == 2);

    // Test 9: Operator przypisania kopiujacy
    MyQueue<int> queue5;
    queue5 = queue4;
    assert(queue5.size() == 2);
    assert(queue5.front() == 1);
    assert(queue5.back() == 2);

    // Test 10: Operator przypisania przenoszacy
    MyQueue<int> queue6;
    queue6 = std::move(queue5);
    assert(queue5.empty());
    assert(queue6.size() == 2);

    // Test 11: clear()
    queue6.clear();
    assert(queue6.empty());

    // Test 12: max_size()
    MyQueue<int> queue7(5);
    assert(queue7.max_size() == 5);

    // Test 13: push(T&&)
    int val = 4;
    queue7.push(std::move(val));
    assert(queue7.front() == 4);

    // Test 14: front() i back()
    queue7.push(5);
    assert(queue7.front() == 4);
    assert(queue7.back() == 5);

    // Test 15: size()
    assert(queue7.size() == 2);

    // Test 16: Poprawnosc kolejnosci
    queue7.push(6);
    assert(queue7.size() == 3);
    queue7.pop();
    assert(queue7.front() == 5);

    // Test 17: push() i pop()
    MyQueue<int> queue8(3);
    queue8.push(1);
    queue8.push(2);
    queue8.pop();
    queue8.push(3);
    assert(queue8.full() == false);
    assert(queue8.front() == 2);
    assert(queue8.back() == 3);

    std::cout << "Wszystko dziala" << std::endl;
    return 0;
}
