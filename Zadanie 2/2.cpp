#include <iostream>

using namespace std;

// Funkcja swap wykorzystywana w bubbleSort
template <typename T>
void wlasnySwap(T &poprzedni, T &nastepny) {
    T tymczsowa = poprzedni;
    poprzedni = nastepny;
    nastepny = tymczsowa;
}

// Sortowanie babelkowe
template <typename T>
void bubbleSort(T *tablica, int left, int right) {
    for (int i = left; i < right - 1; i++) {
        for (int j = left; j < right - (i - left) - 1; j++) {   // Iterujemy po elementach tablicy
            if (tablica[j] > tablica[j + 1]) {                  // i jezeli element jest wiekszy od nastepnego
                wlasnySwap(tablica[j], tablica[j + 1]);         // zamieniamy je miejscami
            }
        }
    }
}

// Funkcja scalajaca wykorzystywna w mergeSort
template <typename T>
void scalanie(T *tablica, int lewo, int srodek, int prawo) {
    int rozmiarScalanejTablicy = prawo - lewo + 1;
    T *tymczasowa = new T[rozmiarScalanejTablicy];

    int indeksLewo = lewo;           // Indeks wskazujacy na pocztek lewej czesci tablicy
    int indeksSrodek = srodek + 1;   // Indeks wskazujacy na poczatek prawej czesci tablicy
    int indeksTymczasowa = 0;        // Indeks wskazujacy na poczatek tablicy tymczasowej

    // Laczenie
    while (indeksLewo <= srodek && indeksSrodek <= prawo) {           // Dopoki indeksy nie wskazuja na koniec tablicy to
        if (tablica[indeksLewo] <= tablica[indeksSrodek]) {           // jezeli element z lewej czesci jest mniejszy lub rowny
            tymczasowa[indeksTymczasowa] = tablica[indeksLewo];       // to przepisujemy go do tablicy tymczasowej
            indeksLewo++;                                             // i zwiekszamy indeks lewej czesci
        } else {                                                      // a jezeli element z prawej czesci jest mniejszy
            tymczasowa[indeksTymczasowa] = tablica[indeksSrodek];     // to przepisujemy go do tablicy tymczasowej
            indeksSrodek++;                                           // i zwiekszamy indeks prawej czesci
        }
        indeksTymczasowa++;
    }

    // Kopiowanie pozostalych elementow z lewej czesci jesli jakies sa
    while (indeksLewo <= srodek) {
        tymczasowa[indeksTymczasowa] = tablica[indeksLewo];
        indeksTymczasowa++;
        indeksLewo++;
    }

    // Kopiowanie pozostalych elementow z prawej czesci jesli jakies sa
    while (indeksSrodek <= prawo) {
        tymczasowa[indeksTymczasowa] = tablica[indeksSrodek];
        indeksTymczasowa++;
        indeksSrodek++;
    }

    // Kopiowanie elementow z tablicy tymczasowej do tablicy oryginalnej
    for (int i = 0; i < rozmiarScalanejTablicy; i++) {
        tablica[lewo + i] = tymczasowa[i];
    }

    delete[] tymczasowa;
}

// Sortowanie przez scalanie rekurencyjne
template <typename T>
void mergeSort(T *tablica, int lewo, int prawo) {
    if (lewo < prawo) {                                 // Jezeli lewy indeks jest mniejszy od prawego
        int srodek = (lewo + prawo) / 2;                // obliczamy srodek tablicy
        mergeSort(tablica, lewo, srodek);               // dzielimy tablice na dwie czesci
        mergeSort(tablica, srodek + 1, prawo);          // i sortujemy je,
        scalanie(tablica, lewo, srodek, prawo);         // a nastepnie scalamy juz posortowane tablice
    }
}

int main() {
    // Tablica przed sortowaniem przez babelkowe
    int tablica1[] = {64, 34, 25, 12, 22, 11, 90};
    int rozmiar1 = sizeof(tablica1) / sizeof(tablica1[0]);

    cout << "Tablica przed sortowaniem (Bubble Sort): ";
    for (int element : tablica1) { // Petla zakresowa do wypisania elementow tablicy
        cout << element << " ";
    }
    cout << endl;

    bubbleSort(tablica1, 0, rozmiar1 - 1); // Wywolanie sortowania babelkowego

    cout << "Tablica po sortowaniu (Bubble Sort): ";
    for (int element : tablica1) {
        cout << element << " ";
    }
    cout << endl;

    // Tablica przed sortowaniem przez scalanie
    int tablica2[] = {70, 24, 17, 15, 75, 94, 9};
    int rozmiar2 = sizeof(tablica2) / sizeof(tablica2[0]);

    cout << "Tablica przed sortowaniem (Merge Sort): ";
    for (int element : tablica2) {
        cout << element << " ";
    }
    cout << endl;

    mergeSort(tablica2, 0, rozmiar2 - 1); // Wywolanie sortowania przez scalanie

    cout << "Tablica po sortowaniu (Merge Sort): ";
    for (int element : tablica2) {
        cout << element << " ";
    }
    cout << endl;

    return 0;
}
