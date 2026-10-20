//
// Created by fasin on 20.10.2026.
//

#include "Ocean.h"

#include <fstream>
#include <iostream>

Ocean::Ocean() {
    for (auto& row : m_cells) {   // auto& -> menime original radek, ne kopii
        row.fill('.');
    }
}

bool Ocean::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) { continue; }

        if (row >= SIZE || line.size() != SIZE) {
            std::cerr << "Spatny format na radku " << row + 1 << std::endl;
            return false;
        }

        for (int col = 0; col < SIZE; ++col) {
            char c = line[col];
            if (c != '.' && (c < 'A' || c > 'Z')) {
                std::cerr << "Neznamy znak '" << c << "' na radku " << row + 1 << std::endl;
                return false;
            }
            m_cells[row][col] = c;

            // kazde policko lodi pricte 1 k jeji velikosti
            // m[klic]: kdyz klic jeste neni, vytvori se s 0 -> pak ++
            if (c != '.') {
                ++m_shipSizes[c];
            }
        }
        ++row;
    }

    if (row != SIZE) {
        std::cerr << "Plocha musi mit " << SIZE << " radku, ma " << row << std::endl;
        return false;
    }
    if (m_shipSizes.empty()) {
        std::cerr << "V souboru neni zadna lod." << std::endl;
        return false;
    }
    return true;
}
