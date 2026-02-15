``` c
#include <stdio.h>

int main(void)

{

	printf("Hello world\n");

}
```

```c
#include <stdio.h>
int main(void)
{

int x = 2;
int y = 3;

if (x < y)

{

	printf("x is less than y\n");

}

else {

	printf("x is greater than y\n");

}

}
```

```c
#include <stdio.h>


int main(void)
{


int x = 9;
int y = 9;

if (x < y)

{

	printf("x is less than y\n");

}

else if (x > y)

{

	printf("x is greater than y\n");

}

else

{

	printf("Both numbers are equal\n");

}

}
```

## While loops 

```c
#include <stdio.h>

int main(void)

{

int i = 0;

while (i < 3)

{

	printf("meow\n");

	i++;

}

}
```

## For loop

```c
#include <stdio.h>


int main(void)

{

for (int i = 0; i < 3; i++)

{

	printf("meou\n");

}
}
```

## Function 

```c
#include <stdio.h>

void meow(int n); // prototype/declaration

int main(void) {

	meow(3);

}

void meow(int n) { // definition

for (int i = 0; i < n; i++) {

	printf("meow\n");

}

}
```