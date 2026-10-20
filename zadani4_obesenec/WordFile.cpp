//
// Created by fasin on 20.10.2026.
//

#include "WordFile.h"

#include <fstream>
#include <iostream>

// tady se radek NEMUSI delit - jeden radek = jedno slovo
// (kdyby byl radek "slovo;napoveda", pridal by se istringstream + getline(..., ';'))
void WordFile::loadWords(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // soubory z Windows maji na konci radku '\r'
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) { continue; }   // prazdny radek preskocime

        m_words.push_back(line);
    }
}
