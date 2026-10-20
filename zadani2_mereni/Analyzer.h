//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_ANALYZER_H
#define CPP2PRACTISE_ANALYZER_H

#include <vector>

#include "Measurement.h"
#include "Range.h"

// vsechny vypocty nad merenimi (kroky 3, 4, 5, 6)
// trida si drzi jen referenci na data a rozsah, nic nekopiruje
class Analyzer {
private:
    const std::vector<Measurement>& m_measurements;
    const Range& m_range;

public:
    Analyzer(const std::vector<Measurement>& measurements, const Range& range);

    // krok 3
    long countInside() const;
    long countOutside() const;

    // krok 4: kopie mereni uvnitr rozsahu, serazena od nejteplejsiho
    std::vector<Measurement> sortedInside() const;

    // krok 5: pri prazdnem vstupu by se delilo nulou / max_element vratil end(),
    // proto vraci bool a vysledek pres referenci
    static bool averageTemp(const std::vector<Measurement>& measurements, double& result);
    static bool mostHumid(const std::vector<Measurement>& measurements, Measurement& result);

    // krok 6: vraci, kolik mereni se smazalo
    static size_t removeOutside(std::vector<Measurement>& measurements, const Range& range);
};

#endif //CPP2PRACTISE_ANALYZER_H
