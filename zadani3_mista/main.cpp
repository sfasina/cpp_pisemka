#include <iostream>
#include <string>

#include "PlaceFile.h"
#include "Rectangle.h"

// main = "lepidlo": PlaceFile a Rectangle o sobe nevedi, propojuje je az main
int main() {
    // ===== KROK 1: nacteni =====
    PlaceFile file;
    file.loadPlaces("mista.txt");
    std::cout << "Nacteno mist: " << file.getPlaces().size()
              << ", vadnych radku: " << file.getInvalidLines() << std::endl << std::endl;

    // ===== KROK 2: obdelnik od uzivatele =====
    // cin >> cte cisla oddelena mezerou, takze jde zadat "49 14" na jeden radek
    double lat1, lon1, lat2, lon2;
    std::cout << "Roh 1 (sirka delka): ";
    std::cin >> lat1 >> lon1;
    std::cout << "Roh 2 (sirka delka): ";
    std::cin >> lat2 >> lon2;

    // kdyz uzivatel zada pismena, cin selze -> radsi skoncime
    if (!std::cin) {
        std::cerr << "Neplatne souradnice." << std::endl;
        return 1;
    }
    Rectangle rect(lat1, lon1, lat2, lon2);

    // ===== KROK 3 + 4: pocitani a vypis mist uvnitr =====
    int inside = 0;
    int outside = 0;
    std::cout << std::endl << "Mista uvnitr:" << std::endl;
    for (const auto& p : file.getPlaces()) {
        if (rect.contains(p)) {
            ++inside;
            std::cout << "  " << p.name << " (" << p.lat << ", " << p.lon << ")" << std::endl;
        } else {
            ++outside;
        }
    }

    std::cout << std::endl << "Uvnitr: " << inside << ", mimo: " << outside << std::endl;
    return 0;
}
