# C++ Basics — A Hands-on Lab for C Programmers

A 50-demo crash course in **the parts of C++ that differ from C**. Every file is a self-contained, compilable program built around one concept and frames it as **"in C you'd do X, in C++ you can do Y because Z"**.

For the **STL** (containers, iterators, algorithms) see the sister lab at [`../cpp-stl-tutorial/`](../cpp-stl-tutorial/).

If you already write C, this lab will get you productive in idiomatic C++ without rehashing what you already know about loops, integer types, or pointer arithmetic.

---

## Table of Contents

1. [Lab Architecture](#1-lab-architecture)
2. [Setup](#2-setup)
3. [Step 1 — Hello World](#3-step-1--hello-world)
4. [Step 2 — Syntax Basics](#4-step-2--syntax-basics)
5. [Step 3 — Strings](#5-step-3--strings)
6. [Step 4 — bool](#6-step-4--bool)
7. [Step 5 — auto](#7-step-5--auto)
8. [Step 6 — cin / cout](#8-step-6--cin--cout)
9. [Step 7 — Overloading & Default Parameters](#9-step-7--overloading--default-parameters)
10. [Step 8 — Namespaces](#10-step-8--namespaces)
11. [Step 9 — Pointers vs References](#11-step-9--pointers-vs-references)
12. [Step 10 — Qualifiers](#12-step-10--qualifiers)
13. [Step 11 — Rvalue References](#13-step-11--rvalue-references)
14. [Step 12 — Allocations](#14-step-12--allocations)
15. [Step 13 — Smart Pointers](#15-step-13--smart-pointers)
16. [Step 14 — Templates](#16-step-14--templates)
17. [Step 15 — Exceptions](#17-step-15--exceptions)
18. [Step 16 — Lambdas](#18-step-16--lambdas)
19. [Step 17 — C++ Casts](#19-step-17--c-casts)
20. [C → C++ Cheat Sheet](#20-c--c-cheat-sheet)

---

## 1. Lab Architecture

```
cpp-basics-tutorial/
├── build.sh           # Compiles every step*/*.cpp into build/<basename>
├── run_all.sh         # Runs every compiled demo with a pause between each
├── README.md          # This file
├── index.html         # Single-page interactive lab (CodeMirror + per-demo output)
├── build/             # Created by build.sh (gitignored)
│
├── step1_hello_world/             ── starting points ──
│   ├── 01a_hello_world.cpp
│   └── 01b_printf_vs_cout.cpp
│
├── step2_syntax_basics/           ── declarations & loops ──
│   ├── 02a_variables_and_init.cpp
│   ├── 02b_uniform_init_aggregate.cpp
│   └── 02c_range_for_loop.cpp
│
├── step3_strings/                 ── std::string vs char* ──
│   ├── 03a_cstring_vs_string.cpp
│   ├── 03b_string_operations.cpp
│   └── 03c_string_conversions.cpp
│
├── step4_bool/
│   └── 04a_bool_type.cpp
│
├── step5_auto/                    ── type deduction ──
│   ├── 05a_auto_basics.cpp
│   └── 05b_auto_caveats.cpp
│
├── step6_iostream/                ── streams (cin / cout) ──
│   ├── 06a_cout_basics.cpp
│   ├── 06b_cin_basics.cpp
│   └── 06c_iomanip_formatting.cpp
│
├── step7_overloading_defaults/    ── functions ──
│   ├── 07a_function_overloading.cpp
│   └── 07b_default_parameters.cpp
│
├── step8_namespaces/
│   ├── 08a_namespaces_basics.cpp
│   └── 08b_using_directives.cpp
│
├── step9_pointers_vs_references/  ── new in C++: references ──
│   ├── 09a_references_intro.cpp
│   ├── 09b_pointer_vs_reference.cpp
│   └── 09c_pass_by_x.cpp
│
├── step10_qualifiers/             ── const & constexpr ──
│   ├── 10a_const_qualifier.cpp
│   └── 10b_constexpr.cpp
│
├── step11_rvalue_references/      ── move semantics core ──
│   ├── 11a_lvalue_vs_rvalue.cpp
│   └── 11b_rvalue_reference_and_move.cpp
│
├── step12_allocations/            ── new/delete vs malloc/free ──
│   ├── 12a_new_vs_malloc.cpp
│   ├── 12b_new_array.cpp
│   └── 12c_manual_memory_dangers.cpp
│
├── step13_smart_pointers/         ── modern memory ownership ──
│   ├── 13a_unique_ptr.cpp
│   ├── 13b_shared_ptr.cpp
│   └── 13c_weak_ptr.cpp
│
├── step14_templates/              ── generic programming (no C analogue) ──
│   ├── 14a_function_template.cpp        type-safe alternative to C macros
│   ├── 14b_class_template.cpp           Stack<T> — write once, use for any T
│   ├── 14c_non_type_template_param.cpp  std::array<T, N> style: N at compile time
│   ├── 14d_template_specialization.cpp  full + partial specialisation
│   ├── 14e_default_template_args.cpp    defaults for type/non-type params
│   ├── 14f_variadic_templates.cpp       parameter packs, fold expressions (C++17)
│   └── 14g_if_constexpr.cpp             compile-time branching in templates (C++17)
│
├── step15_exceptions/             ── structured error handling vs C return codes ──
│   ├── 15a_throw_catch.cpp              try / catch / throw basics
│   ├── 15b_std_exception_hierarchy.cpp  std::exception, runtime_error, custom types
│   ├── 15c_raii_cleanup.cpp             destructors run during stack unwind
│   └── 15d_noexcept.cpp                 'noexcept' specifier; matters for std::vector moves
│
├── step16_lambdas/                ── inline anonymous functions (no C analogue) ──
│   ├── 16a_lambda_basics.cpp            [](){...} syntax
│   ├── 16b_lambda_captures.cpp          [], [=], [&], [x], [&x], [x=expr], mutable
│   ├── 16c_lambdas_with_algorithms.cpp  lambdas as STL predicates / comparators
│   └── 16d_lambda_internals.cpp         lambda = anonymous functor class; std::function
│
└── step17_casts/                  ── named casts replace C-style (T)x ──
    ├── 17a_static_cast.cpp              the 90% case
    ├── 17b_dynamic_cast.cpp             runtime-checked downcast
    ├── 17c_const_cast.cpp               strip const (for legacy APIs); UB warning
    └── 17d_reinterpret_cast.cpp         bit-level — last resort
```

Each `.cpp` file is a **single-concept**, self-contained program with its own `main()`. Compile and run any one independently. Total: **50** mini demos across 17 steps.

For the STL — containers, iterators, and `<algorithm>` — see the sister lab at [`../cpp-stl-tutorial/`](../cpp-stl-tutorial/).

---

## 2. Setup

### Prerequisites

- g++ 7+ (or clang++ 5+) with C++17 support
- A POSIX shell (Linux, macOS, WSL)

### Build all demos

```bash
chmod +x build.sh run_all.sh
./build.sh
```

### Run them all interactively

```bash
./run_all.sh
```

### Run a single demo

```bash
g++ -std=c++17 -Wall -Wextra -g -o build/01a_hello_world step1_hello_world/01a_hello_world.cpp
./build/01a_hello_world
```

### Open the interactive lab page

```bash
python3 -m http.server 8765
# then open http://127.0.0.1:8765/ in a browser
```

---

## 3. Step 1 — Hello World

**Files:** `step1_hello_world/01a_*.cpp` … `01b_*.cpp`

The traditional `int main` shape is the same as C. The two differences you meet immediately:

- `<iostream>` and `std::cout` replace `<stdio.h>` and `printf`. Stream insertion is **type-safe**: `cout << x` picks the right behaviour from `x`'s type, so there are no `%d/%s/%f` mismatches to debug.
- Returning `0` from `main()` is **implicit** — falling off the end is fine.

Both worlds coexist: `<cstdio>` is a C++ header that wraps the C `<stdio.h>`, so `printf` is still legal in C++.

---

## 4. Step 2 — Syntax Basics

**Files:** `step2_syntax_basics/02a_*.cpp` … `02c_*.cpp`

Three initialisation forms in C++ that you didn't have in C:

| Form | Syntax | Notes |
|------|------|------|
| copy init  | `int x = 7;`  | works in C too |
| direct init | `int x(7);` | C++ only |
| **brace / uniform init** | `int x{7};` | C++11; **rejects narrowing conversions** at compile time |

`std::vector<int> v{1,2,3};`, `Point p{1,2};`, `int a[3]{1,2,3}` — the same brace syntax works everywhere.

The C++11 **range-for** loop replaces most index loops:

```cpp
for (const auto& x : container) sum += x;   // const auto& → no copies
```

---

## 5. Step 3 — Strings

**Files:** `step3_strings/03a_*.cpp` … `03c_*.cpp`

`std::string` is the C++ replacement for `char[]`. It owns its memory, knows its length in O(1), grows automatically, and frees itself when it goes out of scope (RAII — no `free()` needed).

| C | C++ |
|------|------|
| `strlen(s)` | `s.length()` / `s.size()` |
| `strcpy(d, s)` | `d = s;` |
| `strcat(d, s)` | `d += s;` |
| `strstr(h, n)` | `h.find(n)` (returns `string::npos` on miss) |
| `strcmp(a, b)` | `a == b`, `a < b`, … |
| `snprintf` | `std::to_string(n)` |
| `atoi(s)` | `std::stoi(s)` (throws on bad input) |

When you need to call a C API, `s.c_str()` hands you a `const char*`.

---

## 6. Step 4 — bool

**File:** `step4_bool/04a_bool_type.cpp`

C did not have a native boolean until C99 (`_Bool` plus the `<stdbool.h>` macros). C++ has had `bool`, `true`, and `false` from day one as **first-class keywords**. `bool ↔ int` conversions are well-defined: `false → 0`, `true → 1`, and any non-zero integer converts to `true`.

```cpp
std::cout << std::boolalpha << (3 < 5);   // prints "true"
```

---

## 7. Step 5 — auto

**Files:** `step5_auto/05a_*.cpp` … `05b_*.cpp`

In C the `auto` keyword was a (rarely used) storage-class specifier. **C++11 repurposed it** to mean "deduce my type from the initialiser":

```cpp
auto i = 42;                  // int
auto m = std::map<std::string, int>{};
for (auto it = m.begin(); it != m.end(); ++it) { ... }
```

Caveats — `auto` strips `&` and `const` by default. Use `auto&` / `const auto&` to keep them:

```cpp
for (auto x       : v)  ...   // copies each element
for (auto& x      : v)  ...   // mutate in place
for (const auto& x : v) ...   // read-only, no copies (best default)
```

---

## 8. Step 6 — cin / cout

**Files:** `step6_iostream/06a_*.cpp` … `06c_*.cpp`

`std::cin` and `std::cout` are **type-safe streams**. Insertion (`<<`) and extraction (`>>`) are overloaded per type, so the right behaviour is selected at compile time:

```cpp
std::cin >> n >> d >> word;        // parses int, double, string in turn
if (!std::cin) { /* failed */ }    // always check the stream state
```

Formatting lives in `<iomanip>`: `setprecision`, `setw`, `setfill`, `fixed`, `hex`, `boolalpha`, etc.

---

## 9. Step 7 — Overloading & Default Parameters

**Files:** `step7_overloading_defaults/07a_*.cpp` … `07b_*.cpp`

C forbids two functions with the same name; C++ allows it as long as the parameter list differs. The compiler picks the best match at the call site (overload resolution), and the linker sees mangled (decorated) names that include the types.

**Default parameters** (also unavailable in C) let a function declare its own fallbacks:

```cpp
void greet(const std::string& name = "World", int times = 1);
greet();              // → "Hello, World!"
greet("Bob", 3);
```

Defaults must trail; you cannot skip a non-trailing argument.

---

## 10. Step 8 — Namespaces

**Files:** `step8_namespaces/08a_*.cpp` … `08b_*.cpp`

C has one global namespace, so library writers prefix everything: `gtk_widget_show`, `png_create_read_struct`. C++ replaces the prefix with a real namespace:

```cpp
namespace math { double square(double x); }
math::square(5);
```

The standard library lives in `namespace std`. You can import names with `using std::cout;` (preferred), or pull everything in with `using namespace std;` — never do that in a header.

---

## 11. Step 9 — Pointers vs References

**Files:** `step9_pointers_vs_references/09a_*.cpp` … `09c_*.cpp`

C has only pointers. C++ adds **references** — an alias for an existing variable that:

- must be initialised at declaration,
- cannot be null,
- cannot be reseated to a different object,
- has the same address as its referent.

|  | pointer | reference |
|------|------|------|
| can be null | yes | no |
| can reseat | yes | no |
| explicit deref | `*p` | none |
| caller-side syntax | `f(&x)` | `f(x)` |
| pointer arithmetic | yes | no |

**Pass by `const` reference** is the modern C++ replacement for "pass a `const T*` you trust isn't null":

```cpp
void process(const std::vector<int>& v);   // no copies, no null check
```

---

## 12. Step 10 — Qualifiers

**Files:** `step10_qualifiers/10a_*.cpp` … `10b_*.cpp`

Both C and C++ have `const`. C++ adds:

- **`const` member functions** (covered in `cpp-oop-tutorial/step8`).
- **`constexpr`** — evaluated **at compile time** when possible. Stronger than `const`:
  - `const` means "this name does not change after initialisation".
  - `constexpr` means "this expression can be computed at compile time" — usable as an array bound, `static_assert` argument, template parameter, etc.

```cpp
constexpr long factorial(int n) { return n <= 1 ? 1 : n * factorial(n-1); }
constexpr long f10 = factorial(10);     // computed at compile time
int arr[factorial(4)];                  // array bound is compile-time
```

---

## 13. Step 11 — Rvalue References

**Files:** `step11_rvalue_references/11a_*.cpp` … `11b_*.cpp`

C never had a way to bind to a temporary and "steal" its resources — every assignment was effectively a bytewise copy.

C++11 introduced **rvalue references** (`T&&`) to identify "this resource is about to die — feel free to steal from it". `std::move` is **just a cast**: it turns an lvalue expression into an rvalue expression. The actual move happens when an operation that overloads on `T&&` (e.g. `std::string`'s move constructor) consumes it.

```cpp
std::string a = "alpha";
std::string b = std::move(a);   // b steals a's heap buffer
                                 // a is now in valid-but-unspecified state (often empty)
```

Move semantics turn unnecessary copies of large objects (strings, vectors, file handles) into pointer-steals. See `cpp-oop-tutorial/step10` for the full **Rule of 5** treatment.

---

## 14. Step 12 — Allocations

**Files:** `step12_allocations/12a_*.cpp` … `12c_*.cpp`

| C | C++ |
|------|------|
| `malloc(sizeof(T))` | `new T(args...)` (also calls the constructor) |
| `free(p)` | `delete p` (calls the destructor) |
| `malloc(n * sizeof(T))` | `new T[n]` |
| `free(arr)` | `delete[] arr` |

**Critical:** the two systems do **not** interoperate. Mixing `new` ↔ `free`, `malloc` ↔ `delete`, or `new[]` ↔ `delete` is undefined behaviour.

Manual `new`/`delete` carries the same bug classes as `malloc`/`free`: leaks, double-free, use-after-free, exception leaks. The next step shows how to make those bugs unrepresentable.

---

## 15. Step 13 — Smart Pointers

**Files:** `step13_smart_pointers/13a_*.cpp` … `13c_*.cpp`

Replace raw `new`/`delete` with **smart pointers** that release the resource automatically (RAII):

| Type | Ownership | Cost | Use it when |
|------|------|------|------|
| `std::unique_ptr<T>` | exclusive (move-only) | none over a raw ptr | one owner — the default |
| `std::shared_ptr<T>` | shared (refcounted, atomic) | atomic count | multiple owners; lifetime ends when the last copy dies |
| `std::weak_ptr<T>`  | non-owning observer | small | break cycles between `shared_ptr`s |

```cpp
auto p = std::make_unique<Connection>("db://main");   // preferred over 'new'
auto q = std::make_shared<Resource>("...");           // shared between threads
```

**Rule of thumb:** prefer `unique_ptr`. Reach for `shared_ptr` only when ownership is genuinely shared. Use `weak_ptr` to observe without extending lifetime (e.g. parent ↔ child links).

---


## 16. Step 14 — Templates

**Files:** `step14_templates/14a_*.cpp` … `14g_*.cpp` (7 mini demos)

Templates are the C++ tool for **generic programming** — you write code parameterised on a TYPE (or a compile-time constant), and the compiler stamps out a real version per use site.

### vs C

C had only **macros** for "code that works for any type":

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

Macros are textual substitution — no type checking, no overloading, surprise precedence problems, and the arguments may be evaluated more than once. Templates are type-checked, scoped, debuggable, and each instantiation is a real function/class with its own type.

### What's in this step

- **`14a_function_template.cpp`** — `template <typename T> T max_of(T, T);` plus auto type deduction at the call site.
- **`14b_class_template.cpp`** — `template <typename T> class Stack;` — same shape as `std::vector`, `std::map`, etc.
- **`14c_non_type_template_param.cpp`** — non-type params (`size_t N`); shows how `std::array<T, N>` bakes the size into the type.
- **`14d_template_specialization.cpp`** — a primary template plus a full specialisation for `bool`/`std::string`, and a partial specialisation for `T*`.
- **`14e_default_template_args.cpp`** — `template <typename T, size_t Cap = 16>`. Real example: `std::set<Key, Compare = std::less<Key>>`.
- **`14f_variadic_templates.cpp`** — parameter packs (`Ts...`), `sizeof...`, and **fold expressions** like `(args + ...)` (C++17).
- **`14g_if_constexpr.cpp`** — compile-time `if` inside a template; the untaken branch is **discarded** so it doesn't need to be valid for the current `T`.

### Quick reference

| Form | Syntax |
|------|------|
| Function template | `template <typename T> R f(T x);` |
| Class template | `template <typename T> class C { ... };` |
| Multiple type params | `template <typename A, typename B> ...` |
| Non-type param | `template <typename T, size_t N> ...` |
| Default for a param | `template <typename T = int>` |
| Full specialisation | `template <> class Printer<bool> { ... };` |
| Partial specialisation (class only) | `template <typename T> class Printer<T*> { ... };` |
| Variadic | `template <typename... Ts> R f(Ts... args);` |
| Pack expansion | `(args + ...)`, `((std::cout << args), ...)` |
| Compile-time branch | `if constexpr (std::is_integral_v<T>) { ... }` |

### Pitfalls

- **Code lives in headers.** Template definitions usually need to be in headers (or `.tpp`/`.ipp` files included from a header), because the compiler needs the full body to instantiate per use site.
- **Slow compiles, large binaries.** Each instantiation is real code; lots of types × lots of templates → a lot of generated code.
- **Cryptic error messages.** A typo in the template body shows up as a wall of text mentioning every instantiation. C++20 concepts help, but they're outside this lab's scope.

### C++ Templates vs Java Generics

If you're coming from Java, this is the **single biggest mental-model difference** between the two language families. They look similar (`Stack<T>`) but the machinery is completely different.

| | **C++ templates** | **Java generics** |
|------|------|------|
| Mechanism | **Compile-time monomorphisation** — the compiler stamps out a real, distinct class/function per instantiation (`Stack<int>`, `Stack<std::string>`, …) | **Type erasure** — at runtime `List<String>` and `List<Integer>` are both `List<Object>`; the type parameter is erased after the compile-time check |
| When type checked | At **instantiation** time (duck-typed: anything you write must compile against the actual `T` you pass) | At **declaration** time using the declared bound (`<T extends Comparable>` permits only `Comparable`'s methods) |
| Primitive types | Any type — `Stack<int>`, `Stack<double>` are real distinct types | Reference types only — you must box: `List<Integer>`, never `List<int>` |
| Runtime types | Each instantiation is a real type with its own `typeid`, `vtable`, `sizeof` | All instantiations share one `Class` object; `someList.getClass() == otherList.getClass()` even for different `T` |
| Specialisation | Full + partial specialisation (see `14d`) | None — a single generic implementation handles all `T` |
| Non-type parameters | `template <typename T, size_t N>` (e.g. `std::array<T, 16>`) | None — bounds only, no compile-time integers |
| Variadic | `template <typename... Ts>` + parameter packs (see `14f`) | `T... args` only with a single type |
| Performance | Zero abstraction cost — generated code is as if you'd written it by hand for each `T`. Inlining and devirtualisation work fully | Boxing of primitives + indirection through `Object` + casts → measurable overhead |
| Bounds / constraints | C++17: SFINAE / `enable_if` (rough); C++20: `concepts` (clean) | `<T extends Number & Comparable<T>>` since day one — clean |
| Code size | Each instantiation is real code → large binaries possible (`Stack<int>`, `Stack<long>`, … are separate functions) | One compiled class per generic type → small binaries |
| Variance | C++ is **invariant**: `Stack<Derived>` and `Stack<Base>` are unrelated types. You can't pass one where the other is expected | Java has **wildcards** for variance: `List<? extends Number>` (covariant), `List<? super Integer>` (contravariant) |
| Headers / compilation | Definitions usually live in **headers** — the compiler needs the body to instantiate | One `.class` file is enough; the type-erased generic compiles like any other class |
| Covariant arrays | C++ arrays are NOT covariant: `int*` is unrelated to `long*` | Java arrays ARE covariant: `Number[] = new Integer[10];` (with runtime `ArrayStoreException`). Generics fix this for collections |
| Reflection | `typeid(T)` per instantiation, but no general "list the type parameters" | Limited — you can sometimes recover bounds, but the actual `T` is erased |

**The most useful summary in one line:**
> **Java generics give you ONE compiled class that pretends to handle any `T`. C++ templates give you a CODE GENERATOR that produces a real, distinct class per `T`.**

That single difference explains everything else: why C++ templates can use any operation `T` supports (the compiler will see your actual `T`), why they support `int` and `double` (no boxing — the compiler stamps out an integer version), why partial specialisation exists in C++ but not Java (specialise on what? all instantiations are the same class in Java), why C++ template error messages are an order of magnitude longer (every instantiation site is a fresh, fully-checked compile), and why C++ template definitions have to live in headers (the compiler needs the body to stamp out new versions).

---

## 17. Step 15 — Exceptions

**Files:** `step15_exceptions/15a_*.cpp` … `15d_*.cpp` (4 mini demos)

C++ uses **structured exceptions** for error reporting and recovery. C doesn't have them — the closest tools are return codes, `errno`, and `setjmp`/`longjmp`.

### vs C

| In C | In C++ |
|------|------|
| Caller checks every return code | `try` / `catch` lets a far-away handler take over |
| `errno` for "what went wrong" | The thrown object carries the message and the type |
| Cleanup chains: `goto err1; goto err2;` | Destructors of locals run as the stack unwinds (RAII) |
| `longjmp` skips destructors → leaks/UB | C++ exceptions run destructors → safe cleanup |

### What's in this step

- **`15a_throw_catch.cpp`** — `try { ... } catch (const std::runtime_error&) { ... } catch (...) { ... }`. Always catch by **const reference** (catching by value slices the exception type).
- **`15b_std_exception_hierarchy.cpp`** — the standard tree (`std::logic_error` / `std::runtime_error` / `std::out_of_range` / …) with their `what()` messages, plus how to define your own type by deriving from `std::runtime_error`.
- **`15c_raii_cleanup.cpp`** — the central insight: when an exception propagates, destructors of local objects fire in reverse order. **There is no `finally` in C++ because RAII makes one unnecessary.**
- **`15d_noexcept.cpp`** — `noexcept` is a promise that the function will not throw. Critical for **move constructors / move assignments**: `std::vector` reallocation only chooses move over copy if the move is `noexcept`.

### Rules of thumb

- Throw by value, catch by **`const T&`**.
- Throw types derived from `std::exception` so generic handlers can catch them.
- Never let an exception escape a destructor — call `std::terminate` instead, or absorb it.
- Mark move ctors / move assigns `noexcept` whenever you can.

---

## 18. Step 16 — Lambdas

**Files:** `step16_lambdas/16a_*.cpp` … `16d_*.cpp` (4 mini demos)

A **lambda** is an inline, anonymous function expression. C had only function pointers; you wrote a separate named function and passed its address. C++ lambdas let you write a one-line callback **at the call site**, with controlled access to the surrounding scope.

### Anatomy

```cpp
[capture](parameters) -> return_type { body }
```

Most parts are optional: the return type is usually deduced; `[]` is the empty capture; the parameter list can be empty.

### What's in this step

- **`16a_lambda_basics.cpp`** — syntax tour, including `auto add = [](int a, int b){ return a + b; };` and `std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });`.
- **`16b_lambda_captures.cpp`** — every capture form, plus `mutable`.
- **`16c_lambdas_with_algorithms.cpp`** — the canonical pairing: lambdas as predicates for `count_if` / `find_if` / `transform` / `accumulate` / `sort`.
- **`16d_lambda_internals.cpp`** — a lambda is sugar for an anonymous functor class. Each lambda has its own unique unnamed type (so `auto`); `std::function<R(Args...)>` provides a uniform storage type at the cost of a small heap allocation. Captureless lambdas decay to a plain function pointer (useful for legacy C callbacks).

### Capture clause cheat sheet

| Capture | Meaning |
|------|------|
| `[]` | capture nothing |
| `[=]` | capture every used local **by value** |
| `[&]` | capture every used local **by reference** |
| `[x]` | capture `x` by value |
| `[&x]` | capture `x` by reference |
| `[=, &x]` | default by value, but `x` by reference |
| `[x = expr]` | init capture (C++14) — store a fresh member with a value |
| `mutable` | (after the parameter list) lets the body modify by-value captures |

---

## 19. Step 17 — C++ Casts

**Files:** `step17_casts/17a_*.cpp` … `17d_*.cpp` (4 mini demos)

C had a single cast syntax — `(T)x` — that silently performed any conversion the compiler could think of: numeric, pointer, dropping `const`, all in one. C++ splits it into **four named casts** so that the intent is reviewable in code review and so that suspicious conversions stand out.

### The four casts

| Cast | What it does | When to use |
|------|------|------|
| `static_cast<T>(x)` | Reasonable, compile-time-checked conversions: numeric narrowing, `void*` ↔ `T*`, `enum` ↔ integer, derived ↔ base | the 90 % case — most replacements for C-style `(T)` |
| `dynamic_cast<T>(x)` | Runtime-checked **downcast** in a polymorphic hierarchy. Returns `nullptr` (pointers) or throws `std::bad_cast` (references) on mismatch | downcasting in an inheritance tree where the dynamic type isn't known statically |
| `const_cast<T>(x)` | Add or remove `const` / `volatile` | calling legacy C APIs that take `T*` but don't write; the Meyers idiom for sharing const/non-const member fns |
| `reinterpret_cast<T>(x)` | Bit-level reinterpretation between unrelated types | low-level systems code, hardware registers, type-punning (prefer `std::memcpy`) |

### What's in this step

- **`17a_static_cast.cpp`** — numeric truncation, `void*` ↔ `T*`, `enum class` ↔ integer. The cast that should replace most of your old `(T)x`.
- **`17b_dynamic_cast.cpp`** — `Animal* → Dog*` with `nullptr` check; reference form throwing `std::bad_cast`. Requires the base to be polymorphic (have a virtual function).
- **`17c_const_cast.cpp`** — the legacy-API use case (`legacy_print(const_cast<char*>(s.c_str()))`) and the Meyers idiom for sharing the body of a const and non-const member function. Plus the warning: **modifying a truly-const object via `const_cast` is undefined behaviour**.
- **`17d_reinterpret_cast.cpp`** — bytes of a `float` (correctly via `std::memcpy`), pointer ↔ `uintptr_t`, hardware registers. Notes on strict aliasing.

### vs C

```c
// C — one cast, every meaning collapsed into ()
double d = (double)x;
int*   p = (int*)malloc(...);
char*  m = (char*)s;            // also strips const
```

```cpp
// C++ — explicit names so each line documents itself
double d = static_cast<double>(x);
int*   p = static_cast<int*>(std::malloc(...));   // for C APIs
char*  m = const_cast<char*>(s);
```

---

## 20. C → C++ Cheat Sheet

A one-page summary of every comparison in this lab:

| C idiom | Modern C++ equivalent |
|------|------|
| `printf("%d\n", x)` | `std::cout << x << "\n"` |
| `scanf("%d", &x)` | `std::cin >> x` |
| `char buf[64]; strcpy(buf, s);` | `std::string buf = s;` |
| `strcmp(a, b) == 0` | `a == b` |
| `int b = x ? 1 : 0;` | `bool b = x;` |
| (no `auto` for deduction) | `auto x = expr;` |
| `int abs(int); long labs(long);` | `int abs(int); int abs(long);  // overloaded` |
| `void f(int x, int y);` (no defaults) | `void f(int x, int y = 0);` |
| `gtk_widget_show(...)` | `gtk::widget::show(...)` (namespaces) |
| `void f(int* p)` (may be null) | `void f(int& r)` (never null) |
| `void f(const char* s)` | `void f(const std::string& s)` |
| `#define MAX 10` | `constexpr int MAX = 10;` |
| (no rvalue refs) | `void f(T&& x)` + `std::move` |
| `T* p = malloc(sizeof *p); free(p);` | `auto p = std::make_unique<T>();` |
| `T* a = malloc(n * sizeof *a); free(a);` | `std::vector<T> a(n);` |
| `static int counter;` | `static int counter;` (same) |
| (manual ref counting) | `std::shared_ptr<T>` |
| `#define MAX(a,b) ((a)>(b)?(a):(b))` | `template <typename T> T max_of(T,T);` |
| typed-per-type (`Stack_int`, `Stack_double`, …) | `template <typename T> class Stack;` |
| no compile-time constants in types | `template <typename T, size_t N> ...` (`std::array<T, N>`) |
| variadic via `va_list` (no type safety) | `template <typename... Ts> R f(Ts... args);` (type-safe) |
| return-code error reporting | `throw std::runtime_error(...)` + `try`/`catch` |
| `errno` for "what went wrong" | thrown object's type + `e.what()` |
| `goto err1; goto err2;` cleanup chains | RAII — destructors run automatically on unwind |
| `setjmp`/`longjmp` (skips cleanup) | `throw` + `catch` (runs destructors) |
| function pointer for callbacks | lambda: `[](int x){ return x*2; }` |
| `static int f(...)` named helper | inline `auto f = [](int x){ ... };` at the call site |
| `(T)x` (one cast for everything) | `static_cast<T>(x)` / `dynamic_cast<T>(x)` / `const_cast<T>(x)` / `reinterpret_cast<T>(x)` |

---

For the **OOP** half (classes, inheritance, polymorphism, the Rule of 5, `friend`, …) see the sister lab at [`../cpp-oop-tutorial/`](../cpp-oop-tutorial/).
