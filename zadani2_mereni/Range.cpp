//
// Created by fasin on 19.10.2026.
//

#include "Range.h"

#include <algorithm>

// inicializacni seznam (: m_x(...)) nastavi cleny jeste pred telem konstruktoru
Range::Range(double temp1, double temp2, int humidity1, int humidity2)
    : m_minTemp(std::min(temp1, temp2)),
      m_maxTemp(std::max(temp1, temp2)),
      m_minHumidity(std::min(humidity1, humidity2)),
      m_maxHumidity(std::max(humidity1, humidity2)) {
}

// "uvnitr rozsahu" = obe hodnoty vcetne krajnich mezi (>= a <=)
bool Range::contains(const Measurement& m) const {
    return m.temp >= m_minTemp && m.temp <= m_maxTemp
        && m.humidity >= m_minHumidity && m.humidity <= m_maxHumidity;
}
