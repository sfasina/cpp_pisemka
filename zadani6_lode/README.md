# Zadání 6: Lodě (pole + mapa)

Program načte rozmístění lodí ze souboru, hráč zadá počet střel a střílí na políčka `b4`.
Hra končí, když potopí všechny lodě, dojdou střely nebo napíše `quit`.

`lode.txt`: 8 × 8 znaků, `.` = voda, písmeno = loď (stejné písmeno = stejná loď):
```
AAAA....      A = 4 políčka
..B.....      B = 3
..B..CC.      C = 2
```

## Rozdělení

| Soubor | Úloha |
|---|---|
| `Position.h` | `SIZE`, `Grid` (2D pole), `struct Position`, `parsePosition("b4")` |
| `Ocean` | **soubor**: načte lodě do pole a spočítá jejich velikosti do mapy |
| `Battle` | **pravidlo**: střelba, zásah, potopení, výpis plochy |
| `main` | lepidlo: počet střel, smyčka, výpis výsledku |

`Battle` dostane jen **data** (`Grid` + `map`), třídu `Ocean` nezná, stejně jako u ostatních zadání.

## Dvě pole a jedna mapa

```cpp
Grid m_ships;                      // kde jsou lodě (ze souboru)      'A' '.' 'B'
Grid m_shots;                      // co hráč vidí                   'X' 'o' '.'
std::map<char, int> m_remaining;   // loď → kolik políček ještě nezasaženo  {A:4, B:3...}
```
Střela na `[row][col]`:
1. `m_shots` už není `'.'` → **už střílel**, střela se nepočítá
2. `m_ships` je `'.'` → **voda**, do `m_shots` dej `'o'`
3. jinak **zásah**: `'X'` a `--m_remaining[lod]`, a když je hodnota 0, loď je **potopená**

**Konec hry:** všechny hodnoty v mapě jsou 0:
```cpp
std::all_of(m.begin(), m.end(), [](const auto& e) { return e.second == 0; });
```

## Nové věci

| Kód | Co dělá |
|---|---|
| `using Grid = std::array<std::array<char, 8>, 8>;` | krátké jméno pro dlouhý typ |
| `constexpr int SIZE = 8;` | konstanta, použitelná i jako velikost pole |
| `inline bool parsePosition(...)` | funkce s tělem v `.h` |
| `enum class ShotResult { Miss, Hit, Sunk, AlreadyShot };` | výsledek jako pojmenovaná možnost |
| `switch (battle.fire(p, ship)) { case ShotResult::Hit: ... }` | větvení podle enumu |
| `'a' + col` / `letter - 'a'` | číslo ↔ písmeno sloupce |
| `std::all_of` / `count_if` nad mapou | prvek mapy je `pair`: `.first` klíč, `.second` hodnota |

## Na trénink
- Náhodné rozmístění lodí místo souboru (`mt19937` + kontrola, že se lodě nepřekrývají).
- Jména lodí ze souboru `A;letadlova lod` do `std::map<char, std::string>`.
- Statistika: přesnost = zásahy / střely v procentech (`fixed`, `setprecision(1)`).
- Dva hráči: dvě `Battle`, střídání jako v šachách.
