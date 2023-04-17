-- 列出所有在 2004 年上映的電影中演出的演員的名字，按照出生年份進行升序排序
-- ERROR --------------------------------------------------
-- :( 9.sql produces correct result
--  Error when executing query: no such column: birth_year
-----------------------------------------------------------
-- SELECT name
-- FROM people
-- JOIN stars ON people.id = stars.person_id
-- JOIN movies ON stars.movie_id = movies.id
-- WHERE year = 2004 AND birth_year IS NOT NULL
-- ORDER BY birth_year ASC;
SELECT DISTINCT name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004 AND birth IS NOT NULL
ORDER BY birth;