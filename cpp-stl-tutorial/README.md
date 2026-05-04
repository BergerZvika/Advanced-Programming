# C++ STL — A Hands-on Lab for C Programmers

A 51-demo deep dive into the **Standard Template Library** (STL) — the part of the C++ standard library built around four interlocking pieces:

1. **Containers** — generic data structures (`vector`, `map`, `set`, `list`, …)
2. **Iterators** — uniform "pointer into a container" abstraction
3. **Algorithms** — free functions in `<algorithm>` and `<numeric>` that work on any iterator pair
4. **Functors** — objects you can call like a function; the customisation hook for almost every algorithm

C does not have anything like this — every project re-implements its own dynamic array, hash table, and sort. This lab walks you through the whole STL one piece at a time, in the now-familiar one-concept-per-file format.

For the basics that come BEFORE the STL (`std::string`, references, smart pointers, etc.) see [`../cpp-basics-tutorial/`](../cpp-basics-tutorial/).
For OOP (classes, inheritance, the Rule of 5, …) see [`../cpp-oop-tutorial/`](../cpp-oop-tutorial/).

---

## 📚 Reference & further reading

Keep these tabs open while you work through the lab:

- **[cppreference.com — Containers library](https://en.cppreference.com/w/cpp/container)** — every STL container with complexity guarantees and examples.
- **[cppreference.com — Iterators library](https://en.cppreference.com/w/cpp/iterator)** — iterator categories, helpers, common idioms.
- **[cppreference.com — Algorithms library](https://en.cppreference.com/w/cpp/algorithm)** — every `<algorithm>` function in one page.
- **[cppreference.com — Numerics library](https://en.cppreference.com/w/cpp/numeric)** — `<numeric>` accumulate / reduce / partial_sum / iota.
- [learncpp.com — The C++ STL](https://www.learncpp.com/cpp-tutorial/introduction-to-the-standard-template-library-stl/) — friendlier tutorial-style intro.
- [Hinnant's STL container choice flow chart](https://github.com/HowardHinnant/Howards-Drawings/blob/master/Containers.png) — picture-form decision tree.

---

## Table of Contents

1. [Lab Architecture](#1-lab-architecture)
2. [Setup](#2-setup)
3. [Picking the Right Container — Quick Guide](#3-picking-the-right-container--quick-guide)
4. [Step 1 — Sequence Containers](#4-step-1--sequence-containers)
5. [Step 2 — Ordered Associative Containers](#5-step-2--ordered-associative-containers)
6. [Step 3 — Hash-based Associative Containers](#6-step-3--hash-based-associative-containers)
7. [Step 4 — Tuple & Adapters](#7-step-4--tuple--adapters)
8. [Step 5 — Iterator Basics](#8-step-5--iterator-basics)
9. [Step 6 — Bidirectional Iterators](#9-step-6--bidirectional-iterators)
10. [Step 7 — Random Access Iterators](#10-step-7--random-access-iterators)
11. [Step 8 — Non-modifying Algorithms](#11-step-8--non-modifying-algorithms)
12. [Step 9 — Modifying Algorithms](#12-step-9--modifying-algorithms)
13. [Step 10 — Sorting & Searching](#13-step-10--sorting--searching)
14. [Step 11 — Removing & Partitioning](#14-step-11--removing--partitioning)
15. [Step 12 — Set Operations on Sorted Ranges](#15-step-12--set-operations-on-sorted-ranges)
16. [Step 13 — Numeric & Permutations](#16-step-13--numeric--permutations)
17. [Step 14 — Functors](#17-step-14--functors)
18. [STL Cheat Sheet](#18-stl-cheat-sheet)

---

## 1. Lab Architecture

```
cpp-stl-tutorial/
├── build.sh           # Compiles every step*/*.cpp into build/<basename>
├── run_all.sh         # Runs every compiled demo with a pause between each
├── README.md          # This file
├── index.html         # Single-page interactive lab (CodeMirror + per-demo output)
├── build/             # Created by build.sh (gitignored)
│
├── step1_sequence_containers/    ── ordered, indexable, in-line ──
│   ├── 01a_vector.cpp
│   ├── 01b_array.cpp
│   ├── 01c_deque.cpp
│   ├── 01d_list.cpp
│   └── 01e_forward_list.cpp
│
├── step2_ordered_associative/    ── red-black trees, sorted by key ──
│   ├── 02a_pair.cpp
│   ├── 02b_map.cpp
│   ├── 02c_set.cpp
│   └── 02d_multimap_multiset.cpp
│
├── step3_hash_associative/       ── hash tables, average O(1) ──
│   ├── 03a_unordered_basics.cpp
│   └── 03b_custom_hash.cpp
│
├── step4_adapters/               ── tuple + restricted-API wrappers ──
│   ├── 04a_tuple.cpp
│   ├── 04b_stack.cpp
│   ├── 04c_queue.cpp
│   └── 04d_priority_queue.cpp
│
├── step5_iterator_basics/        ── pointer-into-a-container ──
│   ├── 05a_iterator_basics.cpp
│   ├── 05b_iterator_categories.cpp
│   ├── 05c_reverse_const_iterators.cpp
│   ├── 05d_advance_distance.cpp
│   └── 05e_iterator_adapters.cpp
│
├── step6_bidirectional_iterators/ ── ++it AND --it ──
│   ├── 06a_bidi_basics.cpp
│   ├── 06b_bidi_in_associative.cpp
│   ├── 06c_algos_needing_bidi.cpp
│   └── 06d_bidi_limits.cpp
│
├── step7_random_access_iterators/ ── it+n, it[n], it1<it2 (O(1)) ──
│   ├── 07a_random_access_basics.cpp
│   ├── 07b_pointer_equivalence.cpp
│   ├── 07c_algos_needing_random.cpp
│   └── 07d_binary_search_complexity.cpp
│
├── step8_non_modifying_algos/    ── search & inspect ──
│   ├── 08a_find.cpp
│   ├── 08b_count_any_all_none.cpp
│   ├── 08c_equal_mismatch.cpp
│   └── 08d_min_max.cpp
│
├── step9_modifying_algos/        ── produce & rearrange ──
│   ├── 09a_copy_fill_generate_iota.cpp
│   ├── 09b_transform_for_each.cpp
│   ├── 09c_replace.cpp
│   └── 09d_reverse_rotate_shuffle.cpp
│
├── step10_sorting_searching/     ── sort + binary search ──
│   ├── 10a_sort.cpp
│   ├── 10b_partial_sort_nth_element.cpp
│   └── 10c_binary_search.cpp
│
├── step11_removing_partitioning/ ── shrink & split ──
│   ├── 11a_remove_erase.cpp
│   ├── 11b_unique.cpp
│   └── 11c_partition.cpp
│
├── step12_set_operations/        ── on sorted ranges ──
│   └── 12a_set_operations.cpp
│
├── step13_numeric_permutations/  ── <numeric> + permutations ──
│   ├── 13a_accumulate_reduce.cpp
│   ├── 13b_inner_product_partial_sum.cpp
│   └── 13c_permutations.cpp
│
└── step14_functors/              ── callable objects ──
    ├── 14a_functor_basics.cpp           class with operator()
    ├── 14b_stateful_functor.cpp         per-instance state across calls
    ├── 14c_predefined_functors.cpp      <functional> std::less, std::plus, …
    ├── 14d_lambdas_as_functors.cpp      lambda = anonymous functor class
    └── 14e_std_function.cpp             type-erased callable holder
```

Each `.cpp` file is a **single-concept**, self-contained program with its own `main()`. Total: **51** mini demos across 14 steps.

---

## 2. Setup

### Prerequisites

- g++ 7+ (or clang++ 5+) with C++17 support
- A POSIX shell (Linux, macOS, WSL)

### Build & run

```bash
chmod +x build.sh run_all.sh
./build.sh                 # compiles every step*/*.cpp
./run_all.sh               # runs all 51 with a pause between each

# or any single demo:
g++ -std=c++17 -Wall -Wextra -g -o build/01a_vector step1_sequence_containers/01a_vector.cpp
./build/01a_vector
```

### Open the interactive lab page

```bash
python3 -m http.server 8765
# http://127.0.0.1:8765/  in a browser
```

---

## 3. Picking the Right Container — Quick Guide

| Need | Container | Header |
|------|------|------|
| Dynamic, contiguous, indexable | **`std::vector`** (default choice) | `<vector>` |
| Fixed size known at compile time | `std::array<T, N>` | `<array>` |
| Fast push at BOTH ends | `std::deque` | `<deque>` |
| O(1) insert/erase given an iterator | `std::list` (rare in practice) | `<list>` |
| Single-link, smallest footprint | `std::forward_list` | `<forward_list>` |
| Ordered key→value | `std::map` | `<map>` |
| Ordered unique values | `std::set` | `<set>` |
| Same, with duplicates allowed | `std::multimap` / `std::multiset` | `<map>` / `<set>` |
| Fast lookup, no order | `std::unordered_map` / `std::unordered_set` | `<unordered_map>` / `<unordered_set>` |
| LIFO / FIFO API | `std::stack` / `std::queue` (adapters over deque) | `<stack>` / `<queue>` |
| Heap (always pop max/min) | `std::priority_queue` | `<queue>` |
| Two heterogeneous values | `std::pair` | `<utility>` |
| N heterogeneous values | `std::tuple` | `<tuple>` |

---

## 4. Step 1 — Sequence Containers

**Files:** `step1_sequence_containers/01a_*.cpp` … `01e_*.cpp` (5 mini demos)

Sequence containers store elements **in the order you put them**.

### Per-container summary

- **`std::vector`** — a contiguous heap array that doubles its capacity on growth. The default sequence container in C++. Cache-friendly, fastest iteration.
- **`std::array<T, N>`** — a fixed-size array; the size is part of the type, baked in at compile time. Lives wherever you put it (stack, member, etc.).
- **`std::deque`** — chunks of fixed-size blocks linked via an index. Element addresses are NOT contiguous, so pointers / iterators can be invalidated by insertions at either end.
- **`std::list`** — doubly-linked nodes. Each insert/erase is just relinking pointers — O(1) given an iterator. Iterators stay valid across other modifications. Poor cache locality.
- **`std::forward_list`** — singly-linked. Smaller per-node overhead but only forward traversal and no `back()`/`size()`.

### Operation complexity

| Operation | `vector` | `array` | `deque` | `list` | `forward_list` |
|------|------|------|------|------|------|
| `[i]` / `at(i)` | **O(1)** | **O(1)** | **O(1)** | — | — |
| `front()` / `back()` | O(1) | O(1) | O(1) | O(1) | front only |
| `push_back` | amortised O(1) | — | O(1) | O(1) | — |
| `push_front` | O(n) | — | O(1) | O(1) | O(1) |
| `pop_back` / `pop_front` | O(1) / O(n) | — | O(1) / O(1) | O(1) / O(1) | — / O(1) |
| `insert` / `erase` at iterator | O(n) | — | O(n) | **O(1)** | O(1) (`*_after`) |
| `find` (linear scan) | O(n) | O(n) | O(n) | O(n) | O(n) |
| `size()` | O(1) | O(1) (constexpr) | O(1) | O(1) | **not provided** — count by hand |
| iterator invalidated on insert | possibly all | — | possibly all | only the erased one | only the erased one |

**Default choice: `std::vector`.** Reach for the others only when their specific property pays for itself.

---

## 5. Step 2 — Ordered Associative Containers

**Files:** `step2_ordered_associative/02a_*.cpp` … `02d_*.cpp` (4 mini demos)

`std::pair<A, B>` is the building block — every entry of `std::map<K, V>` is a `pair<const K, V>`. A `pair` carries two heterogeneous values and is unpackable via C++17 structured bindings.

The four ordered associative containers are all **balanced binary search trees** (red-black trees, in practice). They iterate in **key order** and support range queries (`lower_bound`, `upper_bound`, `equal_range`).

### Per-container summary

- **`std::map<K, V>`** — key→value dictionary, one value per key, sorted by key.
- **`std::set<K>`** — unique values stored in sorted order; effectively a `map<K, void>`.
- **`std::multimap<K, V>`** — same as `map`, but duplicate keys are allowed.
- **`std::multiset<K>`** — same as `set`, but duplicate values are allowed.

### Operation complexity

| Operation | `map` / `set` / `multimap` / `multiset` |
|------|------|
| `find(k)` | **O(log n)** |
| `insert(...)` | O(log n) |
| `erase(it)` | O(log n) (amortised O(1) given iterator) |
| `erase(k)` | O(log n + count) |
| `count(k)` | O(log n + count) |
| `lower_bound` / `upper_bound` / `equal_range` | O(log n) |
| iteration in key order | O(n) total, O(log n) amortised per step |
| `size()` | O(1) |

⚠ `operator[]` on `map` **inserts a default-constructed value** if the key is missing. Use `.find()` / `.count()` for read-only checks.

---

## 6. Step 3 — Hash-based Associative Containers

**Files:** `step3_hash_associative/03a_*.cpp` … `03b_*.cpp` (2 mini demos)

`std::unordered_map<K, V>` and `std::unordered_set<K>` are **hash tables** with separate chaining. Lookup is hash → bucket → linear scan within the bucket.

### Per-container summary

- **`std::unordered_map<K, V>`** — fast lookup dictionary; iteration order is unspecified and may change after a rehash.
- **`std::unordered_set<K>`** — same idea for unique values without an associated payload.

The trade-offs vs the ordered versions:

- ✓ **average O(1)** insert/find/erase
- ✗ worst-case O(n) when the hash distributes badly
- ✗ no order at all, so no range queries (`lower_bound` / `upper_bound`)
- ✗ requires a `std::hash<K>` specialisation and `operator==(K, K)`

### Operation complexity

| Operation | Average | Worst |
|------|------|------|
| `find(k)` | **O(1)** | O(n) |
| `insert(...)` | O(1) | O(n) |
| `erase(k)` | O(1) | O(n) |
| iteration (full range) | O(n + buckets) | O(n + buckets) |
| `rehash(n)` / `reserve(n)` | O(n) amortised | — |
| `size()` | O(1) | O(1) |

To use a **custom struct as the key**, either specialise `std::hash<T>` or pass a hasher type as the third template parameter (see `03b_custom_hash.cpp`).

---

## 7. Step 4 — Tuple & Adapters

**Files:** `step4_adapters/04a_*.cpp` … `04d_*.cpp` (4 mini demos)

`std::tuple<...>` generalises `pair` to any number of heterogeneous fields. The easiest way to **return multiple values from a function**:

```cpp
std::tuple<int, double, std::string> stats() { return {42, 3.14, "ok"}; }
auto [n, pi, status] = stats();    // C++17 structured bindings
```

**Container adapters** wrap a sequence container and expose a restricted API.

### Per-adapter summary

- **`std::stack<T>`** — Last In, First Out. The most recent `push` is what `top` and `pop` see.
- **`std::queue<T>`** — First In, First Out. `push` adds at the back, `front`/`pop` work at the front.
- **`std::priority_queue<T>`** — a binary heap. `top()` is always the largest element by default; pass `std::greater<T>` for a min-heap.

### Operation complexity

| Operation | `stack` | `queue` | `priority_queue` |
|------|------|------|------|
| `push` | O(1) | O(1) | **O(log n)** |
| `pop` | O(1) | O(1) | **O(log n)** |
| `top` / `front` | O(1) | O(1) | O(1) |
| `back` | — | O(1) | — |
| `size` / `empty` | O(1) | O(1) | O(1) |

For `pair` and `tuple`, all access (`.first`, `.second`, `std::get<i>`) is O(1) at compile time.

---

## 8. Step 5 — Iterator Basics

**Files:** `step5_iterator_basics/05a_*.cpp` … `05e_*.cpp` (5 mini demos)

An iterator is "a pointer into a container" with a uniform interface. Every container exposes a **half-open range** `[begin(), end())`:

```cpp
for (auto it = v.begin(); it != v.end(); ++it) std::cout << *it;
```

Range-`for` is just sugar for that loop.

**Iterator categories** (least → most powerful):

| Category | Adds | Examples |
|------|------|------|
| Input | `++it`, `*it` (single-pass read) | `istream_iterator` |
| Output | `*it = v` (single-pass write) | `ostream_iterator`, `back_inserter` |
| Forward | multi-pass read+write | `forward_list` |
| Bidirectional | `--it` | `list`, `set`, `map` |
| **Random Access** | `it + n`, `it[n]`, `it < it2` | `vector`, `deque`, `array`, raw pointers |

Algorithms specify the minimum category they need; passing a weaker iterator is a compile error.

**Helpers** in `<iterator>`: `std::advance`, `std::distance`, `std::next`, `std::prev`. Reverse / const iterators come from `.rbegin()`, `.rend()`, `.cbegin()`, `.cend()`.

**Iterator adapters** turn things into iterator-shaped objects: `back_inserter(c)`, `front_inserter(c)`, `inserter(c, it)`, `ostream_iterator<T>(os, sep)`, `istream_iterator<T>(is)`.

---

## 9. Step 6 — Bidirectional Iterators

**Files:** `step6_bidirectional_iterators/06a_*.cpp` … `06d_*.cpp` (4 mini demos)

Bidirectional iterators are the next tier above forward — you can step **both ways**: `++it` to walk forward, `--it` to walk backward. They are the iterators of `std::list`, `std::set`, `std::map`, `std::multiset`, `std::multimap`. (Random-access iterators — see step 7 — are stronger and also satisfy the bidi concept.)

### What's in this step

- **`06a_bidi_basics.cpp`** — `++` AND `--` on a `std::list`. Shows the canonical "walk forward / walk backward" loops.
- **`06b_bidi_in_associative.cpp`** — walking a `std::set` or `std::map` in both directions, and the rule that `set` keys (and `map` first elements) are **const through the iterator**.
- **`06c_algos_needing_bidi.cpp`** — `std::reverse`, `std::rotate`, `std::next_permutation`, `std::stable_partition` — all require at least bidi (a forward-only iterator would be a compile error).
- **`06d_bidi_limits.cpp`** — what bidi cannot do: `it+n`, `it[n]`, `it < it2`. Use `std::advance` / `std::distance` instead — they compile but cost O(n) hops on bidi.

### Bidi adds vs forward

| Operation | Forward | Bidirectional |
|------|------|------|
| `*it`, `++it`, `==`/`!=` | ✓ | ✓ |
| **`--it`** | — | **✓** |
| `it + n` / `it - n` / `it[n]` / `it < it2` | — | — |

`std::advance(it, n)` and `std::distance(a, b)` work on bidi but **walk one node at a time** — they are O(n), not O(1). For O(1) jumps you need random access.

### Algorithms requiring at least bidirectional

| Algorithm | Why it needs bidi |
|------|------|
| `std::reverse` | swap pairs from both ends inward |
| `std::rotate` | needs to shift through the range |
| `std::next_permutation` / `std::prev_permutation` | scans back from `end` |
| `std::stable_partition` | merges from both halves |

---

## 10. Step 7 — Random Access Iterators

**Files:** `step7_random_access_iterators/07a_*.cpp` … `07d_*.cpp` (4 mini demos)

Random-access iterators are the most powerful tier — they support every operation a raw pointer does in **O(1)**:

```
it + n        jump forward by n          (O(1))
it - n        jump backward
it[n]         subscript — same as *(it + n)
it1 - it2     distance — an integer
it1 < it2     ordering — is one before the other?
```

Containers whose iterators are random-access: `std::vector`, `std::deque`, `std::array`, and **raw C arrays via plain pointers**.

### What's in this step

- **`07a_random_access_basics.cpp`** — every random-access op exercised on a `std::vector`.
- **`07b_pointer_equivalence.cpp`** — a raw `T*` satisfies the random-access iterator concept; STL algorithms accept two pointers anywhere they accept iterators. Mirrors how C-array idioms map onto STL.
- **`07c_algos_needing_random.cpp`** — `std::sort`, `std::nth_element`, `std::shuffle`, `std::partial_sort`, the heap algorithms — all require random access. Trying `std::sort(list)` is a compile error; `list` provides its own member `.sort()` instead.
- **`07d_binary_search_complexity.cpp`** — `std::binary_search` / `lower_bound` / `upper_bound` accept any forward iterator and always do **O(log n) comparisons**, but the **iterator hops** become O(n) on non-random-access iterators. So binary search is only truly O(log n) on random-access containers.

### Random access adds vs bidirectional

| Operation | Bidirectional | Random Access |
|------|------|------|
| `++it`, `--it` | ✓ | ✓ |
| **`it + n`, `it - n`** (O(1)) | — (O(n) via `std::advance`) | **✓** |
| **`it[n]`** | — | **✓** |
| **`it1 - it2`** (an integer) | — (O(n) via `std::distance`) | **✓** |
| **`it1 < it2`** | — | **✓** |

### Algorithms requiring random access

| Algorithm | Why it needs random access |
|------|------|
| `std::sort` / `std::stable_sort` | introsort needs O(1) partitioning around an arbitrary element |
| `std::partial_sort` / `std::nth_element` | quickselect / heap pivots |
| `std::shuffle` | swaps `arr[i] ↔ arr[rand() % n]` |
| `std::push_heap`, `std::pop_heap`, `std::make_heap`, `std::sort_heap` | heap is an array index structure |

`std::binary_search`, `std::lower_bound`, `std::upper_bound`, `std::equal_range` accept any forward iterator but only achieve **true O(log n)** on random-access ones.

---

## 11. Step 8 — Non-modifying Algorithms

**Files:** `step8_non_modifying_algos/08a_*.cpp` … `06d_*.cpp` (4 mini demos)

These algorithms walk a range and report something — they never mutate the elements. Almost all of them are O(n) linear scans (you cannot avoid looking at every element), with optimisations for sorted ranges (binary search lives in step 8).

| Algorithm | What it does | Complexity |
|------|------|------|
| `find(b, e, v)` | first iterator with `*it == v`, else `e` | **O(n)** |
| `find_if(b, e, p)` | first iterator with `p(*it)` true | O(n) |
| `find_if_not(b, e, p)` | first with `p(*it)` false | O(n) |
| `count(b, e, v)` | how many == v | O(n) |
| `count_if(b, e, p)` | how many satisfy p | O(n) |
| `any_of(b, e, p)` | does ANY element satisfy p? | O(n), short-circuits on first true |
| `all_of(b, e, p)` | do ALL elements satisfy p? | O(n), short-circuits on first false |
| `none_of(b, e, p)` | do NONE? | O(n), short-circuits on first true |
| `equal(b1, e1, b2)` | element-wise equality | O(n) |
| `mismatch(b1, e1, b2)` | first index where ranges diverge | O(n) |
| `min(a, b)` / `max(a, b)` | smaller / larger of two values | O(1) |
| `minmax(a, b)` | both — `pair<T, T>` | O(1) |
| `min_element(b, e)` | iterator to smallest in a range | O(n) |
| `max_element(b, e)` | iterator to largest | O(n) |
| `minmax_element(b, e)` | both — at most ⌈3n/2⌉ comparisons | O(n) |

vs C: `bsearch` only handles sorted arrays; you'd write everything else by hand. STL algorithms are templated, type-safe, and work on any iterator pair.

---

## 12. Step 9 — Modifying Algorithms

**Files:** `step9_modifying_algos/09a_*.cpp` … `07d_*.cpp` (4 mini demos)

Every algorithm here visits each element at least once, so the baseline cost is **O(n)**. The interesting axes are: do they need extra space? do they preserve relative order?

| Algorithm | What it does | Complexity |
|------|------|------|
| `copy(b, e, dst)` | copy each element to dst | **O(n)** |
| `move(b, e, dst)` | move each (calls move ctors) | O(n) |
| `fill(b, e, v)` | every element ← v | O(n) |
| `fill_n(dst, n, v)` | same, given a count | O(n) |
| `generate(b, e, fn)` | every element ← fn() | O(n) |
| `iota(b, e, start)` | start, start+1, … (in `<numeric>`) | O(n) |
| `for_each(b, e, fn)` | call fn on each element | O(n) |
| `transform(b, e, dst, fn)` | dst[i] ← fn(src[i]) | O(n) |
| `transform(b1, e1, b2, dst, binop)` | dst[i] ← binop(a[i], b[i]) | O(n) |
| `replace(b, e, old, new)` | every == old becomes new | O(n) |
| `replace_if(b, e, pred, new)` | every element with pred true ← new | O(n) |
| `reverse(b, e)` | reverse the range in place | O(n) |
| `rotate(b, mid, e)` | move `[mid, e)` to the front | O(n) |
| `shuffle(b, e, rng)` | randomise (C++11); requires a random engine | O(n) |

Combine with iterator adapters (`back_inserter`, `ostream_iterator`) to write into containers or streams without pre-sizing.

---

## 13. Step 10 — Sorting & Searching

**Files:** `step10_sorting_searching/10a_*.cpp` … `08c_*.cpp` (3 mini demos)

Sorting is **O(n log n)**; binary search on a sorted range is **O(log n)**. There are also "I don't need a full sort" algorithms (`partial_sort`, `nth_element`) that beat O(n log n) when you only care about the top-k or the median.

| Algorithm | What it does | Complexity |
|------|------|------|
| `sort(b, e [, cmp])` | full sort; order of equals NOT preserved | **O(n log n)** |
| `stable_sort(b, e [, cmp])` | same, equals keep original relative order | O(n log n) typically (O(n log² n) worst case if no extra memory) |
| `partial_sort(b, mid, e [, cmp])` | first `(mid-b)` elements in sorted order; tail unspecified | O(n log k), k = mid−b |
| `nth_element(b, nth, e [, cmp])` | `*nth` ends up where a full sort would put it; left ≤ it ≤ right | **O(n)** average |
| `is_sorted(b, e)` | bool — is the range non-decreasing? | O(n) |
| `binary_search(b, e, v)` | bool — is `v` present in a sorted range? | **O(log n)** on RA, O(n) hops on bidi |
| `lower_bound(b, e, v)` | first iterator with `*it ≥ v` (sorted range) | O(log n) on RA |
| `upper_bound(b, e, v)` | first iterator with `*it > v` | O(log n) on RA |
| `equal_range(b, e, v)` | pair `(lower, upper)` | O(log n) on RA |
| `merge(b1, e1, b2, e2, dst)` | merge two sorted ranges into a sorted output | O(n + m) |

vs C: `qsort` takes a void-pointer comparator returning `int` — slow and cumbersome. `std::sort` takes any callable (free function, lambda, function object), is type-safe, and is often faster.

⚠ The four `*_bound` family algorithms accept any forward iterator — but the binary-search behaviour (true O(log n)) only applies to **random-access** iterators. On a `std::list` you'd still get O(n) hops to find the position, even though the comparison count is O(log n).

---

## 14. Step 11 — Removing & Partitioning

**Files:** `step11_removing_partitioning/11a_*.cpp` … `09c_*.cpp` (3 mini demos)

`std::remove` does **not** shrink the container — it moves keepers to the front and returns `new_end`. Pair it with `.erase()`:

```cpp
v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());   // erase-remove idiom
```

(C++20 simplifies this to `std::erase_if(v, pred);`.)

| Algorithm | What it does | Complexity |
|------|------|------|
| `remove(b, e, v)` | move keepers to front, return new_end (size unchanged!) | **O(n)** |
| `remove_if(b, e, pred)` | same, with a predicate | O(n) |
| `unique(b, e)` | remove **consecutive** duplicates; sort first to dedup whole range | O(n) |
| `unique(b, e, eq)` | same with custom equality | O(n) |
| `partition(b, e, pred)` | true elements first, false after; relative order NOT preserved | **O(n)** |
| `stable_partition(b, e, pred)` | same, original order preserved within each side | O(n log n) typical (depends on extra memory) |
| `partition_point(b, e, pred)` | find boundary on an already-partitioned range | **O(log n)** on RA |

`std::unique` removes only **consecutive** equal elements — to dedup the whole range, sort first then unique then erase.

---

## 15. Step 12 — Set Operations on Sorted Ranges

**File:** `step12_set_operations/12a_set_operations.cpp` (1 mini demo)

All four require **both inputs sorted**. They walk both ranges in parallel and write the result into an output iterator. Cost is therefore **linear in the total size** — much faster than re-sorting after the operation.

| Algorithm | Result | Complexity |
|------|------|------|
| `set_union(a..ae, b..be, out)` | in either A or B | **O(n + m)** |
| `set_intersection(a..ae, b..be, out)` | in both A and B | O(n + m) |
| `set_difference(a..ae, b..be, out)` | in A but not in B | O(n + m) |
| `set_symmetric_difference(a..ae, b..be, out)` | in exactly one of A, B | O(n + m) |
| `includes(a..ae, b..be)` | bool — is B a subset of A? | O(n + m) |

These are the STL way of doing math-set operations on plain containers; they are **independent** of the `set` container — `std::vector` works just fine if you keep it sorted.

---

## 16. Step 13 — Numeric & Permutations

**Files:** `step13_numeric_permutations/13a_*.cpp` … `11c_*.cpp` (3 mini demos)

`<numeric>` reductions touch each element exactly once, so each call is **O(n)**. Permutation algorithms are likewise linear in the range size per call (but **enumerating** all permutations costs O(n · n!) — there are n! permutations of n elements).

| Algorithm | Computes | Complexity |
|------|------|------|
| `accumulate(b, e, init [, op])` | left-fold; default op is `+` | **O(n)** |
| `reduce(b, e, init [, op])` (C++17) | same idea, op MUST be assoc + comm — allows parallelisation | O(n), parallelisable |
| `inner_product(b1, e1, b2, init)` | `Σ a_i · b_i` (dot product) | O(n) |
| `partial_sum(b, e, dst)` | prefix sums `s_k = Σ_{i≤k} a_i` | O(n) |
| `adjacent_difference(b, e, dst)` | first-differences `d_k = a_k − a_{k-1}` | O(n) |
| `iota(b, e, start)` | start, start+1, start+2, … | O(n) |
| `next_permutation(b, e)` | next lex permutation; false when wrapping | O(n) per call |
| `prev_permutation(b, e)` | previous lex permutation | O(n) per call |
| `is_permutation(b1, e1, b2)` | are two ranges permutations of each other? | O(n²) worst case |

Use `next_permutation` in a `do { ... } while (next_permutation(...));` loop to walk all n! permutations.

---

## 17. Step 14 — Functors

**Files:** `step14_functors/14a_*.cpp` … `12e_*.cpp` (5 mini demos)

A **functor** (function object) is an object you can call like a function — a class with an overloaded `operator()`. C had only function pointers; C++ generalises "callable" to anything that responds to `()`. That includes:

- a class with `operator()` (the original meaning of "functor")
- a **lambda** — sugar for an anonymous functor class the compiler writes for you
- a free function or a function pointer
- the result of `std::bind` (legacy)
- a `std::function<R(Args...)>` holding any of the above

Functors are the customisation hook of the STL: every algorithm that takes a comparator, a predicate, or a transformation accepts any callable that matches the expected signature.

### What's in this step

- **`12a_functor_basics.cpp`** — a hand-written class with `operator()` (`Greeter("Hello")("Ada")` calls `Greeter::operator()("Ada")`).
- **`12b_stateful_functor.cpp`** — a `Multiplier` that counts how many times it was called. Pass it via `std::ref` so the algorithm shares one instance instead of copying.
- **`12c_predefined_functors.cpp`** — the templates in `<functional>`: `std::less`, `std::greater`, `std::plus`, `std::multiplies`, `std::negate`, `std::equal_to`, …
- **`12d_lambdas_as_functors.cpp`** — capture clauses (`[]`, `[=]`, `[&]`, `[x]`, `[&x]`, `[x = expr]`), `mutable` lambdas, and the equivalent class the compiler generates.
- **`12e_std_function.cpp`** — `std::function<int(int,int)>` holds free functions, functor objects, and lambdas uniformly. Trade-off: small heap cost vs. the type-parameterised template form.

### Lambda capture cheat sheet

| Capture | Meaning |
|------|------|
| `[]` | capture nothing — closure holds no state |
| `[=]` | capture every used local **by value** |
| `[&]` | capture every used local **by reference** |
| `[x]` | capture `x` by value |
| `[&x]` | capture `x` by reference |
| `[=, &x]` | default by value, but `x` by reference |
| `[x = expr]` | init capture (C++14) — store a fresh member with a value |
| `mutable` | (after the parameter list) lets the body modify by-value captures |

### Function pointer vs functor vs lambda vs std::function

| Form | Holds state? | Compile-time inlinable? | Storage |
|------|------|------|------|
| function pointer | NO | only via inlining of the call site | one pointer |
| functor (class) | YES (members) | YES — type known | one object |
| lambda | YES (captures) | YES — anonymous type known | one object |
| `std::function<...>` | YES (any of the above) | NO — virtual call | small object + heap (for big captures) |

Default to **lambdas** for one-off uses, **named functors** when state and reuse matter, **`std::function`** only when you really need to store heterogeneous callables in a uniform variable.

---

## 18. STL Cheat Sheet

### From "I have a problem" to "I have an STL tool"

| You want… | Use | Cost |
|------|------|------|
| A growable array | `std::vector` | `[i]` O(1), `push_back` amortised O(1) |
| A fixed-size buffer with iterators | `std::array<T, N>` | `[i]` O(1) |
| Push/pop at both ends | `std::deque` | both O(1), `[i]` O(1) |
| Stable iterators while editing | `std::list` | insert/erase O(1) given iterator |
| Key→value lookup, in order | `std::map` | O(log n) |
| Key→value lookup, fastest | `std::unordered_map` | average O(1), worst O(n) |
| Mathematical set | `std::set` / `std::unordered_set` | O(log n) / avg O(1) |
| LIFO / FIFO | `std::stack` / `std::queue` | push/pop O(1) |
| Always pop best | `std::priority_queue` | push/pop O(log n) |
| Return multiple values | `std::tuple` + structured bindings | access O(1) |
| Search (linear) | `std::find` / `std::find_if` | O(n) |
| Search (sorted, log n) | `std::binary_search`, `lower_bound`, `upper_bound` | O(log n) on RA |
| Sort | `std::sort` / `stable_sort` | O(n log n) |
| Top-k / median | `std::partial_sort` / `nth_element` | O(n log k) / O(n) avg |
| Apply f to each | `std::for_each`, `std::transform` | O(n) |
| Sum / product / fold | `std::accumulate`, `std::reduce` | O(n) |
| Drop matching | `std::remove_if` + `.erase()` | O(n) |
| Dedup | sort + `std::unique` + `.erase()` | O(n log n) for the sort |
| Reverse / rotate / shuffle | `std::reverse`, `std::rotate`, `std::shuffle` | O(n) |
| Set ops on sorted ranges | `std::set_union` etc. | O(n + m) |
| Enumerate permutations | `std::next_permutation` in a `do { } while` loop | n! iterations × O(n) each |
| Output to a stream | `std::ostream_iterator<T>(std::cout, " ")` | O(1) per write |
| Read from a stream | `std::istream_iterator<T>(in)` | O(1) per read |

### Big-O at a glance

| Class | Examples |
|------|------|
| **O(1)** | `vector[i]`, `unordered_map::find` (avg), `priority_queue::top`, all `pair`/`tuple` access |
| **O(log n)** | `map::find`, `set::insert`, `binary_search`, `priority_queue::push`/`pop`, `partition_point` |
| **O(n)** | `find`, `count`, `transform`, `for_each`, `accumulate`, `unique`, `reverse`, `rotate`, `partition`, `nth_element` (avg), set operations (n+m), `iota`, `partial_sum` |
| **O(n log n)** | `sort`, `stable_sort`, `partial_sort` (worst when k = n) |
| **O(n!)** | iterating all permutations via `next_permutation` |

---

For the **C++ language basics** (strings, references, smart pointers, move semantics) see [`../cpp-basics-tutorial/`](../cpp-basics-tutorial/).
For **OOP** (classes, inheritance, the Rule of 5, …) see [`../cpp-oop-tutorial/`](../cpp-oop-tutorial/).
