//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_INPUT_H
#define CPP2PRACTISE_INPUT_H

#include <iostream>
#include <sstream>
#include <string>

// sablona (template): jedna funkce pro int, double, ...
// sablony musi byt cele v headeru, compiler potrebuje videt telo pri pouziti
// pta se tak dlouho, dokud uzivatel nezada platne cislo
template <typename T>
T readNumber(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            return T{};   // konec vstupu (Ctrl+Z / Ctrl+D), at se program nezacykli
        }

        std::istringstream ss(line);
        T value;
        char extra;
        // ss >> value se musi povest a za cislem uz nesmi nic zbyt ("12abc" neprojde)
        if (ss >> value && !(ss >> extra)) {
            return value;
        }
        std::cout << "Neplatne cislo, zkus to znovu." << std::endl;
    }
}

#endif //CPP2PRACTISE_INPUT_H
