#include <iostream>
#include "mydeque.h"
#include <cassert>

int main() {
    // Test 1: Destruktor
    {
        MyDeque<int> deque;
        deque.push_back(1);
        deque.push_back(2);
    } // Jeśli destruktor działa poprawnie, nie będzie wycieku pamięci

    // Test 2: Konstruktor kopiujący
    MyDeque<int> deque1;
    deque1.push_back(1);
    deque1.push_back(2);
    MyDeque<int> deque2(deque1);
    assert(deque2.size() == 2);
    assert(deque2[0] == 1);
    assert(deque2[1] == 2);

    // Test 3: push_front
    deque1.push_front(0);
    assert(deque1.front() == 0);
    assert(deque1.size() == 3);

    // Test 4: push_back
    deque1.push_back(3);
    assert(deque1.back() == 3);
    assert(deque1.size() == 4);

    // Test 5: display()
    deque1.display(); // Oczekiwany wynik: 0 1 2 3

    // Test 6: pop_front()
    deque1.pop_front();
    assert(deque1.size() == 3);
    assert(deque1.front() == 1);

    // Test 7: pop_back()
    deque1.pop_back();
    assert(deque1.size() == 2);
    assert(deque1.back() == 2);

    // Test 8: Konstruktor przenoszący
    MyDeque<int> deque3(std::move(deque1));
    assert(deque1.empty());
    assert(deque3.size() == 2);

    // Test 9: operator przypisania kopiujący
    MyDeque<int> deque4;
    deque4 = deque3;
    assert(deque4.size() == 2);
    assert(deque4[0] == 1);
    assert(deque4[1] == 2);

    // Test 10: operator przypisania przenoszący
    MyDeque<int> deque5;
    deque5 = std::move(deque4);
    assert(deque4.empty());
    assert(deque5.size() == 2);

    // Test 11: empty()
    assert(deque1.empty() == true);
    assert(deque5.empty() == false);

    // Test 12: size()
    assert(deque5.size() == 2);
    deque5.push_back(3);
    assert(deque5.size() == 3);

    // Test 13: push_front(T&&)
    int val = 0;
    deque5.push_front(std::move(val));
    assert(deque5.front() == 0);
    assert(deque5.size() == 4);

    // Test 14: push_back(T&&)
    int val2 = 4;
    deque5.push_back(std::move(val2));
    assert(deque5.back() == 4);
    assert(deque5.size() == 5);

    // Test 15: front()
    assert(deque5.front() == 0);

    // Test 16: back()
    assert(deque5.back() == 4);

    // Test 17: clear()
    deque5.clear();
    assert(deque5.empty() == true);

    // Test 18: display_reversed()
    deque5.push_back(1);
    deque5.push_back(2);
    deque5.push_back(3);
    deque5.display_reversed(); // Oczekiwany wynik: 3 2 1

    // Test 19: operator[](std::size_t pos)
    assert(deque5[0] == 1);
    assert(deque5[1] == 2);
    assert(deque5[2] == 3);


    // Test 20: erase(std::size_t pos)
    deque5.erase(1);
    assert(deque5.size() == 2);
    assert(deque5[1] == 3);

    // Test 21: index(const T&)
    assert(deque5.index(1) == 0);
    assert(deque5.index(10) == -1);

    // Test 22: insert(std::size_t pos, const T&)
    deque5.insert(1, 5);
    assert(deque5[1] == 5);
    assert(deque5.size() == 3);

    // Test 23: insert(std::size_t pos, T&&)
    int val3 = 6;
    deque5.insert(2, std::move(val3));
    assert(deque5[2] == 6);
    assert(deque5.size() == 4);

    std::cout << "Wszystko dziala" << std::endl;
    return 0;
}
