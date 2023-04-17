-- 列出所有至少有一部電影評分為 9.0 或更高的導演的名字，並且每個名字只列出一次
SELECT DISTINCT name
FROM people
JOIN directors ON people.id = directors.person_id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE rating >= 9.0;