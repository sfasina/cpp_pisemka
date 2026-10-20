//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_RULES_H
#define CPP2PRACTISE_RULES_H

#include <string>

#include "Board.h"
#include "Position.h"

// trida na pravidlo: smi figurka tahnout z "from" na "to"?
// jen cte Board, nic nemeni; vsechno static -> vola se Rules::canMove(...)
// zjednoduseno: bez sachu, rosady a brani mimochodem; hra konci sebranim krale
class Rules {
public:
    static bool isWhite(char piece);

    // vrati false a do "error" napise duvod, kdyz tah neni platny
    static bool canMove(const Board& board, Position from, Position to,
                        bool whiteTurn, std::string& error);

private:
    static bool canPieceMove(const Board& board, Position from, Position to);
    static bool isPathClear(const Board& board, Position from, Position to);
};

#endif //CPP2PRACTISE_RULES_H
