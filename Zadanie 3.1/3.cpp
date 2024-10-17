#include <iostream>
#include "arraylist.h"

int main() {
    // 1. Konstruktor kopiujacy
    ArrayList<int> list1(10);
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);
    ArrayList<int> list2(list1);
    std::cout << "1. Konstruktor kopiujacy - Lista 2 skopiowana z listy 1: " << list2 << std::endl;

    // 2. Operator przypisania
    ArrayList<int> list3(10);
    list3 = list2;
    std::cout << "2. Copy assignment operator - Lista 3 przypisana z listy 2: " << list3 << std::endl;

    // 3. empty()
    std::cout << "3. empty() - Czy lista 3 jest pusta? (Nie powinna byc) " << (list3.empty() ? "Tak" : "Nie") << std::endl;

    // 4. full()
    list3.push_back(40);
    list3.push_back(50);
    list3.push_back(60);
    list3.push_back(70);
    list3.push_back(80);
    list3.push_back(90);
    list3.push_back(100); // Teraz powinna byc pelna
    std::cout << "4. full() - Czy lista 3 jest pelna? (Powinna byc) " << (list3.full() ? "Tak" : "Nie") << std::endl;
    list3.pop_front();
    list3.pop_front();
    list3.pop_front();
    list3.pop_front();
    list3.pop_front();
    list3.pop_front();
    list3.pop_front();

    // 5. size()
    std::cout << "5. size() - Rozmiar listy 3: " << list3.size() << std::endl;

    // 6. max_size()
    std::cout << "6. max_size() - Maksymalny rozmiar listy 3: " << list3.max_size() << std::endl;

    // 7. push_front()
    list3.push_front(5);
    std::cout << "7. push_front() - Lista 3 po dodaniu elementu na poczatek: " << list3 << std::endl;

    // 8. push_back()
    list3.push_back(40);
    std::cout << "8. push_back() - Lista 3 po dodaniu elementu na koniec: " << list3 << std::endl;

    // 9. front()
    std::cout << "9. front() - Pierwszy element listy 3: " << list3.front() << std::endl;

    // 10. back()
    std::cout << "10. back() - Ostatni element listy 3: " << list3.back() << std::endl;

    // 11. pop_front()
    list3.pop_front();
    std::cout << "11. pop_front() - Lista 3 po usunieciu pierwszego elementu: " << list3 << std::endl;

    // 12. pop_back()
    list3.pop_back();
    std::cout << "12. pop_back() - Lista 3 po usunieciu ostatniego elementu: " << list3 << std::endl;

    // 13. clear()
    list3.clear();
    std::cout << "13. clear() - Lista 3 po wyczyszczeniu: " << list3 << std::endl;

    // 14. display()
    list3.push_back(100);
    list3.push_back(200);
    std::cout << "14. display() - Lista 3: ";
    list3.display();

    // 15. reverse()
    list3.reverse();
    std::cout << "15. reverse() - Lista 3 po odwroceniu kolejnosci: " << list3 << std::endl;

    // 16. sort()
    list3.push_back(150);
    list3.sort();
    std::cout << "16. sort() - Lista 3 po sortowaniu: " << list3 << std::endl;

    // 17. Konstruktor move
    ArrayList<int> list4(std::move(list3));
    std::cout << "17. Konstruktor move - Lista 4 przeniesiona z listy 3: " << list4 << std::endl;

    // 18. Operator przypisania move
    ArrayList<int> list5(15);
    list5 = std::move(list4);
    std::cout << "18. Operator przypisania move - Lista 5 przypisana przeniesieniem z listy 4: " << list5 << std::endl;

    // 19. push_front(T&&)
    int value1 = 1;
    list5.push_front((value1));
    std::cout << "19. push_front(T&&) - Lista 5 po dodaniu przez move na poczatek: " << list5 << std::endl;

    // 20. push_back(T&&)
    int value2 = 300;
    list5.push_back((value2));
    std::cout << "20. push_back(T&&) - Lista 5 po dodaniu przez move na koniec: " << list5 << std::endl;

    // 21. Operator<< (z uzyciem operatora <<)
    std::cout << "21. Operator<< - Lista 5: " << list5 << std::endl;

    // 22. merge()
    ArrayList<int> list6(15);
    list6.push_back(50);
    list6.push_back(250);
    list5.merge(list6);
    std::cout << "22. merge() - Lista 5 po zlaczeniu z lista 6: " << list5 << std::endl;

    // 23. operator[]
    std::cout << "23. operator[] - Drugi element listy 5: " << list5[1] << std::endl;

    // 24. const operator[]
    const ArrayList<int> constList(list5);
    std::cout << "24. const operator[] - Pierwszy element const listy: " << constList[0] << std::endl;

    // 25. erase()
    list5.erase(1);
    std::cout << "25. erase() - Lista 5 po usunieciu elementu na pozycji 1: " << list5 << std::endl;

    // 26. index()
    int idx = list5.index(100);
    std::cout << "26. index() - Indeks elementu 100 w liscie 5: " << idx << std::endl;

    // 27. insert(pos, const T&)
    list5.insert(1, 999);
    std::cout << "27. insert(pos, const T&) - Lista 5 po wstawieniu 999 na pozycje 1: " << list5 << std::endl;

    // 28. insert(pos, T&&)
    int value3 = 888;
    list5.insert(2,(value3));
    std::cout << "28. insert(pos, T&&) - Lista 5 po wstawieniu 888 przez move na pozycje 2: " << list5 << std::endl;

    return 0;
}
