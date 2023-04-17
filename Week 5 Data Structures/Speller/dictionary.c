// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"

// 使用NULL和size_t定義
#include <stddef.h>

// 用於動態內存分配
#include <stdlib.h>

// 處理字符串操作
#include <string.h>

// 用於不區分大小寫地比較字符串
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// 無需修改
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int word_count = 0;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // 計算給定 word 哈希值，用於確定哈希表中索引位置
    unsigned int index = hash(word);
    // 索引值 index 在哈希表（table）中找到對應節點，將其地址賦值給指針 cursor 用於遍歷以查找單詞是否已存在於哈希表中。
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // 給定 word 第一個字母轉換為小寫，減去字符 'a' 的 ASCII 值。產生一個介於 0 到 25 的整數
    int hash_value = tolower(word[0]) - 'a';
    // 哈希值用於確定在哈希表中的索引位置
    return hash_value % N;
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // 打開字典檔案
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    // 讀取單詞直到檔案結尾
    while (fscanf(file, "%s", word) != EOF)
    {
        // 為新節點分配內存
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        // 將單詞複製到新節點
        strcpy(new_node->word, word);
        // 計算單詞的哈希值
        int index = hash(word);
        // 將新節點插入到鏈表中
        new_node->next = table[index];
        table[index] = new_node;
        // 增加單詞計數
        word_count++;
    }
    // 關閉字典檔案
    fclose(file);
    return true;
    //return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // 回傳單詞計數
    return word_count;
    //return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // 遍歷哈希表的所有節點
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        // 釋放每個表的節點
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
    //return false;
}