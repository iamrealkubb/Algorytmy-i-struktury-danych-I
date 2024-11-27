// mypriorityqueue.h

#include <vector>

#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector

    int heap_parent(int indeks) {
        return (indeks - 1) / 2;
    }

    int heap_left(int indeks) {
        return 2 * indeks + 1;
    }

    int heap_right(int indeks) {
        return 2 * indeks + 2;
    }

    void swap(int lewy, int prawy) {
        int element = lst[lewy];
        lst[lewy] = lst[prawy];
        lst[prawy] = element;
    }

    void fix_up(int element) {
        int rodzic = heap_parent(element);
        while (element > 0 && lst[rodzic] < lst[element]) {
            swap(element, rodzic);
            element = rodzic;
            rodzic = heap_parent(element);
        }
    }

    void fix_down(int element, int liczba_elementow) {
        while (true) {
            int lewe_dziecko = heap_left(element);
            int prawe_dziecko = heap_right(element);
            int najwieksza_wartosc = element;

            if (lewe_dziecko < liczba_elementow && lst[lewe_dziecko] > lst[najwieksza_wartosc]) {
                najwieksza_wartosc = lewe_dziecko;
            }
            if (prawe_dziecko < liczba_elementow && lst[prawe_dziecko] > lst[najwieksza_wartosc]) {
                najwieksza_wartosc = prawe_dziecko;
            }
            if (najwieksza_wartosc == element) {
                break;
            }
            swap(element, najwieksza_wartosc);
            element = najwieksza_wartosc;
        }
    }

    void wlasna_push_heap() {
        fix_up(lst.size() - 1);
    }

    void wlasna_pop_heap() {
        if (lst.empty()) {
            throw std::out_of_range("Sterta jest pusta");
        }
        swap(0, lst.size() - 1);
        fix_down(0, lst.size() - 1);
    }

public:
    MyPriorityQueue(std::size_t s=10) {
        lst.reserve(s);
    } // default constructor

    ~MyPriorityQueue() {
        lst.clear();
    }

    MyPriorityQueue(const MyPriorityQueue& other) : lst(other.lst) {} // copy constructor

    MyPriorityQueue(MyPriorityQueue&& other) : lst(std::move(other.lst)) {}// move constructor

    MyPriorityQueue& operator=(const MyPriorityQueue& other) {
        if (this != &other) {
            lst = other.lst;
        }
        return *this;
    } // copy assignment operator, return *this

    MyPriorityQueue& operator=(MyPriorityQueue&& other) {
        if (this != &other) {
            lst = std::move(other.lst);
        }
        return *this;
    } // move assignment operator, return *this

    bool empty() const {
        return lst.empty();
    }

    std::size_t size() const {
        return lst.size();
    } // liczba elementów w kolejce

    void push(const T& item) { // dodanie do kolejki
        lst.push_back(item);
        wlasna_push_heap();
    }

    void push(T&& item) { // dodanie do kolejki
        lst.push_back(std::move(item));
        wlasna_push_heap();
    }

    T& top() {
        return lst.front();
    } // zwraca element największy, nie usuwa

    void pop() { // usuwa element największy
        wlasna_pop_heap();
        lst.pop_back();
    }

    void clear() {
        lst.clear();
    } // czyszczenie listy z elementów

    void display() {
        for (const auto& element : lst) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};

#endif
