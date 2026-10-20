//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_RANGE_H
#define CPP2PRACTISE_RANGE_H

#include "Measurement.h"

// krok 2: rozsah zadany uzivatelem
// konstruktor si sam srovna poradi mezi pres std::min / std::max,
// takze je jedno, jestli uzivatel zada "10 25" nebo "25 10"
class Range {
private:
    double m_minTemp;
    double m_maxTemp;
    int m_minHumidity;
    int m_maxHumidity;

public:
    Range(double temp1, double temp2, int humidity1, int humidity2);

    // const = metoda nemeni objekt, da se volat i na const Range&
    bool contains(const Measurement& m) const;

    double getMinTemp() const { return m_minTemp; }
    double getMaxTemp() const { return m_maxTemp; }
    int getMinHumidity() const { return m_minHumidity; }
    int getMaxHumidity() const { return m_maxHumidity; }
};

#endif //CPP2PRACTISE_RANGE_H
