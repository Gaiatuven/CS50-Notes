#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool only_digits(char *str);

int main(int argc, char *argv[]) {
  // Make sure program was run with just one command-line argument
  if (argc != 2) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // Make sure every character in argv[1] is a digit
  if (!only_digits(argv[1])) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // Make sure every character in argv[1] is a digit

  // Convert argv[1] from a `string` to an `int`

  // Prompt user for plaintext

  // For each character in the plaintext:

  // Rotate the character if it's a letter
}

bool only_digits(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}