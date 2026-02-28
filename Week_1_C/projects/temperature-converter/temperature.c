#include <stdio.h>

/* Function prototypes - declared at top so main can see them */
int message_to_user(void);
double get_temperature(void);

double celsius_to_fahrenheit(double temp);
double fahrenheit_to_celsius(double temp);
double celsius_to_kelvin(double temp);
double kelvin_to_celsius(double temp);
double fahrenheit_to_kelvin(double temp);
double kelvin_to_fahrenheit(double temp);

int main(void) {

  int choice;     /* Stores the user's menu selection (1-6) */
  double result;  /* Stores the converted temperature result */
  double temp;    /* Stores the temperature value to convert */

  /* Display menu and get user's conversion choice */
  choice = message_to_user();

  /* Get the temperature value to convert from the user */
  temp = get_temperature();

  /* Call the appropriate conversion function based on user's choice */
  switch (choice) {
  case 1:
    result = celsius_to_fahrenheit(temp);
    printf("Celsius to Fahrenheit: %.2f\n", result);
    break;
  case 2:
    result = fahrenheit_to_celsius(temp);
    printf("Fahrenheit to Celsius: %.2f\n", result);
    break;
  case 3:
    result = celsius_to_kelvin(temp);
    printf("Celsius to Kelvin: %.2f\n", result);
    break;
  case 4:
    result = kelvin_to_celsius(temp);
    printf("Kelvin to Celsius: %.2f\n", result);
    break;
  case 5:
    result = fahrenheit_to_kelvin(temp);
    printf("Fahrenheit to Kelvin: %.2f\n", result);
    break;
  case 6:
    result = kelvin_to_fahrenheit(temp);
    printf("Kelvin to Fahrenheit: %.2f\n", result);
    break;
  default:
    /* Catch any input that isn't 1-6 */
    printf("Invalid input\n");
  }

  return 0;
}

/* get_temperature() - Prompts the user to enter a temperature value.
   Returns: the temperature as a double */
double get_temperature(void) {
  double temp; /* Holds the temperature entered by the user */
  printf("Enter amount to convert: ");
  scanf("%lf", &temp);  /* %lf used to read a double */
  return temp;
}

/* message_to_user() - Displays the conversion menu and reads the user's choice.
   Returns: the user's menu selection as an int */
int message_to_user(void) {
  int choice; /* Holds the user's menu selection */

  printf("=============================\n");
  printf("    Temperature Converter    \n");
  printf("=============================\n");
  printf("\n");
  printf("  1: Celsius to Fahrenheit\n");
  printf("  2: Fahrenheit to Celsius\n");
  printf("  3: Celsius to Kelvin\n");
  printf("  4: Kelvin to Celsius\n");
  printf("  5: Fahrenheit to Kelvin\n");
  printf("  6: Kelvin to Fahrenheit\n");
  printf("\n");
  printf("=============================\n");
  printf("Enter choice: ");
  scanf("%d", &choice);  /* Read user's menu selection */
  return choice;
}

/* celsius_to_fahrenheit() - Converts Celsius to Fahrenheit.
   Formula: F = (C x 9/5) + 32
   Parameters: temp - temperature in Celsius
   Returns: temperature in Fahrenheit */
double celsius_to_fahrenheit(double temp) {
  double result;
  result = (temp * 9.0 / 5.0) + 32.0;
  return result;
}

/* fahrenheit_to_celsius() - Converts Fahrenheit to Celsius.
   Formula: C = (F - 32) x 5/9
   Parameters: temp - temperature in Fahrenheit
   Returns: temperature in Celsius */
double fahrenheit_to_celsius(double temp) {
  double result;
  result = (temp - 32) * 5.0 / 9.0;
  return result;
}

/* celsius_to_kelvin() - Converts Celsius to Kelvin.
   Formula: K = C + 273.15
   Parameters: temp - temperature in Celsius
   Returns: temperature in Kelvin */
double celsius_to_kelvin(double temp) {
  double result;
  result = temp + 273.15;
  return result;
}

/* kelvin_to_celsius() - Converts Kelvin to Celsius.
   Formula: C = K - 273.15
   Parameters: temp - temperature in Kelvin
   Returns: temperature in Celsius */
double kelvin_to_celsius(double temp) {
  double result;
  result = temp - 273.15;
  return result;
}

/* fahrenheit_to_kelvin() - Converts Fahrenheit to Kelvin.
   Formula: K = (F - 32) x 5/9 + 273.15
   Parameters: temp - temperature in Fahrenheit
   Returns: temperature in Kelvin */
double fahrenheit_to_kelvin(double temp) {
  double result;
  result = (temp - 32) * 5.0 / 9.0 + 273.15;
  return result;
}

/* kelvin_to_fahrenheit() - Converts Kelvin to Fahrenheit.
   Formula: F = (K - 273.15) x 9/5 + 32
   Parameters: temp - temperature in Kelvin
   Returns: temperature in Fahrenheit */
double kelvin_to_fahrenheit(double temp) {
  double result;
  result = (temp - 273.15) * 9.0 / 5.0 + 32;
  return result;
}