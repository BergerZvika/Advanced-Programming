// A small social graph with KNOWS and LIKES relationships,
// nice for trying friend-of-friend and recommendation queries.

CREATE
  (alice:Person  {name:"Alice",  age:30}),
  (bob:Person    {name:"Bob",    age:25}),
  (carol:Person  {name:"Carol",  age:35}),
  (dave:Person   {name:"Dave",   age:42}),
  (eve:Person    {name:"Eve",    age:28}),
  (frank:Person  {name:"Frank",  age:33}),
  (grace:Person  {name:"Grace",  age:29}),
  (heidi:Person  {name:"Heidi",  age:31}),
  (jazz:Hobby    {name:"Jazz"}),
  (chess:Hobby   {name:"Chess"}),
  (cooking:Hobby {name:"Cooking"}),

  (alice)-[:KNOWS {since:2018}]->(bob),
  (alice)-[:KNOWS {since:2020}]->(carol),
  (bob)-[:KNOWS   {since:2019}]->(dave),
  (carol)-[:KNOWS {since:2021}]->(eve),
  (dave)-[:KNOWS  {since:2017}]->(frank),
  (eve)-[:KNOWS   {since:2022}]->(frank),
  (frank)-[:KNOWS {since:2023}]->(grace),
  (grace)-[:KNOWS {since:2024}]->(heidi),
  (alice)-[:KNOWS {since:2024}]->(heidi),

  (alice)-[:LIKES]->(jazz),
  (carol)-[:LIKES]->(jazz),
  (dave)-[:LIKES]->(chess),
  (eve)-[:LIKES]->(chess),
  (grace)-[:LIKES]->(cooking),
  (heidi)-[:LIKES]->(cooking)

// Friends of Alice
MATCH (:Person {name:"Alice"})-[:KNOWS]->(friend) RETURN friend.name AS friend

// People who like the same hobby as Alice (but aren't Alice)
MATCH (:Person {name:"Alice"})-[:LIKES]->(h:Hobby)<-[:LIKES]-(other)
RETURN h.name AS hobby, other.name AS person
