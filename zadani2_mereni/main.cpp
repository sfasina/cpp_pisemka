#include <iomanip>
#include <iostream>
#include <vector>

#include "Analyzer.h"
#include "Input.h"
#include "MeasurementFile.h"
#include "Range.h"

// krok 4: vypis do sloupcu
// setw plati jen pro NASLEDUJICI vystup, fixed a setprecision plati trvale
void printTable(const std::vector<Measurement>& measurements) {
    std::cout << std::left << std::setw(12) << "Stanice"
              << std::right << std::setw(10) << "Teplota"
              << std::setw(10) << "Vlhkost" << std::endl;
    std::cout << std::string(32, '-') << std::endl;

    std::cout << std::fixed << std::setprecision(1);
    for (const auto& m : measurements) {
        std::cout << std::left << std::setw(12) << m.station
                  << std::right << std::setw(10) << m.temp
                  << std::setw(10) << m.humidity << std::endl;
    }
}

int main() {
    // krok 1: nacteni souboru
    MeasurementFile file;
    if (!file.load("mereni.txt")) {
        return 1;
    }
    std::vector<Measurement>& measurements = file.getMeasurements();
    std::cout << "Nacteno mereni: " << measurements.size()
              << ", vadnych radku: " << file.getInvalidLines() << std::endl << std::endl;

    // krok 2: meze od uzivatele, poradi je jedno (Range si je srovna)
    double t1 = readNumber<double>("Prvni mez teploty: ");
    double t2 = readNumber<double>("Druha mez teploty: ");
    int h1 = readNumber<int>("Prvni mez vlhkosti: ");
    int h2 = readNumber<int>("Druha mez vlhkosti: ");
    Range range(t1, t2, h1, h2);

    // krok 3
    Analyzer analyzer(measurements, range);
    std::cout << std::endl << "Uvnitr rozsahu: " << analyzer.countInside()
              << ", mimo rozsah: " << analyzer.countOutside() << std::endl << std::endl;

    // krok 4
    std::vector<Measurement> inside = analyzer.sortedInside();
    printTable(inside);

    // krok 5
    double average;
    if (Analyzer::averageTemp(inside, average)) {
        std::cout << std::endl << "Prumerna teplota uvnitr: " << average << std::endl;
    } else {
        std::cout << std::endl << "V rozsahu neni zadne mereni." << std::endl;
    }

    Measurement humid;
    if (Analyzer::mostHumid(inside, humid)) {
        std::cout << "Nejvlhci mereni: " << humid.station << " (" << humid.humidity << " %)" << std::endl;
    }

    // krok 6 (bonus): az ted menime puvodni vektor, predtim ho Analyzer jen cetl
    size_t removed = Analyzer::removeOutside(measurements, range);
    std::cout << std::endl << "Odstraneno mereni mimo rozsah: " << removed << std::endl;
    if (MeasurementFile::save(measurements, "vyber.txt")) {
        std::cout << "Ulozeno do vyber.txt (" << measurements.size() << " mereni)" << std::endl;
    }

    return 0;
}
