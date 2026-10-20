//
// Created by fasin on 19.10.2026.
//

#include "FileManager.h"

#include <fstream>   // std::ifstream (cteni), std::ofstream (zapis)
#include <iostream>  // std::cerr
#include <random>    // std::mt19937, std::uniform_int_distribution
#include <sstream>   // std::istringstream



// nacte soubor ve formatu "cesky;anglicky" (jeden par na radek) do m_words
void FileManager::loadWords(const std::string& filePath) {
    // otevreni souboru pro cteni
    std::ifstream file(filePath);

    // !file = soubor se nepodarilo otevrit (neexistuje, spatna cesta...)
    // POZOR: relativni cesta "words.txt" se hleda ve slozce, odkud se program
    // spousti (u CLionu cmake-build-debug), ne vedle .cpp souboru
    if (!file) {
        std::cerr << "Unable to open load file: " << filePath << std::endl;   // cerr = chybovy vystup
        return;   // bez return by se pokracovalo s neotevrenym souborem
    }

    std::string line;
    // getline vraci stream; v podmince je "true", dokud se radek podarilo precist
    // -> smycka skonci sama na konci souboru
    while (std::getline(file, line)) {
        // soubory z Windows maji na konci radku "\r\n", getline odstrani jen "\n"
        // takze '\r' (a pripadne mezery) umazeme rucne od konce
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) {continue;}   // prazdny radek preskocime (continue = dalsi kolo smycky)

        // istringstream = string, ze ktereho se da cist jako ze souboru
        std::istringstream ss(line);
        std::string czech, english;

        // getline(ss, czech, ';') cte do stredniku (strednik zahodi)
        // getline(ss, english) cte zbytek radku -> "ice cream" zustane cele i s mezerou
        // kdyz radek nema strednik, druhy getline selze a radek se tise preskoci
        if (std::getline(ss, czech, ';') && std::getline(ss, english)) {
            // emplace_back vytvori pair primo ve vektoru (jako push_back({czech, english}))
            m_words.emplace_back(czech, english);
        }
    }
    // soubor se zavre sam, kdyz "file" zanikne na konci funkce
}



// prida JEDEN par na konec souboru (pouziva se pro spatne uhodnuta slova)
void FileManager::saveWords(const std::pair<std::string, std::string>& pair, const std::string& filePath) {
    // std::ios::app = pridavat na konec, bez nej by se soubor pokazde prepsal
    // a zustalo by v nem jen posledni slovo
    // kdyz soubor neexistuje, ofstream ho sam vytvori
    std::ofstream file(filePath, std::ios::app);
    if (!file) {
        std::cerr << "Unable to open save file: " << filePath << std::endl;
        return;
    }
    // stejny format jako words.txt -> soubor jde pozdeji nacist pres loadWords()
    file << pair.first << ';' << pair.second << std::endl;

};

std::pair<std::string, std::string> FileManager::getRandomWord() {
    // generator nahodnych cisel:
    // - random_device = "skutecne" nahodne cislo od systemu, pouzije se jen jako seed (startovni hodnota)
    // - mt19937 = rychly generator, ktery ze seedu vyrabi dalsi cisla
    // - static = vytvori se jen jednou pri prvnim volani a zustane mezi volanimi
    //   (bez static by se pri kazdem volani seedoval znovu)
    static std::mt19937 gen(std::random_device{}());

    // rovnomerne nahodne cislo od 0 do size-1 (obe meze vcetne) = platny index
    // POZOR: pri prazdnem vektoru je size()-1 u size_t obrovske cislo -> proto main vola hasWords()
    std::uniform_int_distribution<size_t> randomNum(0, m_words.size() - 1);
    size_t randomIndex = randomNum(gen);

    // at() = jako [], ale pri spatnem indexu vyhodi vyjimku misto nedefinovaneho chovani
    // musime si slovo zkopirovat DRIV, nez ho z vektoru smazeme
    auto word = m_words.at(randomIndex);

    // erase chce iterator, ne index -> begin() + index ukazuje na prvek s timto indexem
    m_words.erase(m_words.begin() + randomIndex);

    return word;
}
