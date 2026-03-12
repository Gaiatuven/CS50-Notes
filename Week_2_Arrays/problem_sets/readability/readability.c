#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int total_amount_of_letters(char *userInput);

int main(void) {

  // Variables to store count of letters, words, sentences
  char userInput[256];
  char sentence[256];
  char letters[256];
  char words[256];

  int result;


  // Prompt the user for some text
  printf("Enter some text: \n");
  fgets(userInput, sizeof(userInput), stdin);
  printf("%s", userInput);

  // Count the number of letters, words, and sentences in the text

  result = total_amount_of_letters(userInput);
  printf("%d\n", result);

  // Compute the Coleman-Liau index

  // Print the grade level
}


// Count letters in the text
int total_amount_of_letters(char *userInput)
{
    int amount_of_letters = 0;

    for (int i = 0; userInput[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)userInput[i]))
        {
            amount_of_letters++;
        }
    }

    return amount_of_letters;
}


// // Count words in text
// int total_amount_of_words(char s)
// {
//   // code goes here 
// }

// // Count sentences in the text
// int total_amount_of_sentences(char s)
// {
//   // code goes here 
// }