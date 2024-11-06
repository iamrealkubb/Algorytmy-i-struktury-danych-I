// mydeque.h

#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    MyDeque(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor

    ~MyDeque() {
        delete [] tab;
    }

    MyDeque(const MyDeque& other) : msize(other.msize), head(other.head), tail(other.tail) {
        tab = new T[msize];
        for (std::size_t i = 0; i < msize; i++) {
            tab[i] = other.tab[i];
        }
    } // copy constructor

    MyDeque(MyDeque&& other) : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail) {
        other.tab = nullptr;
        other.msize = 1;
        other.head = 0;
        other.tail = 0;
    } // move constructor NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.

    MyDeque& operator=(const MyDeque& other) {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            head = other.head;
            tail = other.tail;
            tab = new T[msize];
            for (std::size_t i = 0; i < msize; i++) {
                tab[i] = other.tab[i];
            }
        }
        return *this;
    } // copy assignment operator, return *this

    MyDeque& operator=(MyDeque&& other) {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            head = other.head;
            tail = other.tail;
            other.tab = nullptr;
            other.msize = 1;
            other.head = 0;
            other.tail = 0;
        }
        return *this;
    } // move assignment operator, return *this NIEOBOWIĄZKOWE
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.

    bool empty() const {
        return head == tail;
    }

    bool full() const {
        return (tail + 1) % msize == head;
    }
    std::size_t size() const {
        return (tail - head + msize) % msize;
    }

    std::size_t max_size() const {
        return msize-1;
    }

    void push_front(const T& item) {
        assert(!full());
        head = (head + msize - 1) % msize;
        tab[head] = item;
    } // dodanie na początek O(1)

    void push_front(T&& item) {
        assert(!full());
        head = (head + msize - 1) % msize;
        tab[head] = std::move(item);
    } // dodanie na początek O(1) NIEOBOWIĄZKOWE

    void push_back(const T& item) {
        assert(!full());
        tab[tail] = item;
        tail = (tail + 1) % msize;
    } // dodanie na koniec O(1)

    void push_back(T&& item) {
        assert(!full());
        tab[tail] = std::move(item);
        tail = (tail + 1) % msize;
    } // dodanie na koniec O(1) NIEOBOWIĄZKOWE

    T& front() {
        return tab[head];
    } // zwraca poczatek

    T& back() {
        return tab[(tail + msize -1) % msize];
    } // zwraca koniec

    void pop_front() {
        assert(!empty());
        head = (head + 1) % msize;
    } // usuwa początek kolejki O(1)

    void pop_back() {
        assert(!empty());
        tail = (tail + msize - 1) % msize;
    } // usuwa koniec kolejki O(1)

    void clear() {
        head = 0;
        tail = 0;
    } // czyszczenie listy z elementów

    void display() {
        for (std::size_t i = head; i != tail; i=(i+1) % msize) {
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    }

    void display_reversed() {
        for (std::size_t i = (tail + msize - 1) % msize; i != (head + msize - 1) % msize; i = (i + msize - 1) % msize) {
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    }

    // Operacje z indeksami. NIEOBOWIĄZKOWE
    T& operator[](std::size_t pos) {
        assert(pos < size());
        return tab[(head + pos) % msize];
    } // podstawienie L[pos]=item, odczyt L[pos]

    const T& operator[](std::size_t pos) const {
        assert(pos < size());
        return tab[(head + pos) % msize];
    } // dostęp do obiektu const

    void erase(std::size_t pos) {
        assert(pos < size());
        std::size_t pozycjaWKolejce = (head + pos) % msize;
        if (pozycjaWKolejce >= head) {
            for (std::size_t i = pozycjaWKolejce; i != tail; i = (i + 1) % msize) {
                tab[i] = tab[(i + 1) % msize];
            }
        }
        tail = (tail + msize - 1) % msize;
    }

    int index(const T& item) {
        std::size_t i = head;
        int indeks = 0;
        while (i != tail) {
            if (tab[i] == item) {
                return indeks;
            }
            i = (i + 1) % msize;
            indeks++;
        }
        return -1;
    } // jaki index na liście (-1 gdy nie ma)

    void insert(std::size_t pos, const T& item) {
        assert(pos <= size() && !full());
        std::size_t pozycjaWKolejce = (head + pos) % msize;
        if (pozycjaWKolejce == head) {
            push_front(item);
        } else if (pozycjaWKolejce == tail) {
            push_back(item);
        } else {
            std::size_t i = tail;
            tail = (tail + 1) % msize;
            while (i != pozycjaWKolejce) {
                tab[i] = tab[(i + msize - 1) % msize];
                i = (i + msize - 1) % msize;
            }
            tab[pozycjaWKolejce] = item;
        }
    } // inserts item before pos

    void insert(std::size_t pos, T&& item) {
        assert(pos <= size() && !full());
        std::size_t pozycjaWKolejce = (head + pos) % msize;
        if (pozycjaWKolejce == head) {
            push_front(std::move(item));
        } else if (pozycjaWKolejce == tail) {
            push_back(std::move(item));
        } else {
            std::size_t i = tail;
            tail = (tail + 1) % msize;
            while (i != pozycjaWKolejce) {
                tab[i] = tab[(i + msize - 1) % msize];
                i = (i + msize - 1) % msize;
            }
            tab[pozycjaWKolejce] = std::move(item);
        }
    } // inserts item before pos
};

#endif