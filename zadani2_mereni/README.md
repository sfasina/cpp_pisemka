# Zadání 2: Měřicí stanice – průvodce k písemce

Soubor `mereni.txt` má řádky `stanice;teplota;vlhkost` (např. `Brno;21.5;63`).
Program je načte, zeptá se na rozsah, spočítá statistiky a uloží výběr do `vyber.txt`.

## Jak spustit

V CLionu se po načtení CMake objeví nová konfigurace **`mereni`** (vedle `cpp2practise`).
Vyber ji nahoře v liště a dej Run. `mereni.txt` se při sestavení sám zkopíruje do
`cmake-build-debug`, protože program se spouští odtud a relativní cesta `"mereni.txt"` se
hledá v pracovní složce, ne vedle `.cpp`. Pokud soubor změníš, sestav projekt znovu
(nebo v Run Configuration nastav *Working directory* na `zadani2_mereni`).

## Rozdělení do souborů

| Soubor | Co dělá | Krok |
|---|---|---|
| `Measurement.h` | `struct Measurement` – jen data, bez logiky | 1 |
| `MeasurementFile.h/.cpp` | načtení a uložení souboru, počítání vadných řádků | 1, 6 |
| `Range.h/.cpp` | meze od uživatele, `contains()` = „je měření uvnitř?“ | 2 |
| `Analyzer.h/.cpp` | všechny výpočty (`count_if`, `sort`, `accumulate`, `max_element`, `erase_if`) | 3–6 |
| `Input.h` | šablona `readNumber<T>()` – bezpečné načtení čísla od uživatele | 2 |
| `main.cpp` | jen „lepidlo“: volá ostatní třídy a vypisuje tabulku | vše |

**Proč takhle:** každá třída má jednu zodpovědnost. `Range` ví, co je „uvnitř“, takže
podmínka je napsaná **jednou** a všechny lambdy jen volají `range.contains(m)`. Kdyby se
podmínka změnila (třeba `<` místo `<=`), měníš jedno místo.

**Na písemce s časovým limitem** klidně napiš všechno do jednoho `main.cpp` – struct
nahoře, pak funkce `bool parseLine(...)`, `bool contains(...)` a zbytek v `main`. Logika je
úplně stejná, jen bez tříd.

---

## Krok 1: struct a načtení souboru

```cpp
struct Measurement {
    std::string station;
    double temp;
    int humidity;
};
```

Rozdělení řádku (`MeasurementFile::parseLine`):

```cpp
std::istringstream ss(line);
std::string station, tempStr, humidityStr;
std::getline(ss, station, ';');      // čte do středníku, středník zahodí
std::getline(ss, tempStr, ';');
std::getline(ss, humidityStr, ';');  // poslední pole – čte do konce řádku
```

Převod na čísla v `try/catch`:

```cpp
try {
    size_t pos = 0;
    double temp = std::stod(tempStr, &pos);
    if (pos != tempStr.size()) return false;   // "21,5" -> stod přečte jen "21"!
    int humidity = std::stoi(humidityStr, &pos);
    if (pos != humidityStr.size()) return false;
} catch (const std::exception&) {   // invalid_argument i out_of_range
    return false;
}
```

**Pozor:** `stod("21,5")` nevyhodí výjimku – vrátí `21` a zbytek ignoruje. Proto kontrola
`pos`. Bez ní by řádek s desetinnou čárkou prošel se špatnou hodnotou.

Co je v `mereni.txt` schválně špatně (5 vadných řádků):

| Řádek | Proč je vadný |
|---|---|
| `Plzen;22.1` | chybí vlhkost |
| `Liberec;19,5;70` | desetinná čárka místo tečky |
| `Zlin;23.4;55;navic` | pole navíc |
| `Opava;abc;50` | teplota není číslo → `invalid_argument` |
| `Usti;17.9;sedmdesat` | vlhkost není číslo |

Prázdný řádek se přeskočí, ale **nepočítá** se jako vadný (to je volba – na písemce řekni, jak to máš).

## Krok 2: meze v libovolném pořadí

```cpp
Range::Range(double temp1, double temp2, int humidity1, int humidity2)
    : m_minTemp(std::min(temp1, temp2)),
      m_maxTemp(std::max(temp1, temp2)), ... {}
```

Uživatel zadá `25` a `18` → `min = 18`, `max = 25`. Nemusíš nic prohazovat ručně.

Načtení čísla od uživatele (`Input.h`) – šablona, takže funguje pro `int` i `double`:

```cpp
double t = readNumber<double>("Prvni mez teploty: ");
int h = readNumber<int>("Prvni mez vlhkosti: ");
```

Šablona musí být **celá v headeru** – compiler potřebuje vidět tělo funkce, aby ji mohl
vygenerovat pro konkrétní typ.

## Krok 3: `count_if` s lambdou

```cpp
long inside = std::count_if(v.begin(), v.end(),
    [&range](const Measurement& m) { return range.contains(m); });
long outside = v.size() - inside;   // nebo count_if s !range.contains(m)
```

### Zachytávání v lambdě `[ ]`

| Zápis | Význam |
|---|---|
| `[]` | nic nezachytává |
| `[x]` | kopie `x` |
| `[&x]` | reference na `x` (bez kopírování, vidí změny) |
| `[=]` | všechno použité kopií |
| `[&]` | všechno použité referencí |
| `[this]` | členy třídy (`m_range`) uvnitř metody |

Kdyby zadání chtělo zachytit přímo čtyři čísla místo objektu:

```cpp
[minT, maxT, minH, maxH](const Measurement& m) {
    return m.temp >= minT && m.temp <= maxT && m.humidity >= minH && m.humidity <= maxH;
}
```

## Krok 4: seřazení a výpis do sloupců

```cpp
std::copy_if(v.begin(), v.end(), std::back_inserter(inside), lambda);   // vyber
std::sort(inside.begin(), inside.end(),
    [](const Measurement& a, const Measurement& b) { return a.temp > b.temp; });
```

Komparátor vrací `true`, když `a` má být **před** `b`. `>` = sestupně (od nejteplejšího),
`<` = vzestupně. C++20 varianta s projekcí:
`std::ranges::sort(inside, std::greater{}, &Measurement::temp);`

Formátování (`#include <iomanip>`):

```cpp
std::cout << std::fixed << std::setprecision(1);           // platí TRVALE
std::cout << std::left << std::setw(12) << m.station       // setw platí jen pro DALŠÍ výstup
          << std::right << std::setw(10) << m.temp << '\n';
```

- `fixed` + `setprecision(1)` = přesně 1 desetinné místo (`20` → `20.0`). Bez `fixed`
  znamená `setprecision` počet *platných číslic* celkem.
- `setw` se musí psát před **každou** hodnotu znovu.
- Diakritika (`Plzeň`) rozhodí zarovnání, protože `setw` počítá bajty a `ň` má v UTF-8 dva.

## Krok 5: průměr a maximum

```cpp
double sum = std::accumulate(v.begin(), v.end(), 0.0,      // #include <numeric>
    [](double acc, const Measurement& m) { return acc + m.temp; });
double avg = sum / v.size();
```

**Nejčastější chyba:** `0` místo `0.0` → výsledek se počítá v `int` a desetinná místa se ztratí.
**Druhá nejčastější:** prázdný vektor → dělení nulou. Vždy nejdřív `if (v.empty())`.

```cpp
auto it = std::ranges::max_element(v, {}, &Measurement::humidity);   // projekce
Measurement best = *it;
```

- **Projekce** `&Measurement::humidity` = „porovnávej podle tohoto členu“. `{}` = výchozí
  porovnání (`std::less`).
- `max_element` vrací **iterátor**, hodnotu získáš přes `*it`. U prázdného vektoru vrátí
  `end()` a `*it` je pád → zase nejdřív `empty()`.
- Bez projekce (klasická verze):
  `std::max_element(v.begin(), v.end(), [](auto& a, auto& b) { return a.humidity < b.humidity; });`
  Pozor, i pro **max** se píše `<`.

## Krok 6 (bonus): `erase_if` a uložení

```cpp
size_t removed = std::erase_if(v, [&range](const Measurement& m) { return !range.contains(m); });
```

C++20, vrací počet smazaných. Starý zápis (erase-remove idiom), který můžeš potkat:
`v.erase(std::remove_if(v.begin(), v.end(), lambda), v.end());`

Uložení: `std::ofstream file("vyber.txt");` soubor **přepíše**, pro přidávání na konec
`std::ofstream file("vyber.txt", std::ios::app);`. Ukládej ve stejném formátu, v jakém
načítáš (`;` jako oddělovač), ať jde výstup znovu načíst.

---

## Očekávaný výstup

Vstup: teplota `25` a `18`, vlhkost `75` a `50`:

```
Nacteno mereni: 10, vadnych radku: 5
Uvnitr rozsahu: 5, mimo rozsah: 5

Stanice        Teplota   Vlhkost
--------------------------------
Hradec            22.6        66
Brno              21.5        63
Tabor             21.0        58
Pardubice         20.0        60
Praha             18.2        71

Prumerna teplota uvnitr: 20.7
Nejvlhci mereni: Praha (71 %)
Odstraneno mereni mimo rozsah: 5
```

## Includy – co kam patří

| Header | Co z něj potřebuješ |
|---|---|
| `<fstream>` | `ifstream`, `ofstream` |
| `<sstream>` | `istringstream` |
| `<string>` | `string`, `getline`, `stod`, `stoi` |
| `<iomanip>` | `setw`, `setprecision`, `fixed`, `left`, `right` |
| `<algorithm>` | `min`, `max`, `count_if`, `copy_if`, `sort`, `max_element`, `ranges::…` |
| `<numeric>` | `accumulate` |
| `<vector>` | `vector`, `erase_if` (C++20) |
| `<iterator>` | `back_inserter` |

## Checklist před odevzdáním

- [ ] `if (!file)` po otevření souboru + `return`
- [ ] odstranění `'\r'` z konce řádku (soubory z Windows)
- [ ] `stod`/`stoi` v `try/catch` + kontrola `pos`
- [ ] vadné řádky se počítají, ne jen přeskakují
- [ ] meze přes `std::min`/`std::max`
- [ ] `accumulate` s `0.0`
- [ ] `empty()` před průměrem a `max_element`
- [ ] `fixed` před `setprecision`
- [ ] `CMAKE_CXX_STANDARD 20` kvůli `erase_if` a `ranges`
