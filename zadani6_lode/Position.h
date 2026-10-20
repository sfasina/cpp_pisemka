//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_POSITION_H
#define CPP2PRACTISE_POSITION_H

#include <array>
#include <string>

// velikost hraci plochy - spolecna pro vsechny tridy
constexpr int SIZE = 8;

// using = nove jmeno pro dlouhy typ, at se nemusi vypisovat porad dokola
// Grid = 2D pole znaku 8x8, pristup grid[radek][sloupec]
using Grid = std::array<std::array<char, SIZE>, SIZE>;

// policko jako indexy do pole: row 0 = radek 1 (nahore), col 0 = sloupec a
struct Position {
    int row;
    int col;
};

// "b4" -> row 3, col 1; vrati false, kdyz text neni platne policko
// inline = funkce s telem v headeru (jinak "multiple definition" pri vic includech)
inline bool parsePosition(const std::string& text, Position& out) {
    if (text.size() != 2) { return false; }

    char letter = text[0];   // 'a'..'h'
    char digit = text[1];    // '1'..'8'
    if (letter < 'a' || letter > 'a' + SIZE - 1 || digit < '1' || digit > '0' + SIZE) {
        return false;
    }

    out.col = letter - 'a';   // 'a' -> 0, 'b' -> 1
    out.row = digit - '1';    // '1' -> 0, '4' -> 3
    return true;
}

#endif //CPP2PRACTISE_POSITION_H
