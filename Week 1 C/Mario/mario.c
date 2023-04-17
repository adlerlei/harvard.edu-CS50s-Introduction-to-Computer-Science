#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Initialize an integer variable called height
    int height;

    // Repeat the following steps until height is between 1 and 8 (inclusive)
    do
    {
        // Ask the user for the height value
        height = get_int("Height : ");
    }
    // If the user input does not meet the conditions, then return to the previous step.
    while (height < 1 || height > 8);
    {
        for (int i = 0; i < height; i ++)
        {
            // Calculate how many spaces the code needs to output.
            for (int j = 0; j < height - i - 1; j ++)
            {
                printf(" ");
            }
            // Output "#" and a newline character
            for (int k = 0; k <= i; k ++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
}