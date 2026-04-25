#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Ask user to guess the number between 1 - 20.
// User only has 5 tries to guess the number.
// if statement to indicate how low or high

int main(void) {
  int user_guess;
  int guess_tries = 5; // Player starts with 5 tries

  srand(time(NULL)); // Seed random number generator with current time

  int random = (rand() % 20) + 1; // Generate random number between 1 - 20

  printf("Enter a number between 1 - 20 to guess the random number. \n");

  while (guess_tries > 0) { // Loop until player runs out of tries

    printf("Enter number: ");
    scanf("%d", &user_guess); // Read player's guess

    if (user_guess > random) {
      // Guess is too high, show remaining tries
      printf("You guess is too high .. remaining tries %d\n", guess_tries - 1);
      guess_tries--;
      
    } else if (user_guess < random) {
      // Guess is too low, show remaining tries
      printf("You guess is too low .. remaining tries %d\n", guess_tries - 1);
      guess_tries--;
      
    } else {
      // Correct guess, exit the loop
      printf("You guessed correctly: %d\n", random);
      break;
    }
  }

  // If player used all tries, reveal the random number
  if (guess_tries == 0) {
    printf("You have no more tries left, the random number was %d\n", random);
  }

  return 0;
}