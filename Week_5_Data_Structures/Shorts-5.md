
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


## Singly-Linked Lists


So far in the course, we’ve only had one kind of data structure for representing collections of like values. 

• structs, recall, give us “containers” for holding variables of different data types, typically. 

• Arrays are great for element lookup, but unless we want to insert at the very end of the array, inserting elements is quite costly – remember insertion sort?

Arrays also suffer from a great inflexibility – what happens if we need a larger array than we thought? 

• Through clever use of pointers, dynamic memory allocation, and structs, we can put those two pieces together to develop a new kind of data structure that gives us the ability to grow and shrink a collection of like values to fit our needs.

We call this combination of elements, when used in this way, a linked list. • A linked list node is a special kind of struct with two members: 

• Data of some data type (int, char, float…) 
• A pointer to another node of the same type
• In this way, a set of nodes together can be thought of as forming a chain of elements that we can follow from beginning to end.

```c
#include <stdio.h>
#include <stdlib.h>

// VALUE defines what type of data each node holds.
// Change this to whatever type you need (int, double, char*, etc.)
typedef int VALUE;

// A self-referential struct: each node points to the next node of the
// SAME type, which is how the nodes chain together into a list.
typedef struct sllist {
    VALUE val;
    struct sllist *next;   // must say "struct sllist*" here, not "sllnode*",
                            // because the typedef name doesn't exist yet
} sllnode;

// Create a single new node holding 'val', with next set to NULL
sllnode *make_node(VALUE val) {
    sllnode *node = malloc(sizeof(sllnode));
    if (node == NULL) {
        printf("Allocation failed\n");
        exit(1);
    }
    node->val = val;
    node->next = NULL;
    return node;
}

// Add a new node to the front of the list, return the new head
sllnode *push_front(sllnode *head, VALUE val) {
    sllnode *node = make_node(val);
    node->next = head;   // new node points to old head
    return node;          // new node becomes the head
}

// Add a new node to the end of the list
void push_back(sllnode *head, VALUE val) {
    sllnode *node = make_node(val);
    while (head->next != NULL) {   // walk to the last node
        head = head->next;
    }
    head->next = node;              // attach new node at the end
}

// Print every value in the list, following the chain of 'next' pointers
void print_list(sllnode *head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Free every node in the list (important! heap memory doesn't clean itself up)
void free_list(sllnode *head) {
    while (head != NULL) {
        sllnode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    // Start with one node
    sllnode *head = make_node(10);

    // Add nodes to the end
    push_back(head, 20);
    push_back(head, 30);

    printf("List after push_back(20), push_back(30):\n");
    print_list(head);

    // Add a node to the front (this changes who "head" is)
    head = push_front(head, 5);

    printf("List after push_front(5):\n");
    print_list(head);

    // Always free heap-allocated nodes when done
    free_list(head);
    head = NULL;

    return 0;
}
```


linked-list Example 

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int VALUE;

typedef struct sllist {
    VALUE val;
    struct sllist *next;
} sllnode;


/* ------------------------------------------------------------------
 * 1. CREATE a linked list (specifically, create a single new node).
 *    sllnode* create(VALUE val);
 *
 *    Steps:
 *    a. Dynamically allocate space for a new sllnode.
 *    b. Check to make sure we didn't run out of memory.
 *    c. Initialize the node's val field.
 *    d. Initialize the node's next field.
 *    e. Return a pointer to the newly created sllnode.
 * ------------------------------------------------------------------ */
sllnode *create(VALUE val) {
    sllnode *new = malloc(sizeof(sllnode));   // a. allocate

    if (new == NULL) {                        // b. check for out-of-memory
        printf("Error: out of memory\n");
        exit(1);
    }

    new->val = val;                           // c. initialize val
    new->next = NULL;                         // d. initialize next

    return new;                               // e. return the new node
}


/* ------------------------------------------------------------------
 * 2. SEARCH through a linked list to find an element.
 *    bool find(sllnode* head, VALUE val);
 *
 *    Steps:
 *    a. Create a traversal pointer pointing to the list's head.
 *    b. If the current node's val field is what we're looking for,
 *       report success.
 *    c. If not, set the traversal pointer to the next pointer in the
 *       list and go back to step b.
 *    d. If you've reached the end of the list, report failure.
 * ------------------------------------------------------------------ */
bool find(sllnode *head, VALUE val) {
    sllnode *cur = head;          // a. traversal pointer starts at head

    while (cur != NULL) {         // d. stop when we fall off the end
        if (cur->val == val) {    // b. found it
            return true;
        }
        cur = cur->next;          // c. move to the next node
    }

    return false;                 // d. reached the end without finding it
}


/* ------------------------------------------------------------------
 * 3. INSERT a new node into the linked list (insert at the front).
 *    sllnode* insert(sllnode* head, VALUE val);
 *
 *    Steps:
 *    a. Create the new node (using create()).
 *    b. Point the new node's next at the current head.
 *    c. Return the new node as the new head of the list.
 * ------------------------------------------------------------------ */
sllnode *insert(sllnode *head, VALUE val) {
    sllnode *new = create(val);   // a. build the new node
    new->next = head;             // b. link it in front of the old head
    return new;                   // c. new head of the list
}


/* ------------------------------------------------------------------
 * 4. DELETE a single element from a linked list.
 *    sllnode* delete_node(sllnode* head, VALUE val);
 *
 *    Steps:
 *    a. If the list is empty, there's nothing to delete — return head.
 *    b. If the head itself holds the value, remember it, move head
 *       to the next node, free the old head, and return the new head.
 *    c. Otherwise, walk the list keeping a "previous" pointer, until
 *       we find the node to delete or fall off the end.
 *    d. Unlink the found node by pointing prev->next around it,
 *       then free it.
 *    e. Return the (possibly unchanged) head of the list.
 * ------------------------------------------------------------------ */
sllnode *delete_node(sllnode *head, VALUE val) {
    if (head == NULL) {                 // a. empty list
        return NULL;
    }

    if (head->val == val) {             // b. deleting the head node
        sllnode *tmp = head;
        head = head->next;
        free(tmp);
        return head;
    }

    sllnode *prev = head;
    sllnode *cur = head->next;

    while (cur != NULL) {               // c. search the rest of the list
        if (cur->val == val) {
            prev->next = cur->next;     // d. unlink cur
            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    }

    return head;                        // e. value not found, unchanged
}


/* ------------------------------------------------------------------
 * 5. DELETE an entire linked list.
 *    void destroy(sllnode* head);
 *
 *    Steps:
 *    a. Walk the list one node at a time.
 *    b. Before freeing a node, save a pointer to the next one so we
 *       don't lose the rest of the list.
 *    c. Free the current node.
 *    d. Move on to the next node and repeat until the list is empty.
 * ------------------------------------------------------------------ */
void destroy(sllnode *head) {
    sllnode *cur = head;

    while (cur != NULL) {
        sllnode *next = cur->next;   // b. save next before freeing
        free(cur);                   // c. free current node
        cur = next;                  // d. advance
    }
}


/* -------------------------- helper for demo -------------------------- */
void print_list(sllnode *head) {
    sllnode *cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}


int main(void) {
    /* 1. Create the first node of the list */
    sllnode *head = create(6);
    printf("After create(6):\n");
    print_list(head);

    /* 3. Insert some more nodes at the front */
    head = insert(head, 4);
    head = insert(head, 2);
    printf("\nAfter inserting 4, then 2 at the front:\n");
    print_list(head);   // 2 -> 4 -> 6 -> NULL

    /* 2. Search for a couple of values */
    printf("\nSearching the list:\n");
    printf("find(4): %s\n", find(head, 4) ? "found" : "not found");
    printf("find(9): %s\n", find(head, 9) ? "found" : "not found");

    /* 4. Delete a single node (including the head) */
    head = delete_node(head, 4);       // delete a middle/interior value
    printf("\nAfter deleting 4:\n");
    print_list(head);

    head = delete_node(head, 2);       // delete the current head
    printf("\nAfter deleting 2 (the head):\n");
    print_list(head);

    /* 5. Delete the entire list */
    destroy(head);
    head = NULL;   // good practice: avoid a dangling pointer
    printf("\nAfter destroy(), list is empty. head = NULL\n");

    return 0;
}
```


