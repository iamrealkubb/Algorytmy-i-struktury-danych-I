// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList() {
        while (!empty()) {
            pop_front();
        }
    } // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other) : head(nullptr), tail(nullptr) {
        DoubleNode<T>* node = other.head;
        while (node != nullptr) {
            push_back(node->value);
            node = node->next;
        }
    } // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other) : head(other.head), tail(other.tail) {
        other.head = nullptr;
        other.tail = nullptr;
    } // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other) {
        if (this != &other) {
            clear();
            DoubleNode<T>* node = other.head;
            while (node != nullptr) {
                push_back(node->value);
                node = node->next;
            }
        }
        return *this;
    } // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other) {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
        }
        return *this;
    } // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const {
        return head == nullptr;
    }

    std::size_t size() const {
        std::size_t licznik = 0;
        DoubleNode<T>* node = head;
        while (node != nullptr) {
            node = node->next;
            licznik++;
        }
        return licznik;
    } // O(n) bo trzeba policzyc

    void push_front(const T& item) {
        if (!empty()) {
            head = new DoubleNode<T>(item, head);
            head->next->prev = head;
        } else {
            head = tail = new DoubleNode<T>(item);
        }
    } // O(1)

    void push_front(T&& item) {
        if (!empty()) {
            head = new DoubleNode<T>(std::move(item), head);
            head->next->prev = head;
        } else {
            head = tail = new DoubleNode<T>(std::move(item));
        }
    } // O(1) NIEOBOWIAZKOWE

    void push_back(const T& item) {
        if (!empty()) {
            tail = new DoubleNode<T>(item, nullptr, tail);
            tail->prev->next = tail;
        } else {
            head = tail = new DoubleNode<T>(item);
        }
    } // O(1)

    void push_back(T&& item) {
        if (!empty()) {
            tail = new DoubleNode<T>(std::move(item), nullptr, tail);
            tail->prev->next = tail;
        } else {
            head = tail = new DoubleNode<T>(std::move(item));
        }
    } // O(1) NIEOBOWIAZKOWE

    T& front() const {
        assert(!empty());
        return head->value;
    } // zwraca poczatek, nie usuwa

    T& back() const {
        assert(!empty());
        return tail->value;
    } // zwraca koniec, nie usuwa

    void pop_front() {
        assert(!empty());
        DoubleNode<T>* node = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete node;
    } // usuwa poczatek O(1)

    void pop_back() {
        assert(!empty());
        DoubleNode<T>* node = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete node;
    } // usuwa koniec O(1)

    void clear() {
        while (!empty()) {
            pop_front();
        }
    } // czyszczenie listy z elementow O(n)

    void display() {
        DoubleNode<T> *node = head;
        while (node != nullptr){
            std::cout << node->value << " ";
            node = node->next;
        }
        std::cout << std::endl;
    } // O(n)

    void display_reversed() {
        DoubleNode<T> *node = tail;
        while (node != nullptr){
            std::cout << node->value << " ";
            node = node->prev;
        }
        std::cout << std::endl;
    } // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos) {
        assert(pos < size());
        DoubleNode<T>* obecny = head;
        for (std::size_t i = 0; i < pos; i++) {
            obecny = obecny->next;
        }
        return obecny->value;
    } // podstawienie L[pos]=item, odczyt L[pos]

    const T& operator[](std::size_t pos) const {
        assert(pos < size());
        DoubleNode<T>* obecny = head;
        for (std::size_t i = 0; i < pos; i++) {
            obecny = obecny->next;
        }
        return obecny->value;
    } // dostep do obiektu const

    void erase(std::size_t pos) {
        assert(pos < size());
        if (pos == 0) {
            pop_front();
        } else if (pos == size() - 1) {
          pop_back();
        } else {
            DoubleNode<T>* obecny = head;
            for (std::size_t i = 0; i < pos; i++) {
                obecny = obecny->next;
            }
            obecny->prev->next = obecny->next;
            obecny->next->prev = obecny->prev;
            delete obecny;
        }
    }

    int index(const T& item) {
        DoubleNode<T>* obecny = head;
        int indeks = 0;
        while (obecny != nullptr) {
            if (obecny->value == item) {
                return  indeks;
            }
            obecny = obecny->next;
            indeks++;
        }
        return -1;
    } // jaki index na liscie (-1 gdy nie ma) O(n)

    void insert(std::size_t pos, const T& item) {
        assert(pos < size());
        if (pos == 0) {
            push_front(item);
        } else if (pos == size()) {
            push_back(item);
        } else {
            DoubleNode<T>* obecny = head;
            for (std::size_t i = 0; i < pos; i++) {
                obecny = obecny->next;
            }
            DoubleNode<T>* nowy = new DoubleNode<T>(item, obecny, obecny->prev);
            obecny->prev->next = nowy;
            obecny->prev = nowy;
        }
    } // inserts item before pos,

    void insert(std::size_t pos, T&& item) {
        assert(pos < size());
        if (pos == 0) {
            push_front(std::move(item));
        } else if (pos == size()) {
            push_back(std::move(item));
        } else {
            DoubleNode<T>* obecny = head;
            for (std::size_t i = 0; i < pos; i++) {
                obecny = obecny->next;
            }
            DoubleNode<T>* nowy = new DoubleNode<T>(std::move(item), obecny, obecny->prev);
            obecny->prev->next = nowy;
            obecny->prev = nowy;
        }
    } // inserts item before pos,

    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

#endif

// EOF