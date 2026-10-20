//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_RECTANGLE_H
#define CPP2PRACTISE_RECTANGLE_H

#include "Place.h"

// obdelnik zadany dvema rohy (sirka1, delka1) a (sirka2, delka2)
// rohy muzou byt zadane v libovolnem poradi -> konstruktor si je srovna,
// takze uvnitr vzdy plati m_minLat <= m_maxLat a m_minLon <= m_maxLon
//
//   maxLat +-----------+
//          |           |
//          |   Praha   |
//   minLat +-----------+
//        minLon      maxLon
class Rectangle {
private:
    double m_minLat;
    double m_maxLat;
    double m_minLon;
    double m_maxLon;

public:
    Rectangle(double lat1, double lon1, double lat2, double lon2);

    // lezi misto uvnitr obdelniku? (vcetne hrany)
    bool contains(const Place& p) const;
};

#endif //CPP2PRACTISE_RECTANGLE_H
