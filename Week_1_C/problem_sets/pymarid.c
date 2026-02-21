#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while (true)
    {
        int user_input = get_int("Height: ");


        if (user_input <= 0)
        {
            printf("Enter positive interger.");
            continue;
        }
        else
        {   printf("Output: %i\n", user_input);
            break;
        }

        printf("Valid: %d\n", user_input);


        // Print a pyramid of that height
    }
}
