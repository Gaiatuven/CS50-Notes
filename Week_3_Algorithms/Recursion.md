• We might describe an implementation of an algorithm as being particularly “elegant” if it solves a problem in a way that is both interesting and easy to visualize. 

• The technique of recursion is a very common way to implement such an “elegant” solution. 

• The definition of a recursive function is one that, as part of its execution, invokes itself.



• The factorial function (n!) is defined over all positive integers.
• n! equals all of the positive integers less than or equal to n, multiplied together.
• Thinking in terms of programming, we’ll define the mathematical function n! as fact(n).

fact(1) = 1
fact(2) = 2 * 1
fact(3) = 3 * 2 * 1
fact(4) = 4 * 3 * 2 * 1
fact(5) = 5 * 4 * 3 * 2 * 1
...

fact(1) = 1
fact(2) = 2 * fact(1)
fact(3) = 3 * 2 * 1
fact(4) = 4 * 3 * 2 * 1
fact(5) = 5 * 4 * 3 * 2 * 1
...

fact(1) = 1
fact(2) = 2 * fact(1)
fact(3) = 3 * fact(2)
fact(4) = 4 * 3 * 2 * 1
fact(5) = 5 * 4 * 3 * 2 * 1
...

fact(1) = 1
fact(2) = 2 * fact(1)
fact(3) = 3 * fact(2)
fact(4) = 4 * fact(3)
fact(5) = 5 * 4 * 3 * 2 * 1
...

fact(1) = 1
fact(2) = 2 * fact(1)
fact(3) = 3 * fact(2)
fact(4) = 4 * fact(3)
fact(5) = 5 * fact(4)
...

fact(n) = n * fact(n-1)

## 1. The Top-Down View (The "Calls")

When you run `fact(5)`, the computer doesn't know what $4 \times 3 \times 2 \times 1$ is yet. It just knows:

> "To give you `fact(5)`, I first need to go find `fact(4)`."

This continues until it reaches the **Base Case**:

- `fact(5)` = $5 \times$ `fact(4)`
    
- `fact(4)` = $4 \times$ `fact(3)`
    
- `fact(3)` = $3 \times$ `fact(2)`
    
- `fact(2)` = $2 \times$ `fact(1)`
    
- `fact(1)` = $1$ (The search stops here!)
    

---

## 2. The Bottom-Up View (The "Returns")

Once the computer hits `fact(1) = 1`, it can finally start doing the math you listed, working its way backward up the **Call Stack**:

1. It takes the $1$ from `fact(1)` and plugs it into `fact(2)` $\rightarrow$ **2**
    
2. It takes that $2$ and plugs it into `fact(3)` $\rightarrow$ **6**
    
3. It takes that $6$ and plugs it into `fact(4)` $\rightarrow$ **24**
    
4. It takes that $24$ and plugs it into `fact(5)` $\rightarrow$ **120**
    

---

## The Substitution Rule

If we were to write out your logic using the actual function calls, it looks like a series of substitutions:

$$fact(5) = 5 \times (4 \times (3 \times (2 \times (1))))$$

Each set of parentheses represents a new **Stack Frame** being opened. The computer cannot close the outer parentheses until the inner ones return a value.

## Why this matters

This pattern is why recursion is so powerful for **Fractals** or **Data Trees**. You define one small rule ($n \times \text{previous result}$), and the computer handles the massive expansion of logic for you.

```c
int fact(int n)
{
if (n == 1)
	return 1;
else
	return n * fact(n-1);
}
```

• In general, but not always, recursive functions replace loops in
non-recursive functions.
```c
int fact(int n)
{
if (n == 1)
	return 1;
else
	return n * fact(n-1);
}
```

```c
int fact2(int n)
{
	int product = 1;
	while(n > 0)
{
	product *= n;
		n--;
}
	return product;
}
```