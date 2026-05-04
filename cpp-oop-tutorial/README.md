# C++ Object-Oriented Programming Tutorial

A hands-on lab that takes you from the basics of classes and constructors all the way through the diamond problem, virtual inheritance, `const` correctness, `friend` access, CRTP, and real-world pitfalls — each concept illustrated with a self-contained, compilable program.

---

## Table of Contents

1. [What Is OOP?](#1-what-is-oop)
2. [Lab Architecture](#2-lab-architecture)
3. [Setup](#3-setup)
4. [Demo 01 — Classes, Constructors, Encapsulation](#4-demo-01--classes-constructors-encapsulation)
5. [Demo 02 — Single Inheritance](#5-demo-02--single-inheritance)
6. [Demo 03 — Virtual Functions & Polymorphism](#6-demo-03--virtual-functions--polymorphism)
7. [Demo 04 — Multiple Inheritance & the Diamond Problem](#7-demo-04--multiple-inheritance--the-diamond-problem)
8. [Demo 05 — Virtual Inheritance](#8-demo-05--virtual-inheritance)
9. [Demo 06 — Advanced OOP](#9-demo-06--advanced-oop)
10. [Demo 07 — Common Pitfalls](#10-demo-07--common-pitfalls)
11. [Demo 08 — const Correctness](#11-demo-08--const-correctness)
12. [Demo 09 — friend Functions & Classes](#12-demo-09--friend-functions--classes)
13. [Demo 10 — Rule of 5 (and Rule of 0)](#13-demo-10--rule-of-5-and-rule-of-0)
14. [Demo 11 — Operator Overloading](#14-demo-11--operator-overloading)
15. [Key Concepts Reference](#15-key-concepts-reference)
16. [Exercises](#16-exercises)
17. [Key Takeaways](#17-key-takeaways)

---

## 1. What Is OOP?

Object-Oriented Programming is a paradigm that models software as a collection of **objects** that combine state (data members) and behaviour (member functions). C++ supports four pillars of OOP:

| Pillar | Meaning |
|--------|---------|
| **Encapsulation** | Bundle data with the methods that operate on it; hide implementation details behind a public interface. |
| **Inheritance** | A derived class acquires the members of a base class, modelling an "is-a" relationship. |
| **Polymorphism** | A single interface (function call) behaves differently depending on the runtime type of the object. |
| **Abstraction** | Express concepts without exposing unnecessary implementation details (pure virtual / interface classes). |

C++ is a multi-paradigm language: OOP coexists with procedural and generic (template) programming. Understanding when to use each is a key skill.

---

## 2. Lab Architecture

```
cpp-oop-tutorial/
├── build.sh           # Compiles every step*/*.cpp into build/<basename>
├── run_all.sh         # Runs every compiled demo in order
├── README.md          # This file
├── index.html         # Single-page interactive lab (CodeMirror + per-demo output)
├── build/             # Created by build.sh (gitignored)
│
├── step1_basics/                  ── one concept per file ──
│   ├── 01a_classes_access.cpp           public / protected / private
│   ├── 01b_default_ctor.cpp             default constructor
│   ├── 01c_param_ctor.cpp               parameterized constructor
│   ├── 01d_member_init_list.cpp         member initializer list
│   ├── 01e_destructor_order.cpp         destructor LIFO order
│   ├── 01f_copy_ctor.cpp                copy constructor
│   ├── 01g_static_members.cpp           static members (Counter)
│   └── 01h_const_methods_and_this.cpp   const methods + 'this' chaining
│
├── step2_inheritance/             ── single inheritance ──
│   ├── 02a_basic_inheritance.cpp        public inheritance is-a
│   ├── 02b_ctor_dtor_order.cpp          base→derived ctor, reverse dtor
│   ├── 02c_protected_members.cpp        protected access in derived
│   ├── 02d_method_hiding.cpp            non-virtual hiding (vs override)
│   ├── 02e_multi_level.cpp              Animal → Mammal → Dog
│   └── 02f_private_inheritance.cpp      implemented-in-terms-of
│
├── step3_polymorphism/            ── virtual + override ──
│   ├── 03a_abstract_class.cpp           pure virtual, abstract class
│   ├── 03b_virtual_dispatch.cpp         vtable runtime dispatch
│   ├── 03c_virtual_destructor.cpp       why ~Base must be virtual
│   ├── 03d_polymorphic_collection.cpp   vector<unique_ptr<Base>>
│   ├── 03e_covariant_return.cpp         derived-pointer override return
│   └── 03f_virtual_call_from_ctor.cpp   pitfall preview
│
├── step4_multiple_inheritance/    ── multiple bases ──
│   ├── 04a_basic_multiple.cpp           Duck = Flyable + Swimmable
│   ├── 04b_name_ambiguity.cpp           scope-resolution Base::method
│   └── 04c_diamond_problem.cpp          two Device sub-objects
│
├── step5_virtual_inheritance/     ── single shared base ──
│   ├── 05a_virtual_inheritance.cpp      diamond fix
│   ├── 05b_amphibious_vehicle.cpp       most-derived initialises virt base
│   ├── 05c_dynamic_cast.cpp             safe runtime downcast
│   └── 05d_typeid_rtti.cpp              typeid / RTTI
│
├── step6_advanced/                ── design patterns ──
│   ├── 06a_interfaces.cpp               pure-virtual classes as interfaces
│   ├── 06b_mixins.cpp                   reusable behaviour bundles
│   ├── 06c_final_keyword.cpp            seal a method or a class
│   ├── 06d_crtp.cpp                     compile-time polymorphism
│   └── 06e_singleton.cpp                Meyers' singleton
│
├── step7_pitfalls/                ── common OOP mistakes ──
│   ├── 07a_object_slicing.cpp           passing polymorphic by value
│   ├── 07b_non_virtual_dtor.cpp         leak through base*
│   ├── 07c_hiding_vs_overriding.cpp     virtual vs non-virtual
│   ├── 07d_range_for_copy.cpp           auto vs const auto&
│   └── 07e_virtual_call_from_ctor.cpp   the full pitfall
│
├── step8_const_correctness/       ── const all the way down ──
│   ├── 08a_const_methods.cpp            const member fns
│   ├── 08b_const_objects.cpp            const objects only call const fns
│   ├── 08c_const_pointers_refs.cpp      const T* / T* const / both
│   ├── 08d_mutable.cpp                  mutable for caches
│   ├── 08e_const_cast.cpp               const_cast (with UB warning)
│   ├── 08f_const_in_inheritance.cpp     const propagation in overrides
│   └── 08g_constexpr.cpp                compile-time evaluation
│
├── step9_friend/                  ── breaking encapsulation, carefully ──
│   ├── 09a_friend_function.cpp          free function, private access
│   ├── 09b_friend_class.cpp             whole class as friend
│   ├── 09c_friend_operators.cpp         operator<< / operator<
│   ├── 09d_mutual_friends.cpp           Celsius ↔ Fahrenheit
│   ├── 09e_friendship_not_inherited.cpp
│   ├── 09f_friendship_not_transitive.cpp
│   └── 09g_friend_vs_getter.cpp         when to use friend vs getter
│
├── step10_rule_of_five/           ── special members & resource ownership ──
│   ├── 10a_default_members.cpp          = default / = delete, what compiler synthesises
│   ├── 10b_rule_of_three.cpp            dtor + copy ctor + copy=
│   ├── 10c_move_semantics.cpp           lvalue / rvalue / std::move (a cast)
│   ├── 10d_move_constructor.cpp         T(T&&) noexcept — steal & null
│   ├── 10e_move_assignment.cpp          T& operator=(T&&) noexcept
│   ├── 10f_rule_of_five.cpp             all 5 special members in one class
│   └── 10g_rule_of_zero.cpp             prefer NONE — let RAII types do the work
│
└── step11_operator_overloading/   ── teach your class to use built-in operators ──
    ├── 11a_arithmetic_operators.cpp     +, -, *, / — non-member preferred
    ├── 11b_compound_assignment.cpp      +=, -= — members; '+ in terms of +='
    ├── 11c_comparison_operators.cpp     ==, !=, <, >, <=, >=
    ├── 11d_increment_decrement.cpp      ++/-- prefix vs postfix
    ├── 11e_subscript_and_call.cpp       operator[]  and  operator()
    ├── 11f_stream_io.cpp                operator<<  and  operator>>  (free + friend)
    └── 11g_conversion_operators.cpp     operator T()  /  explicit operator T()
```

Each `.cpp` file is a **single-concept**, self-contained program with its own `main()`. You can compile and run any one of them independently. Total: **65** mini demos across 11 steps.

---

## 3. Setup

### Prerequisites

- g++ 7+ (or clang++ 5+) with C++17 support
- A POSIX shell (Linux, macOS, WSL)

### Build all demos

```bash
chmod +x build.sh run_all.sh
./build.sh
```

### Run all demos interactively

```bash
./run_all.sh
```

### Run a single demo

```bash
g++ -std=c++17 -Wall -Wextra -g -o build/01a_classes_access step1_basics/01a_classes_access.cpp
./build/01a_classes_access
```

---

## 4. Demo 01 — Classes, Constructors, Encapsulation

**Files:** `step1_basics/01a_*.cpp` … `01h_*.cpp` (8 mini demos)

A class combines data (member variables) and behaviour (member functions). Access modifiers (`public`, `protected`, `private`) enforce encapsulation. The **member initializer list** (after the `:` in a constructor) is the preferred way to initialise members — it is the only way to initialise `const` and reference members.

Static data members exist in a single shared storage location regardless of how many instances exist. The `this` pointer inside a member function refers to the current object and can be returned to enable method chaining.

### Key code

```cpp
class BankAccount {
public:
    BankAccount(const std::string& owner, double initial_balance)
        : owner_(owner), balance_(initial_balance)  // initializer list
    {}

    void deposit(double amount) {
        if (amount <= 0) return;
        balance_ += amount;
    }

    double get_balance() const { return balance_; }   // const member function

    BankAccount& set_owner(const std::string& name) {
        owner_ = name;
        return *this;   // method chaining via 'this'
    }

private:
    std::string owner_;
    double      balance_;    // cannot be accessed as account.balance_ from outside
};

class Counter {
public:
    Counter() { ++count_; }
    ~Counter() { --count_; }
    static int live_count() { return count_; }   // no 'this' — class-level
private:
    static int count_;   // one copy shared by all Counter instances
};
int Counter::count_ = 0;   // definition at file scope
```

### Expected output (excerpt)

```
── Constructors ──
  [Point] Default ctor → (0, 0)
  [Point] Param ctor  → (3, 4)
  (leaving scope — destructors fire in reverse order)
  [Point] ~Point()    → (3, 4)
  [Point] ~Point()    → (0, 0)

── Static Members (Counter) ──
  Live counters before any: 0
  [Counter] Counter #1 created  (total live: 1)
  [Counter] Counter #2 created  (total live: 2)
  [Counter] Counter #3 created  (total live: 3)
  ...
  Live counters after all destroyed: 0
```

---

## 5. Demo 02 — Single Inheritance

**Files:** `step2_inheritance/02a_*.cpp` … `02f_*.cpp` (6 mini demos)

Public inheritance models the "is-a" relationship: `Dog` is-a `Mammal` is-a `Animal`. The derived class constructor must call the base constructor in its initializer list. Destructors run in **reverse** construction order: derived first, then base.

`protected` members are accessible within the class and all derived classes, but not from outside. A non-virtual method in the base is **hidden** (not overridden) by a same-name method in the derived class — a base pointer will always call the base version.

### Key code

```cpp
class Animal {
public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {}
    std::string sound() const { return "<silence>"; }   // non-virtual — hidden, not overridden
protected:
    std::string name_;
    int         age_;
};

class Mammal : public Animal {
public:
    Mammal(const std::string& name, int age, bool has_fur)
        : Animal(name, age),    // ← base ctor called here
          has_fur_(has_fur) {}
    std::string sound() const { return "<mammal grunt>"; }  // hides Animal::sound
private:
    bool has_fur_;
};

class Dog : public Mammal {
public:
    Dog(const std::string& name, int age, const std::string& breed)
        : Mammal(name, age, true), breed_(breed) {}
    std::string sound() const { return "Woof!"; }  // hides Mammal::sound
private:
    std::string breed_;
};
```

### Expected output (excerpt)

```
── Constructor & Destructor Order ──
  [Animal] ctor → Rex
  [Mammal] ctor → Rex
  [Dog] ctor → Rex (German Shepherd)
  Object fully constructed.
  (leaving scope...)
  [Dog] dtor → Rex
  [Mammal] dtor → Rex
  [Animal] dtor → Rex

── Method Hiding vs. Static Dispatch ──
  Dog    sound(): Woof!
  Mammal sound(): <mammal grunt>
  Animal sound(): <silence>
  Animal* pointing at Dog → sound(): <silence>  ← base version called (no virtual)
```

---

## 6. Demo 03 — Virtual Functions & Polymorphism

**Files:** `step3_polymorphism/03a_*.cpp` … `03f_*.cpp` (6 mini demos)

Adding `virtual` to a method instructs the compiler to generate a **vtable** (virtual dispatch table). When the method is called through a base pointer or reference, the runtime consults the vtable and dispatches to the actual type's implementation. Derived overrides must be marked `override` — the compiler then verifies the signature matches exactly.

A **pure virtual** function (`= 0`) makes the class **abstract**: it cannot be instantiated, only subclassed. A **virtual destructor** is mandatory when objects may be deleted through a base pointer; without it, the derived destructor never runs and resources leak.

### Key code

```cpp
class Shape {
public:
    virtual ~Shape() {}                      // virtual destructor — CRITICAL
    virtual double area()      const = 0;   // pure virtual → Shape is abstract
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
    virtual Shape* clone()     const = 0;   // covariant return type in derived
};

class Circle : public Shape {
public:
    Circle(double r, const std::string& color = "red")
        : Shape(color), radius_(r) {}
    double area()      const override { return M_PI * radius_ * radius_; }
    double perimeter() const override { return 2.0 * M_PI * radius_; }
    std::string name() const override { return "Circle"; }
    Circle* clone()    const override { return new Circle(radius_, color_); }
private:
    double radius_;
};
```

### Expected output (excerpt)

```
── Virtual Destructor ──
  Deleting Circle through a Shape* — should call ~Circle then ~Shape:
  [Circle] ctor r=3
  [Circle] dtor r=3
  [Shape] dtor

── Polymorphic Collection (vector<unique_ptr<Shape>>) ──
  Shape(Circle) color=red area=12.5664 perimeter=12.5664
  Shape(Rectangle) color=blue area=15 perimeter=16
  Shape(Triangle) color=green area=24 perimeter=24
  Total area of all shapes: 51.5...
```

---

## 7. Demo 04 — Multiple Inheritance & the Diamond Problem

**Files:** `step4_multiple_inheritance/04a_*.cpp` … `04c_*.cpp` (3 mini demos)

C++ allows a class to inherit from multiple base classes simultaneously. Base constructors run in **declaration order**; destructors run in reverse. When two bases define a method with the same name, the call is **ambiguous** and must be qualified with `Base::method()`.

The **diamond problem** arises when two base classes share a common ancestor. Without `virtual` inheritance, the most-derived class contains **two separate copies** of the shared base — one per path through the diamond. This causes ambiguous method calls, duplicate construction/destruction, and wasted memory.

### Key code

```cpp
//      Device
//     /      \
// Printer   Scanner    (no 'virtual' — each gets its own Device)
//     \      /
//    AllInOne           (has TWO Device sub-objects)

class AllInOne : public Printer, public Scanner {
public:
    AllInOne()
        : Printer("PrintCo"),   // initialises Printer's Device
          Scanner("ScanCo")     // initialises Scanner's Device (separate!)
    {}
};

AllInOne aio;
// aio.powerOn();              // ERROR: ambiguous
aio.Printer::powerOn();        // OK: explicitly pick Printer's copy
aio.Scanner::powerOn();        // OK: explicitly pick Scanner's copy

// The two Device sub-objects live at different addresses:
const Device* via_printer = static_cast<Printer*>(&aio);
const Device* via_scanner = static_cast<Scanner*>(&aio);
// via_printer != via_scanner  — TWO COPIES
```

### Expected output (excerpt)

```
  sizeof(Device)  = 32 bytes
  sizeof(AllInOne)= 80 bytes  ← contains TWO Device sub-objects

  Device via Printer @ 0x...
  Device via Scanner @ 0x...  (different address)
  Same object? NO — TWO COPIES!
```

---

## 8. Demo 05 — Virtual Inheritance

**Files:** `step5_virtual_inheritance/05a_*.cpp` … `05d_*.cpp` (4 mini demos)

Adding the `virtual` keyword to an inheritance relationship tells the compiler to share a single copy of the virtual base among all paths through the diamond. The **most-derived class** is responsible for initialising the virtual base in its initializer list; intermediate classes' attempts to initialise it are ignored.

Constructor order changes: **virtual bases always initialise first**, before any non-virtual bases, regardless of their position in the declaration list. `dynamic_cast` provides a safe runtime downcast — it returns `nullptr` on failure instead of causing undefined behaviour.

### Key code

```cpp
class VPrinter : public virtual VDevice { ... };  // 'virtual' keyword here
class VScanner : public virtual VDevice { ... };

class VAllInOne : public VPrinter, public VScanner {
public:
    VAllInOne(const std::string& brand = "AllInOneCo")
        : VDevice(brand),    // most-derived initialises virtual base — mandatory
          VPrinter(),        // VPrinter's VDevice(...) is ignored
          VScanner()
    {}
};

// Safe downcast with dynamic_cast:
RTTIBase* base = new RTTIDerived();
RTTIDerived* derived = dynamic_cast<RTTIDerived*>(base);
if (derived) { derived->derived_only(); }   // safe — no crash if type mismatch

RTTIBase* plain = new RTTIBase();
RTTIDerived* fail = dynamic_cast<RTTIDerived*>(plain);
// fail == nullptr — dynamic_cast returned nullptr safely
```

### Expected output (excerpt)

```
  sizeof(VDevice)   = 24 bytes
  sizeof(VAllInOne) = 56 bytes  ← ONE VDevice sub-object (+ vptr overhead)

  VDevice via VPrinter @ 0x...
  VDevice via VScanner @ 0x...  (SAME address)
  Same object? YES — ONE COPY!
```

---

## 9. Demo 06 — Advanced OOP

**Files:** `step6_advanced/06a_*.cpp` … `06e_*.cpp` (5 mini demos)

This demo covers four advanced patterns and one classic design pattern.

**Interfaces** are pure abstract classes with no data members. They define a contract; any class can implement multiple interfaces via multiple inheritance with no diamond risk (no shared state to duplicate).

**Mixins** add reusable behaviour to a class through multiple inheritance. Unlike interfaces, mixins carry state and default implementations. `BlogPost` inherits `TimestampMixin` and `TagsMixin` to gain timestamps and tagging without duplicating that code.

**`final`** locks a class against further subclassing or a virtual method against further overriding, enabling compiler optimisations and expressing design intent.

**CRTP** (Curiously Recurring Template Pattern) achieves static polymorphism at compile time. The base template receives the derived type as a template parameter and casts `this` to call derived methods — all resolved at compile time with zero vtable overhead.

**Singleton** ensures at most one instance exists by hiding the constructor and deleting the copy constructor and assignment operator.

### Key code

```cpp
// Interface — pure abstract, no data
class ISerializable {
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
};

// CRTP — static polymorphism, no vtable
template<typename Derived>
class Printable {
public:
    void print() const {
        // Resolved at compile time — no runtime overhead
        std::cout << static_cast<const Derived*>(this)->toString() << "\n";
    }
};

class Point : public Printable<Point> {
public:
    std::string toString() const { return "Point(x, y)"; }
};

// final — cannot subclass or override further
class Sealed final { ... };
class Middle : public Base {
    void go() const override final { ... }  // cannot override below Middle
};

// Singleton
class AppConfig {
public:
    static AppConfig& instance() {
        static AppConfig inst;   // constructed once
        return inst;
    }
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
private:
    AppConfig() {}
};
```

### Expected output (excerpt)

```
── 1. Interfaces (ISerializable, ILoggable) ──
  Serialized: User{id=42,name=Alice,email=alice@example.com}
  [LOG] User id=42 name=Alice

── 4. CRTP (Static Polymorphism) ──
  Point::print()  → Point(3.000000, 4.000000)
  Color::print()  → Color(r=255, g=128, b=0)

── 5. Singleton Pattern ──
  [AppConfig] Singleton constructed
  &cfg1 == &cfg2? YES — same instance
```

---

## 10. Demo 07 — Common Pitfalls

**Files:** `step7_pitfalls/07a_*.cpp` … `07e_*.cpp` (5 mini demos)

Each pitfall is shown first in a broken/dangerous form (labelled `[WRONG]`), then corrected (labelled `[CORRECT]`).

**Object slicing:** Assigning a derived object to a base-type variable by value strips the derived data and vtable. The result is a plain base object with no connection to the original derived type.

**Non-virtual destructor:** Deleting a derived object through a base pointer with a non-virtual destructor silently skips the derived destructor — resources allocated in the derived class are leaked.

**Hiding vs overriding:** Non-virtual methods are hidden (not overridden) in derived classes. A base pointer always calls the base version. This is a common source of subtle bugs when a developer expects polymorphic behaviour but forgets `virtual`.

**Accidental copy in range-for:** `for (auto obj : vec)` copies every element. For large objects this wastes time; for polymorphic containers it causes slicing.

**Virtual call from constructor:** During construction of a base class, the vtable points to the base implementation. Virtual calls inside a base constructor dispatch to the base version, not the derived one — the derived portion of the object does not exist yet.

### Key code

```cpp
// PITFALL 1 — slicing
Animal sliced = dog;           // WRONG — Dog data is gone
sliced.sound();                // returns "<silence>", not "Woof!"
Animal* ptr = &dog;            // CORRECT — vtable intact
ptr->sound();                  // returns "Woof!"

// PITFALL 2 — non-virtual destructor
LeakyBase* p = new LeakyDerived();
delete p;    // WRONG — ~LeakyDerived never called, buffer_ leaks
             // FIX: declare virtual ~LeakyBase()

// PITFALL 3 — hiding vs overriding
HideBase* bp = &derived_obj;
bp->describe_hidden();    // calls HideBase version (non-virtual — hidden)
bp->describe_virtual();   // calls HideDerived version (virtual — overridden)

// PITFALL 4 — range-for copy
for (auto obj : vec)         { ... }  // WRONG — copies each element
for (const auto& obj : vec)  { ... }  // CORRECT — no copy

// PITFALL 5 — virtual call from ctor
class Parent {
    Parent() { greet(); }         // dispatches to Parent::greet — NOT Child::greet
    virtual void greet() const;
};
```

### Expected output (excerpt)

```
── Pitfall 1: Object Slicing ──
  [WRONG] sliced.sound() = <silence>  ← should be Woof! but we get base class result
  [CORRECT] ptr->sound() = Woof!  ← vtable intact, correct dispatch

── Pitfall 2: Non-Virtual Destructor ──
  [WRONG] delete through base pointer with non-virtual dtor:
  [LeakyDerived] ctor — allocated 256-byte buffer
  [LeakyBase] dtor (non-virtual)
  ^^^ ~LeakyDerived never ran → buffer_ leaked!

  [CORRECT] delete through base pointer with virtual dtor:
  [SafeDerived] ctor — allocated 256-byte buffer
  [SafeDerived] dtor — freed buffer
  [SafeBase] dtor (virtual)
```

---

## 11. Demo 08 — const Correctness

`const` correctness is the discipline of marking every function and variable that
doesn't need to mutate as `const`. It costs nothing at runtime but lets the compiler
catch accidental mutations and enables more aggressive optimisations.

**Key concepts**

| Form | Meaning |
|------|---------|
| `void f() const` | member function cannot modify any data member |
| `const T obj` | object — only `const` methods callable |
| `const T&` | read-only reference — no copy, no modification |
| `const T*` | pointer-to-const — can't modify through pointer |
| `T* const` | const pointer — pointer itself can't be reassigned |
| `mutable` | member is exempt from `const`; modifiable in `const` methods |
| `const_cast<T&>` | strips const — UB if underlying object was truly const |
| `constexpr` | value/function evaluated at compile time |

**Lazy cache with `mutable`**
```cpp
class ExpensiveCalc {
public:
    double result() const {
        if (!cached_) {               // const method …
            cache_  = compute();      // … but mutable fields can be written
            cached_ = true;
        }
        return cache_;
    }
private:
    double input_;
    mutable double cache_  = 0.0;
    mutable bool   cached_ = false;
};
```

**Three pointer forms — easy to confuse**
```cpp
const int* pc  = &x;   // pointer-to-const:  *pc read-only,  pc reassignable
int* const cp  = &x;   // const-pointer:     *cp writable,   cp fixed
const int* const cpc = &x;  // both read-only
```

Run the demo:
```bash
./build/08_const_correctness
```

---

## 12. Demo 09 — friend Functions & Classes

`friend` grants a specific function or class direct access to another class's
`private` and `protected` members. It is a deliberate, named exception to
encapsulation — not a way to bypass it carelessly.

**Rules**
- Friendship is **not inherited** — derived classes don't get it automatically.
- Friendship is **not transitive** — friend-of-a-friend is not your friend.
- Friendship is **not symmetric** — A befriending B does not mean B befriends A.

**friend function — canonical use: `operator<<`**
```cpp
class BankAccount {
    friend std::ostream& operator<<(std::ostream&, const BankAccount&);
private:
    std::string owner_;
    double      balance_;
};

std::ostream& operator<<(std::ostream& os, const BankAccount& acc) {
    return os << acc.owner_ << " $" << acc.balance_;  // direct private access
}
```

**friend class — tightly coupled pairs**
```cpp
class Vector2D {
    friend class Matrix;   // all Matrix methods can read x_, y_
private:
    double x_, y_;
};

class Matrix {
public:
    Vector2D operator*(const Vector2D& v) const {
        return Vector2D(a_*v.x_ + b_*v.y_,   // private x_, y_ directly
                        c_*v.x_ + d_*v.y_);
    }
    …
};
```

**Friendship not inherited**
```cpp
class Base   { friend class Inspector; int secret_ = 42; };
class Derived : public Base { int other_ = 99; };

class Inspector {
    void check(const Base& b)    { b.secret_; }   // OK — Base is friend
    void check(const Derived& d) { d.other_;  }   // ERROR — Derived is NOT friend
};
```

Run the demo:
```bash
./build/09_friend
```

---

## 13. Demo 10 — Rule of 5 (and Rule of 0)

**Files:** `step10_rule_of_five/10a_*.cpp` … `10g_*.cpp` (7 mini demos)

The **Rule of 5** says: if a class manages a raw resource (heap buffer, file handle, mutex, network socket, …) and you find yourself defining ANY of these five special member functions, you almost certainly need to define **all five**:

1. **Destructor** — release the resource.
2. **Copy constructor** — make a deep copy.
3. **Copy assignment** — release current, deep-copy from source.
4. **Move constructor** — steal the source's resource, null its handle. `noexcept`.
5. **Move assignment** — release current, steal, null source. `noexcept`.

The **Rule of 0** is the modern alternative: prefer to write **none** of them. Compose your class out of types that already manage their own resources (`std::string`, `std::vector`, `std::unique_ptr`, `std::shared_ptr`) and the compiler-synthesised members will do the right thing for free.

### Key code

```cpp
class Buffer {
    std::size_t n_;
    int*        data_;
public:
    explicit Buffer(std::size_t n) : n_(n), data_(new int[n]) {}

    // 1. destructor
    ~Buffer() { delete[] data_; }

    // 2. copy ctor — deep copy
    Buffer(const Buffer& o) : n_(o.n_), data_(new int[o.n_]) {
        std::memcpy(data_, o.data_, n_ * sizeof(int));
    }

    // 3. copy assignment — release, deep-copy, return *this
    Buffer& operator=(const Buffer& o) {
        if (this == &o) return *this;
        delete[] data_;
        n_    = o.n_;
        data_ = new int[o.n_];
        std::memcpy(data_, o.data_, n_ * sizeof(int));
        return *this;
    }

    // 4. move ctor — steal & null. noexcept!
    Buffer(Buffer&& o) noexcept : n_(o.n_), data_(o.data_) {
        o.n_ = 0; o.data_ = nullptr;
    }

    // 5. move assignment — release, steal & null. noexcept!
    Buffer& operator=(Buffer&& o) noexcept {
        if (this == &o) return *this;
        delete[] data_;
        n_      = o.n_;    data_   = o.data_;
        o.n_    = 0;       o.data_ = nullptr;
        return *this;
    }
};
```

`std::move` itself does NOT move — it is a **cast** that turns an lvalue into an rvalue reference. The actual move only happens when an operation (a move ctor, a move assignment) consumes that rvalue ref.

### Why `noexcept` matters
`std::vector` and other STL containers will only choose your move ctor/assignment over the copy versions if they are marked `noexcept`. A throwing move during reallocation could leave the container in an inconsistent state, so the standard library refuses to take that risk.

---

## 14. Demo 11 — Operator Overloading

**Files:** `step11_operator_overloading/11a_*.cpp` … `11g_*.cpp` (7 mini demos)

C++ lets your class type behave like a built-in: write `a + b`, `v[i]`, `*p`, `cout << x`, `if (handle)` and have it call code you wrote. Each operator is just a function with a special name (`operator+`, `operator[]`, `operator<<`, …).

### Two forms

| Form | Signature | Use when |
|------|------|------|
| **Member function** | `T T::operator@(args) const;` | left side is always `*this`; you want it to be a member of the class. **Required** for `=`, `[]`, `()`, `->`. |
| **Non-member (free)** | `T operator@(const T&, const T&);` | binary operators that should be **symmetric** under implicit conversion (e.g. `2 + v` AND `v + 2`). Often `friend` if it needs private access. |

### What's in this step

- **`11a_arithmetic_operators.cpp`** — binary `+`, `-`, `*`, `/`. Implemented as **non-member** so `2 * v` and `v * 2` both work. Take the first operand by value to use it as a working copy; return by value.
- **`11b_compound_assignment.cpp`** — `+=`, `-=`, `*=`, `/=`, `%=`. Always members, mutate `*this`, return `*this` by reference. Idiom: implement free `+` in terms of `+=` so the math lives in one place.
- **`11c_comparison_operators.cpp`** — implement `==` and `<` as primitives; derive `!=`, `>`, `<=`, `>=` from them. Once you have `<` and `==`, your type is usable in `std::sort`, `std::set<T>`, `std::map<T, ...>`, `std::find`, etc. (Brief mention of C++20 `<=>` to generate them all.)
- **`11d_increment_decrement.cpp`** — prefix `++c` returns `T&`; postfix `c++` returns `T` (a copy of the old value) and takes a dummy `int` parameter. Prefer prefix when you don't need the old value.
- **`11e_subscript_and_call.cpp`** — `operator[]` provided in **two overloads** (one returning `T&`, one returning `const T&`) so const objects can read but not write. `operator()` lets your object be called like a function (also covered as functors in the STL lab).
- **`11f_stream_io.cpp`** — `operator<<` / `operator>>` are **free functions** because the left operand is `std::ostream`/`std::istream`. Often `friend` to read/write private state. Always return the stream by reference so insertions chain: `cout << a << b << c;`.
- **`11g_conversion_operators.cpp`** — user-defined conversions: `operator T() const` (implicit) and `explicit operator T() const` (only via cast or in a context that **expects** `bool`/`int`). The "safe-bool" idiom uses `explicit operator bool()`.

### Cheat sheet

| Operator | Form | Returns | Notes |
|------|------|------|------|
| `a + b` | non-member | `T` (by value) | symmetric; can `friend` if needs privates |
| `a += b` | member | `T&` (`*this`) | mutates self |
| `a == b`, `a < b` | non-member | `bool` | implement these two; derive the rest |
| `++c` (prefix) | member | `T&` | no extra copy |
| `c++` (postfix) | member | `T` (the OLD value) | takes a dummy `int` parameter |
| `c[i]` | member | `T&` and `const T&` | provide both overloads |
| `c(args...)` | member | anything | makes the object callable / a functor |
| `os << x` | non-member | `std::ostream&` | `friend` if x has private state |
| `is >> x` | non-member | `std::istream&` | check `is` for failure on bad input |
| `static_cast<T>(x)` | member | `T` | use `explicit operator T()` to opt out of implicit conversions |

### Operators you generally should NOT overload

- `&&`, `||` — short-circuit semantics are LOST in user-defined overloads (operands always evaluated).
- `,` (comma) — you'll surprise more readers than you help.
- `&` (address-of) — almost always a mistake; breaks code that takes `&obj` for real.
- `->*` (pointer-to-member) — almost no one uses it.

---

## 15. Key Concepts Reference

| Concept | Rule |
|---------|------|
| virtual destructor | Always declare virtual if the class has virtual methods or may be deleted through a base pointer |
| override | Always use `override` in derived classes — compiler catches typos and signature mismatches |
| object slicing | Never pass polymorphic objects by value — use pointer or reference |
| diamond problem | Use `virtual` base class when two inheritance paths lead to the same base |
| virtual base init | Most-derived class must initialize virtual bases in its initializer list |
| pure virtual | Makes the class abstract; derived classes must implement or they are also abstract |
| CRTP | Static polymorphism — method dispatch resolved at compile time, no vtable cost |
| final | Prevents further subclassing (on class) or overriding (on method) |
| initializer list | Prefer member initializer list over assignment in constructor body; required for const/reference members |
| hiding vs overriding | Non-virtual methods are hidden (not overridden); base pointer always calls base version |
| virtual from ctor | Never call virtual functions from constructors or destructors |
| range-for by value | `for (auto x : v)` copies; use `for (const auto& x : v)` unless a copy is needed |
| access modifiers | `public` = anyone; `protected` = class + derived; `private` = class only |
| static member | Shared across all instances; must be defined at file scope outside the class |
| const method | Mark `const` if the method doesn't modify state; required to call it on a `const` object |
| const object | Can only call `const`-qualified methods; enforced at compile time |
| mutable | Allows a member to be modified inside `const` methods; used for caches and counters |
| const_cast | Strips constness from pointer/reference; UB if the underlying object was truly `const` |
| constexpr | Value or function evaluated at compile time; stronger and broader guarantee than `const` |
| friend function | Named free function that can access `private`/`protected` members directly |
| friend class | All methods of the named class can access `private`/`protected` members |
| friendship rules | Not inherited, not transitive, not symmetric; limit to operator overloading and tightly coupled pairs |

---

## 16. Exercises

1. **(Easy — Demo 01)** Add a `transaction_history_` member to `BankAccount` (a `std::vector<double>`) and extend `deposit()` and `withdraw()` to record each amount. Add a `print_history()` method. Notice that the copy constructor does NOT deep-copy the history by default — fix it.

2. **(Easy — Demo 02)** Add a `Bird` class that inherits from `Animal` and a `Parrot` class that inherits from `Bird`. Give `Bird` a `wingspan_` member and a non-virtual `fly()` method. Override `sound()` in `Parrot` (still non-virtual). Then observe what happens when you call `fly()` and `sound()` through an `Animal*`.

3. **(Medium — Demo 03)** Add a `Square` class that inherits `Rectangle` (pass the same value for width and height). Add a `describe()` override that prints "Square" instead of "Rectangle". Store a mix of shapes in a `vector<unique_ptr<Shape>>` and compute the total perimeter.

4. **(Medium — Demo 04)** Extend the diamond example: add a `fax()` method to a new `FaxMachine` class that also inherits (non-virtual) `Device`. Create a `SuperAllInOne` that inherits `AllInOne` and `FaxMachine`. Count how many `Device` ctors fire and explain the memory layout using `sizeof`.

5. **(Medium — Demo 05)** Convert the non-virtual `Device` hierarchy from Demo 04 to use `virtual` inheritance throughout. Verify (by printing addresses) that `SuperAllInOne` now contains exactly one `Device`. Notice the change in sizeof values.

6. **(Hard — Demo 06)** Extend the CRTP `Comparable` example to also provide `operator<`, `operator<=`, `operator>`, and `operator>=` from just `operator<` defined in the derived class (similar to how `std::rel_ops` works, but via CRTP). Test with `Temperature` and a new `Distance` class.

7. **(Hard — Demo 06)** Implement a `ThreadSafeSingleton` using a mutex and double-checked locking (or `std::call_once`). Add a `reset()` method that's only available in test builds (controlled via a `#ifdef TESTING` preprocessor guard).

8. **(Hard — Demo 07)** Create a benchmark that allocates 100,000 `Animal` objects in a `vector<Animal>` (causing slicing) vs a `vector<unique_ptr<Animal>>` (no slicing). Measure the time difference using `std::chrono::high_resolution_clock` and print the results. Then extend the benchmark to compare virtual dispatch vs CRTP for the `sound()` method.

9. **(Medium — Demo 08)** Add a `Cache<T>` class template with a `value() const` method that stores its result in a `mutable` cache member. Make the computation function a `std::function` passed to the constructor. Call `value()` three times and verify via a counter that the computation only runs once. Try making the `Cache` object `const` — does everything still work?

10. **(Hard — Demo 09)** Implement a `LinkedList<T>` class and a separate `LinkedListIterator<T>` class. Grant `LinkedListIterator` friend access to `LinkedList` so the iterator can walk the private node pointers. Then verify that a class derived from `LinkedListIterator` does NOT inherit that friendship (the derived iterator cannot access the list's private nodes).

---

## 17. Key Takeaways

- **Encapsulate aggressively.** Make data `private`; expose only what callers need. The `BankAccount` demo shows how private data enforces invariants that public data cannot.

- **Constructor chaining is automatic but explicit in the initializer list.** Always call the base constructor explicitly when it requires arguments. Omitting it compiles only if the base has a default constructor.

- **`virtual` changes everything.** Without it, method calls are resolved at compile time based on the pointer/reference type (static dispatch). With it, calls are resolved at runtime based on the actual object (dynamic dispatch via vtable).

- **Always declare a virtual destructor when you have virtual methods.** This is one of the most common C++ bugs. If a class is meant to be a base class and objects may be deleted through a base pointer, the destructor must be virtual.

- **Always use `override`.** It is free documentation and free compiler checking. If you accidentally mistype the method name or change the signature, the compiler catches it immediately.

- **Multiple inheritance is a tool, not a problem — used carefully.** Interfaces (pure abstract) and mixins are safe patterns. The diamond problem only bites when a concrete base is shared; `virtual` inheritance solves it, at the cost of slightly more complex initialisation rules.

- **CRTP gives you polymorphism without a vtable.** When the dispatch target is known at compile time, prefer CRTP over virtual functions. This is used extensively in the standard library (`std::enable_shared_from_this`, iterators, etc.).

- **Object slicing is silent and deadly.** The compiler will not warn you. The only protection is discipline: never store polymorphic objects by value in containers or pass them by value to functions. Use `unique_ptr` or references.

- **Virtual calls from constructors lie.** During base construction, the vtable pointer is set to the base vtable. The derived class simply does not exist yet. Design constructors to avoid this.

- **`const auto&` in range-for is the safe default.** A copy costs both time and correctness. Add it by habit and remove it only when you deliberately want a local copy.

- **`const` correctness is free correctness.** Mark every method and parameter that doesn't mutate state as `const`. The compiler enforces your intent, prevents bugs, enables optimisations, and documents the API. Retrofitting `const` into an existing codebase is painful — get it right from the start.

- **`friend` is a named exception, not a workaround.** Use it when two classes are so tightly coupled that getters would leak implementation detail to everyone. The canonical cases are `operator<<`, arithmetic operators, and iterator/container pairs. Never use it just to bypass encapsulation you disagree with.
