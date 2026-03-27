• In selection sort, the idea of the algorithm is to find the smallest unsorted element and add it to the end of the sorted list. 

In pseudocode: 

	•Repeat until no unsorted elements remain: 
	• Search the unsorted part of the data to find the smallest value • Swap the smallest found value with the first element of the unsorted part

```c
#include <stdio.h>

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int data[] = {64, 25, 12, 22, 11};
    int n = sizeof(data) / sizeof(data[0]);

    selectionSort(data, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    return 0;
}
```

|**Feature**|**Complexity / Detail**|
|---|---|
|**Time Complexity (Best/Avg/Worst)**|$O(n^2)$|
|**Space Complexity**|$O(1)$ (In-place)|
|**Stability**|Generally **Not Stable**|
|**Best Use Case**|Small datasets or when memory swaps are expensive.|
$O(n^2)$

• Worst-case scenario: 

We have to iterate over each of the n elements of the array (to find the smallest unsorted element) and we must repeat this process n times, since only one element gets sorted on each pass. 

• Best-case scenario: 

Exactly the same! There’s no way to guarantee the array is sorted until we go through this process for all the elements.

O( n 2 ) Ω ( n 2 )