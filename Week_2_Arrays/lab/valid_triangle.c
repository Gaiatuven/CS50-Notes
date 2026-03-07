#include <stdbool.h>
#include <stdio.h>

bool valid_triangle(float a, float b, float c);

int main(void) {
  int result;
  result = valid_triangle(3, 4, 5);
  printf("%d\n", result);
}

bool valid_triangle(float a, float b, float c) {
  if (a <= 0 || b <= 0 || c <= 0) {
    return false;
  }

  if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
    return false;
  }
  return true;
}