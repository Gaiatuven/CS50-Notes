#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
} node;

int main(void)
{

    int userInput;
    node *list = NULL;

    for (int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("No memory");
            return 0;
        }

        printf("Enter a number: \n");
        scanf("%d", &userInput);

        if (userInput < 0)
        {
            printf("Invalid, enter positive numbers");
            return 1;
        }

        n->num = userInput;
        n->next = list;
        list = n;
    }

    // print once, after the loop
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->num);
    }

    return 0;
}
