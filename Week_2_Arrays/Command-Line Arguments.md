```c
int main(void) 
{
	//code 
}
```


● To collect so called command-line arguments from the user, declare main as: 
```c
int main(int argc, string argv[]) 
{
	// code
}

```

● These two special arguments enable you to know what data the user provided at the command line and how much data they provided.

##### ● argc (argument count) 

● This integer-type variable will store the number of command-line arguments the user typed when the program was executed

![[Screenshot from 2026-03-07 12-15-39.png]]

● argv (argument vector) 

●This array of strings stores, one string per element, the actual text the user typed at the command-line when the program was executed. 

● The first element of argv is always found at argv[0]. The last element of argv is always found at argv[argc-1]. 


