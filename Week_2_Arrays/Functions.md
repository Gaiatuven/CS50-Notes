
What is a function?

● A black box with a set of 0+ inputs and 1 output.

![[Screenshot from 2026-03-06 17-44-20.png]]

### Why use functions? 

● Organization 
● Functions help break up a complicated problem into more manageable subparts.
● Simplification 
● Smaller components tend to be easier to design, implement, and debug. 
● Reusability 
● Functions can be recycled; you only need to write them once, but can use them as often as you need!

## Function Declarations 

● The first step to creating a function is to declare it. This gives the compiler a heads-up that a user-written function appears in the code. 

● Function declarations should always go atop your code, before you begin writing main(). 

● There is a standard form that every function declaration follows.

```c
	return-type name(argument-list);
```

The return-type is what kind of variable the function will output. 

● The name is what you want to call your function.
● The argument-list is the comma-separated set of inputs to your function, each of which has a type and a name

## Function Definitions

```C
float mult_two_reals(float x, float y); // Function declaraction
```

```c
float mult_two_reals(float x, float y) // Function definition
{
float product = x * y;
return product;
} 
```

