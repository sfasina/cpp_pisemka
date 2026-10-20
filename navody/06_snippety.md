# Snippety na Ctrl+C / Ctrl+V

Hotové kusy kódu ze všech zadání. Zkopíruj a uprav jen řádky označené **`// UPRAV`**.
Příklady jsou na `Place` (`jmeno;sirka;delka`) a na oběšenci. Přejmenuj podle zadání.

Obsah: [Includy](#0-includy) · [Header](#1-header-h) · [Struct](#2-struct) · [Načtení souboru](#3-načtení-souboru-se-středníky) · [Slovo na řádek](#4-načtení-jedno-slovo-na-řádek) · [Zápis](#5-zápis-do-souboru) · [Vstup od uživatele](#6-vstup-od-uživatele) · [Rozsah / obdélník](#7-třída-pravidlo-rozsah--obdélník) · [Počítání](#8-počítání-uvnitř--mimo) · [Algoritmy](#9-algoritmy-na-jeden-řádek) · [Tabulka](#10-výpis-do-tabulky) · [Oběšenec](#11-oběšenec-hádání-písmen) · [Výběr slova](#12-výběr-ze-seznamu) · [Víc kol](#13-víc-kol-se-společnými-pokusy) · [main](#14-main) · [CMake](#15-cmakeliststxt)

---

## 0. Includy

**Kdy:** nahoru do `.cpp`. Přebytečné nevadí.

```cpp
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
```

---

## 1. Header (`.h`)

**Kdy:** každá třída. Guard chrání před dvojím vložením.

```cpp
#ifndef PLACEFILE_H              // UPRAV: jméno souboru velkými
#define PLACEFILE_H

#include <string>
#include <vector>
#include "Place.h"

class PlaceFile {                // UPRAV
private:
    std::vector<Place> m_places;
    int m_invalidLines = 0;

    static bool parseLine(const std::string& line, Place& out);

public:
    void load(const std::string& filePath);
    const std::vector<Place>& getPlaces() const { return m_places; }
    int getInvalidLines() const { return m_invalidLines; }
};

#endif
```

---

## 2. Struct

**Kdy:** 1 řádek souboru = 1 struct. Kolik polí, tolik členů.

```cpp
struct Place {          // UPRAV
    std::string name;
    double lat;
    double lon;
};
```

---

## 3. Načtení souboru se středníky

**Kdy:** řádky typu `Brno;49.20;16.61`. Vadné řádky počítá.
**Uprav:** počet `getline`, `stod`/`stoi`, struct.

```cpp
void PlaceFile::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();                     // \r z Windows souboru
        }
        if (line.empty()) { continue; }

        Place p;
        if (parseLine(line, p)) {
            m_places.push_back(p);
        } else {
            ++m_invalidLines;
        }
    }
}

bool PlaceFile::parseLine(const std::string& line, Place& out) {
    std::istringstream ss(line);
    std::string name, latStr, lonStr;                   // UPRAV: 1 string na pole

    if (!std::getline(ss, name, ';') ||
        !std::getline(ss, latStr, ';') ||
        !std::getline(ss, lonStr)) {                    // POSLEDNÍ bez ';'
        return false;
    }

    try {
        size_t pos = 0;
        double lat = std::stod(latStr, &pos);           // UPRAV: stod / stoi
        if (pos != latStr.size()) { return false; }     // "49,40" → vadné (volitelné)
        double lon = std::stod(lonStr, &pos);
        if (pos != lonStr.size()) { return false; }

        out = Place{name, lat, lon};                    // UPRAV
        return true;
    } catch (const std::exception&) {                   // text místo čísla
        return false;
    }
}
```

---

## 4. Načtení: jedno slovo na řádek

**Kdy:** oběšenec, seznam slov. Bez dělení.

```cpp
void WordFile::loadWords(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (line.empty()) { continue; }
        m_words.push_back(line);
    }
}
```

**Varianta `cesky;anglicky` do `pair`:**

```cpp
std::istringstream ss(line);
std::string czech, english;
if (std::getline(ss, czech, ';') && std::getline(ss, english)) {
    m_words.emplace_back(czech, english);   // vector<pair<string, string>>
}
```

---

## 5. Zápis do souboru

**Celý vektor (soubor přepíše):**

```cpp
bool save(const std::vector<Place>& places, const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file) { return false; }

    file << std::fixed << std::setprecision(2);                   // UPRAV: počet des. míst
    for (const auto& p : places) {
        file << p.name << ';' << p.lat << ';' << p.lon << '\n';   // UPRAV
    }
    return true;
}
```

**Jeden řádek na konec (append):**

```cpp
std::ofstream file("wrong_words.txt", std::ios::app);   // UPRAV
if (file) {
    file << word << '\n';
}
```

---

## 6. Vstup od uživatele

**Číslo v rozsahu, ptá se znovu** (volba 1–N):

```cpp
int readChoice(int min, int max) {
    std::string input;
    while (true) {
        std::cout << "Vyber cislo " << min << " az " << max << ": ";
        if (!std::getline(std::cin, input)) { return 0; }
        try {
            int choice = std::stoi(input);
            if (choice >= min && choice <= max) { return choice; }
        } catch (const std::exception&) {}
        std::cout << "Neplatna volba." << std::endl;
    }
}
```

**Desetinné číslo, ptá se znovu:**

```cpp
double readDouble(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input)) { return 0; }
        try {
            return std::stod(input);
        } catch (const std::exception&) {
            std::cout << "Neplatne cislo." << std::endl;
        }
    }
}
```

**Rychlá verze bez kontroly** (pak už nepoužívej `getline`, nebo napiš `std::cin.ignore();`):

```cpp
double lat1, lon1;
std::cin >> lat1 >> lon1;
if (!std::cin) { std::cerr << "Neplatny vstup." << std::endl; return 1; }
```

---

## 7. Třída pravidlo: rozsah / obdélník

**Kdy:** „uživatel zadá rozsah / dva rohy“. Pořadí mezí je jedno.

```cpp
// Rectangle.h
class Rectangle {
private:
    double m_minLat, m_maxLat, m_minLon, m_maxLon;
public:
    Rectangle(double lat1, double lon1, double lat2, double lon2);
    bool contains(const Place& p) const;
};

// Rectangle.cpp
Rectangle::Rectangle(double lat1, double lon1, double lat2, double lon2)
    : m_minLat(std::min(lat1, lat2)), m_maxLat(std::max(lat1, lat2)),
      m_minLon(std::min(lon1, lon2)), m_maxLon(std::max(lon1, lon2)) {
}

bool Rectangle::contains(const Place& p) const {
    return p.lat >= m_minLat && p.lat <= m_maxLat      // UPRAV: pole
        && p.lon >= m_minLon && p.lon <= m_maxLon;
}
```

**1D rozsah** (jen jedna hodnota): smaž druhou dvojici min/max.
**Kruh:** `return std::sqrt(dx * dx + dy * dy) <= m_radius;` (`#include <cmath>`)

---

## 8. Počítání uvnitř / mimo

```cpp
int inside = 0, outside = 0;
for (const auto& p : file.getPlaces()) {
    if (rect.contains(p)) {
        ++inside;
        std::cout << "  " << p.name << std::endl;   // vypíše ty uvnitř
    } else {
        ++outside;
    }
}
std::cout << "Uvnitr: " << inside << ", mimo: " << outside << std::endl;
```

---

## 9. Algoritmy na jeden řádek

`v` = `std::vector<Place>`. Podrobně: [01_lambda.md](01_lambda.md).

```cpp
// kolik splňuje
long n = std::count_if(v.begin(), v.end(), [&rect](const Place& p) { return rect.contains(p); });

// seřadit sestupně (> ) / vzestupně (<)
std::sort(v.begin(), v.end(), [](const Place& a, const Place& b) { return a.lat > b.lat; });

// vybrat do nového vektoru
std::vector<Place> inside;
std::copy_if(v.begin(), v.end(), std::back_inserter(inside), [&rect](const Place& p) { return rect.contains(p); });

// smazat ty mimo (C++20)
std::erase_if(v, [&rect](const Place& p) { return !rect.contains(p); });

// největší (pro max i min se píše <)
if (!v.empty()) {
    auto it = std::max_element(v.begin(), v.end(), [](const Place& a, const Place& b) { return a.lat < b.lat; });
    std::cout << it->name;
}

// průměr
if (!v.empty()) {
    double avg = std::accumulate(v.begin(), v.end(), 0.0,
                                 [](double s, const Place& p) { return s + p.lat; }) / v.size();
}

// najít podle jména
auto it = std::find_if(v.begin(), v.end(), [](const Place& p) { return p.name == "Brno"; });
if (it != v.end()) { /* nalezeno: *it */ }
```

---

## 10. Výpis do tabulky

```cpp
std::cout << std::left << std::setw(15) << "Jmeno"
          << std::right << std::setw(10) << "Sirka" << std::setw(10) << "Delka" << '\n';
std::cout << std::string(35, '-') << '\n';

std::cout << std::fixed << std::setprecision(2);
for (const auto& p : v) {
    std::cout << std::left << std::setw(15) << p.name
              << std::right << std::setw(10) << p.lat << std::setw(10) << p.lon << '\n';
}
```

---

## 11. Oběšenec: hádání písmen

```cpp
// Hangman.h
class Hangman {
private:
    std::string m_word;
    std::string m_guessWord;
    bool revealLetter(char letter);
    void printState(int attempts) const;
public:
    explicit Hangman(const std::string& word);
    bool play(int& attempts);          // & = ubírá pokusy přímo v main
};

// Hangman.cpp
Hangman::Hangman(const std::string& word)
    : m_word(word), m_guessWord(word.size(), '_') {
    for (size_t i = 0; i < m_word.size(); ++i) {      // mezery rovnou odkryj
        if (!std::isalpha(static_cast<unsigned char>(m_word[i]))) {
            m_guessWord[i] = m_word[i];
        }
    }
}

bool Hangman::play(int& attempts) {
    std::string input;
    while (attempts > 0 && m_guessWord != m_word) {
        printState(attempts);
        std::cout << "Pismeno: ";
        if (!std::getline(std::cin, input)) { return false; }
        if (input.empty()) { continue; }

        char letter = std::tolower(static_cast<unsigned char>(input[0]));
        if (revealLetter(letter)) {
            std::cout << "Trefa!" << std::endl;
        } else {
            --attempts;
            std::cout << "Vedle!" << std::endl;
        }
    }

    if (m_guessWord == m_word) {
        std::cout << "Vyhral jsi! " << m_word << std::endl;
        return true;
    }
    std::cout << "Prohral jsi. Slovo bylo: " << m_word << std::endl;
    return false;
}

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

void Hangman::printState(int attempts) const {
    for (char c : m_guessWord) { std::cout << c << ' '; }
    std::cout << "  (pokusy: " << attempts << ")" << std::endl;
}
```

**Pokusy jen pro jedno slovo?** Volej `int attempts = 5; game.play(attempts);` pro každé slovo znovu.

---

## 12. Výběr ze seznamu

**Uživatel vybere číslem:**

```cpp
const auto& words = file.getWords();
if (words.empty()) { std::cerr << "Zadna slova." << std::endl; return 1; }

int choice = readChoice(1, static_cast<int>(words.size()));
std::string word = words[choice - 1];        // uživatel od 1, vektor od 0
```

**Náhodně a bez opakování** (vektor musí jít měnit):

```cpp
std::string getRandomWord(std::vector<std::string>& words) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, words.size() - 1);
    size_t i = dist(gen);

    std::string word = words[i];
    words.erase(words.begin() + i);          // aby se neopakovalo
    return word;
}
```

---

## 13. Víc kol se společnými pokusy

**Kdy:** „hraje, dokud neuhodne všechna slova, nebo mu nedojdou pokusy“.

```cpp
std::vector<std::string> remaining = file.getWords();   // kopie, budeme mazat
int attempts = 5;                                       // UPRAV

while (!remaining.empty() && attempts > 0) {
    std::cout << "Zbyva slov: " << remaining.size() << std::endl;
    int choice = readChoice(1, static_cast<int>(remaining.size()));
    if (choice == 0) { break; }

    Hangman game(remaining[choice - 1]);
    if (game.play(attempts)) {
        remaining.erase(remaining.begin() + (choice - 1));
    }
}
std::cout << (remaining.empty() ? "Vyhral jsi vse!" : "Dosly pokusy.") << std::endl;
```

**Quit:** v `play` přidej `if (input == "quit") { m_quit = true; return false; }` a v `main` `if (game.hasQuit()) break;`

---

## 14. main

```cpp
#include <iostream>
#include "PlaceFile.h"     // UPRAV
#include "Rectangle.h"

int main() {
    // 1) načti
    PlaceFile file;
    file.load("mista.txt");                                     // UPRAV
    std::cout << "Nacteno: " << file.getPlaces().size()
              << ", vadnych: " << file.getInvalidLines() << std::endl;

    // 2) vstup
    double lat1 = readDouble("Sirka 1: "), lon1 = readDouble("Delka 1: ");
    double lat2 = readDouble("Sirka 2: "), lon2 = readDouble("Delka 2: ");
    Rectangle rect(lat1, lon1, lat2, lon2);

    // 3) smyčka + výstup → snippet 8

    return 0;
}
```
