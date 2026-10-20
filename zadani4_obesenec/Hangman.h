//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_HANGMAN_H
#define CPP2PRACTISE_HANGMAN_H

#include <string>

// trida na pravidlo: hra s JEDNIM slovem (podtrzitka, hadani, pokusy)
// nevi, odkud slovo prislo - dostane ho v konstruktoru
class Hangman {
private:
    std::string m_word;        // hadane slovo, napr. "kolo"
    std::string m_guessWord;   // co hrac vidi, napr. "_o_o"
    int m_attempts;            // kolik netref jeste zbyva

    bool revealLetter(char letter);   // odkryje pismeno, vrati true pri zasahu
    void printState() const;          // vypise "_ o _ o   (pokusy: 4)"

public:
    Hangman(const std::string& word, int attempts);

    // vnitrni smycka hadani; vrati true = vyhra, false = dosly pokusy
    bool play();
};

#endif //CPP2PRACTISE_HANGMAN_H
