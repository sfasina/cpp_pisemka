# Lambda funkce v C++

Lambda = **funkce bez jména, napsaná přímo na místě**, kde ji potřebuješ.
Skoro vždy ji předáváš do algoritmu (`count_if`, `sort`, `find_if`…), aby věděl, *co* má dělat.

---

## 1. Syntaxe

```cpp
[zachyceni](parametry) { telo }
```

```cpp
auto plus = [](int a, int b) { return a + b; };
std::cout << plus(2, 3);   // 5
```

| Část | Co to je | Příklad |
|---|---|---|
| `[ ]` | jaké proměnné **zvenku** lambda vidí | `[]`, `[&range]` |
| `( )` | parametry, stejně jako u funkce | `(const Place& p)` |
| `{ }` | tělo, `return` vrací výsledek | `{ return p.lat > 50; }` |
| `auto` | typ lambdy se nedá napsat, proto `auto` | `auto f = ...;` |

Návratový typ si compiler odvodí z `return` sám. Psát ho (`-> bool`) skoro nikdy nemusíš.

---

## 2. Zachytávání `[ ]` – nejdůležitější část

Lambda **nevidí** lokální proměnné okolo, pokud je nezachytíš.

```cpp
double limit = 20.0;
auto hot = [](const Measurement& m) { return m.temp > limit; };        // CHYBA: limit nevidí
auto hot = [limit](const Measurement& m) { return m.temp > limit; };   // OK
```

| Zápis | Význam | Kdy použít |
|---|---|---|
| `[]` | nic | lambda pracuje jen se svými parametry (`sort` komparátor) |
| `[x]` | **kopie** `x` | malé hodnoty (`int`, `double`) |
| `[&x]` | **reference** na `x` | objekty (`Range`, `Rectangle`, `string`), nic se nekopíruje |
| `[=]` | všechno použité kopií | rychlé, ale nevidíš, co se zachytilo |
| `[&]` | všechno použité referencí | totéž |
| `[this]` | členy třídy (`m_range`…) | lambda uvnitř metody třídy |
| `[a, &b]` | kombinace | `a` kopií, `b` referencí |

**Pravidlo na písemku:** čísla `[x]`, objekty `[&x]`. Když nevíš, `[&]`.

---

## 3. Lambda + algoritmy (99 % použití)

Všechny příklady pracují s `std::vector<Place> places` a `Rectangle rect` (viz `zadani3_mista`).

### Spočítat – `count_if`
```cpp
int inside = std::count_if(places.begin(), places.end(),
    [&rect](const Place& p) { return rect.contains(p); });
```
Lambda vrací `bool`: `true` = počítej.

### Najít první – `find_if`
```cpp
auto it = std::find_if(places.begin(), places.end(),
    [](const Place& p) { return p.name == "Brno"; });
if (it != places.end()) std::cout << it->lat;   // vždy kontroluj end()!
```

### Seřadit – `sort`
```cpp
std::sort(places.begin(), places.end(),
    [](const Place& a, const Place& b) { return a.lat > b.lat; });   // od nejsevernějšího
```
Lambda dostane **dva** prvky a vrací `true`, když `a` má být **před** `b`.
`<` = vzestupně, `>` = sestupně. **Nikdy `<=`** (sort pak může spadnout).

### Vybrat do nového vektoru – `copy_if`
```cpp
std::vector<Place> inside;
std::copy_if(places.begin(), places.end(), std::back_inserter(inside),
    [&rect](const Place& p) { return rect.contains(p); });
```

### Smazat – `erase_if` (C++20)
```cpp
std::erase_if(places, [&rect](const Place& p) { return !rect.contains(p); });   // smaže ty MIMO
```

### Sečíst – `accumulate`
```cpp
double sum = std::accumulate(places.begin(), places.end(), 0.0,
    [](double acc, const Place& p) { return acc + p.lat; });
```
Lambda dostane **mezisoučet** a prvek, vrací nový mezisoučet. Start `0.0`, ne `0`!

### Největší / nejmenší – `max_element`
```cpp
auto it = std::max_element(places.begin(), places.end(),
    [](const Place& a, const Place& b) { return a.lat < b.lat; });   // i pro MAX se píše <
std::cout << it->name;
```

### Projít a něco udělat – `for_each`
```cpp
std::for_each(places.begin(), places.end(),
    [](const Place& p) { std::cout << p.name << '\n'; });
```
(stejné jako `for (const auto& p : places)`, ten je čitelnější)

---

## 4. Jaký tvar má lambda pro který algoritmus

| Algoritmus | Parametry lambdy | Vrací |
|---|---|---|
| `count_if`, `find_if`, `copy_if`, `erase_if`, `remove_if` | `(const T& x)` | `bool` |
| `sort`, `max_element`, `min_element` | `(const T& a, const T& b)` | `bool` (`a` před `b` / `a < b`) |
| `accumulate` | `(Vysledek acc, const T& x)` | nový `acc` |
| `for_each` | `(const T& x)` | nic |

---

## 5. Lambda uvnitř metody třídy

Člen třídy (`m_range`) nejde zachytit jménem. Dvě možnosti:

```cpp
long Analyzer::countInside() const {
    // a) zachytit this
    return std::count_if(m_data.begin(), m_data.end(),
        [this](const Measurement& m) { return m_range.contains(m); });

    // b) lokální reference (tak je to v zadani2_mereni)
    const Range& range = m_range;
    return std::count_if(m_data.begin(), m_data.end(),
        [&range](const Measurement& m) { return range.contains(m); });
}
```

---

## 6. Pasti

- **Zapomenutý `[&x]`** → chyba `'x' is not captured`.
- **`const T&` v parametru**, ne `T`, jinak se každý prvek kopíruje.
- **`sort` s `<=`** → nedefinované chování.
- **`find_if` / `max_element` vrací iterátor** → `*it` nebo `it->`, a nejdřív `it != end()`.
- **`accumulate` s `0`** místo `0.0` → sčítá se v `int`, desetinná místa zmizí.
- **Středník** za lambdou uloženou do proměnné: `auto f = [](){ ... };` ← tady.
