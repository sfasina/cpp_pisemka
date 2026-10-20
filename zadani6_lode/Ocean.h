//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_OCEAN_H
#define CPP2PRACTISE_OCEAN_H

#include <map>
#include <string>

#include "Position.h"

// trida na soubor: nacte rozmisteni lodi
// '.' = voda, pismeno A-Z = cast lodi (stejne pismeno = stejna lod)
// o strelbe nic nevi - to resi Battle
class Ocean {
private:
    Grid m_cells;                      // pole: kde lezi lode
    std::map<char, int> m_shipSizes;   // mapa: pismeno lodi -> kolik ma policek

public:
    Ocean();

    // 8 radku po 8 znacich; vrati false pri spatnem formatu
    bool load(const std::string& filePath);

    const Grid& getCells() const { return m_cells; }
    const std::map<char, int>& getShipSizes() const { return m_shipSizes; }
};

#endif //CPP2PRACTISE_OCEAN_H
