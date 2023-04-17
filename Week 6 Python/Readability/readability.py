# 引入cs50
from cs50 import get_string


# 宣告函式
def count_letters(text):
    count = 0
    # 利用 for 迴圈遍歷字串中的每個字符，判斷是否為字母，是的話 count 變數加 1
    for char in text:
        if char.isalpha():
            count += 1
    return count


def count_words(text):
    count = 0
    # 以空格分隔單詞，利用 split() 方法將字串轉為陣列，再計算陣列的長度
    words = text.split()
    count = len(words)
    return count


def count_sentences(text):
    count = 0
    # 以空格分隔單詞，利用 split() 方法將字串轉為陣列，再計算陣列的長度
    words = text.split()
    count = len(words)
    return count


def count_sentences(text):
    count = 0
    # 每個字符如果是句點 . 驚嘆號 ! 或問號 ? 中的一個，則計數器 count 加 1
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count


# 獲取用戶輸入的文章
text = get_string("Text : ")


# 計算文章的字母數、單字數和句子數
letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)


# 以每 100 個單字為基礎，計算文章的字母數和句子數
L = (letters / words) * 100
S = (sentences / words) * 100


# 利用 Coleman-Liau 公式計算文章等級
index = round(0.0588 * L - 0.296 * S - 15.8)


# 判斷等級並輸出結果
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")