-- 列出所有在 2018 年及之後上映的電影的標題，按照字母順序進行排序
SELECT title
FROM movies
WHERE year >= 2018
ORDER BY title ASC;