#include <stdio.h>
#include <stdlib.h>
// 將 BLOCK_SIZE 定義為一個常量，值為 512 代表每個數據塊的大小。
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // 檢查命令行參數的數量是否正確
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s image\n", argv[0]);
        return 1;
    }

    // 打開記憶卡映像文件
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // 定義一個計數器，用於命名被恢復的圖像文件
    int img_count = 0;

    // 定義一個字符數組，用於存儲每個圖像文件的文件名
    char filename[8];

    // 定義一個緩存數組，用於存儲每個圖像的512個字節
    unsigned char buffer[BLOCK_SIZE];

    // 定義一個文件指針，用於保存已打開的圖像文件
    FILE *outfile = NULL;

    // 循環讀取記憶卡映像文件中的每個512字節的數據塊
    while (fread(buffer, BLOCK_SIZE, 1, infile))
    {
        // 判斷當前數據塊是否是一個JPEG圖像的開始
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // 如果已經打開了一個圖像文件，則關閉它
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            // 創建一個新的圖像文件名
            sprintf(filename, "%03i.jpg", img_count);

            // 打開一個新的圖像文件，準備寫入數據
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                fclose(infile);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }

            // 將數據塊寫入新的圖像文件
            fwrite(buffer, BLOCK_SIZE, 1, outfile);

            // 將計數器加1，為下一個圖像文件準備名稱
            img_count++;
        }
        else
        {
            // 如果已經打開了一個圖像文件，則繼續將數據塊寫入它
            if (outfile != NULL)
            {
                fwrite(buffer, BLOCK_SIZE, 1, outfile);
            }
        }
    }

    // 如果有一個圖像文件已經打開，則關閉它
    if (outfile != NULL)
    {
        fclose(outfile);
    }

    // 關閉記憶卡映像文件
    fclose(infile);

    // 成功結束程式
    return 0;
}

