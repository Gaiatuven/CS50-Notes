#include <stdio.h>

void count_swaps(int arr[], int n);

int main(void)
{
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    count_swaps(arr, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

void count_swaps(int arr[], int n)
{
    int total_swaps = 0; 
    for (int i = 0; i < n - 1; i++)
    {
        int swaps_this_pass = 0; 
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                total_swaps++;
                swaps_this_pass++;
            }
        }

        if (swaps_this_pass == 0) break;
    }
    printf("Total swaps done: %d\n", total_swaps);
}