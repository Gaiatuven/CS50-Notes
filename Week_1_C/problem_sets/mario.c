#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i, j;
    int user_input;
    while (true)
    { // Takes user input for height of pyramid
        user_input = get_int("Height: ");

        // Checks if input is below 0 or above 8
        if (user_input < 1 || user_input >= 8)
        {
            printf("Enter positive between 1 - 8.");
            continue;
        }
        else
        {

            break;
        }
    }

    
    for (i = 0; i < user_input; i++)
    {
        for (j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}