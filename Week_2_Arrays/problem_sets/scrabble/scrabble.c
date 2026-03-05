#include <ctype.h>
#include <stdio.h>
#include <string.h>

int length_of_word(void);

int main(void) {
  
    length_of_word();  
}

int length_of_word(void) {

    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  int values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                  1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int sum = 0;

    char word[] = "Cherelene";
    int length = strlen(word);

    for (int i = 0; i < length; i++) {

      for (int j = 0; j < 26; j++) {
        if (toupper(word[i]) == letters[j]) {
          sum += values[j];
          break;
        }
      }
    }

    printf("Total: %d\n", sum);
  }

