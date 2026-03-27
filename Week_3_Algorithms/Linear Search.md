
• In linear search, the idea of the algorithm is to iterate across the array from left to right, searching for a specified element. In pseudocode:
• Repeat, starting at the first element: 
• If the first element is what you’re looking for (the target), stop. 
• Otherwise, move to the next element.


• Worst-case scenario: 

We have to look through the entire array of n elements, either because the target element is the last element of the array or doesn’t exist in the array at all. 

• Best-case scenario: 

The target element is the first element of the array, and so we can stop looking immediately after we start.

O( n ) Ω ( 1 )

```c
#include <stdio.h>

int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;  // Return index where found
    }
    return -1;  // Not found
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 22;

    int result = linearSearch(arr, size, target);

    if (result != -1)
        printf("Found %d at index %d\n", target, result);
    else
        printf("%d not found in array\n", target);

    return 0;
}
```

![[Screenshot from 2026-03-26 17-48-41.png]]

**Key points:**

- **Works on any array** — sorted or unsorted, unlike binary search.
- **Simple but slow** — O(n) in the worst case; every element may be checked.
- **Best case O(1)** — if the target is the first element.
- Use it for small arrays or unsorted data. For large sorted arrays, binary search (O(log n)) is vastly faster.