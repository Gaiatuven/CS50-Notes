#include <cs50.h>
#include <stdio.h>

int main(void)
{ // Get user name
    string user_name = get_string("What's your name?\n");
    // Print message to user
    printf("hello, %s\n", user_name);
}
