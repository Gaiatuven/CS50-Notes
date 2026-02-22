#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int change);
int calculate_dimes(int change);
int calculate_nickels(int change);
int calculate_pennies(int change);

int subtract_quarters(int change, int quarters);

int main(void)
{
    int change;
    int total_coins;
    while (true)
    {

        // Prompt the user for change owed, in cents
        change = get_float("Change owned: ");

        if (change < 1)
        {
            printf("Enter a number positive amount: ");
            continue;
        }
        else
        {
            printf("%i\n", change);
            break;
        }
    }

    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(change);
    // Subtract the value of those quarters from cents
    change = subtract_quarters(change, quarters);

    // Calculate how many dimes you should give customer
    int dimes = calculate_dimes(change);
    // Subtract the value of those dimes from remaining cents
    change = change - dimes * 10;


    // Calculate how many nickels you should give customer
    int nickels = calculate_nickels(change);
    // Subtract the value of those nickels from remaining cents
    change = change - nickels * 5;


    // Calculate how many pennies you should give customer
    int pennies = calculate_pennies(change);

    // Subtract the value of those pennies from remaining cents
    change = change - pennies * 1;


    // Sum the number of quarters, dimes, nickels, and pennies used
    total_coins = quarters + dimes + nickels + pennies;
    // Print that sum
    printf("Total: %i\n", total_coins);
}


int subtract_quarters(int change, int quarters)
{
    return change - quarters * 25;
}


int calculate_quarters(int change)
{
    int quarters = 0;
    while (change >= 25)
    {
        change = change - 25;
        quarters++;
    }
    return quarters;
}

int calculate_dimes(int change)
{
    int dimes = 0;
    while (change >= 10)
    {
        change = change - 10;
        dimes++;
    }
    return dimes;
}

int calculate_nickels(int change)
{
    int nickels = 0;
    while (change >= 5)
    {
        change = change - 5;
        nickels++;
    }
    return nickels;
}

int calculate_pennies(int change)
{
    int penny = 0;
    while (change >= 1)
    {
        change = change - 1;
        penny++;
    }
    return penny;
}
