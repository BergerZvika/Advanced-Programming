// ============================================================
//  WHAT IS NEO4J?
// ============================================================
// Neo4j is a NATIVE graph database — data is stored as nodes
// and relationships, not as rows in tables. Queries traverse
// edges in O(degree) time instead of doing JOIN after JOIN.
//
// The query language is Cypher, which reads like ASCII art
// of the pattern you want to match:
//
//     (alice:Person)-[:KNOWS {since: 2018}]->(bob:Person)
//
// Each node carries one or more labels (Person, Movie…) and a
// JSON-like map of properties. Relationships are first-class
// objects — they have a type, a direction, and their own
// properties.

// ============================================================
//  ADVANTAGES vs. relational / document DBs
// ============================================================
// 1. Connected-data queries (friend-of-friend, shortest path,
//    impact analysis, fraud rings) are extremely fast — there
//    are no JOINs, just pointer chases through index-free
//    adjacency
// 2. Schema-flexible — new labels / properties drop in at
//    runtime, no DDL migration required
// 3. Cypher is declarative and visual — easy to read, easy to
//    map onto a whiteboard sketch of your domain
// 4. Strong ACID transactions on a single instance, with
//    causal consistency in clusters (3.x+)
// 5. Rich ecosystem: APOC procedures, Bloom for ad-hoc viz,
//    Graph Data Science library for algorithms (PageRank,
//    Louvain, etc.)

// ============================================================
//  DISADVANTAGES
// ============================================================
// 1. Not the right tool for huge aggregate scans across flat,
//    tabular data — column stores (BigQuery, ClickHouse) or
//    classic OLAP engines win there
// 2. Horizontal sharding is harder than in document DBs.
//    Neo4j 4.x added "Fabric" for sharded reads, but a single
//    write leader is still the norm
// 3. Property indexes only out of the box — no built-in
//    full-text search at the level of Elasticsearch (you can
//    integrate one or use Neo4j's bundled Lucene index)
// 4. Cypher is a new language — there's a learning curve if
//    your team only knows SQL
// 5. Memory-hungry for very large graphs; tuning the page
//    cache is an ops task

// ============================================================
//  WHEN TO USE NEO4J
// ============================================================
//   - Social networks, recommendation engines
//   - Fraud detection, money-laundering rings
//   - Knowledge graphs, ontologies, semantic data
//   - Network / IT-asset topology, dependency analysis
//   - Bill-of-materials, supply chain, master-data management
//   - Identity & access management (role/permission graphs)
//   - Causal reasoning over events (incident analysis, etc.)

// ============================================================
//  THE CAP THEOREM — Consistency · Availability · Partition tolerance
// ============================================================
// CAP says that when a distributed database is split by a
// network partition, it can only promise 2 of the 3:
//
//   C — every read sees the latest committed write
//   A — every request gets a (non-error) response
//   P — the system keeps working when nodes can't reach
//       each other
//
// Network partitions are a fact of life on real networks, so
// in practice every distributed DB picks between CP and AP.
//
// ┌──────────────────────────┬──────────────────────────────┐
// │ Database                 │ CAP choice (default config)  │
// ├──────────────────────────┼──────────────────────────────┤
// │ Neo4j Causal Cluster     │ CP — consistent + partition- │
// │                          │      tolerant; writes block  │
// │                          │      while a leader election │
// │                          │      finishes                │
// │ MongoDB (majority writes)│ CP                           │
// │ PostgreSQL single node   │ CA (no partition by design)  │
// │ Cassandra / DynamoDB     │ AP — eventually consistent   │
// │ Redis Cluster            │ AP                           │
// └──────────────────────────┴──────────────────────────────┘
//
// Neo4j chooses CP: writes go to a single LEADER replica and
// are quorum-replicated to FOLLOWER replicas. If the leader is
// partitioned away, the remaining members elect a new leader
// — during that window writes are paused, but no client ever
// sees stale data. Pick Neo4j when the GRAPH SHAPE matters and
// you can't tolerate divergent reads.

// ============================================================
//  Try it out — every Run resets the in-memory graph
// ============================================================
CREATE
  (alice:Person {name: "Alice"}),
  (bob:Person   {name: "Bob"}),
  (carol:Person {name: "Carol"}),
  (alice)-[:KNOWS]->(bob),
  (bob)-[:KNOWS]->(carol)

MATCH (n) RETURN n
