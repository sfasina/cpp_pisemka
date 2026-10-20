//
// Created by fasin on 19.10.2026.
//

#include "Game.h"

#include <cctype>    // std::isalpha, std::tolower
#include <iostream>  // std::cin, std::cout

// konstruktor
// ": m_numberOfAttempts(attempts)" = inicializacni seznam - nastavi clen jeste
// pred telem konstruktoru (lepsi nez prirazeni v tele)
Game::Game(const std::pair<std::string, std::string>& word, int attempts)
    : m_numberOfAttempts(attempts) {
    parsePairInWords(word);
}

void Game::parsePairInWords(const std::pair<std::string, std::string>& pair) {
    m_czechWord = pair.first;
    m_englishWord = pair.second;

    // std::string(pocet, znak) = string z "pocet" stejnych znaku, napr. "___"
    m_guessWord = std::string(m_englishWord.size(), '_');

    // same podtrzitka, jen mezery (napr. "ice cream") rovnou odkryjeme
    // isalpha = je to pismeno? kdyz ne (mezera, pomlcka), znak rovnou ukazeme
    // static_cast<unsigned char>: isalpha/tolower se zapornym char (napr. diakritika
    // v UTF-8) je nedefinovane chovani, proto pretypujeme na unsigned
    for (size_t i = 0; i < m_englishWord.size(); ++i) {
        if (!std::isalpha(static_cast<unsigned char>(m_englishWord[i]))) {
            m_guessWord[i] = m_englishWord[i];
        }
    }
}

// vnitrni smycka: hadani pismen jednoho slova
// vraci true, kdyz hrac slovo uhodl
bool Game::play() {
    std::string input;

    // bezi, dokud zbyvaji pokusy A slovo jeste neni cele odkryte
    // (m_guessWord == m_englishWord znamena, ze uz tam neni zadne '_')
    while (m_numberOfAttempts > 0 && m_guessWord != m_englishWord) {
        printState();
        std::cout << "Pismeno (nebo quit): ";

        // getline cte cely radek -> "quit" se precte cele, ne po pismenkach
        // (cin >> char by vzal jen 'q' a zbytek "uit" by zustal ve vstupu)
        // konec vstupu (Ctrl+Z) bereme stejne jako quit, jinak by se vsechna
        // zbyla slova ulozila jako spatna
        if (!std::getline(std::cin, input) || input == "quit") {
            m_quit = true;
            return false;
        }
        if (input.empty()) { continue; }   // jen Enter -> zeptame se znovu, pokus neubira

        // bereme jen prvni znak; tolower -> 'A' i 'a' se hada stejne
        char letter = std::tolower(static_cast<unsigned char>(input[0]));
        if (!revealLetter(letter)) {
            --m_numberOfAttempts;   // ubirame jen za netrefu
            std::cout << "Vedle!" << std::endl;
        }
        // POZOR: pri zasahu se nic nevypise, jen se v dalsim printState() objevi pismeno
        // a uz odkryte pismeno se bere jako zasah (pokus neubere)
    }

    // smycka skoncila ze dvou duvodu - zjistime ktery
    if (m_guessWord == m_englishWord) {
        std::cout << "Spravne! " << m_czechWord << " = " << m_englishWord << std::endl;
        return true;
    }
    std::cout << "Dosly pokusy. Spravne bylo: " << m_englishWord << std::endl;
    return false;
}

// doplni pismeno na vsechna mista, kde ve slove je
// vraci true, kdyz se aspon jednou trefil
bool Game::revealLetter(char letter) {
    bool hit = false;
    // projdeme CELE slovo (nekoncime u prvniho nalezu), aby se odkryla
    // vsechna stejna pismena - napr. "o" v "book" odkryje obe
    for (size_t i = 0; i < m_englishWord.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(m_englishWord[i])) == letter) {
            m_guessWord[i] = m_englishWord[i];   // zachova puvodni velikost pismena
            hit = true;
        }
    }
    return hit;
}

// const = jen vypisuje, nic v objektu nemeni
void Game::printState() const {
    std::cout << m_czechWord << "   ";
    // range-based for: projde kazdy znak stringu
    for (char c : m_guessWord) {
        std::cout << c << ' ';   // "_ _ _" je citelnejsi nez "___"
    }
    std::cout << "  (pokusy: " << m_numberOfAttempts << ")" << std::endl;
}

// nacte radek a prevede ho na cislo; pri neplatnem vstupu nastavi 0
// int& target = reference -> funkce zapisuje primo do promenne v main
// (v .cpp se "static" nepise, jen v headeru)
void Game::loadAndCheckInput(int& target, std::string& input) {
    std::getline(std::cin, input);

    // stoi = string -> int; pri "abc" vyhodi std::invalid_argument,
    // pri moc velkem cisle std::out_of_range - obe chyti std::exception
    // POZOR: "5abc" projde jako 5 (stoi precte, co umi, a zbytek ignoruje)
    try {
        target = std::stoi(input);
    } catch (const std::exception&) {
        target = 0;   // s 0 slovy/pokusy se hra rovnou ukonci
    }
}
