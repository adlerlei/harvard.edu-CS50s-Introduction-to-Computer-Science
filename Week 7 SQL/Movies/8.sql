-- 列出所有在 Toy Story 中演出的演員的名字
SELECT name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE title = 'Toy Story';