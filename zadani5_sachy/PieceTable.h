//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_PIECETABLE_H
#define CPP2PRACTISE_PIECETABLE_H

#include <map>
#include <string>

// co o figurce vime: jmeno a hodnotu (kolik bodu za jeji sebrani)
struct PieceInfo {
    std::string name;
    int value;
};

// tabulka figurek nactena ze souboru "K;kral;100"
// std::map<klic, hodnota> = slovnik: podle klice ('K') najde hodnotu (PieceInfo)
// klic je vzdy VELKE pismeno -> 'k' (cerny kral) i 'K' (bily kral) najdou stejny zaznam
class PieceTable {
private:
    std::map<char, PieceInfo> m_pieces;

public:
    bool load(const std::string& filePath);

    // vrati "?" / 0, kdyz figurka v tabulce neni
    std::string name(char piece) const;
    int value(char piece) const;
};

#endif //CPP2PRACTISE_PIECETABLE_H
