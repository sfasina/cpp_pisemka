#include <iostream>
#include <string>

#include "FileManager.h"
#include "Game.h"

// main = "lepidlo": jako jediny zna obe tridy a propojuje je
// - FileManager dodava slova
// - Game hraje jedno slovo
// - main ridi vnejsi smycku (kolik slov), pocita skore a uklada spatna slova
int main() {
    FileManager fm;
    fm.loadWords("words.txt");

    // 1) nastaveni hry - nacteme JEDNOU, pred smyckou
    // loadAndCheckInput je static, proto Game::... (zadny objekt Game jeste neexistuje)
    std::string input;
    int attempts, numberOfWords;
    std::cout << "How many attempts would you like to play?" << std::endl;
    Game::loadAndCheckInput(attempts, input);
    std::cout << "How many words?" << std::endl;
    Game::loadAndCheckInput(numberOfWords, input);

    int score = 0;    // kolik slov hrac uhodl
    int played = 0;   // kolik slov se opravdu dohralo

    // 2) vnejsi smycka: jedno kolo = jedno slovo
    // konci, kdyz se odehraje zadany pocet slov NEBO dojdou slova v souboru
    // (hasWords() musi byt v podmince, jinak by getRandomWord() bral z prazdneho vektoru)
    for (int i = 0; i < numberOfWords && fm.hasWords(); ++i) {
        // slovo si ulozime, abychom ho pri prohre mohli zapsat do souboru
        auto word = fm.getRandomWord();   // auto = compiler doplni typ std::pair<std::string, std::string>

        // novy objekt pro kazde slovo -> pokusy zacinaji vzdy od zadane hodnoty
        // (objekt zanikne na konci kazdeho kola smycky)
        Game game(word, attempts);
        bool won = game.play();   // 3) vnitrni smycka (hadani pismen) bezi uvnitr play()

        // quit neni prohra -> slovo neukladame a koncime celou hru
        // break = okamzite vyskoceni z for smycky
        if (game.hasQuit()) {
            std::cout << "Konec hry." << std::endl;
            break;
        }

        ++played;
        if (won) {
            ++score;
        } else {
            // 4) prohrane slovo se prida na konec wrong_words.txt (v cmake-build-debug)
            fm.saveWords(word, "wrong_words.txt");
        }
    }
    // played misto numberOfWords: po quit nebo kdyz dojdou slova jich bylo min
    std::cout << "Score: " << score << "/" << played << std::endl;
}
