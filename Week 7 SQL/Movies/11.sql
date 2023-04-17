-- 列出 Chadwick Boseman 演出的評分最高的五部電影的名字，按照評分進行降序排序
SELECT title
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;