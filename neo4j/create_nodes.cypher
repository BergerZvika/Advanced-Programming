// Create some nodes with different labels and properties
CREATE
  (alice:Person {name: "Alice", age: 30, city: "TLV"}),
  (bob:Person   {name: "Bob",   age: 25, city: "Haifa"}),
  (carol:Person {name: "Carol", age: 35, city: "TLV"}),
  (apple:Company  {name: "Apple",  founded: 1976}),
  (google:Company {name: "Google", founded: 1998})

// View all of them
MATCH (n) RETURN n

// Return only people, only their names
MATCH (p:Person) RETURN p.name AS name, p.age AS age
