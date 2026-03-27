• In bubble sort, the idea of the algorithm is to move higher valued elements generally towards the right and lower value elements generally towards the left. 

In pseudocode: 
	• Set swap counter to a non-zero value 
	• Repeat until the swap counter is 0: 
	• Reset swap counter to 0 • Look at each adjacent pair 
	• If two adjacent elements are not in order, swap them and add one to the swap counte

```c
#include <stdio.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before: ");
    printArray(arr, n);

    bubbleSort(arr, n);

    printf("After:  ");
    printArray(arr, n);

    return 0;
}
```

**Output:**
```
Before: 64 34 25 12 22 11 90
After:  11 12 22 25 34 64 90
```

**Key points:**

- **O(n²) time** in average and worst case — two nested loops over the array.
- **O(1) space** — sorts in-place, no extra memory needed.
- **Stable sort** — equal elements maintain their original relative order.
- **Optimisation tip:** add a `swapped` flag — if a full pass completes with no swaps, the array is already sorted and you can exit early (best case becomes O(n)).

Worst-case scenario: 

The array is in reverse order; we have to “bubble” each of the n elements all the way across the array, and since we can only fully bubble one element into position per pass, we must do this n times.

• Best-case scenario: 

The array is already perfectly sorted, and we make no swaps on the first pass.

O(n2) Ω(n)