//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_PLACEFILE_H
#define CPP2PRACTISE_PLACEFILE_H

#include <string>
#include <vector>

#include "Place.h"

// stejny princip jako FileManager ve slovnikove hre:
// stara se JEN o soubor, o obdelniku nic nevi
class PlaceFile {
private:
    std::vector<Place> m_places;
    int m_invalidLines = 0;   // kolik radku se nepodarilo precist

    // z jednoho radku naplni "out"; vrati false, kdyz je radek vadny
    // static = nepotrebuje zadne cleny objektu, jen dostane radek
    static bool parseLine(const std::string& line, Place& out);

public:
    void loadPlaces(const std::string& filePath);

    const std::vector<Place>& getPlaces() const { return m_places; }
    int getInvalidLines() const { return m_invalidLines; }
};

#endif //CPP2PRACTISE_PLACEFILE_H
