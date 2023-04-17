#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* pseudocode --------------------------------------
1.從輸入中讀取一個字串。
2.對字串中每個字元轉換成對應的 8 位元二進位數字。
3.對每個 8 位元二進位數字使用提供的 print_bulb 函數印出一個由黃色和黑色的燈泡 emoji 組成的序列，表示開啟和關閉的燈泡。
4.每個 8 位元二進位數字應該在自己的一行上印出，每行末尾應該有一個換行符號 \n。
5.將修改後的程式儲存於名為 bulbs.c 的檔案中。

// Remark -------------------------------------------
使用 get_string 函數要求使用者輸入要顯示在燈條上的文字。
遍歷每個字符，使用 ASCII 編碼將其轉換為對應的 8 位二進制數字。
每 8 位二進制數字組成一個“位元組”，使用 print_bulb 函數將每個“位元組”轉換為一列黃色或黑色表情符號（表示燈泡的開和關），並在每個“位元組”後面加上一個換行符 \n。
輸出所有轉換後的“位元組”，顯示在燈條上。
將字符轉換為 ASCII 編碼，使用 int 類型的變量存儲每個字符，並將其強制轉換為 unsigned char 類型，這樣就可以保證其值在 0~255 之間。
每個字符轉換為二進制數字時，需要使用位運算符將其轉換為一個 8 位的二進制數字，可以使用移位運算符 >> 和 << 以及位與運算符 & 來實現。
將二進制數字轉換為表情符號可以使用 print_bulb 函數，如果輸入是 0，則輸出黑色表情符號（表示燈關閉），如果輸入是 1，則輸出黃色表情符號（表示燈泡打開）。
*/

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // 提示用戶輸入
    string message = get_string("Message : ");

    // 將每個字符轉換為8位二進制
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        // 獲取當前字符串的ASCII
        int ascii_code = (int) message[i];

        // 將ASCII轉換為8位二進制
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int bit = (ascii_code >> j) & 1;
            print_bulb(bit);
        }
        // 在每個8符號字節後添加一個新的行
        printf("\n");
    }
    return 0;
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
