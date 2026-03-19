#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(char *str);
void rotate(int k, char *str);
char *user_text(void);

char *text;

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

  // Convert argv[1] from a `string` to an `int`

  int k = atoi(argv[1]);
  char *plaintext = user_text();

  printf("ciphertext: ");
  rotate(k, plaintext);
  printf("\n");

  free(plaintext);
  return 0;
}

bool only_digits(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

// Prompt user for plaintext
char *user_text(void) {
  char *plaintext = malloc(1024);
  if (plaintext == NULL)
    return NULL;

  printf("Plaintext: ");
  fgets(plaintext, 1024, stdin);

  plaintext[strcspn(plaintext, "\n")] = '\0';
  return plaintext;
}

void rotate(int k, char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (isupper(str[i])) {
      // (Current index + key) % 26 + ASCII offset for 'A'
      printf("%c", (str[i] - 'A' + k) % 26 + 'A');
    } else if (islower(str[i])) {
      printf("%c", (str[i] - 'a' + k) % 26 + 'a');
    } else {
      printf("%c", str[i]);
    }
  }
}