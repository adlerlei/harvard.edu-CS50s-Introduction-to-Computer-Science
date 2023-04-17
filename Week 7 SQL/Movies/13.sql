-- 列出所有和 Kevin Bacon （1958 年出生）合作過的演員的名字
SELECT DISTINCT p.name
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN people p ON s1.person_id = p.id
WHERE m.id IN (
  SELECT movie_id
  FROM stars s2
  JOIN people p2 ON s2.person_id = p2.id
  WHERE p2.name = 'Kevin Bacon' AND p2.birth = 1958
) AND p.name != 'Kevin Bacon';