● Arrays are a fundamental data structure, and they are extremely useful! 
● We use arrays to hold values of the same type at contiguous memory locations. 
● One way to analogise the notion of array is to think of your local post office, which usually has a large bank of post office boxes.

![[Screenshot from 2026-03-07 11-39-43.png]]

● In C, the elements of an array are indexed starting from 0. 
	● This is one of the major reasons we count from zero! 
	
● If an array consists of n elements, the first element is located at index 0. The last element is located at index (n-1). 

● C is very lenient. It will not prevent you from going “out of bounds” of your array; be careful!

## Array declaration

```c
type name[size];
```

●  The type is what kind of variable each element of the array will be. 
● The name is what you want to call your array. 
● The size is how many elements you would like your array to contain.

```c
int student_grades[40];
```

● The type is what kind of variable each element of the array will be. 
● The name is what you want to call your array. 
● The size is how many elements you would like your array to contain.

```c
double menu_prices[8];
```

● The type is what kind of variable each element of the array will be. 
● The name is what you want to call your array. 
● The size is how many elements you would like your array to contain.

### Declaring and initialising an array
```c
// instantiation syntax 
bool truthtable[3] = { false, true, true };
```

```c
// individual element syntax 
bool truthtable[3]; 
truthtable[0] = false; 
truthtable[1] = true; 
truthtable[2] = true;
```

```c
// instantiation syntax
 bool truthtable[] = { false, true, true };
```

# Important 

● While we can treat individual elements of arrays as variables, we cannot treat entire arrays themselves as variables. 

● We cannot, for instance, assign one array to another using the assignment operator. That is not legal C. 

● Instead, we must use a loop to copy over the elements one at a time.


## ● Recall that most variables in C are passed by value in function calls.

## ● Arrays do not follow this rule. Rather, they are passed by reference. The callee receives the actual array, not a copy of it. 

## ● What does that mean when the callee manipulates elements of the array?
