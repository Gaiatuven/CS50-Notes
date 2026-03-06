#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function prototype
int length_of_word(char word[]);

int main(void) {

  // Buffers to store each player's word
  char player1[100];
  char player2[100];

  // Scrabble scores for each player
  int playerOneTotal = 0;
  int playerTwoTotal = 0;

  // Get words from each player
  printf("Enter a word: ");
  scanf("%s", player1);

  printf("Enter a word: ");
  scanf("%s", player2);

  // Calculate the Scrabble score for each word
  playerOneTotal = length_of_word(player1);
  playerTwoTotal = length_of_word(player2);

  // Determine and announce the winner
  if (playerOneTotal > playerTwoTotal) {
    printf("Player 1 wins!\n");
  } else if (playerTwoTotal > playerOneTotal) {
    printf("Player 2 wins!\n");
  } else {
    printf("Tie!\n");
  }
}

// Calculates the Scrabble score of a given word
int length_of_word(char word[]) {

  // All uppercase letters and their corresponding Scrabble point values
  char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  int values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                  1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int sum = 0;

  int length = strlen(word);

  // Loop through each character in the word
  for (int i = 0; i < length; i++) {
    // Compare the character (uppercased) against each letter in the alphabet
    for (int j = 0; j < 26; j++) {
      if (toupper(word[i]) == letters[j]) {
        sum += values[j]; // Add the letter's point value to the total
        break;            // Move on to the next character
      }
    }
  }
  return sum; // Return the total Scrabble score
}

char letters1 = []