//
// Created by fasin on 19.10.2026.
//

#ifndef CPP2PRACTISE_MEASUREMENTFILE_H
#define CPP2PRACTISE_MEASUREMENTFILE_H

#include <string>
#include <vector>

#include "Measurement.h"

// prace se souborem - stejny princip jako FileManager ve slovnikove hre
class MeasurementFile {
private:
    std::vector<Measurement> m_measurements;
    int m_invalidLines = 0;

    // pomocna funkce: z jednoho radku naplni "out"; vrati false, kdyz je radek vadny
    static bool parseLine(const std::string& line, Measurement& out);

public:
    bool load(const std::string& filePath);
    static bool save(const std::vector<Measurement>& measurements, const std::string& filePath);

    // vraci referenci -> nekopiruje se cely vektor
    std::vector<Measurement>& getMeasurements() { return m_measurements; }
    int getInvalidLines() const { return m_invalidLines; }
};

#endif //CPP2PRACTISE_MEASUREMENTFILE_H
