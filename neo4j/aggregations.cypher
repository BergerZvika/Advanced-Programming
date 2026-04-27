CREATE
  (alice:Person {name:"Alice", age:30}),
  (bob:Person   {name:"Bob",   age:25}),
  (carol:Person {name:"Carol", age:35}),
  (dave:Person  {name:"Dave",  age:42}),
  (apple:Company  {name:"Apple"}),
  (google:Company {name:"Google"}),
  (alice)-[:WORKS_AT]->(apple),
  (bob)-[:WORKS_AT]->(apple),
  (carol)-[:WORKS_AT]->(google),
  (dave)-[:WORKS_AT]->(google)

// How many people?
MATCH (p:Person) RETURN count(p) AS people

// Average / min / max age
MATCH (p:Person) RETURN avg(p.age) AS avgAge, min(p.age) AS youngest, max(p.age) AS oldest

// Group by company → headcount
MATCH (p:Person)-[:WORKS_AT]->(c:Company)
RETURN c.name AS company, count(p) AS headcount
ORDER BY headcount DESC
