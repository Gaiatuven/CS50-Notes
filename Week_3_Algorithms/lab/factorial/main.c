#include <stdio.h>

int factorial(int n);
int forloop(int n);


int main(void)
{
    int n;
    int result; 
    int result2;

    printf("Enter a number to get the factorial: ");
    scanf("%d", &n);

    result = factorial(n);
    printf("Factorial of %d: %d\n", n, result);

    result2 = forloop(n);
    printf("Using a for loop %d: %d\n", n, result2);

    return 0;
}

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int forloop(int n)
{
    if (n == 0 || n == 1)  
    {
        return 1;
    }

    int numb = 1;          
    for (int i = 2; i <= n; i++)  
    {
        numb *= i;          
    }
    return numb;            
}