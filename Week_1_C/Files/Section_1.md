#####  # include
Keyword to import libraries

The stdio.h(standard Input/Output) allows us to use the printf function 

```c
#include <stdio.h> // header

int main(void)
{
	printf("Hello, world\n");
	
}
```


## Variables

`string name = "David"' // string;
int balance = 20  // integer 


![[Screenshot from 2026-02-19 06-27-09.png]]


## Arithmetic Operators

|Operator|Description|Example|
|---|---|---|
|`+`|Addition|`a + b`|
|`-`|Subtraction|`a - b`|
|`*`|Multiplication|`a * b`|
|`/`|Division|`a / b`|
|`%`|Modulus (remainder)|`a % b`|
|`++`|Increment|`a++` or `++a`|
|`--`|Decrement|`a--` or `--a`|

## Relational (Comparison) Operators

|Operator|Description|Example|
|---|---|---|
|`==`|Equal to|`a == b`|
|`!=`|Not equal to|`a != b`|
|`>`|Greater than|`a > b`|
|`<`|Less than|`a < b`|
|`>=`|Greater than or equal|`a >= b`|
|`<=`|Less than or equal|`a <= b`|

## Logical Operators

|Operator|Description|Example|
|---|---|---|
|`&&`|Logical AND|`a && b`|
|`\|`|Logical OR|`a \| b`|
|`!`|Logical NOT|`!a`|

## Bitwise Operators

|Operator|Description|Example|
|---|---|---|
|`&`|Bitwise AND|`a & b`|
|`\|`|Bitwise OR|`a \| b`|
|`^`|Bitwise XOR|`a ^ b`|
|`~`|Bitwise NOT|`~a`|
|`<<`|Left shift|`a << 2`|
|`>>`|Right shift|`a >> 2`|

## Assignment Operators

|Operator|Description|Example|
|---|---|---|
|`=`|Assign|`a = 5`|
|`+=`|Add and assign|`a += 5`|
|`-=`|Subtract and assign|`a -= 5`|
|`*=`|Multiply and assign|`a *= 5`|
|`/=`|Divide and assign|`a /= 5`|
|`%=`|Modulus and assign|`a %= 5`|
|`&=`|Bitwise AND assign|`a &= 5`|
|`\|=`|Bitwise OR assign|`a \|= 5`|
|`^=`|Bitwise XOR assign|`a ^= 5`|
|`<<=`|Left shift assign|`a <<= 2`|
|`>>=`|Right shift assign|`a >>= 2`|

## Other Operators

|Operator|Description|Example|
|---|---|---|
|`? :`|Ternary (conditional)|`a > b ? a : b`|
|`sizeof`|Size of a type/variable|`sizeof(int)`|
|`&`|Address-of|`&a`|
|`*`|Dereference (pointer)|`*ptr`|
|`.`|Member access (struct)|`obj.field`|
|`->`|Pointer member access|`ptr->field`|
|`,`|Comma (sequence)|`a = (x++, x+1)`|
|`(type)`|Cast|`(float)a`|

## Key Notes

**Pre vs Post increment:**

```c
int a = 5;
int b = ++a; // b = 6, a = 6 (increment first)
int c = a++; // c = 6, a = 7 (use first, then increment)
```

**Ternary operator:**

```c
int max = (a > b) ? a : b;
```

**Operator precedence** (high to low, simplified):

1. `()`, `[]`, `->`, `.`
2. Unary: `!`, `~`, `++`, `--`, `sizeof`, `(type)`, `*`, `&`
3. `*`, `/`, `%`
4. `+`, `-`
5. `<<`, `>>`
6. `<`, `<=`, `>`, `>=`
7. `==`, `!=`
8. `&`, `^`, `|`
9. `&&`, `||`
10. `? :`
11. Assignment: `=`, `+=`, etc.
12. `,`

When in doubt, use **parentheses** to make precedence explicit!

## CS50 FUNCTIONS

###### Get input

![[Screenshot from 2026-02-19 06-36-44.png]]

# Format Codes in C (`printf` / `scanf`)

## Basic Format Specifiers

| Specifier | Data Type               | Example                               |
| --------- | ----------------------- | ------------------------------------- |
| `%d`      | `int` (decimal)         | `printf("%d", 42)` → `42`             |
| `%i`      | `int` (integer)         | same as `%d`                          |
| `%u`      | `unsigned int`          | `printf("%u", 42u)`                   |
| `%f`      | `float` / `double`      | `printf("%f", 3.14)` → `3.140000`     |
| `%lf`     | `double` (in scanf)     | `scanf("%lf", &d)`                    |
| `%e`      | Scientific notation     | `printf("%e", 3.14)` → `3.140000e+00` |
| `%g`      | Shorter of `%f`/`%e`    | `printf("%g", 3.14)` → `3.14`         |
| `%c`      | `char`                  | `printf("%c", 'A')` → `A`             |
| `%s`      | `string` (char array)   | `printf("%s", "hi")` → `hi`           |
| `%p`      | Pointer address         | `printf("%p", ptr)`                   |
| `%o`      | Octal                   | `printf("%o", 8)` → `10`              |
| `%x`      | Hexadecimal (lowercase) | `printf("%x", 255)` → `ff`            |
| `%X`      | Hexadecimal (uppercase) | `printf("%X", 255)` → `FF`            |
| `%ld`     | `long int`              | `printf("%ld", 100L)`                 |
| `%lld`    | `long long int`         | `printf("%lld", 100LL)`               |
| `%lu`     | `unsigned long`         | `printf("%lu", 100UL)`                |
| `%%`      | Literal `%` sign        | `printf("%%")` → `%`                  |

---

## Format Modifiers

### Width & Precision

```c
printf("%10d", 42);       // "        42"  (right-aligned, width 10)
printf("%-10d", 42);      // "42        "  (left-aligned)
printf("%010d", 42);      // "0000000042"  (zero-padded)
printf("%.2f", 3.14159);  // "3.14"        (2 decimal places)
printf("%8.2f", 3.14159); // "    3.14"    (width 8, 2 decimals)
printf("%*d", 10, 42);    // "        42"  (width from argument)
```

### Length Modifiers

|Modifier|Meaning|Example|
|---|---|---|
|`h`|`short int`|`%hd`|
|`hh`|`char` as int|`%hhd`|
|`l`|`long int`|`%ld`|
|`ll`|`long long int`|`%lld`|
|`L`|`long double`|`%Lf`|

---

## Common Examples

```c
#include <stdio.h>

int main() {
    int i = 42;
    float f = 3.14159;
    char c = 'A';
    char s[] = "Hello";

    printf("%d\n", i);          // 42
    printf("%05d\n", i);        // 00042
    printf("%.2f\n", f);        // 3.14
    printf("%10.3f\n", f);      //      3.142
    printf("%c\n", c);          // A
    printf("%s\n", s);          // Hello
    printf("%-10s|\n", s);      // Hello     |
    printf("%x\n", 255);        // ff
    printf("%X\n", 255);        // FF
    printf("%o\n", 8);          // 10
    printf("%e\n", f);          // 3.141590e+00
    printf("%p\n", &i);         // 0x7ffee4b (address)

    return 0;
}
```

---

## `scanf` Notes

```c
int i;
float f;
double d;
char s[50];

scanf("%d", &i);      // read int
scanf("%f", &f);      // read float
scanf("%lf", &d);     // read double (must use %lf for double in scanf!)
scanf("%s", s);       // read string (no & needed, stops at whitespace)
scanf("%c", &c);      // read single char
scanf(" %c", &c);     // space before %c skips whitespace/newline
```

> ⚠️ **Key difference:** `printf` uses `%f` for both `float` and `double`, but `scanf` requires `%f` for `float` and `%lf` for `double`.