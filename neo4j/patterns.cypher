// A small social graph
CREATE
  (a:Person {name:"Alice"}),
  (b:Person {name:"Bob"}),
  (c:Person {name:"Carol"}),
  (d:Person {name:"Dave"}),
  (e:Person {name:"Eve"}),
  (a)-[:KNOWS]->(b),
  (b)-[:KNOWS]->(c),
  (c)-[:KNOWS]->(d),
  (a)-[:KNOWS]->(d),
  (d)-[:KNOWS]->(e)

// All the graph
MATCH (n) RETURN n

// Direct friends of Alice
MATCH (:Person {name:"Alice"})-[:KNOWS]->(friend) RETURN friend.name

// Friends-of-friends of Alice (excluding Alice and her direct friends)
MATCH (:Person {name:"Alice"})-[:KNOWS]->()-[:KNOWS]->(fof)
RETURN DISTINCT fof.name

// Directed pair (A knows B)
MATCH (a:Person)-[:KNOWS]->(b:Person) RETURN a.name AS from, b.name AS to
