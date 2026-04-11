
## What is a Struct?

-  How can we group different types of related data into a single unit?

```c
typedef struct 
	{ 
	string name; 
	int votes; 
} 
candidate;
```

```c
candidate president;
// candidate - type 
// president - name 

candidate president; 
president.name = "Alice"; 
president.votes = 10;
```

