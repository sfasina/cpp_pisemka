# Zadání 3: Místa v obdélníku

## Zadání (od učitele)

> Samozřejmě nemusíme jen načítat prostá slova, ale sekvence, kde je na řádku např. místo
> a jeho zeměpisná šířka a délka ve stupních. Uživatel si zadá obdélník pomocí dvou
> souřadnic šířky a délky, já projdu seznam a vypočítám, kolik bodů ze souboru leží
> v daném obdélníku, kolik je jich mimo atp. Toto je ukázka zase toho, že vstup může být
> nutné nějak rozdělit.

Soubor `mista.txt`: `jmeno;sirka;delka`, např. `Brno;49.20;16.61`

---

## Tutoriál v 5 krocích

### 1. `struct` = jeden řádek souboru (`Place.h`)
```cpp
struct Place { std::string name; double lat; double lon; };
```
Kolik polí má řádek, tolik členů má struct.

### 2. Třída na soubor: načíst a rozdělit (`PlaceFile`)
```cpp
while (std::getline(file, line)) {          // čti řádek po řádku
    std::istringstream ss(line);            // z řádku udělej "mini soubor"
    std::getline(ss, name, ';');            // kus do středníku
    std::getline(ss, latStr, ';');
    std::getline(ss, lonStr);               // poslední kus = zbytek řádku
    try { lat = std::stod(latStr); ... }    // text → číslo
    catch (const std::exception&) { ++m_invalidLines; }   // "sever" → vadný řádek
}
```
**Tohle je jádro všech zadání.** Mění se jen počet `getline` a `stod`/`stoi`.

### 3. Třída na pravidlo: co je „uvnitř“ (`Rectangle`)
```cpp
Rectangle(lat1, lon1, lat2, lon2)
    : m_minLat(std::min(lat1, lat2)), m_maxLat(std::max(lat1, lat2)), ...   // pořadí rohů je jedno

bool contains(const Place& p) const {
    return p.lat >= m_minLat && p.lat <= m_maxLat     // šířka mezi
        && p.lon >= m_minLon && p.lon <= m_maxLon;    // A délka mezi
}
```

### 4. `main` = lepidlo
```cpp
PlaceFile file;  file.loadPlaces("mista.txt");
std::cin >> lat1 >> lon1 >> lat2 >> lon2;
Rectangle rect(lat1, lon1, lat2, lon2);
for (const auto& p : file.getPlaces())
    if (rect.contains(p)) ++inside; else ++outside;
```
`PlaceFile` a `Rectangle` o sobě nevědí, propojuje je jen `main`.

### 5. „atp.“ = další `if` ve stejné smyčce
Vypsat místa uvnitř, nejsevernější místo (`lat` největší), průměr… všechno se dělá ve
stejném `for` nebo přes `count_if`, `max_element` či `accumulate` (viz `zadani2_mereni`).

### Pasti
- V souboru je pořadí `šířka;délka`, nepřehoď ho při čtení ani v podmínce.
- Šířka = sever/jih (osa Y), délka = východ/západ (osa X).
- `stod("49,40")` vrátí 49 bez chyby. Pokud na tom záleží, použij kontrolu `pos` (viz `PlaceFile.cpp`).
- `'\r'` na konci řádku u souborů z Windows, takže `pop_back()`.
- Kompiluj po každém kroku.

---

## Univerzální vzor: co se mění a co ne

Všechna zadání mají **stejnou kostru**. Na písemce si nejdřív odpověz na 4 otázky:

| Otázka | Tady (místa) | Kde to měníš |
|---|---|---|
| Jaká pole má řádek? | `jmeno;sirka;delka` | `struct` + počet `getline` |
| Jaké typy? | `string`, `double`, `double` | `stod` / `stoi` |
| Co zadá uživatel? | 2 rohy = 4 čísla | konstruktor „pravidla“ |
| Kdy je to „uvnitř“? | šířka mezi **a** délka mezi | `contains()` |

Zbytek (otevření souboru, smyčka, `try/catch`, počítání vadných, `main`) je **pokaždé stejný**.

---

## Podobná zadání na trénink

### A) Studenti v intervalu bodů *(nejjednodušší)*
`studenti.txt`: `Novak;78;2` (jméno; body; ročník)
Uživatel zadá rozsah bodů. Vypiš, kolik studentů v něm je a kolik mimo, a jejich průměr.

| Proti místům | Změna |
|---|---|
| `struct` | `name`, `int points`, `int year` |
| rozdělení | 3× `getline`, 2× `stoi` místo `stod` |
| pravidlo | `PointRange` jen s **jednou** dvojicí `min`/`max` (1D místo 2D) |
| `contains` | `s.points >= m_min && s.points <= m_max` |

### B) Místa v kruhu *(nejbližší tomuhle zadání)*
Stejný `mista.txt`. Uživatel zadá střed (šířka, délka) a poloměr ve stupních.

| Proti místům | Změna |
|---|---|
| `struct`, `PlaceFile` | **beze změny**, použij přesně stejné |
| pravidlo | `Circle(lat, lon, radius)` místo `Rectangle` |
| `contains` | vzdálenost od středu: `std::sqrt(dLat*dLat + dLon*dLon) <= m_radius` (`<cmath>`) |

Tohle je nejlepší ukázka, proč dávají třídy smysl: vyměníš **jednu** třídu a zbytek zůstane.

### C) Produkty v cenovém rozpětí
`sklad.txt`: `Mleko;24.90;120` (název; cena; počet kusů)
Uživatel zadá dvě ceny. Spočítej produkty uvnitř a mimo a **celkovou hodnotu skladu**
uvnitř (`cena * kusy`).

| Proti místům | Změna |
|---|---|
| `struct` | `name`, `double price`, `int count` |
| rozdělení | `stod` + `stoi` (mix typů) |
| pravidlo | 1D rozsah jako u A |
| „atp.“ | v smyčce `total += p.price * p.count;` |

### D) Měřicí stanice *(už hotové v `zadani2_mereni`)*
`Brno;21.5;63`: rozsah teploty **a** vlhkosti. Je to přesně tohle zadání, jen se jinak
jmenují pole. `Range` = `Rectangle`, teplota = šířka, vlhkost = délka.

### E) Objekty na obrazovce
`objekty.txt`: `tlacitko;120;45` (název; x; y v pixelech)
Uživatel zadá výřez okna dvěma rohy. Kolik objektů je vidět?

| Proti místům | Změna |
|---|---|
| vše | **stejné**, jen `lat`/`lon` → `x`/`y` a `stoi` místo `stod` |

### F) Knihy podle roku *(dva textové sloupce)*
`knihy.txt`: `Babicka;Nemcova;1855` (název; autor; rok)
Uživatel zadá rozsah let. Vypiš knihy uvnitř seřazené podle roku.

| Proti místům | Změna |
|---|---|
| rozdělení | 3× `getline`, z toho 2 zůstanou `string`, 1× `stoi` |
| pravidlo | 1D rozsah let |
| „atp.“ | `std::sort` s lambdou `a.year < b.year` |

---

## Na písemce

1. Přečti zadání a odpověz na **4 otázky** z tabulky výše.
2. Napiš `struct` a hlavičky tříd, pak **zkompiluj**.
3. Napiš načítání a vypiš si načtená data, abys viděl, že sedí. To je **60 % práce**.
4. Napiš `contains()` a smyčku v `main`.
5. Pak „atp.“ a nakonec zkus vadné řádky.

Pokud se zasekneš, otevři si v hlavě to zadání z tréninku, které je nejpodobnější
(A–F), a jen přepiš názvy polí.
