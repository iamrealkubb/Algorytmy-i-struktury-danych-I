// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <utility>    // move()

template <typename T>
struct SingleNode {
// the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
public:
    SingleList() : head(nullptr), tail(nullptr) {}

    ~SingleList() {
        while (!empty()) {
            pop_front();
        }
    } // tu trzeba wyczyscic wezly

    SingleList(const SingleList& other) : head(nullptr), tail(nullptr) {
        SingleNode<T>* node = other.head;
        while (node != nullptr) {
            push_back(node->value);
            node = node->next;
        }
    } // copy constructor
    // usage:   SingleList<int> list2(list1);

    SingleList(SingleList&& other) : head(other.head), tail(other.tail) {
        other.head = nullptr;
        other.tail = nullptr;
    } // move constructor NIEOBOWIAZKOWE
    // usage:   SingleList<int> list2(std::move(list1));

    SingleList& operator=(const SingleList& other) {
        if (this != &other) {
            clear();
            SingleNode<T>* node = other.head;
            while (node != nullptr) {
                push_back(node->value);
                node = node->next;
            }
        }
        return *this;
    } // copy assignment operator, return *this
    // usage:   list2 = list1;

    SingleList& operator=(SingleList&& other) {
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

    bool empty() const { return head == nullptr; }

    std::size_t size() const {
        std::size_t licznik = 0;
        SingleNode<T>* node = head;
        while (node != nullptr) {
            node = node->next;
            licznik++;
        }
        return licznik;
    } // O(n) bo trzeba policzyc

    void push_front(const T& item) {
        if (!empty()) {
            head = new SingleNode<T>(item, head);
        } else {
            head = tail = new SingleNode<T>(item);
        }
    } // O(1), L.push_front(item)

    void push_front(T&& item) {
        if (!empty()) {
            head = new SingleNode<T>(std::move(item), head);
        } else {
            head = tail = new SingleNode<T>(std::move(item));
        }
    } // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE

    void push_back(const T& item) {
        if (!empty()) {
            tail->next = new SingleNode<T>(item);
            tail = tail->next;
        } else {
            head = tail = new SingleNode<T>(item);
        }
    } // O(1), L.push_back(item)

    void push_back(T&& item) {
        if (!empty()) {
            tail->next = new SingleNode<T>(std::move(item));
            tail = tail->next;
        } else {
            head = tail = new SingleNode<T>(std::move(item));
        }
    } // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE

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
        SingleNode<T> *node = head; // zapamietujemy
        if (head == tail) { // jeden wezel na liscie
            head = tail = nullptr;
        } else { // wiecej niz jeden wezel na liscie
            head = head->next;
        }
        delete node;
    } // usuwa poczatek O(1)

    void pop_back() {
        assert(!empty());
        SingleNode<T> *node = tail; // zapamietujemy
        if (head == tail) { // jeden wezel na liscie
            head = tail = nullptr;
        } else { // wiecej niz jeden wezel na liscie
            // Szukamy poprzednika ogona.
            SingleNode<T> *before=head;
            while (before->next != tail) {
                before = before->next;
            }
            tail = before;
            tail->next = nullptr;
        }
        delete node;
    } // usuwa koniec O(n)

    void clear() {
        while (!empty()) {
            pop_front();
        }
    } // czyszczenie listy z elementow O(n)

    void display() {
        SingleNode<T> *node = head;
        while (node != nullptr){
            std::cout << node->value << " ";
            node = node->next;
        }
        std::cout << std::endl;
    } // O(n)

    void reverse() {
        SingleNode<T>* poprzedni = nullptr;
        SingleNode<T>* obecny = head;
        SingleNode<T>* nastepny = nullptr;
        tail = head;
        while (obecny != nullptr) {
            nastepny = obecny->next;
            obecny->next = poprzedni;
            poprzedni = obecny;
            obecny = nastepny;
        }
        head = poprzedni;
    } // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos) {
        assert(pos < size());
        SingleNode<T>* node = head;
        for (std::size_t i = 0; i < pos; i++) {
            node = node->next;
        }
        return node->value;
    } // podstawienie L[pos]=item, odczyt L[pos]

    const T& operator[](std::size_t pos) const {
        assert(pos < size());
        SingleNode<T>* node = head;
        for (std::size_t i = 0; i < pos; i++) {
            node = node->next;
        }
        return node->value;
    } // dostep do obiektu const

    void erase(std::size_t pos) {
        assert(pos < size());
        if (pos == 0) {
            pop_front();
        } else {
            SingleNode<T>* poprzedni = head;
            for (std::size_t i = 0; i < pos - 1; i++) {
                poprzedni = poprzedni->next;
            }
            SingleNode<T>* doUsuniecia = poprzedni->next;
            poprzedni->next = doUsuniecia->next;
            if (doUsuniecia == tail) {
                tail = poprzedni;
            }
            delete doUsuniecia;
        }
    }

    int index(const T& item) {
        SingleNode<T>* node = head;
        int indeks = 0;
        while (node != nullptr) {
            if (node->value == item) {
                return  indeks;
            }
            node = node->next;
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
            SingleNode<T>* poprzedni = head;
            for (std::size_t i = 0; i < pos - 1; i++) {
                poprzedni = poprzedni->next;
            }
            poprzedni->next = new SingleNode<T>(item, poprzedni->next);
        }
    } // inserts item before pos,

    void insert(std::size_t pos, T&& item) {
        assert(pos < size());
        if (pos == 0) {
            push_front(std::move(item));
        } else if (pos == size()) {
            push_back(std::move(item));
        } else {
            SingleNode<T>* poprzedni = head;
            for (std::size_t i = 0; i < pos - 1; i++) {
                poprzedni = poprzedni->next;
            }
            poprzedni->next = new SingleNode<T>(std::move(item), poprzedni->next);
        }
    } // inserts item before pos,

    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

#endif