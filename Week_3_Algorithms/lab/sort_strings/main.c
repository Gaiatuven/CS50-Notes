#include <stdio.h>
#include <string.h>

void sort_alpahbetically(char arr[][50], int n);

int main(void)
{
    char fruit[5][50] = {"banana", "apple", "cherry", "date", "elderberry"};
    int size = sizeof(fruit) / sizeof(fruit[0]);

    sort_alpahbetically(fruit, size);

    printf("Sorted order:\n");

    for (int i = 0; i < size; i++) {
        printf("%s\n", fruit[i]);
    }
    return 0;
}


void sort_alpahbetically(char arr[][50], int n)
{
    char temp[50];
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }

}