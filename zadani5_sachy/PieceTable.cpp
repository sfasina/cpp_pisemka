//
// Created by fasin on 20.10.2026.
//

#include "PieceTable.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

// stejny vzor nacitani jako v ostatnich zadanich: getline + istringstream + stoi v try
bool PieceTable::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) { continue; }

        std::istringstream ss(line);
        std::string symbol, name, valueStr;
        if (!std::getline(ss, symbol, ';') ||
            !std::getline(ss, name, ';') ||
            !std::getline(ss, valueStr) ||
            symbol.size() != 1) {   // klic musi byt jeden znak
            continue;               // vadny radek preskocime
        }

        try {
            char key = std::toupper(static_cast<unsigned char>(symbol[0]));
            // m[klic] = hodnota: kdyz klic neexistuje, vytvori ho; kdyz ano, prepise
            m_pieces[key] = PieceInfo{name, std::stoi(valueStr)};
        } catch (const std::exception&) {
            // "abc" misto cisla -> radek preskocime
        }
    }
    return !m_pieces.empty();
}

std::string PieceTable::name(char piece) const {
    char key = std::toupper(static_cast<unsigned char>(piece));

    // find vrati iterator; end() = nenalezeno
    // (m_pieces[key] tady nejde: v const metode, a navic by chybejici klic VYTVORIL)
    auto it = m_pieces.find(key);
    if (it == m_pieces.end()) { return "?"; }

    // it->first = klic, it->second = hodnota (PieceInfo)
    return it->second.name;
}

int PieceTable::value(char piece) const {
    char key = std::toupper(static_cast<unsigned char>(piece));
    auto it = m_pieces.find(key);
    return it == m_pieces.end() ? 0 : it->second.value;
}
