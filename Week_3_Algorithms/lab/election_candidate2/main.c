#include <stdio.h>


struct candidate {
  char name[255];
  int number_of_votes;
};


int main(void)

{
  struct candidate employee;

  printf("Enter your name:\n" );
  scanf("%254s", employee.name);
  printf("Hello, %c", employee.name);
    return 0;
}
