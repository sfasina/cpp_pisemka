//
// Created by fasin on 20.10.2026.
//

#include "Battle.h"

#include <algorithm>
#include <iostream>

// m_remaining zacina jako kopie velikosti lodi: lod A ma 4 policka -> zbyva 4
Battle::Battle(const Grid& ships, const std::map<char, int>& shipSizes, int shots)
    : m_ships(ships), m_remaining(shipSizes), m_shotsLeft(shots) {
    for (auto& row : m_shots) {
        row.fill('.');
    }
}

ShotResult Battle::fire(Position p, char& ship) {
    // uz sem strilel -> nic se nemeni, strela se nepocita
    if (m_shots[p.row][p.col] != '.') {
        return ShotResult::AlreadyShot;
    }

    --m_shotsLeft;
    ship = m_ships[p.row][p.col];

    if (ship == '.') {
        m_shots[p.row][p.col] = 'o';
        return ShotResult::Miss;
    }

    m_shots[p.row][p.col] = 'X';
    --m_remaining[ship];   // lodi ubude jedno nezasazene policko

    if (m_remaining[ship] == 0) {
        return ShotResult::Sunk;
    }
    return ShotResult::Hit;
}

// vsechny lode potopene = u kazde zbyva 0 policek
// all_of: true, kdyz lambda plati pro VSECHNY prvky
// prvek mapy je pair: .first = klic (pismeno), .second = hodnota (zbyva)
bool Battle::allSunk() const {
    return std::all_of(m_remaining.begin(), m_remaining.end(),
                       [](const auto& entry) { return entry.second == 0; });
}

int Battle::sunkCount() const {
    return std::count_if(m_remaining.begin(), m_remaining.end(),
                         [](const auto& entry) { return entry.second == 0; });
}

//   a b c d e f g h
// 1 X X o . . . . .
void Battle::print(bool reveal) const {
    std::cout << std::endl << "  ";
    for (int col = 0; col < SIZE; ++col) {
        std::cout << static_cast<char>('a' + col) << ' ';   // 'a' + 1 = 'b'
    }
    std::cout << std::endl;

    for (int row = 0; row < SIZE; ++row) {
        std::cout << row + 1 << ' ';
        for (int col = 0; col < SIZE; ++col) {
            char c = m_shots[row][col];
            // na konci ukazeme netrefene lode jejich pismenem
            if (reveal && c == '.' && m_ships[row][col] != '.') {
                c = m_ships[row][col];
            }
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
