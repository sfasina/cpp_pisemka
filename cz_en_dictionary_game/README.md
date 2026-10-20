# Slovníková hra CZ → EN – průvodce

Program načte dvojice slov ze souboru, ukáže české slovo a místo anglického podtržítka.
Hráč hádá písmena, každé trefené se odkryje. Prohraná slova se ukládají do `wrong_words.txt`.

## Jak spustit a hrát

1. V CLionu otevři složku `cz_en_dictionary_game` a dej Run. `words.txt` se při sestavení
   sám zkopíruje do `cmake-build-debug`, odkud se program spouští.
2. Zadej počet pokusů (= kolik **netref** smíš mít na jedno slovo) a počet slov.
3. Hádej písmena. Velikost nehraje roli, z delšího vstupu se bere jen první znak.
4. **Prohra** = dojdou pokusy → slovo se zapíše do `cmake-build-debug/wrong_words.txt`.
5. **Konec** = napiš `quit` (samotné `q` je normální písmeno). Rozehrané slovo se neuloží.

## Rozdělení do tříd

| Soubor | Zodpovědnost | Ví o |
|---|---|---|
| `FileManager.h/.cpp` | načíst `words.txt`, dát náhodné slovo, uložit špatné slovo | jen o souborech |
| `Game.h/.cpp` | jedno slovo: podtržítka, hádání, pokusy | jen o jednom slově |
| `main.cpp` | propojení: nastavení, smyčka přes slova, skóre, ukládání | o obou třídách |

**`FileManager` a `Game` o sobě navzájem nevědí.** `Game` dostane jen `std::pair` se slovem,
odkud pochází, ji nezajímá. Díky tomu jde každá třída změnit nebo otestovat zvlášť – třeba
slova brát z jiného souboru nebo z klávesnice a `Game` se vůbec nemění.

## Tok programu (dvě smyčky v sobě)

```
main
 ├─ fm.loadWords("words.txt")
 ├─ Game::loadAndCheckInput(attempts)        ← nastavení jen jednou
 ├─ Game::loadAndCheckInput(numberOfWords)
 │
 ├─ for (každé slovo)                       ← VNĚJŠÍ smyčka (main)
 │    ├─ word = fm.getRandomWord()
 │    ├─ Game game(word, attempts)
 │    ├─ game.play()
 │    │    └─ while (pokusy > 0 && neuhodnuto) ← VNITŘNÍ smyčka (Game)
 │    │         ├─ printState()
 │    │         ├─ getline → "quit"? → konec
 │    │         └─ revealLetter() → netrefa? → --pokusy
 │    ├─ quit?   → break
 │    ├─ výhra?  → ++score
 │    └─ prohra? → fm.saveWords(word, "wrong_words.txt")
 │
 └─ vypiš skóre
```

## Klíčové věci v kódu

**Načtení souboru** (`loadWords`) – stejný vzor jako u každého `;` formátu:
```cpp
std::ifstream file(path);
if (!file) { /* chyba */ return; }
while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::getline(ss, czech, ';');   // do středníku
    std::getline(ss, english);      // zbytek řádku
}
```

**Náhodné slovo bez opakování** (`getRandomWord`) – vybere index, zkopíruje prvek a pak
ho smaže přes `erase(begin() + index)`. Generátor je `static`, aby se seedoval jen jednou.

**Podtržítka** (`parsePairInWords`) – `std::string(n, '_')` vytvoří `n` podtržítek. Znaky,
které nejsou písmena (mezera v „ice cream“), se rovnou odkryjí.

**Hádání** (`revealLetter`) – projde **celé** slovo a odkryje všechny výskyty písmena
(`book` → obě `o`). Vrací `bool`, jestli se trefil – podle toho `play()` ubírá pokus.

**Quit vs. prohra** – `play()` vrací jen `true`/`false`. Aby `main` poznal, jestli hráč
prohrál nebo skončil, `Game` si uloží `m_quit` a `main` se zeptá přes `hasQuit()`.

**`static` metoda** – `loadAndCheckInput` se volá jako `Game::loadAndCheckInput(...)`
bez objektu, protože nastavení se čte dřív, než první `Game` vznikne.

**Ukládání** (`saveWords`) – `std::ofstream(path, std::ios::app)` přidává na konec.
Bez `app` se soubor při každém otevření vymaže.

## Časté chyby

- `Unable to open load file` → `words.txt` není ve složce, odkud se program spouští.
  Sestav projekt znovu (zkopíruje se), nebo nastav *Working directory* v Run Configuration.
- `getRandomWord()` na prázdném vektoru → `size() - 1` přeteče. Vždy nejdřív `hasWords()`.
- `isalpha`/`tolower` s `char` z diakritiky → nedefinované chování, proto `static_cast<unsigned char>`.
- Písmeno, které už je odkryté, se bere jako zásah – pokus neubere a nic se nevypíše.
- Neplatné číslo na začátku (`abc`) → `0` → hra hned skončí se `Score: 0/0`.
- `cin >> c` místo `getline` → `quit` by se četlo po písmenech a nikdy by nefungovalo.

## Formát souborů

`words.txt` i `wrong_words.txt` mají stejný formát, takže špatná slova jde znovu procvičit
přes `fm.loadWords("wrong_words.txt")`:

```
kocka;cat
zmrzlina;ice cream
```
