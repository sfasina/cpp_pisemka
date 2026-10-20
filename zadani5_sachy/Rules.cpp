//
// Created by fasin on 20.10.2026.
//

#include "Rules.h"

#include <cctype>
#include <cstdlib>   // std::abs

bool Rules::isWhite(char piece) {
    return std::isupper(static_cast<unsigned char>(piece));
}

bool Rules::canMove(const Board& board, Position from, Position to,
                    bool whiteTurn, std::string& error) {
    char piece = board.get(from);
    char target = board.get(to);

    // obecne kontroly (plati pro vsechny figurky)
    if (piece == '.') {
        error = "Na tom policku nic neni.";
        return false;
    }
    if (isWhite(piece) != whiteTurn) {
        error = "To neni tvoje figurka.";
        return false;
    }
    if (target != '.' && isWhite(target) == whiteTurn) {
        error = "Nemuzes brat vlastni figurku.";
        return false;
    }

    // pohyb konkretni figurky
    if (!canPieceMove(board, from, to)) {
        error = "Tahle figurka takhle tahnout nemuze.";
        return false;
    }
    return true;
}

bool Rules::canPieceMove(const Board& board, Position from, Position to) {
    char piece = board.get(from);
    bool white = isWhite(piece);

    // o kolik se posouvame: dr = radky, dc = sloupce (adr, adc = absolutni hodnota)
    int dr = to.row - from.row;
    int dc = to.col - from.col;
    int adr = std::abs(dr);
    int adc = std::abs(dc);
    if (adr == 0 && adc == 0) { return false; }   // tah na stejne policko

    // tolower -> 'K' i 'k' se resi stejne
    switch (std::tolower(static_cast<unsigned char>(piece))) {
        case 'k':   // kral: o 1 libovolnym smerem
            return adr <= 1 && adc <= 1;

        case 'n':   // kun: do L (2 + 1), muze preskakovat
            return (adr == 2 && adc == 1) || (adr == 1 && adc == 2);

        case 'r':   // vez: rovne, nesmi preskakovat
            return (dr == 0 || dc == 0) && isPathClear(board, from, to);

        case 'b':   // strelec: sikmo (stejne radku jako sloupcu)
            return adr == adc && isPathClear(board, from, to);

        case 'q':   // dama: vez + strelec
            return (dr == 0 || dc == 0 || adr == adc) && isPathClear(board, from, to);

        case 'p': {   // pesec: { } kvuli promennym uvnitr case
            // bily jde nahoru (row se zmensuje), cerny dolu
            int dir = white ? -1 : 1;
            int startRow = white ? 6 : 1;
            bool targetEmpty = board.get(to) == '.';

            // o 1 dopredu na prazdne
            if (dc == 0 && dr == dir && targetEmpty) { return true; }

            // o 2 dopredu z vychozi rady, obe policka prazdna
            if (dc == 0 && dr == 2 * dir && from.row == startRow && targetEmpty) {
                return isPathClear(board, from, to);
            }

            // brani sikmo o 1 dopredu (vlastni figurku uz vyloucil canMove)
            return adc == 1 && dr == dir && !targetEmpty;
        }

        default:
            return false;
    }
}

// projde policka MEZI from a to (bez nich) a zkontroluje, ze jsou prazdna
bool Rules::isPathClear(const Board& board, Position from, Position to) {
    // krok: -1, 0 nebo +1 v kazdem smeru
    int stepRow = (to.row > from.row) - (to.row < from.row);
    int stepCol = (to.col > from.col) - (to.col < from.col);

    Position p{from.row + stepRow, from.col + stepCol};
    while (p.row != to.row || p.col != to.col) {
        if (board.get(p) != '.') { return false; }
        p.row += stepRow;
        p.col += stepCol;
    }
    return true;
}
