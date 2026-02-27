#include <stdio.h>

int main(void) {
  char user_input[50];
  printf("Enter: ");
  scanf(" %s", user_input);
  printf("%s", user_input);
  return 0;
}

// Celsius to Fahrenheit F = (C × 9/5) + 32
double celsius_to_fahrenheit(double temp) {
  double result;
  result = (temp * 9.0 / 5.0) + 32.0;
  return result;
}

// Fahrenheit to Celsius C = (F - 32) × 5/9
double fahrenheit_to_celsius(double temp) {}

// Celsius to Kelvin K = C + 273.15
double celsius_to_kelvin(double temp) {}

// Kelvin to Celsius C = K - 273.15
double kelvin_to_celsius(double temp) {}

// Fahrenheit to Kelvin K = (F - 32) × 5/9 + 273.15
double fahrenheit_to_kelvin(double temp) {}

// Kelvin to Fahrenheit F = (K - 273.15) × 9/5 + 32
double kelvin_to_fahrenheit(double temp) {}