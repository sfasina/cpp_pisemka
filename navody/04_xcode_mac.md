# Xcode a Mac – rychlá příručka

## Nový projekt
1. **File → New → Project → macOS → Command Line Tool**
2. Language: **C++** → vyber složku → vznikne `main.cpp` s Hello World.
3. Nová třída: **File → New → File → C++ File** → zaškrtni *Also create a header file* → vznikne `Trida.cpp` + `Trida.hpp`.
   (`.hpp` = totéž co `.h`, include pak `#include "Trida.hpp"`)

## Nastavit hned na začátku
| Co | Kde |
|---|---|
| **C++20** (kvůli `erase_if`, `ranges`) | klik na projekt → *Build Settings* → hledej **C++ Language Dialect** → `C++20` |
| **Složka pro soubory** (`mista.txt`) | *Product → Scheme → Edit Scheme → Run → Options* → **Working Directory** → *Use custom* → složka s `.txt` |

Bez Working Directory program hledá soubor ve skryté build složce → `Unable to open file`.
Nouzově: absolutní cesta `"/Users/jmeno/Desktop/mista.txt"`.

## Ovládání
| Akce | Mac / Xcode | Windows / CLion |
|---|---|---|
| Spustit | `Cmd + R` | `Shift + F10` |
| Jen zkompilovat | `Cmd + B` | `Ctrl + F9` |
| Zastavit | `Cmd + .` | `Ctrl + F2` |
| Ukázat konzoli | `Cmd + Shift + Y` | okno *Run* dole |
| Konec vstupu (EOF) | `Ctrl + D` | `Ctrl + Z` + Enter |
| Kopírovat / vložit | `Cmd + C / V` | `Ctrl + C / V` |
| Zakomentovat řádky | `Cmd + /` | `Ctrl + /` |
| Odsadit kód | `Ctrl + I` | `Ctrl + Alt + L` |

Vstup píšeš **do konzole dole** (pravá část), Enter odešle.

## Rozdíly Mac × Windows
| | Mac | Windows |
|---|---|---|
| Kompilátor | clang (Apple) | MinGW g++ (CLion) |
| Konec řádku v souborech | `\n` | `\r\n` → **na Macu vždy maž `'\r'`**, když je soubor z Windows |
| Projekt | Xcode projekt (`.xcodeproj`) | `CMakeLists.txt` |
| Přidání souboru | *File → New → File* (Xcode ho přidá sám) | ručně do `add_executable(...)` |

Pokud soubor přetáhneš do Xcode zvenku, zaškrtni **Target Membership** (pravý panel), jinak se nekompiluje → `undefined symbol`.

## Klávesnice
Na české klávesnici se `{ } [ ] | \ ~ < >` hledají těžko. Nejjednodušší:
přidej **ABC / U.S.** rozložení (*Nastavení → Klávesnice → Vstupní zdroje*) a přepínej `Ctrl + mezerník`.
Na US: `[ ]` vedle P, `{ }` = Shift + `[ ]`, `|` a `\` nad Enterem, `< >` = Shift + `, .`

## Bez Xcode (Terminál)
```bash
clang++ -std=c++20 *.cpp -o app && ./app
```
Spouští se ve složce, kde jsi → soubory `.txt` najde bez nastavování.

CLion funguje na Macu **úplně stejně** jako na Windows (CMake), pokud ho smíš použít.
