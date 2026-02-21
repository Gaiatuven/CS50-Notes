#include <stdio.h>

int main(void)
{
    int pyramid_height;
    int i, j;
    // Prompt the user for the pyramid's height
    printf("Provide a height for the pyramid: ");
    // Print a pyramid of that height
    scanf("%d", &pyramid_height);

    for (i = 0; i < pyramid_height; i++)
    {
        
        for (j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}