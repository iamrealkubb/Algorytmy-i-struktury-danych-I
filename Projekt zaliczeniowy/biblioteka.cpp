#include "biblioteka.h"
#include <iostream>

int main() {
    Biblioteka biblioteka;

    biblioteka.wczytajDane();
    Administrator admin;

    std::string imie;
    int idCzytelnika = biblioteka.ileCzytelnikow();
    int wszystkieID = biblioteka.ileCzytelnikow();
    bool wylogowany = true;
    bool trybAdministratora = false;
    int wybor;

    while (true) {
        if (wylogowany) {
            std::cout << "-------------------- WITAMY W NASZEJ BIBLIOTECE --------------------\n";
            std::cout << "\nPodaj swoje imie (lub wpisz \"exit\" aby wyjsc): ";
            std::cin >> imie;

            if (imie == "exit") {
                std::cout << "Do zobaczenia!\n";
                break;
            }

            if (imie == "TajnyAdmin") {
                trybAdministratora = true;
                wylogowany = false;
                czyszczenieEkranu();
                continue;
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

        if (trybAdministratora) {
            std::cout << "-----------------------------------*";
            std::cout << "\nWYBIERZ OPCJE ADMINISTRATORA:\n";
            std::cout << "1. Dodaj ksiazke\n";
            std::cout << "2. Zmien dostepnosc ksiazki\n";
            std::cout << "3. Pokaz status ksiazek\n";
            std::cout << "4. Sprawdz kto wypozyczyl ksiazke\n";
            std::cout << "5. Wyloguj\n";
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
                int id;
                std::string tytul, autor;
                std::cout << "Podaj ID ksiazki: ";
                while (!(std::cin >> id)) {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Niepoprawne ID. Sprobuj ponownie: ";
                }
                czyszczenieBufora();
                std::cout << "Podaj tytul ksiazki: ";
                std::getline(std::cin, tytul);
                std::cout << "Podaj autora ksiazki: ";
                std::getline(std::cin, autor);
                admin.dodajKsiazke(biblioteka, id, tytul, autor);
                kontynuacja();
                czyszczenieEkranu();
            } else if (wybor == 2) {
                int idKsiazki;
                std::cout << "Podaj ID ksiazki: ";
                while (!(std::cin >> idKsiazki)) {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Niepoprawne ID. Sprobuj ponownie: ";
                }
                admin.zmienDostepnoscKsiazki(biblioteka, idKsiazki);
                czyszczenieBufora();
                kontynuacja();
                czyszczenieEkranu();
            } else if (wybor == 3) {
                admin.pokazStatusKsiazek(biblioteka);
                czyszczenieBufora();
                kontynuacja();
                czyszczenieEkranu();
            } else if (wybor == 4) {
                int idKsiazki;
                std::cout << "Podaj ID ksiazki, aby sprawdzic kto ja wypozyczyl: ";
                while (!(std::cin >> idKsiazki)) {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Niepoprawne ID. Sprobuj ponownie: ";
                }
                admin.sprawdzKtoWypozyczylKsiazke(biblioteka, idKsiazki);
                czyszczenieBufora();
                kontynuacja();
                czyszczenieEkranu();
            } else if (wybor == 5) {
                trybAdministratora = false;
                wylogowany = true;
                czyszczenieEkranu();
            } else {
                std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
                czyszczenieBufora();
            }
        } else {
            std::cout << "-----------------------------------*";
            std::cout << "\nWYBIERZ OPCJE:\n";
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
                while (!(std::cin >> idKsiazki)) {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Nieprawidlowe ID. Podaj liczbe: ";
                }
                biblioteka.wypozyczKsiazke(idCzytelnika, idKsiazki);
                czyszczenieBufora();
                kontynuacja();
                czyszczenieEkranu();
            } else if (wybor == 3) {
                int idKsiazki;
                std::cout << "Podaj ID ksiazki do zwrotu: ";
                while (!(std::cin >> idKsiazki)) {
                    std::cin.clear();
                    czyszczenieBufora();
                    std::cout << "Nieprawidlowe ID. Podaj liczbe: ";
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
    }
    biblioteka.zapiszDane();
    return 0;
}