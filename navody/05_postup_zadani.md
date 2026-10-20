# Jak projít zadání na písemce

## 1. Přečti a odpověz na 4 otázky (5 min)

| Otázka | Oběšenec | Místa v obdélníku |
|---|---|---|
| **Co je na řádku souboru?** | `slovo` | `jmeno;sirka;delka` |
| **Co zadá uživatel?** | číslo 1–N, pak písmena | 2 rohy = 4 čísla |
| **Jaké je pravidlo?** | písmeno ve slově → odkryj | bod mezi mezemi → uvnitř |
| **Co vypsat?** | `_ o _ _`, výhra/prohra | kolik uvnitř / mimo |

Odpovědi = rovnou struktura programu.

## 2. Rozděl do tříd (vždy stejně)

```
struct Polozka      ← 1 řádek souboru (pole z otázky 1)
class  XxxFile      ← načte soubor do vector<Polozka>, počítá vadné řádky
class  Pravidlo     ← konstruktor (vstup uživatele) + contains() / play()
main                ← propojí: načti → zeptej se → smyčka → vypiš
```
`XxxFile` a `Pravidlo` o sobě **nevědí**. Jen `main` zná obě.

## 3. Pořadí psaní (kompiluj po každém kroku)

1. `struct` + prázdné třídy + `main` → **kompiluj**
2. Načítání → v `main` vypiš, co se načetlo → **kompiluj a spusť**
3. Pravidlo (`contains` / `play`)
4. Smyčka v `main` + výstup
5. „atp.“ – co zbylo ze zadání
6. Zkus vadný vstup

## 4. Slovo v zadání → co napsat

| Zadání říká | Napíšeš |
|---|---|
| „načti ze souboru“ | `ifstream` + `while (getline)` |
| „na řádku je X a Y“ | `istringstream` + `getline(ss, x, ';')` |
| „číslo“ | `stoi` / `stod` v `try/catch` |
| „uživatel zadá rozsah / obdélník“ | `std::min` / `std::max` v konstruktoru |
| „kolik je uvnitř / mimo“ | `if (contains) ++in; else ++out;` nebo `count_if` |
| „vypiš ty, které…“ | `if` ve smyčce, nebo `copy_if` |
| „seřaď“ | `std::sort` + lambda |
| „nejvyšší / nejmenší“ | `std::max_element` / `min_element` |
| „průměr / součet“ | `std::accumulate(..., 0.0, ...)` |
| „vyber číslo 1 až N“ | kontrola `1 <= x <= v.size()`, pak `v[x - 1]` |
| „náhodně“ | `mt19937` + `uniform_int_distribution` |
| „má N pokusů“ | počítadlo, `--` jen při chybě |
| „dokud…“ | `while (podmínka)` |
| „ulož do souboru“ | `ofstream` (přepíše) / `ios::app` (přidá) |
| „smaž ty, které…“ | `std::erase_if` |

## 5. Co se může pokazit (ošetři)

| Situace | Řešení |
|---|---|
| soubor neexistuje | `if (!file)` → hláška + `return` |
| prázdný soubor | `if (v.empty())` před výběrem / průměrem / `max_element` |
| prázdný řádek, `\r` na konci | `pop_back()` + `continue` |
| málo polí na řádku | `getline` vrátí `false` → vadný řádek |
| text místo čísla | `catch` → vadný řádek |
| meze v obráceném pořadí | `min` / `max` |
| uživatel zadá písmena místo čísla | `getline` + `stoi` v `try/catch`, ptej se znovu |
| číslo mimo 1–N | ptej se znovu |
| velké písmeno | `tolower` |
| opakované písmeno | buď ignoruj, nebo `string used` + `find` |
| mezera ve slově (`ice cream`) | odkryj rovnou, `isalpha` |

## 6. Tréninková zadání (podle oběšence a obdélníku)

**Z obdélníku** – mění se jen struct a `contains()`:
1. **Body v kruhu** – `jmeno;x;y`, uživatel zadá střed a poloměr → `sqrt(dx*dx + dy*dy) <= r`.
2. **Studenti v rozsahu bodů** – `jmeno;body`, jen 1D: `body >= min && body <= max`.
3. **Produkty v cenovém rozpětí** – `nazev;cena;kusu`, + celková hodnota uvnitř (`cena * kusu`).
4. **Nejsevernější místo v obdélníku** – obdélník + `max_element` podle `lat` na vybraných.
5. **Místa na sever / jih od zadané šířky** – žádný obdélník, jen `p.lat > hranice`.

**Z oběšence** – mění se soubor nebo počítání pokusů:
6. **Oběšenec s nápovědou** – `slovo;napoveda`, rozděl přes `;` a nápovědu vypiš.
7. **Víc slov, společné pokusy** – `play(int& attempts)`, uhodnutá slova `erase` (viz `zadani4_obesenec/README.md`).
8. **Náhodné slovo** místo volby čísla – `getRandomWord()`.
9. **Slova podle délky** – uživatel zadá délku, nabídni jen slova s `size() == delka`.
10. **Statistika** – na konci vypiš počet chyb a ulož neuhodnutá slova do souboru (`ios::app`).

Pokud nevíš, začni tím, které zadání z 1–10 je nejpodobnější, a přepiš ho.
