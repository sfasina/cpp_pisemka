# Zadání 5: Šachy (pole + mapa)

Zjednodušené šachy pro dva hráče v konzoli. Načte šachovnici a figurky ze souborů,
hráči se střídají v tazích `e2 e4`. Hra končí **sebráním krále** nebo `quit`.
Bez šachu, rošády a braní mimochodem.

| Soubor | Formát |
|---|---|
| `sachovnice.txt` | 8 řádků × 8 znaků, `.` prázdné, VELKÁ = bílý, malá = černý |
| `figurky.txt` | `znak;jmeno;hodnota`, např. `Q;dama;9` |

## Rozdělení

| Třída | Úloha | Novinka |
|---|---|---|
| `Position` | `struct {row, col}` + `parsePosition("e2")` | převod znaku na index |
| `Board` | šachovnice, načtení, výpis | **2D pole** `std::array` |
| `PieceTable` | jméno a hodnota figurky | **`std::map`** |
| `Rules` | smí figurka táhnout? | `switch`, cesta po polích |
| `main` | střídání hráčů, braní, souhrn | `std::array<int, 2>`, `std::map<char, int>` |

---

## Pole – `std::array` (`<array>`)

```cpp
std::array<int, 2> points{0, 0};                       // pevná velikost 2
std::array<std::array<char, 8>, 8> cells;              // 2D: cells[radek][sloupec]

points[0] += 5;                 // přístup indexem (od 0)
cells[6][4] = 'P';              // řádek 6, sloupec 4
row.fill('.');                  // všechny prvky na stejnou hodnotu
points.size();                  // 2

for (auto& row : cells)         // auto& = měníš originál, ne kopii
    for (char c : row) std::cout << c;
```
| | `std::array` | `std::vector` |
|---|---|---|
| velikost | pevná, známá předem (`8`) | mění se (`push_back`) |
| kdy | šachovnice, bludiště, body hráčů | řádky ze souboru |

**Souřadnice → index:** `col = 'e' - 'a'` = 4, `row = '8' - '2'` = 6 (řada 8 je nahoře = řádek 0).

## Mapa – `std::map` (`<map>`)

Slovník **klíč → hodnota**, klíče jsou unikátní a **vždy seřazené**.

```cpp
std::map<char, int> captured;

captured['p'] = 3;              // vlož / přepiš
++captured['q'];                // chybějící klíč se VYTVOŘÍ s 0 → pak 1

auto it = captured.find('k');   // hledání BEZ vytvoření
if (it != captured.end()) {
    it->first;                  // klíč
    it->second;                 // hodnota
}

captured.count('k');            // 1 = existuje, 0 = ne
captured.erase('p');            // smaž klíč
captured.size(); captured.empty();

for (const auto& [key, value] : captured)   // projde seřazeně podle klíče
    std::cout << key << ": " << value << '\n';
```

| Chceš | Použij |
|---|---|
| vložit / zvýšit počítadlo | `m[key] = x;` / `++m[key];` |
| jen zjistit, jestli tam je | `m.find(key) != m.end()` nebo `m.count(key)` |
| číst v `const` metodě | `find` (ne `[]` – ten v `const` nejde) |
| hodnota, nebo výjimka | `m.at(key)` |

**Past:** `if (m[key] == 0)` klíč **vytvoří**. Na zjištění používej `find` / `count`.

## Jak to číst v kódu
1. `Board::load` → stejný vzor jako ostatní načítání, jen každý znak jde do `m_cells[row][col]`.
2. `PieceTable::load` → `getline` + `;` + `stoi`, výsledek do `m_pieces[key]`.
3. `Rules::canMove` → obecné kontroly (je tam figurka, je moje, neberu svoji), pak `canPieceMove`.
4. `canPieceMove` → `dr`, `dc` = o kolik se táhne; každá figurka má jednu podmínku.
5. `main` → `while (true)`: vypiš, načti tah, zkontroluj, přesuň, prohoď hráče.

## Na trénink
- Ulož partii: každý tah `ios::app` do `partie.txt`.
- Spočítej figurky na šachovnici do `std::map<char, int>` (projdi obě pole).
- Načti jinou pozici ze souboru (třeba jen králové a pár figurek) a zkus koncovku.
