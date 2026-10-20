//
// Created by fasin on 19.10.2026.
//

#include "Analyzer.h"

#include <algorithm>
#include <iterator>
#include <numeric>

Analyzer::Analyzer(const std::vector<Measurement>& measurements, const Range& range)
    : m_measurements(measurements), m_range(range) {
}

long Analyzer::countInside() const {
    // lambda [&range] zachytava rozsah referenci, aby ho mohla pouzit uvnitr
    // (clen tridy nejde zachytit primo jmenem, proto si ho ulozime do lokalni promenne)
    const Range& range = m_range;
    return std::count_if(m_measurements.begin(), m_measurements.end(),
                         [&range](const Measurement& m) { return range.contains(m); });
}

long Analyzer::countOutside() const {
    // stejny count_if, jen s negaci podminky
    // (slo by i: return m_measurements.size() - countInside();)
    const Range& range = m_range;
    return std::count_if(m_measurements.begin(), m_measurements.end(),
                         [&range](const Measurement& m) { return !range.contains(m); });
}

std::vector<Measurement> Analyzer::sortedInside() const {
    // 1) vyber jen ty uvnitr -> copy_if + back_inserter (vektor se sam zvetsuje)
    std::vector<Measurement> inside;
    const Range& range = m_range;
    std::copy_if(m_measurements.begin(), m_measurements.end(), std::back_inserter(inside),
                 [&range](const Measurement& m) { return range.contains(m); });

    // 2) serad od nejteplejsiho: komparator vraci true, kdyz "a" ma byt pred "b"
    std::sort(inside.begin(), inside.end(),
              [](const Measurement& a, const Measurement& b) { return a.temp > b.temp; });
    // C++20 alternativa s projekci: std::ranges::sort(inside, std::greater{}, &Measurement::temp);

    return inside;
}

bool Analyzer::averageTemp(const std::vector<Measurement>& measurements, double& result) {
    if (measurements.empty()) { return false; }

    // pocatecni hodnota MUSI byt 0.0 (double), s 0 by se scitalo v int a ztratila by se desetinna mista
    double sum = std::accumulate(measurements.begin(), measurements.end(), 0.0,
                                 [](double acc, const Measurement& m) { return acc + m.temp; });
    result = sum / measurements.size();
    return true;
}

bool Analyzer::mostHumid(const std::vector<Measurement>& measurements, Measurement& result) {
    if (measurements.empty()) { return false; }

    // projekce = "porovnavej podle tohoto clenu"; {} = vychozi porovnani (std::less)
    auto it = std::ranges::max_element(measurements, {}, &Measurement::humidity);
    // klasicka verze bez projekce:
    // auto it = std::max_element(measurements.begin(), measurements.end(),
    //     [](const Measurement& a, const Measurement& b) { return a.humidity < b.humidity; });

    result = *it;   // max_element vraci iterator, hodnotu ziskame dereferenci
    return true;
}

size_t Analyzer::removeOutside(std::vector<Measurement>& measurements, const Range& range) {
    // C++20: smaze vsechny prvky, pro ktere lambda vrati true, a vrati jejich pocet
    // (stara verze: v.erase(std::remove_if(v.begin(), v.end(), lambda), v.end());)
    return std::erase_if(measurements, [&range](const Measurement& m) { return !range.contains(m); });
}
