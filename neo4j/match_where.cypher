// Set up a tiny dataset
CREATE
  (alice:Person {name:"Alice", age:30, city:"TLV"}),
  (bob:Person   {name:"Bob",   age:25, city:"Haifa"}),
  (carol:Person {name:"Carol", age:35, city:"TLV"}),
  (dave:Person  {name:"Dave",  age:42, city:"Jerusalem"})

// All people
MATCH (n:Person) RETURN n

// Filter with WHERE — comparisons
MATCH (p:Person) WHERE p.age >= 30 RETURN p.name AS name, p.age AS age

// Equality
MATCH (p:Person) WHERE p.city = "TLV" RETURN p.name

// Inline equality (in the pattern itself)
MATCH (p:Person {city: "TLV"}) RETURN p.name

// IN list
MATCH (p:Person) WHERE p.name IN ["Alice", "Dave"] RETURN p

// ORDER BY + LIMIT
MATCH (p:Person) RETURN p.name, p.age ORDER BY p.age DESC LIMIT 2
