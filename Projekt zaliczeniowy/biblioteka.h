// biblioteka.h

#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

void czyszczenieBufora() {
    std::cin.ignore(100, '\n');
}

void czyszczenieEkranu() {
    std::system("clear");
}

void kontynuacja() {
    std::cout << "\nWcisnij ENTER aby kontynuowac...";
    getchar();
}

std::string naMaleLitery(const std::string& ciag) {
    std::string maleCiag;
    for (char c : ciag) {
        maleCiag += std::tolower(c);
    }
    return maleCiag;
}

class Ksiazka {
private:
    int identyfikator;
    std::string tytul;
    std::string autor;
    bool czyDostepna;

public:
    Ksiazka(int identyfikator, const std::string& tytul, const std::string& autor) {
        this->identyfikator = identyfikator;
        this->tytul = tytul;
        this->autor = autor;
        this->czyDostepna = true;
    }

    int pobierzIdentyfikator() const {
        return identyfikator;
    }

    const std::string& pobierzTytul() const {
        return tytul;
    }

    const std::string& pobierzAutora() const {
        return autor;
    }

    bool sprawdzDostepnosc() const {
        return czyDostepna;
    }

    void wypozycz() {
        czyDostepna = false;
    }

    void zwroc() {
        czyDostepna = true;
    }

    void wyswietl() const {
        std::cout << "Ksiazka pt. " << tytul << ":" << std::endl;
        std::cout << "ID: " << identyfikator << std::endl;
        std::cout << "Autor: " << autor << std::endl;
        std::cout << "Czy jest dostepna: " << (czyDostepna ? "Tak" : "Nie") << std::endl;
    }

    void ustawDostepnosc(bool dostepnosc) {
        this->czyDostepna = dostepnosc;
    }

    void zapiszDoPliku(std::ofstream& plik) const {
        plik << identyfikator << "|" << tytul << "|" << autor << "|" << czyDostepna << "\n";
    }

    static Ksiazka wczytajZPliku(std::ifstream& plik) {
        int id;
        std::string tytul;
        std::string autor;
        bool dostepna;
        std::string linia;
        if (std::getline(plik, linia)) {
            std::stringstream ss(linia);
            std::getline(ss, linia, '|');
            id = std::stoi(linia);
            std::getline(ss, tytul, '|');
            std::getline(ss, autor, '|');
            std::getline(ss, linia);
            dostepna = std::stoi(linia);
        }
        Ksiazka ksiazka(id, tytul, autor);
        ksiazka.ustawDostepnosc(dostepna);
        return ksiazka;
    }
};

class Czytelnik {
private:
    int identyfikator;
    std::string imie;
    std::vector<Ksiazka> wypozyczoneKsiazki;

    friend class Biblioteka;
public:
    Czytelnik(int identyfikator, const std::string& imie) {
        this->identyfikator = identyfikator;
        this->imie = imie;
    }

    int pobierzIdentyfikator() const {
        return identyfikator;
    }

    const std::string& pobierzImie() const {
        return imie;
    }

    void wypozyczKsiazke(Ksiazka& ksiazka) {
        ksiazka.wypozycz();
        wypozyczoneKsiazki.push_back(ksiazka);
    }

    void zwrocKsiazke(Ksiazka& ksiazka) {
        for (auto szukana = wypozyczoneKsiazki.begin(); szukana != wypozyczoneKsiazki.end(); szukana++) {
            if (szukana->pobierzIdentyfikator() == ksiazka.pobierzIdentyfikator()) {
                szukana->zwroc();
                wypozyczoneKsiazki.erase(szukana);
                break;
            }
        }
    }

    void wyswietlWypozyczoneKsiazki() const {
        std::cout << "Ksiazki wypozyczone przez czytelnika: " << imie << " (id: " << identyfikator << ")" << std::endl;
        for (Ksiazka ksiazka : wypozyczoneKsiazki) {
            std::cout << "-> " << ksiazka.pobierzAutora() << " " << ksiazka.pobierzTytul() << std::endl;
        }
    }

    void zapiszDoPliku(std::ofstream& plik) const {
        plik << identyfikator << "|" << imie;
        for (const auto& ksiazka : wypozyczoneKsiazki) {
            plik << "|" << ksiazka.pobierzIdentyfikator();
        }
        plik << "\n";
    }

    static Czytelnik wczytajZPliku(const std::string& linia, std::vector<Ksiazka>& ksiazki) {
        std::stringstream ss(linia);
        std::string fragment;

        std::getline(ss, fragment, '|');
        int id = std::stoi(fragment);
        std::string imie;
        std::getline(ss, imie, '|');

        Czytelnik czytelnik(id, imie);

        while (std::getline(ss, fragment, '|')) {
            int idKsiazki = std::stoi(fragment);
            auto it = std::find_if(ksiazki.begin(), ksiazki.end(), [&idKsiazki](const Ksiazka& k) {
                return k.pobierzIdentyfikator() == idKsiazki;
            });
            if (it != ksiazki.end()) {
                czytelnik.wypozyczKsiazke(*it);
            }
        }

        return czytelnik;
    }

    const std::vector<Ksiazka>& pobierzWypozyczoneKsiazki() const {
        return wypozyczoneKsiazki;
    }
};

class Biblioteka {
private:
    std::vector<Ksiazka> ksiazki;
    std::vector<Czytelnik> czytelnicy;
public:
    void dodajKsiazke(const Ksiazka& ksiazka) {
        ksiazki.push_back(ksiazka);
    }

    int sprawdzCzyWBazieImie(const std::string& imie) const {
        int znalezionych = 0;
        for (const auto& istniejacy : czytelnicy) {
            if (istniejacy.pobierzImie() == imie) {
                znalezionych++;
            }
        }
        return znalezionych;
    }

    bool sprawdzCzyWBazieID(int id) const {
        for (const auto& istniejacy : czytelnicy) {
            if (id == 0) {
                return false;
            } else if (istniejacy.pobierzIdentyfikator() == id) {
                return true;
            }
        }
        return false;
    }

    void dodajCzytelnika(const Czytelnik& czytelnik) {
        czytelnicy.push_back(czytelnik);
    }

    void wyszukajKsiazke(const std::string& tytul) const {
        for (auto& szukana : ksiazki) {
            if (naMaleLitery(szukana.pobierzTytul()) == "\"" + naMaleLitery(tytul) + "\"") {
                szukana.wyswietl();
                return;
            }
        }
        std::cout << "Nie znaleziono takiej ksiazki" << std::endl;
    }

    void wypozyczKsiazke(int idCzytelnika, int idKsiazki) {
        for (auto& czytelnik : czytelnicy) {
            if (czytelnik.pobierzIdentyfikator() == idCzytelnika) {
                for (auto& ksiazka : ksiazki) {
                    if (ksiazka.pobierzIdentyfikator() == idKsiazki) {
                        if (ksiazka.sprawdzDostepnosc()) {
                            czytelnik.wypozyczKsiazke(ksiazka);
                            std::cout << "Ksiazka " << ksiazka.pobierzTytul() << " zostala wypozyczona.\n";
                            return;
                        } else {
                            std::cout << "Ksiazka " << ksiazka.pobierzTytul() << " jest teraz niedostepna.\n";
                            return;
                        }
                    }
                }
                std::cout << "Ksiazka o podanym ID nie istnieje.\n";
                return;
            }
        }
    }

    void zwrocKsiazke(int idCzytelnika, int idKsiazki) {
        for (auto& czytelnik : czytelnicy) {
            if (czytelnik.pobierzIdentyfikator() == idCzytelnika) {
                if (czytelnik.wypozyczoneKsiazki.empty()) {
                    std::cout << "Nie masz wypozyczonych ksiazek.\n";
                    return;
                }

                for (auto zwracana = czytelnik.wypozyczoneKsiazki.begin(); zwracana != czytelnik.wypozyczoneKsiazki.end(); ++zwracana) {
                    if (zwracana->pobierzIdentyfikator() == idKsiazki) {
                        for (auto& ksiazka : ksiazki) {
                            if (ksiazka.pobierzIdentyfikator() == idKsiazki) {
                                ksiazka.zwroc();
                                czytelnik.wypozyczoneKsiazki.erase(zwracana);
                                std::cout << "Ksiazka " << ksiazka.pobierzTytul() << " zostala zwrocona.\n";
                                return;
                            }
                        }
                    }
                }

                std::cout << "Ksiazka o podanym ID nie zostala wypozyczona.\n";
                return;
            }
        }
    }

    void zamianaKsiazek(Ksiazka& pierwsza, Ksiazka& druga) {
        Ksiazka temp = pierwsza;
        pierwsza = druga;
        druga = temp;
    }

    void pokazDostepneKsiazki() {
        std::vector<Ksiazka> dostepneKsiazki;

        for (const auto& ksiazka : ksiazki) {
            if (ksiazka.sprawdzDostepnosc()) {
                dostepneKsiazki.push_back(ksiazka);
            }
        }

        for (size_t i = 0; i < dostepneKsiazki.size(); i++) {
            for (size_t j = 0; j < dostepneKsiazki.size() - i - 1; j++) {
                if (dostepneKsiazki[j].pobierzTytul() > dostepneKsiazki[j+1].pobierzTytul()) {
                    zamianaKsiazek(dostepneKsiazki[j], dostepneKsiazki[j + 1]);
                }
            }
        }

        if (dostepneKsiazki.empty()) {
            std::cout << "-> Nie ma obecnie zadnych dostepnych ksiazek\n";
        } else {
            for (const auto& ksiazka : dostepneKsiazki) {
                std::cout << "-> " << ksiazka.pobierzTytul() << " (id: " << ksiazka.pobierzIdentyfikator() << ")" << std::endl;
            }
        }
    }

    void pokazWypozyczoneKsiazki(int idCzytelnika) {
        for (const auto& czytelnik : czytelnicy) {
            if (czytelnik.pobierzIdentyfikator() == idCzytelnika) {
                if (czytelnik.wypozyczoneKsiazki.empty()) {
                    std::cout << "-> Brak\n";
                    return;
                }

                for (const auto& ksiazka : czytelnik.wypozyczoneKsiazki) {
                    std::cout << "-> " << ksiazka.pobierzTytul() << " (id: " << ksiazka.pobierzIdentyfikator() << ")" << std::endl;
                }
                return;
            }
        }
    }

    void zapiszDane() const {
        std::ofstream plikKsiazki("ksiazki.txt");
        for (const auto& ksiazka : ksiazki) {
            ksiazka.zapiszDoPliku(plikKsiazki);
        }
        plikKsiazki.close();

        std::ofstream plikCzytelnicy("czytelnicy.txt");
        for (const auto& czytelnik : czytelnicy) {
            czytelnik.zapiszDoPliku(plikCzytelnicy);
        }
        plikCzytelnicy.close();
    }

    void wczytajDane() {
        ksiazki.clear();
        czytelnicy.clear();

        std::ifstream plikKsiazki("ksiazki.txt");
        if (!plikKsiazki.is_open()) {
            std::cerr << "Blad otwierania pliku z ksiazkami!" << std::endl;
            return;
        }
        while (plikKsiazki.peek() != EOF) {
            ksiazki.push_back(Ksiazka::wczytajZPliku(plikKsiazki));
        }
        plikKsiazki.close();

        std::ifstream plikCzytelnicy("czytelnicy.txt");
        if (!plikCzytelnicy.is_open()) {
            std::cerr << "Blad otwierania pliku z czytelnikami!" << std::endl;
            return;
        }
        std::string linia;
        while (std::getline(plikCzytelnicy, linia)) {
            if (!linia.empty()) {
                czytelnicy.push_back(Czytelnik::wczytajZPliku(linia, ksiazki));
            }
        }
        plikCzytelnicy.close();
    }

    int ileCzytelnikow() {
        return czytelnicy.size();
    }

    std::vector<Ksiazka>& pobierzKsiazki() {
        return ksiazki;
    }

    const std::vector<Ksiazka>& pobierzKsiazki() const {
        return ksiazki;
    }

    const std::vector<Czytelnik>& pobierzCzytelnikow() const {
        return czytelnicy;
    }
};

class Administrator {
public:
    void dodajKsiazke(Biblioteka& biblioteka, int id, const std::string& tytul, const std::string& autor) {
        Ksiazka nowaKsiazka(id, tytul, autor);
        biblioteka.dodajKsiazke(nowaKsiazka);
        std::cout << "Dodano nowa ksiazke: " << tytul << " (id: " << id << ")\n";
    }

    void zmienDostepnoscKsiazki(Biblioteka& biblioteka, int idKsiazki) {
        auto& ksiazki = biblioteka.pobierzKsiazki();
        auto it = std::find_if(ksiazki.begin(), ksiazki.end(), [idKsiazki](const Ksiazka& ksiazka) {
            return ksiazka.pobierzIdentyfikator() == idKsiazki;
        });

        if (it != ksiazki.end()) {
            if (it->sprawdzDostepnosc()) {
                it->ustawDostepnosc(false);
                std::cout << "Ksiazka o ID: " << idKsiazki << " zostala oznaczona jako niedostepna.\n";
            } else
            {
                it->ustawDostepnosc(true);
                std::cout << "Ksiazka o ID: " << idKsiazki << " zostala oznaczona jako dostepna.\n";
            }
        } else {
            std::cout << "Nie znaleziono ksiazki o ID: " << idKsiazki << "\n";
        }
    }

    void pokazStatusKsiazek(const Biblioteka& biblioteka) {
        const auto& ksiazki = biblioteka.pobierzKsiazki();
        for (const auto& ksiazka : ksiazki) {
            std::cout << "ID: " << ksiazka.pobierzIdentyfikator()
                      << ", Tytul: " << ksiazka.pobierzTytul()
                      << ", Autor: " << ksiazka.pobierzAutora()
                      << ", Dostepnosc: " << (ksiazka.sprawdzDostepnosc() ? "Dostepna" : "Niedostepna") << "\n";
        }
    }

    void sprawdzKtoWypozyczylKsiazke(const Biblioteka& biblioteka, int idKsiazki) {
        const auto& czytelnicy = biblioteka.pobierzCzytelnikow();
        for (const auto& czytelnik : czytelnicy) {
            for (const auto& ksiazka : czytelnik.pobierzWypozyczoneKsiazki()) {
                if (ksiazka.pobierzIdentyfikator() == idKsiazki) {
                    std::cout << "Ksiazka o ID: " << idKsiazki << " zostala wypozyczona przez: " << czytelnik.pobierzImie() << ", id: " << czytelnik.pobierzIdentyfikator() << "\n";
                    return;
                }
            }
        }
        std::cout << "Ksiazka o ID: " << idKsiazki << " nie zostala wypozyczona.\n";
    }
};

#endif