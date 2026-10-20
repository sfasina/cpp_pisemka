//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_BOARD_H
#define CPP2PRACTISE_BOARD_H

#include <array>
#include <string>

#include "Position.h"

// trida na soubor + data: sachovnice jako 2D pole znaku
// '.' = prazdne, velka pismena = bily (K Q R B N P), mala = cerny (k q r b n p)
// o pravidlech tahu nic nevi - to resi Rules
class Board {
public:
    // static constexpr = konstanta spolecna pro celou tridu, zna ji uz compiler
    static constexpr int SIZE = 8;

private:
    // std::array<typ, velikost> = pole s pevnou velikosti
    // pole poli = 2D pole: m_cells[radek][sloupec]
    std::array<std::array<char, SIZE>, SIZE> m_cells;

public:
    Board();

    // nacte 8 radku po 8 znacich; vrati false pri spatnem formatu
    bool load(const std::string& filePath);
    void print() const;

    char get(Position p) const { return m_cells[p.row][p.col]; }
    void set(Position p, char piece) { m_cells[p.row][p.col] = piece; }
};

#endif //CPP2PRACTISE_BOARD_H
