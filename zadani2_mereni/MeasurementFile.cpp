//
// Created by fasin on 19.10.2026.
//

#include "MeasurementFile.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

bool MeasurementFile::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;   // bez return by se pokracovalo se zavrenym souborem
    }

    std::string line;
    while (std::getline(file, line)) {
        // soubor z Windows muze mit na konci radku '\r'
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) { continue; }   // prazdny radek neni chyba, jen ho preskocime

        Measurement m;
        if (parseLine(line, m)) {
            m_measurements.push_back(m);
        } else {
            ++m_invalidLines;
        }
    }
    return true;
}

bool MeasurementFile::parseLine(const std::string& line, Measurement& out) {
    std::istringstream ss(line);
    std::string station, tempStr, humidityStr, rest;

    // getline(..., ';') cte do stredniku; posledni pole cte do konce radku
    if (!std::getline(ss, station, ';') ||
        !std::getline(ss, tempStr, ';') ||
        !std::getline(ss, humidityStr, ';')) {
        return false;   // malo poli, napr. "Plzen;22.1"
    }
    if (std::getline(ss, rest)) {
        return false;   // neco navic, napr. "Zlin;23.4;55;navic"
    }
    if (station.empty()) {
        return false;
    }

    try {
        // pos = kolik znaku stod/stoi skutecne precetly
        // bez kontroly by "21,5" proslo jako 21 a "50abc" jako 50
        size_t pos = 0;
        double temp = std::stod(tempStr, &pos);
        if (pos != tempStr.size()) { return false; }

        int humidity = std::stoi(humidityStr, &pos);
        if (pos != humidityStr.size()) { return false; }

        out = Measurement{station, temp, humidity};
        return true;
    } catch (const std::exception&) {
        // std::invalid_argument ("abc") i std::out_of_range (moc velke cislo)
        return false;
    }
}

bool MeasurementFile::save(const std::vector<Measurement>& measurements, const std::string& filePath) {
    std::ofstream file(filePath);   // bez std::ios::app soubor prepise
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return false;
    }

    // ukladame ve stejnem formatu, v jakem jsme nacitali
    file << std::fixed << std::setprecision(1);
    for (const auto& m : measurements) {
        file << m.station << ';' << m.temp << ';' << m.humidity << '\n';
    }
    return true;
}
