# Template (šablony) v C++

Template = **jedna funkce (nebo třída) pro víc typů**. Napíšeš ji jednou s „zástupným“ typem `T`
a compiler si sám vyrobí verzi pro `int`, `double`, `string`… podle toho, s čím ji zavoláš.

---

## 1. Proč

Bez šablony:
```cpp
int    biggest(int a, int b)       { return a > b ? a : b; }
double biggest(double a, double b) { return a > b ? a : b; }
// ... a pro string znovu
```
Se šablonou:
```cpp
template <typename T>
T biggest(T a, T b) {
    return a > b ? a : b;
}

biggest(3, 7);                      // T = int    → 7
biggest(2.5, 1.0);                  // T = double → 2.5
biggest(std::string("a"), std::string("b"));   // T = string → "b"
```

---

## 2. Syntaxe

```cpp
template <typename T>        // "T je nějaký typ" (místo typename jde psát i class – je to totéž)
T funkce(T parametr) { ... } // T používáš jako normální typ
```

| Volání | Co se stane |
|---|---|
| `biggest(3, 7)` | compiler **odvodí** `T = int` z argumentů |
| `biggest<double>(3, 7.5)` | `T` zadáš **ručně** (nutné, když se typy argumentů liší) |
| `readNumber<int>("Zadej:")` | ručně, protože `T` není v parametrech, jen v návratovém typu |

---

## 3. Příklady, které se hodí

### Vypsat libovolný vektor
```cpp
template <typename T>
void printVector(const std::vector<T>& v) {
    for (const auto& x : v) std::cout << x << ' ';
    std::cout << '\n';
}

printVector(std::vector<int>{1, 2, 3});
printVector(std::vector<std::string>{"pes", "kocka"});
```

### Načíst číslo od uživatele (z `zadani2_mereni/Input.h`)
```cpp
template <typename T>
T readNumber(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return T{};   // T{} = "nula" daného typu

        std::istringstream ss(line);
        T value;
        char extra;
        if (ss >> value && !(ss >> extra)) return value; // číslo a nic za ním
        std::cout << "Neplatne cislo.\n";
    }
}

int    n = readNumber<int>("Pocet: ");
double t = readNumber<double>("Teplota: ");
```

### Je hodnota v rozsahu (min/max v libovolném pořadí)
```cpp
template <typename T>
bool inRange(T value, T a, T b) {
    return value >= std::min(a, b) && value <= std::max(a, b);
}

inRange(21.5, 25.0, 18.0);   // true
inRange(63, 50, 75);         // true
```

### Dva různé typy
```cpp
template <typename K, typename V>
void printPair(const std::pair<K, V>& p) {
    std::cout << p.first << " = " << p.second << '\n';
}

printPair(std::pair<std::string, std::string>{"kocka", "cat"});
printPair(std::pair<std::string, int>{"Brno", 63});
```

---

## 4. Template třída

Stejný princip, `T` platí pro celou třídu:

```cpp
template <typename T>
class Box {
private:
    T m_value;

public:
    explicit Box(T value) : m_value(value) {}
    T get() const { return m_value; }
};

Box<int> a(5);               // u třídy typ píšeš do < >
Box<std::string> b("ahoj");
std::cout << a.get() << ' ' << b.get();
```

`std::vector<int>`, `std::pair<A, B>` – to všechno jsou template třídy ze standardní knihovny.

---

## 5. Kam šablonu napsat

**Celou do headeru (`.h`), i s tělem.** Ne do `.cpp`.

Proč: compiler vyrábí verzi pro konkrétní typ až ve chvíli, kdy šablonu použiješ.
V tu chvíli musí vidět **celé tělo**. Když je tělo v `.cpp`, linker hlásí
`undefined reference to 'readNumber<int>'`.

```
Input.h       ← template <typename T> T readNumber(...) { ...celé tělo... }
main.cpp      ← #include "Input.h"  a  readNumber<int>(...)
```

---

## 6. Pasti

- **Různé typy argumentů:** `biggest(1, 2.5)` → chyba, `T` nemůže být zároveň `int` i `double`.
  Řešení: `biggest<double>(1, 2.5)`.
- **Typ musí umět, co s ním děláš:** `biggest` používá `>`, `printVector` používá `<<`.
  Pro vlastní `struct` bez `operator>` / `operator<<` to nepřeloží.
- **`T` jen v návratovém typu** → compiler ho neodvodí, piš `readNumber<int>(...)`.
- **Tělo v `.cpp`** → `undefined reference`. Šablona patří do `.h`.
- **Řetězce:** `biggest("a", "b")` porovná **adresy** (`const char*`), ne text.
  Piš `std::string("a")` nebo `biggest<std::string>("a", "b")`.

---

## 7. Bonus: `auto` v parametru (C++20)

Krátký zápis šablony – compiler z toho udělá `template` sám:
```cpp
void printAll(const auto& v) {
    for (const auto& x : v) std::cout << x << ' ';
}
```
Funguje stejně jako `template <typename T> void printAll(const T& v)`.
Na písemku ale radši klasický `template <typename T>`, ten učitel pozná na první pohled.
