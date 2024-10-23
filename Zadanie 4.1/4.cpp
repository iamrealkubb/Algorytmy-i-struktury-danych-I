#include <iostream>
#include "singlelist.h"
#include <cassert>

int main() {
    // Test 1: Destruktor
    {
        SingleList<int> list;
        list.push_back(1);
        list.push_back(2);
    } // Jezeli destruktor poprawnie usuwa wezly to nie bedzie wycieku pamieci

    // Test 2: Konstruktor kopiujacy
    SingleList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    SingleList<int> list2(list1);
    assert(list2.size() == 2);
    assert(list2[0] == 1);
    assert(list2[1] == 2);

    // Test 3: push_front(const T&)
    list1.push_front(0);
    assert(list1.front() == 0);
    assert(list1.size() == 3);

    // Test 4: push_back(const T&)
    list1.push_back(3);
    assert(list1.back() == 3);
    assert(list1.size() == 4);

    // Test 5: display()
    list1.display(); // Oczekiwany wynik: 0 1 2 3

    // Test 6: pop_front()
    list1.pop_front();
    assert(list1.size() == 3);
    assert(list1.front() == 1);

    // Test 7: pop_back()
    list1.pop_back();
    assert(list1.size() == 2);
    assert(list1.back() == 2);

    // Test 8: Konstruktor move
    SingleList<int> list3(std::move(list1));
    assert(list1.empty());
    assert(list3.size() == 2);

    // Test 9: = copiujacy
    SingleList<int> list4;
    list4 = list3;
    assert(list4.size() == 2);
    assert(list4[0] == 1);
    assert(list4[1] == 2);

    // Test 10: = move
    SingleList<int> list5;
    list5 = std::move(list4);
    assert(list4.empty());
    assert(list5.size() == 2);

    // Test 11: empty()
    assert(list1.empty() == true);
    assert(list5.empty() == false);

    // Test 12: size()
    assert(list5.size() == 2);
    list5.push_back(3);
    assert(list5.size() == 3);

    // Test 13: push_front(T&&)
    int val = 0;
    list5.push_front(std::move(val));
    assert(list5.front() == 0);
    assert(list5.size() == 4);

    // Test 14: push_back(T&&)
    int val2 = 4;
    list5.push_back(std::move(val2));
    assert(list5.back() == 4);
    assert(list5.size() == 5);

    // Test 15: front()
    assert(list5.front() == 0);

    // Test 16: back()
    assert(list5.back() == 4);

    // Test 17: clear()
    list5.clear();
    assert(list5.empty() == true);

    // Test 18: reverse()
    list5.push_back(1);
    list5.push_back(2);
    list5.push_back(3);
    list5.reverse();
    assert(list5[0] == 3);
    assert(list5[1] == 2);
    assert(list5[2] == 1);

    // Test 19: operator[](std::size_t pos)
    assert(list5[0] == 3);
    assert(list5[1] == 2);
    assert(list5[2] == 1);

    // Test 20: const operator[](std::size_t pos)
    const SingleList<int> list6 = list5;
    assert(list6[0] == 3);
    assert(list6[1] == 2);
    assert(list6[2] == 1);

    // Test 21: erase(std::size_t pos)
    list5.erase(1);
    assert(list5.size() == 2);
    assert(list5[1] == 1);

    // Test 22: index(const T&)
    assert(list5.index(1) == 1);
    assert(list5.index(10) == -1);

    // Test 23: insert(std::size_t pos, const T&)
    list5.insert(1, 5);
    assert(list5[1] == 5);
    assert(list5.size() == 3);

    // Test 24: insert(std::size_t pos, T&&)
    int val3 = 6;
    list5.insert(2, std::move(val3));
    assert(list5[2] == 6);
    assert(list5.size() == 4);

    std::cout << "Wszystko dziala" << std::endl;
    return 0;
}
