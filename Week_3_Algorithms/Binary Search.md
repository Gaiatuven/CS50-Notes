• In binary search, the idea of the algorithm is to divide and conquer, reducing the search area by half each time, trying to find a target number. 

• In order to leverage this power however, our array must first be sorted, else we cannot make assumptions about the array’s contents.

• Repeat until the (sub)array is of size 0:
	• Calculate the middle point of the current (sub)array.
	 • If the target is at the middle, stop. 
	 • Otherwise, if the target is less than what’s at the middle, repeat, changing the end point to be just to the left of the middle. 
	 • Otherwise, if the target is greater than what’s at the middle, repeat, changing the start point to be just to the right of the middle.

```c
#include <stdio.h>

int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;  // Not found
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    int result = binarySearch(arr, size, target);

    if (result != -1)
        printf("Found %d at index %d\n", target, result);
    else
        printf("%d not found in array\n", target);

    return 0;
}
```

![[Screenshot from 2026-03-26 17-46-22.png]]

**Key points about this implementation:**

- **Requires a sorted array** — binary search only works on sorted data.
- **Mid calculation** uses `low + (high - low) / 2` instead of `(low + high) / 2` to avoid integer overflow.
- **Returns `-1`** if the target isn't found, or the index if it is.
- **O(log n) time** — far faster than linear search for large arrays (e.g., 1 million elements needs at most ~20 comparisons).

• Worst-case scenario: 

We have to divide a list of n elements in half repeatedly to find the target element, either because the target element will be found at the end of the last division or doesn’t exist in the array at all. 

• Best-case scenario: 

The target element is at the midpoint of the full array, and so we can stop looking immediately after we start.