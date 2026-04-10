#include <stdio.h>

void iterativeforloop(int n);
void recursive(int n, int a, int b);

int main(void)
{
    int n;
    int result;

    printf("Enter a number to get the fibonacci sequence: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Error: n must be non-negative\n");
        return 1;
    }

    printf("Sequence: \n");
    iterativeforloop(n);

    printf("Recursive: \n");
    recursive(n, 0, 1);

    return 0;
}

void iterativeforloop(int n)
{
    int a = 0;
    int b = 1;

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a);
        int c = a + b;
        a = b;
        b = c;
    }
    printf("\n");
}

void recursive(int n, int a, int b)
{
    if (n == 0)
        return;

    printf("%d ", a);
    recursive(n - 1, b, a + b);
}