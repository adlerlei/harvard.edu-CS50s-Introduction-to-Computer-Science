#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// 在main之前先宣告函式
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // 接收用戶輸入文章內容
    string text = get_string("Text: ");

    // 將用戶輸入賦值給以下三個變數
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // 透過除以和乘法計算L和S
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // 計算指數
    // 附上參考來源：https://www.facebook.com/groups/cs50/permalink/1781451348668569/
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // 輸出等級
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
    return 0;
}

// 撰寫上面宣告三個函式的內容
int count_letters(string text)
{
    // 計算傳入的text字串有多少個字母，並將結果存在 count 整數變數，遍歷字串中的每個字符，判斷 isalpha(text[i] 結果為真就將 count 變數增加1。後返回 count 變數的值，即為字母數量。
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count ++;
        }
    }
    return count;
}

int count_words(string text)
{
    // 計算文章單字數量，以空格分隔單詞。變數count初始化為1，用for迴圈遍歷 text 字符串，當遍歷到一個空格時，就代表已經找到了一個單詞，所以 count 的值就要加1。最終，count 的值就是文章的單字數量。
    int count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            count ++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    // 計算一個字符串中的句子數量，它使用了與上面兩個函式相似的方式進行計數。每個字符如果是句點 . 驚嘆號 ! 或問號 ? 中的一個，則將計數器 count 加 1。
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count ++;
        }
    }
    return count;
}