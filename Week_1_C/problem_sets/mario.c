#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i, j, k;
    int user_input;
    while (true)
    { // Takes user input for height of pyramid
        user_input = get_int("Height: ");

        // Checks if input is below 0 or above 8
        if (user_input < 1 || user_input >= 8)
        {
            printf("Enter positive between 1 - 8.\n");
            continue;
        }
        else
        {

            break;
        }
    }

    for (i = 1; i <= user_input; i++)
    {
        for (j = i; j < user_input; j++)
        { // Print spaces
            printf(" ");
        }
        // Print brics
        for (k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
