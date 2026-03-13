#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int total_amount_of_letters(char *userInput);
int total_amount_of_words(char *userInput);
int total_amount_of_sentences(char *userInput);

int main(void) {

  // Variables to store count of letters, words, sentences
  char userInput[256];
  int total_amount_of_characters;
  int total_amount_of_words_count;
  int total_amount_of_sentence;

  double coleman_liau_index;

  // Prompt the user for some text
  printf("Enter some text: \n");
  fgets(userInput, sizeof(userInput), stdin);

  // Count the number of letters, words, and sentences in the text
  total_amount_of_characters = total_amount_of_letters(userInput);
  total_amount_of_words_count = total_amount_of_words(userInput);
  total_amount_of_sentence = total_amount_of_sentences(userInput);

  printf("\n--------------------------------------------\n");
  printf("Text: %s", userInput);
  printf("--------------------------------------------\n");
  printf("Letters   : %d\n", total_amount_of_characters);
  printf("Words     : %d\n", total_amount_of_words_count);
  printf("Sentences : %d\n", total_amount_of_sentence);
  printf("--------------------------------------------\n");

  // Compute the Coleman-Liau index

  double L =
      ((double)total_amount_of_characters / total_amount_of_words_count) * 100;
  double S =
      ((double)total_amount_of_sentence / total_amount_of_words_count) * 100;

  coleman_liau_index = 0.0588 * L -
                       0.296 * S - 15.8;
  printf("%f\n", coleman_liau_index);

  // Print the grade level
}

// Count letters in the text
int total_amount_of_letters(char *userInput) {
  int amount_of_letters = 0;
  // Checking for letters
  for (int i = 0; userInput[i] != '\0'; i++) {
    if (isalpha((unsigned char)userInput[i])) {
      amount_of_letters++;
    }
  }

  return amount_of_letters;
}

// Count words in text
int total_amount_of_words(char *userInput) {
  int amount_of_words = 0;

  for (int i = 0; userInput[i] != '\0';
       i++) { // Checking for transition from non-space to space
    if (!isspace((unsigned char)userInput[i]) &&
        isspace((unsigned char)userInput[i + 1])) {
      amount_of_words++;
    }
  }
  return amount_of_words;
}

// // Count sentences in the text
int total_amount_of_sentences(char *userInput) {
  int amount_of_sentences = 0;
  for (int i = 0; userInput[i] != '\0'; i++) {
    // Checking for sentence-ending punctuation only
    if (userInput[i] == '.' || userInput[i] == '!' || userInput[i] == '?') {
      amount_of_sentences++;
    }
  }
  return amount_of_sentences;
}