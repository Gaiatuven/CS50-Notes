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
        // allocate a new node on the heap
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
            free(n); 
            return 1;
        }

        // fill in the new node's data
        n->num = userInput;
        n->next = list;
        list = n;
    }

    // walk the list from head to tail and print each value
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->num);
    }

    // free every node to avoid memory leaks
    node *ptr = list;
    while (ptr != NULL)
    {
        node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }

    return 0;
}