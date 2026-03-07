
#### What are the characteristics of good design.

##### Is your code efficient? 

Avoid unnecessary repetition and redundant operations. 

● Avoiding copy-pasting code, even with slight changes. Instead, consider loops or abstraction via functions. 

● If a value is computed multiple times, consider storing in a variable to prevent redundant computation.

##### Is your code easy to maintain? 

● Prototype functions at the top of their code file, above main(). 

● Avoid “magic numbers.” (i.e., hard coded numbers.) If a value will not change throughout the program, it should be defined as a constant.

Option A

```c
for (int i = 0; i < strlen(string); i++);
```

Option B 
```c
for (int i = 0; n = strlen(string); i < n; i++);
```

Option B - readable - length of string gets stored in n, Option A would have to calculate length before using it


Option A

```c
const int MONTHS_IN_YEAR = 12;
for (int i = 0; i < MONTHS_IN_YEAR; i++);
```

Option B 
```c
for (int i = 0; i < 12; i++);
```

Option A - Using constant to set variable. 
Option B - Hard cods the number 12.

Option A
```c
int main(void)
{
	if (Expression)
	{
		return 0;
	}
	return 1; // only reached if Expression is FALSE
}
```


Option B 

```c
int main(void)
{
	if (Expression)
	{
		return 0;
	}
	else
	{
		return 1; // // this is redundant
	}
	
}
```

Option A - Return true if not False
Option B - Checks unnecessary Else block if its already false.

- The `else` block is **unnecessary** because if the `if` branch executes, the function already returned
- The code still works, but the `else` adds noise and implies a relationship that doesn't need to be stated

Option A
```c
int main(void)
{
	bool success = true;
	if (success)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}
```

Option B

```c
int main(void)
{
	bool success = true;
	if (!success)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
```

Option A - Readable, checks for true first then false;
Option B - inverting true to false unnecessary step checks for false before true. 