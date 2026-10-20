//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_BATTLE_H
#define CPP2PRACTISE_BATTLE_H

#include <map>

#include "Position.h"

// vysledek jedne strely
// enum class = vycet pojmenovanych moznosti, pouziti: ShotResult::Hit
enum class ShotResult { Miss, Hit, Sunk, AlreadyShot };

// trida na pravidlo: strelba, zasahy, potopeni
// dostane jen DATA (pole a mapu), tridu Ocean nezna -> spojuje je main
class Battle {
private:
    Grid m_ships;                     // kde jsou lode (kopie z Ocean)
    Grid m_shots;                     // co hrac vidi: '.' nestrileno, 'o' voda, 'X' zasah
    std::map<char, int> m_remaining;  // lod -> kolik policek jeste NENI zasazeno
    int m_shotsLeft;

public:
    Battle(const Grid& ships, const std::map<char, int>& shipSizes, int shots);

    // vystreli na policko; do "ship" ulozi pismeno zasazene lodi
    ShotResult fire(Position p, char& ship);

    bool allSunk() const;
    int sunkCount() const;
    int shipCount() const { return static_cast<int>(m_remaining.size()); }
    int shotsLeft() const { return m_shotsLeft; }

    // reveal = true -> ukaze i lode, ktere hrac netrefil (na konci hry)
    void print(bool reveal) const;
};

#endif //CPP2PRACTISE_BATTLE_H
