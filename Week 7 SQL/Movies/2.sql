-- 查詢 Emma Stone 的出生年份，使用 SELECT 子句來選擇要從表格中選取的列，並使用 WHERE 子句來選擇符合條件的行
-- 選擇 people 表格中名字為 Emma Stone 的那一行，然後選擇出生年份
SELECT birth
FROM people
WHERE name = 'Emma Stone';