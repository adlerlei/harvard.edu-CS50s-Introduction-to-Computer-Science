-- 計算有多少部電影的 IMDb 評分是 10.0
SELECT COUNT(*)
FROM ratings
WHERE rating = 10.0;