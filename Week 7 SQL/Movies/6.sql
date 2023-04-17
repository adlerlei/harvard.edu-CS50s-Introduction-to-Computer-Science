-- 計算所有在 2012 年上映的電影的平均 IMDb 評分
SELECT AVG(rating)
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2012;