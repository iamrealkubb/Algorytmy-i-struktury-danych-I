// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <algorithm> // alogrytmy

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor

    ~ArrayList() { delete [] tab; } // destruktor

    ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) {
        tab = new T[msize];
        std::copy(other.tab, other.tab + other.last, tab);
    } // copy constructor --- usage:   ArrayList<int> list2(list1);

    ArrayList(ArrayList&& other) : tab(other.tab), msize(other.msize), last(other.last) {
        other.tab = nullptr;
        other.msize = 0;
        other.last = 0;
    } // move constructor NIEOBOWIAZKOWE --- usage:   ArrayList<int> list2(std::move(list1));

    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            last = other.last;
            tab = new T[msize];
            std::copy(other.tab, other.tab + other.last, tab);
        }
        return *this;
    } // copy assignment operator, return *this --- usage:   list2 = list1;

    ArrayList& operator=(ArrayList&& other) {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            last = other.last;
            tab = other.tab;
            other.tab = nullptr;
            other.msize = 0;
            other.last = 0;
        }
        return *this;
    } // move assignment operator, return *this --- usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return last == 0; } // checks if the container has no elements

    bool full() const { return last == msize; } // checks if the container is full

    int size() const { return last; } // liczba elementow na liscie

    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow

    void push_front(const T& item) {
        assert(!full());
        for (int i = last; i > 0; i--) {
            tab[i] = tab[i - 1];
        }
        tab[0] = item;
        last++;
    } // dodanie na poczatek

    void push_front(T&& item) {
        assert(!full());
        for (int i = last; i > 0; i--) {
            tab[i] = std::move(tab[i - 1]);
        }
        tab[0] = std::move(item);
        last++;
    } // dodanie na poczatek NIEOBOWIAZKOWE

    void push_back(const T& item) {
        assert(!full());
        tab[last] = item;
        last++;
    } // dodanie na koniec

    void push_back(T&& item) {
        assert(!full());
        tab[last] = std::move(item);
        last++;
    } // dodanie na koniec NIEOBOWIAZKOWE

    T& front() {
        assert(!empty());
        return tab[0];
    } // zwraca poczatek, nie usuwa, error dla pustej listy

    T& back() {
        assert(!empty());
        return tab[last - 1];
    } // zwraca koniec, nie usuwa, error dla pustej listy

    void pop_front() {
        assert(!empty());
        for (int i = 0; i < last - 1; i++) {
            tab[i] = tab[i + 1];
        }
        last--;
    } // usuwa poczatek, error dla pustej listy

    void pop_back() {
        assert(!empty());
        last--;
    } // usuwa koniec, error dla pustej listy

    void clear() {
        last = 0;
    } // czyszczenie listy z elementow

    void display() {
        for (int i = 0; i < last; i++) {
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    } // lepiej zdefiniowac operator<<

    void reverse() {
        std::reverse(tab, tab + last);
    } // odwracanie kolejnosci

    void sort() {
        std::sort(tab, tab + last);
    } // sortowanie listy

    void merge(ArrayList& other) {
        int calkowityRozmiar = this->last + other.last;
        assert(calkowityRozmiar <= this->msize); // Sprawdzam czy pojemnosc jest wystarczajaca

        T* nowa = new T[calkowityRozmiar];
        int i = 0, j = 0, k = 0;

        // Przechodze przez obie listy i dodaje elementy w porzadku rosnacym
        while (i < this->last && j < other.last) {
            if (this->tab[i] < other.tab[j]) {
                nowa[k] = this->tab[i];
                k++;
                i++;
            } else {
                nowa[k] = other.tab[j];
                k++;
                j++;
            }
        }

        // Dodaje pozostale elementy z `this`
        while (i < this->last) {
            nowa[k++] = this->tab[i++];
        }

        // Dodaje pozostale elementy z `other`
        while (j < other.last) {
            nowa[k++] = other.tab[j++];
        }

        delete[] this->tab;
        this->tab = nowa;
        this->last = calkowityRozmiar;
    } //  merges two sorted lists into one NIEOBOWIAZKOWE

    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator

    T& operator[](int pos) {
        assert(pos >= 0 && pos < last);
        return tab[pos];
    } // podstawienie L[pos]=item, odczyt L[pos]

    const T& operator[](int pos) const {
        assert(pos >= 0 && pos < last);
        return tab[pos];
    } // dostep do obiektu const

    void erase(int pos) {
        assert(pos >= 0 && pos < last);
        for (int i = pos; i < last - 1; i++) {
            tab[i] = tab[i + 1];
        }
        last--;
    } // usuniecie elementu na pozycji pos

    int index(const T& item) {
        for (int i = 0; i < last; i++) {
            if (tab[i] == item) {
                return i;
            }
        }
        return -1;
    } // jaki index na liscie (-1 gdy nie ma)

    void insert(int pos, const T& item) {
        assert(!full() && pos >= 0 && pos <= last);
        for (int i = last; i > pos; i--) {
            tab[i] = tab[i - 1];
        }
        tab[pos] = item;
        last++;
    } // inserts item before pos

    void insert(int pos, T&& item) {
        assert(!full() && pos >= 0 && pos <= last);
        for (int i = last; i > pos; i--) {
            tab[i] = std::move(tab[i - 1]);
        }
        tab[pos] = std::move(item);
        last++;
    } // inserts item before posssert(pos >= 0 && pos < last);

    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
