#include "biblioteka.h"
#include <iostream>

int main() {
    Biblioteka biblioteka;

    biblioteka.dodajKsiazke(Ksiazka(1, "Pan Tadeusz", "Adam Mickiewicz"));
    biblioteka.dodajKsiazke(Ksiazka(2, "Potop", "Henryk Sienkiewicz"));
    biblioteka.dodajKsiazke(Ksiazka(3, "Kordian", "Juliusz Slowacki"));
    biblioteka.dodajKsiazke(Ksiazka(4, "Jezyk C++", "Stephen Prata"));
    biblioteka.dodajKsiazke(Ksiazka(5, "Algorytmy i struktury danych", "Alfred V.Aho"));
    biblioteka.dodajKsiazke(Ksiazka(6, "Python", "Mark Lutz"));
    biblioteka.dodajKsiazke(Ksiazka(7, "Wprowadzenie do algorytmow", "Thomas Cormen"));
    biblioteka.dodajKsiazke(Ksiazka(8, "Inny swiat", "Gustaw Herling-Grudzinsk"));
    biblioteka.dodajKsiazke(Ksiazka(9, "Zdazyc przed Panem Bogiem", "Hanna Krall"));
    biblioteka.dodajKsiazke(Ksiazka(10, "Lalka", "Boleslaw Prus"));
    biblioteka.dodajKsiazke(Ksiazka(11, "Ferdydurke", "Witold Gombrowicz"));
    biblioteka.dodajKsiazke(Ksiazka(12, "Wiedzmin", "Andrzej Sapkowski"));

    std::string imie;
    int idCzytelnika = 0;
    int wszystkieID = 0;
    bool wylogowany = true;
    int wybor;

    while (true) {
        if (wylogowany) {
            std::cout << "-------------------- WITAMY W NASZEJ BIBLIOTECE --------------------\n";
            std::cout << "\nPodaj swoje imie (lub wpisz \"exit\", aby wyjsc): ";
            std::cin >> imie;

            if (imie == "exit") {
                std::cout << "Do zobaczenia!\n";
                break;
            }

            switch (biblioteka.sprawdzCzyWBazieImie(imie)) {
                case 0:
                    idCzytelnika++;
                    wszystkieID++;
                    biblioteka.dodajCzytelnika(Czytelnik(wszystkieID, imie));
                    std::cout << "Zalogowano jako nowy uzytkownik. Twoje ID: " << wszystkieID << "\n";
                    wylogowany = false;
                    break;
                default:
                    int wpisaneID;
                    std::cout << "Znaleziono uzytkownikow o podanym imieniu. Podaj swoje ID (jesli nie masz, wpisz 0): ";
                    while (true) {
                        if (std::cin >> wpisaneID) {
                            break;
                        } else {
                            std::cin.clear();
                            czyszczenieBufora();
                            std::cout << "Nieprawidlowe ID. Podaj liczbe: ";
                        }
                }

                if (wpisaneID == 0) {
                    idCzytelnika++;
                    wszystkieID++;
                    biblioteka.dodajCzytelnika(Czytelnik(wszystkieID, imie));
                    std::cout << "Zalogowano jako nowy uzytkownik. Twoje ID: " << wszystkieID << "\n";
                    wylogowany = false;
                } else if (!biblioteka.sprawdzCzyWBazieID(wpisaneID)) {
                    while (!biblioteka.sprawdzCzyWBazieID(wpisaneID)) {
                        std::cout << "Uzytkownik o podanym ID nie istnieje.\n";
                        czyszczenieBufora();
                        std::cout << "Podaj poprawne ID: ";
                        std::cin >> wpisaneID;
                    }
                    idCzytelnika = wpisaneID;
                    std::cout << "Zalogowano jako uzytkownik o ID: " << idCzytelnika << "\n";
                    wylogowany = false;
                } else {
                    idCzytelnika = wpisaneID;
                    std::cout << "Zalogowano jako uzytkownik o ID: " << idCzytelnika << "\n";
                    wylogowany = false;
                }
                break;
            }
        }

        std::cout << "-----------------------------------*";
        std::cout << "\nWybierz opcje:\n";
        std::cout << "1. Wyszukaj ksiazke\n";
        std::cout << "2. Wypozycz ksiazke\n";
        std::cout << "3. Zwroc ksiazke\n";
        std::cout << "4. Pokaz twoje wypozyczone ksiazki\n";
        std::cout << "5. Pokaz dostepne ksiazki\n";
        std::cout << "6. Wyloguj\n";
        std::cout << "7. Wyjscie\n";
        std::cout << "-----------------------------------*\n";
        std::cout << "Wybor: ";
        while (true) {
            if (std::cin >> wybor) {
                break;
            } else {
                std::cin.clear();
                czyszczenieBufora();
                std::cout << "Niepoprawny wybor. Podaj liczbe: ";
            }
        }
        czyszczenieEkranu();

        if (wybor == 1) {
            czyszczenieBufora();
            std::string tytul;
            std::cout << "Podaj tytul ksiazki: ";
            std::getline(std::cin, tytul);
            czyszczenieEkranu();
            biblioteka.wyszukajKsiazke(tytul);
            kontynuacja();
            czyszczenieEkranu();
        } else if (wybor == 2) {
            int idKsiazki;
            std::cout << "Podaj ID ksiazki do wypozyczenia: ";
            while (true) {
                if (std::cin >> idKsiazki) {
                    break;
                } else {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Nieprawidlowe ID. Podaj liczbe: ";
                }
            }
            biblioteka.wypozyczKsiazke(idCzytelnika, idKsiazki);
            czyszczenieBufora();
            kontynuacja();
            czyszczenieEkranu();
        } else if (wybor == 3) {
            int idKsiazki;
            std::cout << "Podaj ID ksiazki do zwrotu: ";
            while (true) {
                if (std::cin >> idKsiazki) {
                    break;
                } else {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Nieprawidlowe ID. Podaj liczbe: ";
                }
            }
            biblioteka.zwrocKsiazke(idCzytelnika, idKsiazki);
            czyszczenieBufora();
            kontynuacja();
            czyszczenieEkranu();
        } else if (wybor == 4) {
            std::cout << "Wypozyczone przez Ciebie ksiazki:\n";
            biblioteka.pokazWypozyczoneKsiazki(idCzytelnika);
            czyszczenieBufora();
            kontynuacja();
            czyszczenieEkranu();
        } else if (wybor == 5) {
            std::cout << "Dostepne ksiazki w kolejnosci alfabetycznej:\n";
            biblioteka.pokazDostepneKsiazki();
            czyszczenieBufora();
            kontynuacja();
            czyszczenieEkranu();
        } else if (wybor == 6) {
            wylogowany = true;
            czyszczenieEkranu();
        } else if (wybor == 7) {
            std::cout << "Do zobaczenia!\n";
            break;
        } else {
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
            czyszczenieBufora();
        }
    }

    return 0;
}