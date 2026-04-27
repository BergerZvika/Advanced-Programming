// MERGE = "find a matching pattern, or create it if it doesn't exist".
// Re-running the same MERGE never creates duplicates.

// Creates Alice — no node matches yet
MERGE (:Person {name: "Alice"})

// Same MERGE — finds the existing Alice, no duplicate
MERGE (:Person {name: "Alice"})

// Different props → creates a new node
MERGE (:Person {name: "Bob", age: 25})

// MERGE on a path — creates Alice…KNOWS…Carol if missing,
// or reuses each piece that already exists.
MERGE (alice:Person {name: "Alice"})-[:KNOWS]->(carol:Person {name: "Carol"})

// Run the same path MERGE again — Alice and Carol are reused,
// the KNOWS edge is reused too. Counts: 3 matched / 0 created.
MERGE (alice:Person {name: "Alice"})-[:KNOWS]->(carol:Person {name: "Carol"})

// View the final graph
MATCH (n) RETURN n
