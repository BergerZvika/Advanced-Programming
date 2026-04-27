// Seed some data first (the in-memory graph resets every Run)
CREATE
  (:Person {name: "Alice", age: 30, city: "Haifa"}),
  (:Person {name: "Bob",   age: 25, city: "TLV"}),
  (:Person {name: "Carol", age: 35, city: "TLV"})

// SET — overwrite a single property on a single node
MATCH (alice:Person {name: "Alice"}) SET alice.age = 31

// SET multiple properties at once
MATCH (alice:Person {name: "Alice"}) SET alice.role = "Engineer", alice.city = "TLV"

// SET on every matching node — works on whole rows
MATCH (p:Person) SET p.year = 2025

// SET also adds a label (a node can carry several)
MATCH (alice:Person {name: "Alice"}) SET alice:Admin

// REMOVE a property
MATCH (alice:Person {name: "Alice"}) REMOVE alice.role

// REMOVE a label
MATCH (alice:Person {name: "Alice"}) REMOVE alice:Admin

// View the final state
MATCH (n) RETURN n
