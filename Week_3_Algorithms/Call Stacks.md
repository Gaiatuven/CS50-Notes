• When you call a function, the system sets aside space in memory for that function to do its necessary work. 
	• We frequently call such chunks of memory stack frames or function frames.
	
	 • More than one function’s stack frame may exist in memory at a given time. If main() calls move(), which then calls direction(), all three functions have open frames.

• These frames are arranged in a stack. The frame for the most recently called function is always on the top of the stack. 

• When a new function is called, a new frame is pushed onto the top of the stack and becomes the active frame. 

• When a function finishes its work, its frame is popped off of the stack, and the frame immediately below it becomes the new, active, function on the top of the stack. This function picks up immediately where it left off.

```c
int fact(int n) 
{ if (n == 1) 
	return 1; 
else return n * fact(n-1); } 

int main(void) 
{ printf(“%i\n”, fact(5)); }
```

When you call `fact(5)`, the computer doesn't get the answer `120` immediately. Instead, it "suspends" each function call until it hits the **Base Case** ($n == 1$).

---

## The Expansion (Pushing to the Stack)

Each time `fact(n-1)` is called, a new **Stack Frame** is pushed onto the call stack. Each frame waits for the one above it to return a value.

1. `main()` calls `fact(5)`
    
2. `fact(5)` calls `fact(4)`
    
3. `fact(4)` calls `fact(3)`
    
4. `fact(3)` calls `fact(2)`
    
5. `fact(2)` calls `fact(1)` $\rightarrow$ **Base Case Reached!**
    

---

## The Resolution (Popping from the Stack)

Once `fact(1)` returns `1`, the stack begins to "unwind." Each function finally performs its multiplication and returns the result to the caller below it.

- `fact(1)` returns **1**
    
- `fact(2)` calculates $2 \times 1$ and returns **2**
    
- `fact(3)` calculates $3 \times 2$ and returns **6**
    
- `fact(4)` calculates $4 \times 6$ and returns **24**
    
- `fact(5)` calculates $5 \times 24$ and returns **120**
    
- `main()` receives **120** and prints it.