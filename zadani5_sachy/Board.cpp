//
// Created by fasin on 20.10.2026.
//

#include "Board.h"

#include <fstream>
#include <iostream>

// na zacatku vsechna policka prazdna
Board::Board() {
    for (auto& row : m_cells) {   // auto& = reference, jinak bychom menili kopii radku
        row.fill('.');            // fill = nastavi vsechny prvky pole na stejnou hodnotu
    }
}

bool Board::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }

    // povolene znaky na policku; find vrati npos, kdyz tam znak neni
    const std::string allowed = ".KQRBNPkqrbnp";

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) { continue; }

        // vic nez 8 radku nebo spatna delka -> spatny soubor
        if (row >= SIZE || line.size() != SIZE) {
            std::cerr << "Spatny format sachovnice na radku " << row + 1 << std::endl;
            return false;
        }

        for (int col = 0; col < SIZE; ++col) {
            if (allowed.find(line[col]) == std::string::npos) {
                std::cerr << "Neznamy znak '" << line[col] << "' na radku " << row + 1 << std::endl;
                return false;
            }
            m_cells[row][col] = line[col];
        }
        ++row;
    }

    if (row != SIZE) {
        std::cerr << "Sachovnice musi mit " << SIZE << " radku, ma " << row << std::endl;
        return false;
    }
    return true;
}

// vypise sachovnici s oznacenim sloupcu a rad
//   a b c d e f g h
// 8 r n b q k b n r 8
void Board::print() const {
    std::cout << std::endl << "  a b c d e f g h" << std::endl;
    for (int row = 0; row < SIZE; ++row) {
        int rank = SIZE - row;   // row 0 -> rada 8
        std::cout << rank << ' ';
        for (int col = 0; col < SIZE; ++col) {
            std::cout << m_cells[row][col] << ' ';
        }
        std::cout << rank << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl << std::endl;
}
