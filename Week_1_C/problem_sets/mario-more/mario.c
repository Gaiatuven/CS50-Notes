#include <stdio.h>

int main(void) {
  int n = 5;
  int i, j, k;

  for (i = 1; i <= n; i++) {
    // Right pyramid
    for (j = 1; j <= i; j++) {
      printf("#");
    }

    // Gap between them
    for (j = i; j < n; j++) {
      printf(" ");
    }
    printf("  "); // extra space separator

    // Left pyramid (spaces + stars)
    for (j = i; j < n; j++) {
      printf(" ");
    }
    for (k = 1; k <= i; k++) {
      printf("#");
    }

    printf("\n");
  }
}
