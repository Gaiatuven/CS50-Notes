```c
#include <stdio.h>

void set_array(int array[4]);
void set_int(int x);

int main(void)
{
    int a = 10;
    int b[4] = { 0, 1, 2, 3 };

    set_int(a);
    set_array(b);

    printf("%d %d\n", a, b[0]);
}

void set_array(int array[4])
{
    array[0] = 22;
}

void set_int(int x)
{
    x = 22;
}
```

This code demonstrates the difference between **pass by value** and **pass by reference** in C.

---

### What the code does

Two functions are declared up top:

- `set_array` — takes an array of 4 ints
- `set_int` — takes a single int

In `main`, an int `a = 10` and an array `b = {0, 1, 2, 3}` are created, both functions are called, then the values are printed.

---

### The key concept: How C passes arguments

**`set_int(a)` — Pass by Value**

c

```c
void set_int(int x) {
    x = 22;  // modifies a LOCAL COPY of a
}
```

- C copies the _value_ of `a` into `x`
- Changing `x` inside the function has **no effect** on `a`
- After the call, `a` is still `10`

**`set_array(b)` — Pass by Reference (pointer)**

c

````c
void set_array(int array[4]) {
    array[0] = 22;  // modifies the ORIGINAL array
}
```

- Arrays in C automatically decay to a **pointer** to their first element
- So `array` inside the function points to the **same memory** as `b` in main
- Changing `array[0]` **does** affect the original `b`
- After the call, `b[0]` is `22`

---

### Output
```
10 22
````

- `a` → still `10` (copy was modified, not the original)
- `b[0]` → now `22` (original memory was modified)

---

### The golden rule

|Type|How it's passed|Can function modify original?|
|---|---|---|
|`int`, `char`, etc.|By value (copy)|❌ No|
|Array|By pointer (reference)|✅ Yes|

This is why in C, if you want a function to modify a plain variable, you have to explicitly pass a pointer to it: `set_int(&a)`.