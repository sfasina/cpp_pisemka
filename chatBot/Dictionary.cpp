//
//  Dictionary.cpp
//  chatBot
//
//  Created by Štěpán Fašina on 29.09.2026.
//

#include "Dictionary.hpp"
#include <fstream>
#include <iostream>
#include <regex>

const std::string Dictionary::FALLBACK = "Nerozumím, zkuste znova";

Dictionary::Dictionary(const std::string& fileName) {
    std::ifstream file;
    file.open(fileName);
    if (!file) {
        std::cerr << "Soubor nefuguje " << fileName << std::endl;
        return;
    }

    add_to_entries(file);
}

std::string Dictionary::find_response(const std::string& query) const {
    for (const auto& entry : entries) {
        std::regex pattern("(^|[\\s.,!?;:\"])" + entry.first + "($|[\\s.,!?;:\"])",
                           std::regex::icase);
        if (std::regex_search(query, pattern)) {
            return entry.second;
        }
    }
    return FALLBACK;
}

void Dictionary::add_to_entries(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        size_t separator = line.find(' ');
        entries.push_back({line.substr(0, separator), line.substr(separator + 1)});
    }
}