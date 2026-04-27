// Welcome to Cypher!
// Variable bindings (alice, bob…) are scoped to one statement. Reuse them
// inside the same statement by separating patterns with commas.

CREATE
  (alice:Person {name: "Alice", age: 30}),
  (bob:Person   {name: "Bob",   age: 25}),
  (carol:Person {name: "Carol", age: 35}),
  (alice)-[:KNOWS {since: 2018}]->(bob),
  (bob)-[:KNOWS   {since: 2019}]->(carol),
  (alice)-[:KNOWS {since: 2020}]->(carol)

// Show every node in the graph
MATCH (n) RETURN n
