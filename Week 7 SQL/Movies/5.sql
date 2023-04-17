-- 列出所有哈利波特電影的標題和發行年份，按照年份進行升序排序
SELECT title, year
FROM movies
WHERE title LIKE 'Harry Potter%'
ORDER BY year ASC;