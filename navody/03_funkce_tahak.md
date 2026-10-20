# Tahák funkcí – co jsme používali a co si pamatovat

Každá sekce: **include**, funkce, krátký příklad. Na konci univerzální kostra načítání.

---

## 1. Soubory – `<fstream>`

| Kód | Co dělá |
|---|---|
| `std::ifstream file("a.txt");` | otevře pro **čtení** |
| `std::ofstream file("a.txt");` | otevře pro **zápis**, soubor **přepíše** |
| `std::ofstream file("a.txt", std::ios::app);` | zápis **na konec** (append) |
| `if (!file) { ... return; }` | soubor se nepodařilo otevřít |
| `while (std::getline(file, line))` | čte řádek po řádku do konce souboru |
| `file << a << ';' << b << '\n';` | zápis, stejně jako `cout` |

Relativní cesta `"a.txt"` se hledá ve složce, **odkud se program spouští** (CLion: `cmake-build-debug`).
Soubor se zavře sám na konci bloku.

---

## 2. Rozdělení řádku – `<sstream>`, `<string>`

```cpp
std::istringstream ss(line);          // z řádku "mini soubor"
std::getline(ss, name, ';');          // do středníku (středník zahodí)
std::getline(ss, latStr, ';');
std::getline(ss, lonStr);             // poslední pole = zbytek řádku
```
Když `getline` selže (málo polí), vrátí `false` → vadný řádek.

**Úklid konce řádku** (soubory z Windows mají `\r`, hlavně na macOS):
```cpp
while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
if (line.empty()) continue;
```

---

## 3. Text → číslo – `<string>`

| Funkce | Převod | Chyba |
|---|---|---|
| `std::stoi(s)` | `string` → `int` | `"abc"` → `std::invalid_argument` |
| `std::stod(s)` | `string` → `double` | moc velké → `std::out_of_range` |
| `std::to_string(x)` | číslo → `string` | – |

Vždy v `try/catch`:
```cpp
try {
    double lat = std::stod(latStr);
} catch (const std::exception&) {   // chytí obě výjimky
    ++invalid;
}
```

**Past:** `stod("49,40")` vrátí `49` bez chyby. Přísná kontrola:
```cpp
size_t pos = 0;
double x = std::stod(s, &pos);
if (pos != s.size()) { /* za číslem něco zbylo → vadné */ }
```

---

## 4. Práce se `std::string`

| Kód | Co dělá |
|---|---|
| `s.size()` / `s.empty()` | délka / je prázdný |
| `s[i]`, `s.back()` | znak na indexu / poslední znak |
| `s.pop_back()` | smaže poslední znak |
| `std::string(5, '_')` | `"_____"` |
| `s.find("ab")` | index, nebo `std::string::npos` když tam není |
| `s.substr(od, delka)` | podřetězec |
| `a == b`, `a + b` | porovnání, spojení |
| `for (char c : s)` | projde znaky |

**Znaky – `<cctype>`** (vždy přetypuj na `unsigned char`):
```cpp
char c = std::tolower(static_cast<unsigned char>(input[0]));   // 'A' → 'a'
if (std::isalpha(static_cast<unsigned char>(c))) { ... }       // je to písmeno?
```
Další: `isdigit`, `isspace`, `toupper`.

---

## 5. `std::vector` – `<vector>`

| Kód | Co dělá |
|---|---|
| `v.push_back(x)` | přidá na konec |
| `v.emplace_back(a, b)` | vytvoří prvek rovnou ve vektoru (`pair`, `struct`) |
| `v.size()`, `v.empty()` | počet / je prázdný |
| `v[i]` / `v.at(i)` | prvek; `at` při špatném indexu vyhodí výjimku |
| `v.erase(v.begin() + i)` | smaže prvek na indexu `i` |
| `std::erase_if(v, lambda)` | smaže všechny, pro které lambda vrátí `true` (C++20) |
| `v.clear()` | smaže vše |
| `for (const auto& x : v)` | projde prvky bez kopírování |

**Uživatel čísluje od 1, vektor od 0** → `v[choice - 1]`.

---

## 6. `std::pair` a `struct`

```cpp
std::pair<std::string, std::string> p{"kocka", "cat"};
p.first;  p.second;

struct Place { std::string name; double lat; double lon; };
Place x{"Brno", 49.20, 16.61};
```
`pair` na 2 hodnoty, `struct` od 3 hodnot nebo když chceš čitelná jména.

---

## 7. Algoritmy – `<algorithm>`, `<numeric>`

Detail lambd viz [01_lambda.md](01_lambda.md).

| Funkce | Co dělá | Include |
|---|---|---|
| `std::min(a, b)`, `std::max(a, b)` | menší / větší | `<algorithm>` |
| `std::sort(b, e, cmp)` | seřadí | `<algorithm>` |
| `std::count_if(b, e, pred)` | kolik splňuje | `<algorithm>` |
| `std::find_if(b, e, pred)` | první, co splňuje (iterátor) | `<algorithm>` |
| `std::copy_if(b, e, std::back_inserter(out), pred)` | vybere do nového vektoru | `<algorithm>`, `<iterator>` |
| `std::max_element(b, e, cmp)` | největší (iterátor) | `<algorithm>` |
| `std::remove_if` + `erase` | starý způsob mazání | `<algorithm>` |
| `std::accumulate(b, e, 0.0, f)` | součet | `<numeric>` |

`b, e` = `v.begin(), v.end()`.

**C++20 `ranges`** – bez `begin/end` a s **projekcí** (porovnej podle členu):
```cpp
std::ranges::sort(v, std::greater{}, &Measurement::temp);          // sestupně podle temp
auto it = std::ranges::max_element(v, {}, &Measurement::humidity); // nejvlhčí
```

**Průměr:**
```cpp
if (!v.empty()) {
    double avg = std::accumulate(v.begin(), v.end(), 0.0,
        [](double s, const Place& p) { return s + p.lat; }) / v.size();
}
```

---

## 8. Formátovaný výpis – `<iomanip>`

```cpp
std::cout << std::fixed << std::setprecision(1);     // TRVALE: 1 desetinné místo
std::cout << std::left  << std::setw(12) << name     // setw jen pro DALŠÍ výstup
          << std::right << std::setw(8)  << temp << '\n';
```
| | |
|---|---|
| `setw(n)` | šířka sloupce, platí **jen pro jednu** hodnotu |
| `left` / `right` | zarovnání, platí trvale |
| `fixed` + `setprecision(n)` | přesně `n` desetinných míst (bez `fixed` = `n` platných číslic) |

Diakritika rozhodí `setw` (počítá bajty).

---

## 9. Vstup od uživatele – `<iostream>`

| Kód | Kdy |
|---|---|
| `std::cin >> a >> b;` | čísla oddělená mezerou |
| `std::getline(std::cin, line);` | celý řádek (text, `quit`) |
| `if (!std::cin)` | `cin >>` selhal (zadána písmena) |
| `std::cin.ignore();` | **po `cin >>`, před `getline`**, jinak `getline` přečte prázdný Enter |

Nejbezpečnější: **všude `getline`** a číslo převést přes `stoi`/`stod` v `try/catch`.

---

## 10. Náhoda – `<random>`

```cpp
static std::mt19937 gen(std::random_device{}());               // static = seed jen jednou
std::uniform_int_distribution<size_t> dist(0, v.size() - 1);   // obě meze VČETNĚ
size_t i = dist(gen);
```
Na prázdném vektoru `v.size() - 1` přeteče → nejdřív `if (v.empty())`.

---

## 11. Třídy – co se opakovalo

```cpp
class Rectangle {
private:
    double m_min;                                     // m_ = člen třídy
public:
    Rectangle(double a, double b)
        : m_min(std::min(a, b)) {}                    // inicializační seznam
    bool contains(const Place& p) const;              // const = nemění objekt
    static void helper();                             // static = volá se Rectangle::helper()
    double getMin() const { return m_min; }           // getter rovnou v .h
};
```
| | |
|---|---|
| `const T&` parametr | předání bez kopie, funkce ho nezmění |
| `T&` parametr | funkce **mění** proměnnou volajícího (`play(int& attempts)`) |
| `#ifndef X_H / #define X_H / #endif` | include guard v každém `.h` |
| `.h` | deklarace (co třída umí), `.cpp` = těla metod `Trida::metoda` |

**Vzor všech zadání:** třída na **soubor** + třída na **pravidlo** + `main` jako lepidlo.

---

## 12. Univerzální kostra načítání (umět zpaměti)

```cpp
std::ifstream file(path);
if (!file) { std::cerr << "Nejde otevrit " << path << '\n'; return; }

std::string line;
while (std::getline(file, line)) {
    while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
    if (line.empty()) continue;

    std::istringstream ss(line);
    std::string a, b, c;
    if (!std::getline(ss, a, ';') || !std::getline(ss, b, ';') || !std::getline(ss, c)) {
        ++m_invalid;
        continue;
    }
    try {
        m_items.push_back({a, std::stod(b), std::stod(c)});
    } catch (const std::exception&) {
        ++m_invalid;
    }
}
```
Mění se jen: **počet `getline`**, **`stod`/`stoi`** a **název structu**.

---

## Includy na jednom místě

| Include | Pro |
|---|---|
| `<iostream>` | `cout`, `cin`, `cerr` |
| `<fstream>` | `ifstream`, `ofstream` |
| `<sstream>` | `istringstream` |
| `<string>` | `string`, `getline`, `stoi`, `stod`, `to_string` |
| `<vector>` | `vector`, `erase_if` |
| `<utility>` | `pair` |
| `<algorithm>` | `min`, `max`, `sort`, `count_if`, `find_if`, `copy_if`, `max_element`, `ranges::…` |
| `<numeric>` | `accumulate` |
| `<iterator>` | `back_inserter` |
| `<iomanip>` | `setw`, `setprecision`, `fixed`, `left`, `right` |
| `<cctype>` | `tolower`, `isalpha`, `isdigit` |
| `<random>` | `mt19937`, `uniform_int_distribution` |
