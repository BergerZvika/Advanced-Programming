// A small org-chart graph — Company, Departments, People with HEADS,
// WORKS_IN, and REPORTS_TO relationships. Good for testing path
// queries and hierarchical aggregations.

CREATE
  (acme:Company    {name:"ACME Corp",        founded:2010}),
  (eng:Department  {name:"Engineering"}),
  (sales:Department{name:"Sales"}),
  (alice:Person    {name:"Alice",  role:"CEO"}),
  (bob:Person      {name:"Bob",    role:"VP Engineering"}),
  (carol:Person    {name:"Carol",  role:"VP Sales"}),
  (dave:Person     {name:"Dave",   role:"Senior Engineer"}),
  (eve:Person      {name:"Eve",    role:"Engineer"}),
  (frank:Person    {name:"Frank",  role:"Engineer"}),
  (grace:Person    {name:"Grace",  role:"Sales Lead"}),
  (heidi:Person    {name:"Heidi",  role:"Account Exec"}),

  (eng)-[:PART_OF]->(acme),
  (sales)-[:PART_OF]->(acme),
  (bob)-[:HEADS]->(eng),
  (carol)-[:HEADS]->(sales),
  (dave)-[:WORKS_IN]->(eng),
  (eve)-[:WORKS_IN]->(eng),
  (frank)-[:WORKS_IN]->(eng),
  (grace)-[:WORKS_IN]->(sales),
  (heidi)-[:WORKS_IN]->(sales),

  (bob)-[:REPORTS_TO]->(alice),
  (carol)-[:REPORTS_TO]->(alice),
  (dave)-[:REPORTS_TO]->(bob),
  (eve)-[:REPORTS_TO]->(bob),
  (frank)-[:REPORTS_TO]->(bob),
  (grace)-[:REPORTS_TO]->(carol),
  (heidi)-[:REPORTS_TO]->(carol)

// Headcount per department
MATCH (p:Person)-[:WORKS_IN]->(d:Department)
RETURN d.name AS department, count(p) AS headcount

// Direct reports of each VP
MATCH (vp:Person)<-[:REPORTS_TO]-(report:Person)
WHERE vp.role <> "CEO"
RETURN vp.name AS manager, collect(report.name) AS reports
