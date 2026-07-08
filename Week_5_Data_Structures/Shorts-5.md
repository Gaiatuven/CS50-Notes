
Structures

Structures provide a way to unify several variables of different types into a single, new variable type which can be assigned its own type name. 

• We use structures (structs) to group together elements of a variety of data types that have a logical connection. 

• Think of a structure like a “super-variable”.

```c
#include <stdio.h>
#include <string.h>

// A struct groups related variables of different types under one name.
// Here, "car" bundles together everything you'd want to know about a car.
struct car {
    int year;
    char model[10];
    char plate[7];
    int odometer;
    double engine_size;
};

// Function that takes a struct by value (a copy) and prints its fields
void print_car(struct car c) {
    printf("Year:        %d\n", c.year);
    printf("Model:       %s\n", c.model);
    printf("Plate:       %s\n", c.plate);
    printf("Odometer:    %d miles\n", c.odometer);
    printf("Engine size: %.1f L\n", c.engine_size);
    printf("------------------------------\n");
}

// Function that takes a pointer to a struct, so it can MODIFY the original
void add_miles(struct car *c, int miles) {
    c->odometer += miles;   // "->" is shorthand for (*c).odometer
}

int main(void) {
    // 1. Declare and initialize a struct variable using an initializer list
    struct car my_car = {2020, "Civic", "CA1234", 35000, 2.0};

    // 2. Access individual fields with the dot operator
    printf("My car is a %d %s\n", my_car.year, my_car.model);

    // 3. Assign/modify a field directly
    strcpy(my_car.plate, "XYZ987");   // char arrays need strcpy, not '='
    my_car.odometer = 35200;

    // 4. Pass the whole struct to a function
    print_car(my_car);

    // 5. Pass a pointer so the function can change the original data
    add_miles(&my_car, 150);
    printf("After a road trip:\n");
    print_car(my_car);

    // 6. An array of structs — useful for storing many cars
    struct car fleet[3] = {
        {2018, "Corolla", "ABC111", 60000, 1.8},
        {2022, "Model3",  "TSL500", 12000, 0.0},   // electric, no engine size
        {2015, "F150",    "TRK777", 98000, 5.0}
    };

    printf("Fleet overview:\n");
    for (int i = 0; i < 3; i++) {
        print_car(fleet[i]);
    }

    // 7. A pointer to a struct
    struct car *ptr = &my_car;
    printf("Using a pointer, model is: %s\n", ptr->model);

    return 0;
}
```

- **Declaring & initialising** — `struct car my_car = {2020, "Civic", "CA1234", 35000, 2.0};` sets all fields at once.
- **Accessing fields** with the dot operator: `my_car.year`, `my_car.model`.
- **Modifying fields** — note that `char` arrays need `strcpy()`, you can't just use `=` on them.
- **Passing a struct to a function by value** (`print_car`) — the function gets a copy, so changes inside it don't affect the original.
- **Passing a pointer to a struct** (`add_miles`) — this lets a function actually modify the original data, using `->` instead of `.` to access fields through a pointer.
- **Arrays of structs** — `fleet[3]` shows how to store multiple cars together, handy for lists of records.
- **Pointers to structs** in general (`struct car *ptr = &my_car;`).


Once we have defined a structure, which we typically do in separate .h files or atop our programs outside of any functions, we have effectively created a new type. 

• That means we can create variables of that type using the familiar syntax. 

• We can also access the various fields (also known as members) of the structure using the dot operator (.)

Structures, like variables of all other data types, do not need to be created on the stack. We can dynamically allocate structures at run time if our program requires it. 

• In order to access the fields of our structures in that situation, we first need to dereference the pointer to the structure, and then we can access its fields.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car {
    int year;
    char model[10];
    char plate[7];
    int odometer;
    double engine_size;
};

int main(void) {
    // Allocate enough memory on the heap for one struct car
    struct car *mycar = malloc(sizeof(struct car));

    // ALWAYS check malloc didn't fail before using the pointer
    if (mycar == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Since mycar is a pointer, use -> instead of . to access fields
    mycar->year = 2021;
    strcpy(mycar->model, "Accord");
    strcpy(mycar->plate, "HND555");
    mycar->odometer = 15000;
    mycar->engine_size = 1.5;

    printf("%d %s, plate %s, %d miles, %.1fL engine\n",
           mycar->year, mycar->model, mycar->plate,
           mycar->odometer, mycar->engine_size);

    // Free the memory when you're done with it — heap memory doesn't
    // clean itself up automatically like stack variables do
    free(mycar);
    mycar = NULL;   // good practice: avoid leaving a "dangling pointer"

    return 0;
}
```


`Key differences from your earlier struct car my_car = {...};:`

`|                   Stack (struct car my_car;)                     Heap (malloc)|`
`|---|---|---|`
`|Memory lives|           Automatically,   until scope ends|Until you call free()|`
`|Access syntax|         my_car.year (dot)|                   mycar->year (arrow)|`
`|Must check for failure?|        No|                Yes — malloc can return NULL|`
`|Must free manually?|            No|              Yes — or you get a memory leak|`


This is a little annoying. And so as you might expect, there’s a shorter way! 

• The arrow operator (->) makes this process easier. It’s an operator that does two things back-to-back: 

• First, it deference the pointer on the left side of the operator. • Second, it accesses the field on the right side of the operator.


