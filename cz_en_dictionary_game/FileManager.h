//
// Created by fasin on 19.10.2026.
//

// HEADER (.h) = "co trida umi" - seznam clenu a metod (deklarace)
// telo metod (definice) je v FileManager.cpp
//
// FileManager se stara JEN o soubory: nacist slova, ulozit slovo, dat nahodne slovo.
// O hre (Game) nic nevi - propojeni obou trid dela az main.cpp

// include guard: kdyz se header includne vickrat, obsah se vlozi jen poprve
// (bez nej by compiler hlasil "redefinition of class FileManager")
#ifndef CPP2PRACTISE_DICTIONARY_H
#define CPP2PRACTISE_DICTIONARY_H

#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

class FileManager {
private:
    // private = zvenku na to nikdo nesahne, jen metody teto tridy
    // vektor dvojic: first = ceske slovo, second = anglicke slovo
    // prefix m_ = "member" (clen tridy), at se to neplete s lokalnimi promennymi
    std::vector<std::pair<std::string, std::string>> m_words;

public:
    // = default -> compiler vygeneruje obycejny konstruktor/destruktor sam
    // (nic specialniho nepotrebujeme, vektor se uklidi sam)
    FileManager() = default;
    ~FileManager() = default;

    // const std::string& = predani referenci bez kopirovani, const = funkce ho nezmeni
    void loadWords(const std::string& filePath);
    void saveWords(const std::pair<std::string, std::string>& pair, const std::string& filePath);

    // vrati nahodne slovo a ZAROVEN ho z vektoru odebere -> zadne slovo se neopakuje
    std::pair<std::string, std::string> getRandomWord();

    // metoda napsana primo v headeru (inline) - na jeden radek se nevyplati .cpp
    // const za zavorkou = metoda nemeni objekt
    // main ji vola pred getRandomWord(), aby se nikdy nebralo z prazdneho vektoru
    bool hasWords() const { return !m_words.empty(); }
};

#endif //CPP2PRACTISE_DICTIONARY_H
