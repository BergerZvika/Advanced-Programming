// Movies dataset — actors, directors, and films from "The Matrix" series.
// Run, then explore with your own MATCH queries.

CREATE
  (keanu:Person   {name:"Keanu Reeves",       born:1964}),
  (carrie:Person  {name:"Carrie-Anne Moss",   born:1967}),
  (laurence:Person {name:"Laurence Fishburne", born:1961}),
  (hugo:Person    {name:"Hugo Weaving",       born:1960}),
  (lana:Person    {name:"Lana Wachowski",     born:1965}),
  (lilly:Person   {name:"Lilly Wachowski",    born:1967}),
  (matrix:Movie    {title:"The Matrix",          released:1999}),
  (matrix2:Movie   {title:"The Matrix Reloaded", released:2003}),
  (matrix3:Movie   {title:"The Matrix Revolutions", released:2003}),

  (keanu)-[:ACTED_IN {role:"Neo"}]->(matrix),
  (carrie)-[:ACTED_IN {role:"Trinity"}]->(matrix),
  (laurence)-[:ACTED_IN {role:"Morpheus"}]->(matrix),
  (hugo)-[:ACTED_IN {role:"Agent Smith"}]->(matrix),
  (lana)-[:DIRECTED]->(matrix),
  (lilly)-[:DIRECTED]->(matrix),

  (keanu)-[:ACTED_IN {role:"Neo"}]->(matrix2),
  (carrie)-[:ACTED_IN {role:"Trinity"}]->(matrix2),
  (laurence)-[:ACTED_IN {role:"Morpheus"}]->(matrix2),
  (lana)-[:DIRECTED]->(matrix2),
  (lilly)-[:DIRECTED]->(matrix2),

  (keanu)-[:ACTED_IN {role:"Neo"}]->(matrix3),
  (carrie)-[:ACTED_IN {role:"Trinity"}]->(matrix3),
  (lana)-[:DIRECTED]->(matrix3)

// Who directed which movie?
MATCH (p:Person)-[:DIRECTED]->(m:Movie) RETURN p.name AS director, m.title AS movie

// Who played Neo, and in how many films?
MATCH (p:Person)-[r:ACTED_IN {role:"Neo"}]->(m:Movie) RETURN p.name, count(m) AS films

// Cast of the original Matrix
MATCH (p:Person)-[r:ACTED_IN]->(:Movie {title:"The Matrix"})
RETURN p.name AS actor, r.role AS role
