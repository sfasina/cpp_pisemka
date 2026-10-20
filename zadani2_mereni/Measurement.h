//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_MEASUREMENT_H
#define CPP2PRACTISE_MEASUREMENT_H

#include <string>

// krok 1: jeden radek souboru = jedno mereni
// struct = vsechno public, idealni pro "balicek dat" bez logiky
struct Measurement {
    std::string station;
    double temp;
    int humidity;
};

#endif //CPP2PRACTISE_MEASUREMENT_H
