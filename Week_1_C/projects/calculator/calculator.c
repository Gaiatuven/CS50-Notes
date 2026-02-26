#include <stdio.h>

int operators(int number_1, char operator, int number_2);

int main(void){

    int number_1;
    int number_2;
    char operator;

    int result;

    printf("Enter number: ");
    scanf("%d", &number_1);
    printf("Operator: ");
    scanf(" %c", &operator);
    printf("Enter number: ");
    scanf("%d", &number_2);

    result = operators(number_1, operator, number_2);
    printf("%d\n", result);

    return 0;
}

int operators(int number_1, char operator, int number_2)
{
    int answer;
    char plus = '+';
    char minus = '-';
    char multiply = '*';
    char division = '/';

    if (operator == '+')
    {
        answer = number_1 + number_2;
        return answer;
    }
}