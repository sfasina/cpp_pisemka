#include <iostream>
#include <string>

#include "Hangman.h"
#include "WordFile.h"

// nacte cislo od min do max; pri spatnem vstupu se pta znovu
// getline + stoi (ne cin >>), protoze pismena v Hangman se ctou taky pres getline
// -> nemichame cin >> a getline, takze neni potreba cin.ignore()
int readChoice(int min, int max) {
    std::string input;
    while (true) {
        std::cout << "Vyber cislo " << min << " az " << max << ": ";
        if (!std::getline(std::cin, input)) { return 0; }   // konec vstupu

        try {
            int choice = std::stoi(input);
            if (choice >= min && choice <= max) {
                return choice;
            }
        } catch (const std::exception&) {
            // "abc" -> stoi vyhodi vyjimku -> zeptame se znovu
        }
        std::cout << "Neplatna volba." << std::endl;
    }
}

// main = lepidlo: WordFile dodava slova, Hangman hraje, main je propoji
int main() {
    WordFile file;
    file.loadWords("slova.txt");

    const auto& words = file.getWords();
    if (words.empty()) {   // bez slov neni co hrat (a N by bylo 0)
        std::cerr << "Zadna slova k hrani." << std::endl;
        return 1;
    }

    // N = pocet nactenych slov
    int n = static_cast<int>(words.size());
    std::cout << "Nacteno slov: " << n << std::endl;

    int choice = readChoice(1, n);
    if (choice == 0) { return 0; }   // konec vstupu

    // uzivatel cisluje od 1, vektor od 0 -> index je choice - 1
    Hangman game(words[choice - 1], 5);
    game.play();

    return 0;
}
