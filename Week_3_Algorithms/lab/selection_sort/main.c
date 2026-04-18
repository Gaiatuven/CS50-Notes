#include <stdio.h>

void selection_sort(int arr[], int n);

int main(void)
{
    int arr[] = {99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0};
    int size = sizeof(arr) / sizeof(arr[0]); 

    selection_sort(arr, size);
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

void selection_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) 
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}