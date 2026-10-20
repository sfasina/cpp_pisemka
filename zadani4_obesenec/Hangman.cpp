//
// Created by fasin on 20.10.2026.
//

#include "Hangman.h"

#include <cctype>
#include <iostream>

// std::string(pocet, znak) -> "____" stejne dlouhe jako slovo
Hangman::Hangman(const std::string& word, int attempts)
    : m_word(word), m_guessWord(word.size(), '_'), m_attempts(attempts) {
}

bool Hangman::play() {
    std::string input;

    // hraje se, dokud zbyvaji pokusy A slovo neni cele odkryte
    while (m_attempts > 0 && m_guessWord != m_word) {
        printState();
        std::cout << "Pismeno: ";

        if (!std::getline(std::cin, input)) { return false; }   // konec vstupu
        if (input.empty()) { continue; }                        // jen Enter -> znovu

        // bereme jen prvni znak, tolower -> 'A' i 'a' je totez
        char letter = std::tolower(static_cast<unsigned char>(input[0]));
        if (revealLetter(letter)) {
            std::cout << "Trefa!" << std::endl;
        } else {
            --m_attempts;   // pokus ubira jen netrefa
            std::cout << "Vedle!" << std::endl;
        }
    }

    // smycka skoncila - zjistime proc
    if (m_guessWord == m_word) {
        std::cout << "Vyhral jsi! Slovo bylo: " << m_word << std::endl;
        return true;
    }
    std::cout << "Prohral jsi. Slovo bylo: " << m_word << std::endl;
    return false;
}

// projde CELE slovo -> v "kolo" odkryje obe 'o' najednou
bool Hangman::revealLetter(char letter) {
    bool hit = false;
    for (size_t i = 0; i < m_word.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(m_word[i])) == letter) {
            m_guessWord[i] = m_word[i];
            hit = true;
        }
    }
    return hit;
}

void Hangman::printState() const {
    for (char c : m_guessWord) {
        std::cout << c << ' ';   // "_ o _ o" misto "_o_o"
    }
    std::cout << "  (pokusy: " << m_attempts << ")" << std::endl;
}
