-- 列出所有 2010 年上映的電影的標題和評分，按照評分進行降序排序，如果評分相同，則按照標題進行升序排序
SELECT title, rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010 AND rating IS NOT NULL
ORDER BY rating DESC, title ASC;