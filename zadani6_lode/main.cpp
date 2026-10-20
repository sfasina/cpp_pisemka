#include <iostream>
#include <string>

#include "Battle.h"
#include "Ocean.h"
#include "Position.h"

// cislo v rozsahu min..max, pri spatnem vstupu se pta znovu (stejne jako u obesence)
int readChoice(const std::string& prompt, int min, int max) {
    std::string input;
    while (true) {
        std::cout << prompt << " (" << min << " az " << max << "): ";
        if (!std::getline(std::cin, input)) { return 0; }
        try {
            int choice = std::stoi(input);
            if (choice >= min && choice <= max) { return choice; }
        } catch (const std::exception&) {}
        std::cout << "Neplatna volba." << std::endl;
    }
}

// main = lepidlo: Ocean nacte lode, Battle hraje, main je propoji
int main() {
    Ocean ocean;
    if (!ocean.load("lode.txt")) {
        return 1;
    }

    std::cout << "Lodi na mori: " << ocean.getShipSizes().size() << std::endl;
    int shots = readChoice("Kolik mas strel", 1, SIZE * SIZE);
    if (shots == 0) { return 0; }

    // Battle dostane jen data, ne cely Ocean
    Battle battle(ocean.getCells(), ocean.getShipSizes(), shots);

    // hraje se, dokud zbyvaji strely A neni vsechno potopene
    while (battle.shotsLeft() > 0 && !battle.allSunk()) {
        battle.print(false);
        std::cout << "Strely: " << battle.shotsLeft()
                  << ", potopeno: " << battle.sunkCount() << "/" << battle.shipCount() << std::endl;
        std::cout << "Policko (napr. b4, quit = konec): ";

        std::string input;
        if (!std::getline(std::cin, input) || input == "quit") {
            break;
        }

        Position p{};
        if (!parsePosition(input, p)) {
            std::cout << "Zadej policko jako b4 (a-h, 1-8)." << std::endl;
            continue;
        }

        char ship = '.';
        // switch nad enum class: kazda moznost ma vlastni case
        switch (battle.fire(p, ship)) {
            case ShotResult::Miss:
                std::cout << "Voda." << std::endl;
                break;
            case ShotResult::Hit:
                std::cout << "Zasah!" << std::endl;
                break;
            case ShotResult::Sunk:
                std::cout << "Zasah! Lod " << ship << " je potopena!" << std::endl;
                break;
            case ShotResult::AlreadyShot:
                std::cout << "Sem uz jsi strilel, strela se nepocita." << std::endl;
                break;
        }
    }

    // konec: ukazeme celou plochu i s netrefenymi lodemi
    battle.print(true);
    if (battle.allSunk()) {
        std::cout << "Vyhral jsi! Zbylo strel: " << battle.shotsLeft() << std::endl;
    } else {
        std::cout << "Konec. Potopeno " << battle.sunkCount() << " z " << battle.shipCount() << " lodi." << std::endl;
    }
    return 0;
}
