# Zadání 4: Oběšenec

## Zadání

> Mám hru oběšenec. Načtu si ze zadaného souboru jednotlivá slova. Uživateli nabídnu, ať
> zvolí číslo 1 až N, kde N je počet načtených slov. Jakmile uživatel vybere číslo, zobrazím
> místo daného slova jen podtržítka `_ _ _ _` a nechám ho hádat písmena. Pokud zvolí dobře,
> tak ho zobrazím: `_ o _ _`. Má např. 5 pokusů. Vyhraje, pokud uhádne všechna slova,
> než vyčerpá pokusy.

„Všechna slova“ tu chápu jako **všechna písmena slova**, tedy jedno slovo na hru.

Soubor `slova.txt`: jedno slovo na řádek.

## Rozdělení (stejný vzor jako vždy)

| Soubor | Úloha |
|---|---|
| `WordFile` | načte slova do `vector<string>` |
| `Hangman` | hra s jedním slovem: podtržítka, hádání, pokusy |
| `main` | volba čísla 1–N, `words[choice - 1]`, spustí hru |

**Proti slovníkové hře** (`cz_en_dictionary_game`) je to skoro totéž:
- `WordFile` = `FileManager`, jen bez `;`, protože na řádku je jen jedno slovo.
- `Hangman` = `Game`, jen bez českého slova.
- Místo náhodného slova si ho hráč vybere číslem.

## Postup v 5 krocích

1. **`WordFile::loadWords`**: `getline` po řádcích, umazat `'\r'`, přeskočit prázdné a `push_back`. Řádek se tu **nedělí**.
2. **Volba čísla** (`readChoice` v `main`): `getline` + `stoi` v `try/catch`, opakovat, dokud `1 <= x <= N`.
3. **Index**: hráč počítá od 1, vektor od 0, takže `words[choice - 1]`.
4. **Konstruktor `Hangman`**: `m_guessWord(word.size(), '_')` vytvoří podtržítka.
5. **`play()`**: `while (pokusy > 0 && guess != word)` → načti písmeno → `revealLetter` → při netrefě `--pokusy`.

```cpp
// jádro hry - revealLetter (zjednodušeně, v kódu je navíc tolower kvůli velkým písmenům)
for (size_t i = 0; i < m_word.size(); ++i)
    if (m_word[i] == letter) { m_guessWord[i] = m_word[i]; hit = true; }   // odkryje VŠECHNY výskyty
```

## Pasti

- `words[choice]` místo `choice - 1` čte o jedno slovo vedle a u N je to mimo vektor.
- Prázdný soubor → N = 0 → nejdřív zkontroluj `words.empty()`.
- **Nemíchej `cin >>` a `getline`.** Po `cin >> choice` zůstane ve vstupu Enter a první
  `getline` v `play()` přečte prázdný řádek. Buď všude `getline` (jako tady), nebo
  po `cin >>` napiš `std::cin.ignore();`.
- `revealLetter` musí projít **celé** slovo, ne skončit u prvního nálezu (`kolo` → obě `o`).

## Kdyby zadání znělo jinak

| Varianta | Co změnit |
|---|---|
| Řádek `slovo;napoveda` | v `loadWords` přidat `istringstream` + `getline(ss, ..., ';')` jako u míst |
| Hádat **víc slov** se společnými pokusy | `m_attempts` přesunout do `main` a předávat `int&`, smyčku volby čísla dát do `while` |
| Opakované písmeno má stát pokus | `std::string m_used;` a když `m_used.find(letter) != std::string::npos`, je to netrefa |
| Náhodné slovo místo volby | `getRandomWord()` z `cz_en_dictionary_game/FileManager.cpp` |
