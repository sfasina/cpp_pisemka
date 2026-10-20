//
// Created by fasin on 19.10.2026.
//

#include "Rectangle.h"

#include <algorithm>   // std::min, std::max

// ===== KROK 2: obdelnik =====
// stejne jako Range v zadani2_mereni
// inicializacni seznam rovnou ulozi mensi/vetsi hodnotu -> poradi rohu je jedno
Rectangle::Rectangle(double lat1, double lon1, double lat2, double lon2)
    : m_minLat(std::min(lat1, lat2)),
      m_maxLat(std::max(lat1, lat2)),
      m_minLon(std::min(lon1, lon2)),
      m_maxLon(std::max(lon1, lon2)) {
}

// uvnitr = sirka je mezi mezemi A ZAROVEN delka je mezi mezemi (vcetne hrany)
bool Rectangle::contains(const Place& p) const {
    return p.lat >= m_minLat && p.lat <= m_maxLat
        && p.lon >= m_minLon && p.lon <= m_maxLon;
}
