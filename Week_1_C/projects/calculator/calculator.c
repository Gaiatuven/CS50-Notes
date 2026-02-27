#include <stdio.h>

/* Function prototype: takes two integers and an operator character,
   returns the result of the operation as an integer */
int operators(int number_1, char operator, int number_2);

int main(void) {

  int number_1;  /* First operand entered by the user */
  int number_2;  /* Second operand entered by the user */
  char operator; /* The arithmetic operator (+, -, *, /) */

  int result; /* Stores the final calculated result */

  printf("\n");
  printf("Enter number: ");
  scanf("%d", &number_1); /* Read first integer from user */

  printf("Operator: ");
  scanf(" %c",
        &operator); /* Space before %c skips leftover newline in buffer */

  printf("Enter number: ");
  scanf("%d", &number_2); /* Read second integer from user */

  /* Pass both numbers and the operator to the function and store the result */
  result = operators(number_1, operator, number_2);
  printf("Result: %d\n", result);

  return 0;
}

/* operators() - Performs arithmetic based on the given operator.
   Parameters:
     number_1 - the left-hand operand
     operator - the arithmetic symbol (+, -, *, /)
     number_2 - the right-hand operand
   Returns: the result of the operation, or 0 on error */
int operators(int number_1, char operator, int number_2) {
  int answer; /* Holds the result before returning */

  /* Check if operator is '+' and perform addition */
  if (operator == '+') {
    answer = number_1 + number_2;
    return answer;
  }

  /* Check if operator is '-' and perform subtraction */
  if (operator == '-') {
    answer = number_1 - number_2;
    return answer;
  }

  /* Check if operator is '*' and perform multiplication */
  if (operator == '*') {
    answer = number_1 * number_2;
    return answer;
  }

  /* Check if operator is '/' and perform division */
  if (operator == '/') {

    /* Guard against division by zero before performing the operation */
    if (number_2 == 0) {
      printf("Error: Division by zero!\n");
      return 0;
    }

    answer = number_1 / number_2;
    return answer;
  }

  /* If none of the valid operators matched, the input is unrecognised.
     This else catches any character that isn't +, -, *, or / */
  else {
    printf("Error: Unknown operator '%c'\n", operator);
    return 0;
  }
}