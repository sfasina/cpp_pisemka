//
// Created by fasin on 19.10.2026.
//

#include "PlaceFile.h"

#include <fstream>
#include <iostream>
#include <sstream>

// ===== KROK 1a: nacteni souboru =====
// skoro stejne jako FileManager::loadWords ve slovnikove hre
void PlaceFile::loadPlaces(const std::string& filePath) {
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
        if (line.empty()) { continue; }   // prazdny radek neni chyba

        Place p;
        if (parseLine(line, p)) {
            m_places.push_back(p);
        } else {
            ++m_invalidLines;
        }
    }
}

// ===== KROK 1b: rozdeleni jednoho radku =====
// "Brno;49.20;16.61"  ->  name = "Brno", lat = 49.20, lon = 16.61
bool PlaceFile::parseLine(const std::string& line, Place& out) {
    std::istringstream ss(line);
    std::string name, latStr, lonStr;

    // getline(..., ';') cte do stredniku, posledni getline cte zbytek radku
    // kdyz nektery selze, radek ma malo casti (napr. "Zlin;49.23")
    if (!std::getline(ss, name, ';') ||
        !std::getline(ss, latStr, ';') ||
        !std::getline(ss, lonStr)) {
        return false;
    }

    // stod pri textu ("sever") vyhodi vyjimku -> catch -> vadny radek
    try {
        // pos = kolik znaku stod precetl; bez kontroly by "49,40" proslo jako 49
        // (na pisemce klidne vynech, kdyz na to neni cas)
        size_t pos = 0;
        double lat = std::stod(latStr, &pos);
        if (pos != latStr.size()) { return false; }

        double lon = std::stod(lonStr, &pos);
        if (pos != lonStr.size()) { return false; }

        out = Place{name, lat, lon};
        return true;
    } catch (const std::exception&) {
        return false;
    }
}
