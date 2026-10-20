//
// Created by fasin on 19.10.2026.
//

// Game = hra s JEDNIM slovem: podtrzitka, hadani pismen, pocitani pokusu.
// Nevi, odkud slovo prislo (FileManager), ani kolik slov se hraje - to resi main.cpp.
// Pro kazde slovo se v main vytvori novy objekt Game.

#ifndef CPP2PRACTISE_GAME_H
#define CPP2PRACTISE_GAME_H
#include <string>    // std::string
#include <utility>   // std::pair


class Game {
private:
    std::string m_czechWord;     // co se zobrazi hraci, napr. "kocka"
    std::string m_englishWord;   // co hrac hada, napr. "cat"
    std::string m_guessWord;     // co hrac zatim vidi, napr. "_a_" (stejne dlouhe jako m_englishWord)
    int m_numberOfAttempts;      // kolik netref jeste zbyva
    bool m_quit = false;         // hrac napsal "quit" (nebo skoncil vstup)
                                 // "= false" = vychozi hodnota, nastavi se pri vytvoreni objektu

    // pomocne metody - private, protoze je pouziva jen play() uvnitr tridy
    // (nejsou nutne, jejich obsah by sel napsat primo do play())
    bool revealLetter(char letter);   // odkryje pismeno, vrati true pri zasahu
    void printState() const;          // vypise "kocka   _ a _   (pokusy: 3)"

public:
    // konstruktor: vola se pri "Game game(word, attempts);" v main
    Game(const std::pair<std::string, std::string>& word, int attempts);

    // rozlozi pair na ceske/anglicke slovo a pripravi podtrzitka
    void parsePairInWords(const std::pair<std::string, std::string>& pair);

    // odehraje slovo (vnitrni smycka), vrati true = uhodnuto, false = prohra nebo quit
    bool play();

    // play() vraci jen true/false, takze quit od prohry pozname touto metodou
    bool hasQuit() const { return m_quit; }

    // static = metoda patri tride, ne objektu -> vola se Game::loadAndCheckInput(...)
    // bez vytvoreneho objektu; main ji potrebuje DRIV, nez existuje nejaka Game
    static void loadAndCheckInput(int& target, std::string& input);
};
#endif //CPP2PRACTISE_GAME_H
