#include <stdio.h>
#include <stdbool.h>

void early_exit(int arr[], int n);

int main(void)
{
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    int unsorted_arr[] = {5, 4, 3, 2, 1};

    int sorted_arr_size = sizeof(sorted_arr) / sizeof(sorted_arr[0]);
    int unsorted_arr_size = sizeof(unsorted_arr) / sizeof(unsorted_arr[0]);

    early_exit(sorted_arr, sorted_arr_size);

    for (int i = 0; i < sorted_arr_size; i++)
    {
        printf("%d ", sorted_arr[i]);
    }
    printf("\n");
    return 0;
}

void early_exit(int arr[], int n)
{
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped)
        {
            printf("Early exit at pass %d\n", i + 1);
            break;
        }
    }
}