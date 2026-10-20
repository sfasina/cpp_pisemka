//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_PLACE_H
#define CPP2PRACTISE_PLACE_H

#include <string>

// jeden radek souboru = jedno misto, napr. "Brno;49.20;16.61"
// struct = vsechno public, jen "balicek dat" bez logiky
//
// sirka (latitude)  = sever/jih, -90 az 90   -> na mape osa Y (nahoru/dolu)
// delka (longitude) = vychod/zapad, -180 az 180 -> na mape osa X (doleva/doprava)
struct Place {
    std::string name;
    double lat;   // zemepisna sirka
    double lon;   // zemepisna delka
};

#endif //CPP2PRACTISE_PLACE_H
