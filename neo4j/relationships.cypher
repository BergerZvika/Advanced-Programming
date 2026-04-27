// Build a small employer + friendship graph
CREATE
  (alice:Person {name:"Alice"}),
  (bob:Person   {name:"Bob"}),
  (carol:Person {name:"Carol"}),
  (dave:Person  {name:"Dave"}),
  (apple:Company  {name:"Apple"}),
  (google:Company {name:"Google"}),

  (alice)-[:KNOWS {since:2018}]->(bob),
  (bob)-[:KNOWS   {since:2019}]->(carol),
  (carol)-[:KNOWS {since:2021}]->(dave),
  (alice)-[:KNOWS {since:2020}]->(carol),

  (alice)-[:WORKS_AT {role:"Engineer"}]->(apple),
  (bob)-[:WORKS_AT   {role:"Designer"}]->(apple),
  (carol)-[:WORKS_AT {role:"Manager"}]->(google),
  (dave)-[:WORKS_AT  {role:"Engineer"}]->(google)

MATCH (n) RETURN n
