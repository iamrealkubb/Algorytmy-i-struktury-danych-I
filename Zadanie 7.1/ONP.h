// ONP.h

#ifndef ONP_H
#define ONP_H

#include <vector>
#include <stack>
#include <string>
#include <stdexcept>

int rpn(const std::vector<std::string>& input) {
    std::stack<int> stos; // Tworze stos

    for (const auto &w : input) {
        if (isdigit(w[0]) || (w[0] == '+' && w.size() > 1) || (w[0] == '-' && w.size() > 1)) { // Jesli jest liczba
            stos.push(std::stoi(w)); // To klade ja na stos
        } else { // Jesli jest operatorem
            if (stos.size() < 2) { // Jesli brakuje liczb do przeprowadzenia operacji
                throw std::invalid_argument("Za malo argumentow;");
            }
            int a = stos.top(); // Biore dwa argumenty ze stosu
            stos.pop();
            int b = stos.top();
            stos.pop();

            if (w == "+") { // Wykonuje obliczenia w zaleznosci od operacji
                stos.push(b + a);
            } else if (w == "-") {
                stos.push(b - a);
            } else if (w == "*") {
                stos.push(b * a);
            } else if (w == "/") {
                if (a == 0) { // Jesli ktos probuje dzielic przez zero
                    throw std::domain_error("Nie wolno dzielic przez zero");
                }
                stos.push(b / a);
            } else { // Jesli podano nieznany operator
                throw std::invalid_argument("Podano nieznany operator");
            }
        }
    }
    if (stos.size() != 1) { // Jesli podano niepoprawny input
        throw std::invalid_argument("Podano bledne wyrazenie");
    }
    return stos.top();
}

#endif