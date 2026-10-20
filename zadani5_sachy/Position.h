//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_POSITION_H
#define CPP2PRACTISE_POSITION_H

#include <string>

// policko na sachovnici jako indexy do pole
// row 0 = rada 8 (nahore, cerny), row 7 = rada 1 (dole, bily)
// col 0 = sloupec a, col 7 = sloupec h
struct Position {
    int row;
    int col;
};

// "e2" -> row 6, col 4; vrati false, kdyz text neni platne policko
// inline = funkce s telem v headeru, jinak by linker hlasil "multiple definition"
inline bool parsePosition(const std::string& text, Position& out) {
    if (text.size() != 2) { return false; }

    char file = text[0];   // pismeno sloupce 'a'..'h'
    char rank = text[1];   // cislo rady '1'..'8'
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') { return false; }

    // znak - 'a' = poradi pismena: 'a' -> 0, 'e' -> 4
    out.col = file - 'a';
    // rada 8 je v poli nahore (row 0), proto '8' - rank: '8' -> 0, '1' -> 7
    out.row = '8' - rank;
    return true;
}

#endif //CPP2PRACTISE_POSITION_H
