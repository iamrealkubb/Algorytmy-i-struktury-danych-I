// myqueue.h

#include <iostream>
#include <cassert>

#ifndef MYQUEUE_H
#define MYQUEUE_H

template <typename T>
class MyQueue {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyQueue(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor

    ~MyQueue() {
        delete [] tab;
    }

    MyQueue(const MyQueue& other) : msize(other.msize), head(other.head), tail(other.tail) {
        tab = new T[msize];
        assert(tab != nullptr);
        for (std::size_t i = 0; i < msize; i++) {
            tab[i] = other.tab[i];
        }
    } // copy constructor

    MyQueue(MyQueue&& other) : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail) {
        other.tab = nullptr;
        other.msize = 1;
        other.head = 0;
        other.tail = 0;
    } // move constructor
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.

    MyQueue& operator=(const MyQueue& other) {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            head = other.head;
            tail = other.tail;
            tab = new T[msize];
            assert(tab != nullptr);
            for (std::size_t i = 0; i < msize; i++) {
                tab[i] = other.tab[i];
            }
        }
        return *this;
    } // copy assignment operator, return *this

    MyQueue& operator=(MyQueue&& other) {
        if (this != &other) {
            delete[] tab;
            tab = other.tab;
            msize = other.msize;
            head = other.head;
            tail = other.tail;
            other.tab = nullptr;
            other.msize = 1;
            other.head = 0;
            other.tail = 0;
        }
        return *this;
    } // move assignment operator, return *this
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.

    bool empty() const {
        return head == tail;
    }

    bool full() const {
        return (head + msize -1) % msize == tail;
    }

    std::size_t size() const {
        return (tail - head + msize) % msize;
    }

    std::size_t max_size() const {
        return msize-1;
    }

    void push(const T& item) {
        assert(!full());
        tab[tail] = item;
        tail = (tail + 1) % msize;
    } // dodanie na koniec

    void push(T&& item) {
        assert(!full());
        tab[tail] = std::move(item);
        tail = (tail + 1) % msize;
    } // dodanie na koniec

    T& front() {
        assert(!empty());
        return tab[head];
    } // zwraca początek

    T& back() {
        assert(!empty());
        return tab[(tail + msize -1) % msize];
    } // zwraca koniec

    void pop() {
        assert(!empty());
        head = (head + 1) % msize;
    } // usuwa początek

    void clear() {
        head = 0;
        tail = 0;
    } // czyszczenie listy z elementów

    void display() {
        for (std::size_t i = head; i != tail; i = (i + 1) % msize) {
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif