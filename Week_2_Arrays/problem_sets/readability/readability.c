#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int total_amount_of_letters(char *userInput);
int total_amount_of_words(char *userInput);

int main(void) {

  // Variables to store count of letters, words, sentences
  char userInput[256];
  int total_amount_of_characters;
  int total_amount_of_words_count;

  // Prompt the user for some text
  printf("Enter some text: \n");
  fgets(userInput, sizeof(userInput), stdin);
  printf("%s", userInput);

  // Count the number of letters, words, and sentences in the text

  total_amount_of_characters = total_amount_of_letters(userInput);
  printf("%d\n", total_amount_of_characters);

  printf("--------------------------------------------\n");

  total_amount_of_words_count = total_amount_of_words(userInput);
  printf("%d\n", total_amount_of_words_count);

  // Compute the Coleman-Liau index

  // Print the grade level
}

// Count letters in the text
int total_amount_of_letters(char *userInput) {
  int amount_of_letters = 0;

  for (int i = 0; userInput[i] != '\0'; i++) { // Checking for letters
    if (isalpha((unsigned char)userInput[i])) {
      amount_of_letters++;
    }
  }

  return amount_of_letters;
}

// Count words in text
int total_amount_of_words(char *userInput)
{
  int amount_of_words = 0;

  for (int i = 0; userInput[i] != '\0'; i++)
  { // Checking for transition from non-space to space
    if (!isspace((unsigned char)userInput[i]) && isspace((unsigned char)userInput[i + 1]))
    {
      amount_of_words++;
    }
  }
  return amount_of_words;
}

// // Count sentences in the text
// int total_amount_of_sentences(char s)
// {
//   // code goes here
// }