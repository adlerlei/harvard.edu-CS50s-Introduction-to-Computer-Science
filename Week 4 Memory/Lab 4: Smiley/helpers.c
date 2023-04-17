#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // 將所有黑色像素更改為您選擇的顏色
    for (int i = 0; i < height; i++)
    {
        // 遍歷並將像素更改為選擇顏色
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            if (pixel.rgbtRed == 0x00 && pixel.rgbtGreen == 0x00 && pixel.rgbtBlue == 0x00)
            {
                // 將黑色像素更改為您選擇的顏色
                pixel.rgbtRed = 0xff;   // red
                pixel.rgbtGreen = 0x00; // green
                pixel.rgbtBlue = 0x00;  // blue
                image[i][j] = pixel;
            }
        }
    }
}
