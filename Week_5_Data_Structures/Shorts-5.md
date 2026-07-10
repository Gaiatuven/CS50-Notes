
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


## Doubly-Linked Lists

• Singly-linked lists really extend our ability to collect and organize data, but they suffer from a crucial limitation. 
• We can only ever move in one direction through the list.
• Consider the implication that would have for trying to delete a node. 
• A doubly-linked list, by contrast, allows us to move forward and backward through the list, all by simply adding one extra pointer to our struct definition. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int VALUE;

/* A doubly-linked list node has TWO pointers instead of one:
 * 'next' points forward, 'prev' points backward. This lets you
 * traverse the list in either direction, and makes deletion easier
 * since a node can unlink itself without needing a separate
 * "previous" tracking pointer during traversal. */
typedef struct dllist {
    VALUE val;
    struct dllist *next;
    struct dllist *prev;
} dllnode;


/* ------------------------------------------------------------------
 * 1. CREATE a linked list (create a single new node).
 *    dllnode* create(VALUE val);
 *
 *    Steps:
 *    a. Dynamically allocate space for a new dllnode.
 *    b. Check to make sure we didn't run out of memory.
 *    c. Initialize the node's val field.
 *    d. Initialize both the next and prev fields.
 *    e. Return a pointer to the newly created dllnode.
 * ------------------------------------------------------------------ */
dllnode *create(VALUE val) {
    dllnode *new = malloc(sizeof(dllnode));   // a. allocate

    if (new == NULL) {                         // b. check for out-of-memory
        printf("Error: out of memory\n");
        exit(1);
    }

    new->val = val;                            // c. initialize val
    new->next = NULL;                          // d. initialize next
    new->prev = NULL;                          // d. initialize prev

    return new;                                // e. return the new node
}


/* ------------------------------------------------------------------
 * 2. SEARCH through a linked list to find an element.
 *    bool find(dllnode* head, VALUE val);
 *
 *    Steps (same logic as the singly-linked case, using 'next'):
 *    a. Create a traversal pointer pointing to the list's head.
 *    b. If the current node's val field is what we're looking for,
 *       report success.
 *    c. If not, advance the traversal pointer via next and repeat.
 *    d. If you reach the end of the list, report failure.
 * ------------------------------------------------------------------ */
bool find(dllnode *head, VALUE val) {
    dllnode *cur = head;         // a. traversal pointer starts at head

    while (cur != NULL) {        // d. stop when we fall off the end
        if (cur->val == val) {   // b. found it
            return true;
        }
        cur = cur->next;         // c. move forward
    }

    return false;                // d. not found
}


/* ------------------------------------------------------------------
 * 3. INSERT a new node into the linked list (insert at the front).
 *    dllnode* insert(dllnode* head, VALUE val);
 *
 *    Steps:
 *    a. Dynamically allocate space for a new dllnode.
 *    b. Check to make sure we didn't run out of memory.
 *    c. Populate and insert the node at the beginning of the list
 *       (set its val, point its next at the old head, and its
 *       prev at NULL since it's now the first node).
 *    d. Fix the prev pointer of the OLD head so it points back at
 *       the new node (this is the step singly-linked lists don't need).
 *    e. Return a pointer to the new head of the linked list.
 * ------------------------------------------------------------------ */
dllnode *insert(dllnode *head, VALUE val) {
    dllnode *new = malloc(sizeof(dllnode));   // a. allocate

    if (new == NULL) {                         // b. check for out-of-memory
        printf("Error: out of memory\n");
        exit(1);
    }

    new->val = val;          // c. populate...
    new->next = head;        // c. ...and insert at the front
    new->prev = NULL;        // c. new node is the first, so no prev

    if (head != NULL) {      // d. fix the OLD head's prev pointer
        head->prev = new;    //    (only if the list wasn't empty)
    }

    return new;               // e. new node is the new head
}


/* ------------------------------------------------------------------
 * 4. DELETE a single element from a linked list.
 *    dllnode* delete_node(dllnode* head, VALUE val);
 *
 *    Because each node knows both its neighbors, deletion doesn't
 *    need a separate "prev" tracking pointer during the search --
 *    the node being deleted already has direct access to both sides.
 *
 *    Steps:
 *    a. Walk the list looking for the node with a matching val.
 *    b. If not found, return head unchanged.
 *    c. If the node has a predecessor, point that predecessor's
 *       next past the deleted node (otherwise we're deleting the
 *       head, so the head becomes the next node).
 *    d. If the node has a successor, point that successor's prev
 *       back past the deleted node.
 *    e. Free the node and return the (possibly updated) head.
 * ------------------------------------------------------------------ */
dllnode *delete_node(dllnode *head, VALUE val) {
    dllnode *cur = head;

    while (cur != NULL && cur->val != val) {   // a. search
        cur = cur->next;
    }

    if (cur == NULL) {         // b. not found
        return head;
    }

    if (cur->prev != NULL) {          // c. relink the predecessor
        cur->prev->next = cur->next;
    } else {                          // c. deleting the head
        head = cur->next;
    }

    if (cur->next != NULL) {          // d. relink the successor
        cur->next->prev = cur->prev;
    }

    free(cur);                        // e. free the removed node
    return head;
}


/* ------------------------------------------------------------------
 * 5. DELETE an entire linked list.
 *    void destroy(dllnode* head);
 *
 *    Steps:
 *    a. Walk the list one node at a time.
 *    b. Save a pointer to the next node before freeing the current one.
 *    c. Free the current node.
 *    d. Advance and repeat until the list is empty.
 * ------------------------------------------------------------------ */
void destroy(dllnode *head) {
    dllnode *cur = head;

    while (cur != NULL) {
        dllnode *next = cur->next;   // b. save next before freeing
        free(cur);                   // c. free current node
        cur = next;                  // d. advance
    }
}


/* -------------------------- helpers for demo -------------------------- */
void print_forward(dllnode *head) {
    dllnode *cur = head;
    printf("forward: ");
    while (cur != NULL) {
        printf("%d <-> ", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}

void print_backward(dllnode *tail) {
    dllnode *cur = tail;
    printf("backward: ");
    while (cur != NULL) {
        printf("%d <-> ", cur->val);
        cur = cur->prev;
    }
    printf("NULL\n");
}


int main(void) {
    /* 1. Create the first node */
    dllnode *head = create(6);
    printf("After create(6):\n");
    print_forward(head);

    /* 3. Insert more nodes at the front */
    head = insert(head, 4);
    head = insert(head, 2);
    printf("\nAfter inserting 4, then 2 at the front:\n");
    print_forward(head);   // 2 <-> 4 <-> 6 <-> NULL

    /* Find the tail so we can demonstrate backward traversal */
    dllnode *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    print_backward(tail);  // 6 <-> 4 <-> 2 <-> NULL

    /* 2. Search for a couple of values */
    printf("\nSearching the list:\n");
    printf("find(4): %s\n", find(head, 4) ? "found" : "not found");
    printf("find(9): %s\n", find(head, 9) ? "found" : "not found");

    /* 4. Delete a single node (interior, then head) */
    head = delete_node(head, 4);
    printf("\nAfter deleting 4 (interior node):\n");
    print_forward(head);

    head = delete_node(head, 2);
    printf("\nAfter deleting 2 (the head):\n");
    print_forward(head);

    /* 5. Delete the entire list */
    destroy(head);
    head = NULL;
    printf("\nAfter destroy(), list is empty. head = NULL\n");

    return 0;
}
```

## Stacks

A stack is a special type of structure that can be used to maintain data in an organized way. 
• This data structure is commonly implemented in one of two ways: as an array or as a linked list. 
• In either case, the important rule is that when data is added to the stack, it sits “on top,” and so if an element needs to be removed, the most recently added element is the only element that can legally be removed. 

### • Last in, first out (LIFO) Stacks (Data Structure) 

• There are only two operations that may legally be performed on a stack.

• Push: Add a new element to the top of the stack. 
• Pop: Remove the most recently-added element from the top of the stack.

```c
#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 5

typedef int VALUE;

/* Array-based stack: instead of nodes and pointers, we use a fixed-size
 * array as the backing storage. 'top' is an index that tracks how many
 * elements are currently on the stack (and where the next push goes).
 * No malloc/free needed here for individual elements -- the whole
 * stack lives in one contiguous block of memory. */
typedef struct _stack {
    VALUE array[CAPACITY];
    int top;     // index of the next free slot; also equals the count
} stack;


/* ------------------------------------------------------------------
 * Initialize / "create" a stack.
 *
 * Unlike linked lists, we don't need malloc for each element -- the
 * array is already allocated as part of the struct. We just need to
 * set 'top' to indicate the stack is empty.
 * ------------------------------------------------------------------ */
void init(stack *s) {
    s->top = 0;   // 0 elements currently on the stack
}


/* ------------------------------------------------------------------
 * Check whether the stack is empty or full.
 * These checks guard every push/pop so we never read or write
 * outside the bounds of the array.
 * ------------------------------------------------------------------ */
bool is_empty(stack *s) {
    return s->top == 0;
}

bool is_full(stack *s) {
    return s->top == CAPACITY;
}


/* ------------------------------------------------------------------
 * PUSH a value onto the stack.
 *
 * Steps:
 * a. Check if the stack is full -- if so, report failure (can't grow
 *    an array-based stack past its fixed CAPACITY).
 * b. Place the new value at the index 'top' points to.
 * c. Increment 'top' so it points past the new element.
 * d. Report success.
 * ------------------------------------------------------------------ */
bool push(stack *s, VALUE val) {
    if (is_full(s)) {              // a. no room left
        return false;
    }

    s->array[s->top] = val;        // b. place the value
    s->top++;                      // c. advance top
    return true;                   // d. success
}


/* ------------------------------------------------------------------
 * POP the top value off the stack.
 *
 * Steps:
 * a. Check if the stack is empty -- if so, report failure.
 * b. Decrement 'top' so it points at the last pushed element.
 * c. Read that element out through the out-parameter 'val'.
 * d. Report success. (We don't need to erase the old array slot --
 *    decrementing 'top' logically removes it; the next push will
 *    overwrite it anyway.)
 * ------------------------------------------------------------------ */
bool pop(stack *s, VALUE *val) {
    if (is_empty(s)) {              // a. nothing to pop
        return false;
    }

    s->top--;                       // b. move top back onto the last element
    *val = s->array[s->top];        // c. hand the value back to the caller
    return true;                    // d. success
}


/* ------------------------------------------------------------------
 * PEEK at the top value without removing it.
 * ------------------------------------------------------------------ */
bool peek(stack *s, VALUE *val) {
    if (is_empty(s)) {
        return false;
    }

    *val = s->array[s->top - 1];    // top-1, since 'top' points PAST the last element
    return true;
}


/* ------------------------------------------------------------------
 * "Destroy" the stack.
 *
 * Since this is array-based (no malloc'd nodes), there's nothing to
 * free individually -- if 's' itself was heap-allocated, you'd just
 * free(s) once. Here we just reset it, for symmetry with the
 * linked-list destroy().
 * ------------------------------------------------------------------ */
void destroy(stack *s) {
    s->top = 0;
}


int main(void) {
    stack s;
    init(&s);

    printf("New stack created. is_empty: %s\n",
           is_empty(&s) ? "true" : "false");

    /* Push some values */
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    printf("\nPushed 10, 20, 30.\n");

    /* Peek at the top without removing it */
    VALUE top_val;
    if (peek(&s, &top_val)) {
        printf("peek(): %d\n", top_val);
    }

    /* Pop everything off and print in LIFO order */
    printf("\nPopping everything off:\n");
    VALUE popped;
    while (pop(&s, &popped)) {
        printf("popped: %d\n", popped);
    }

    /* Try popping from an empty stack */
    if (!pop(&s, &popped)) {
        printf("\nStack is empty, pop() correctly failed.\n");
    }

    /* Fill the stack to CAPACITY and try to overfill it */
    printf("\nFilling to capacity (%d):\n", CAPACITY);
    for (int i = 1; i <= CAPACITY; i++) {
        push(&s, i * 100);
        printf("pushed %d\n", i * 100);
    }
    if (!push(&s, 999)) {
        printf("Stack is full, push(999) correctly failed.\n");
    }

    destroy(&s);
    printf("\nStack destroyed (reset). is_empty: %s\n",
           is_empty(&s) ? "true" : "false");

    return 0;
}
```



## Queues

A queue is a special type of structure that can be used to maintain data in an organized way. 

• This data structure is commonly implemented in one of two ways: as an array or as a linked list. 
• In either case, the important rule is that when data is added to the queue, it is tacked onto the end, and so if an element needs to be removed, the element at the front is the only element that can legally be removed. 

### • First in, first out (FIFO)

```c
#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 5

typedef int VALUE;

/* Array-based queue, implemented as a CIRCULAR BUFFER.
 *
 * Why circular? A naive array queue would shift every element left
 * after each dequeue, which is slow (O(n)). Instead, we let 'front'
 * wrap around the end of the array back to index 0 using modulo
 * arithmetic, so both enqueue and dequeue are O(1).
 *
 * 'front' = index of the oldest element (next to be dequeued)
 * 'size'  = how many elements are currently stored
 * (the "rear" index isn't stored directly -- it's computed as
 *  (front + size) % CAPACITY whenever we need it) */
typedef struct _queue {
    VALUE array[CAPACITY];
    int front;
    int size;
} queue;


/* ------------------------------------------------------------------
 * Initialize / "create" a queue.
 * ------------------------------------------------------------------ */
void init(queue *q) {
    q->front = 0;
    q->size = 0;
}


bool is_empty(queue *q) {
    return q->size == 0;
}

bool is_full(queue *q) {
    return q->size == CAPACITY;
}


/* ------------------------------------------------------------------
 * ENQUEUE a value (add to the back of the line).
 *
 * Steps:
 * a. Check if the queue is full -- if so, report failure.
 * b. Compute the index of the next free slot: (front + size) % CAPACITY.
 *    The modulo is what lets this index "wrap around" to 0 once it
 *    reaches the end of the array.
 * c. Store the value there.
 * d. Increment size to reflect the new element.
 * e. Report success.
 * ------------------------------------------------------------------ */
bool enqueue(queue *q, VALUE val) {
    if (is_full(q)) {                          // a. no room left
        return false;
    }

    int rear = (q->front + q->size) % CAPACITY; // b. wrap-around index
    q->array[rear] = val;                        // c. store the value
    q->size++;                                   // d. one more element
    return true;                                 // e. success
}


/* ------------------------------------------------------------------
 * DEQUEUE a value (remove from the front of the line).
 *
 * Steps:
 * a. Check if the queue is empty -- if so, report failure.
 * b. Read the value out of the 'front' slot through the out-parameter.
 * c. Advance 'front' forward by one, wrapping around with modulo.
 * d. Decrement size.
 * e. Report success.
 * ------------------------------------------------------------------ */
bool dequeue(queue *q, VALUE *val) {
    if (is_empty(q)) {                    // a. nothing to remove
        return false;
    }

    *val = q->array[q->front];            // b. read the oldest element
    q->front = (q->front + 1) % CAPACITY; // c. advance front, wrap if needed
    q->size--;                            // d. one fewer element
    return true;                          // e. success
}


/* ------------------------------------------------------------------
 * PEEK at the front value without removing it.
 * ------------------------------------------------------------------ */
bool peek(queue *q, VALUE *val) {
    if (is_empty(q)) {
        return false;
    }

    *val = q->array[q->front];
    return true;
}


/* ------------------------------------------------------------------
 * "Destroy" the queue. Array-based, so nothing to individually free --
 * just reset it (mirrors destroy() for the array-based stack).
 * ------------------------------------------------------------------ */
void destroy(queue *q) {
    q->front = 0;
    q->size = 0;
}


int main(void) {
    queue q;
    init(&q);

    printf("New queue created. is_empty: %s\n",
           is_empty(&q) ? "true" : "false");

    /* Enqueue some values */
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printf("\nEnqueued 10, 20, 30.\n");

    VALUE front_val;
    if (peek(&q, &front_val)) {
        printf("peek(): %d\n", front_val);   // should be 10 (FIFO)
    }

    /* Dequeue two, then enqueue two more -- this forces the circular
     * wrap-around, since front will advance past where it started */
    VALUE out;
    dequeue(&q, &out);
    printf("\ndequeued: %d\n", out);
    dequeue(&q, &out);
    printf("dequeued: %d\n", out);

    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);   // this one wraps around to index 0 internally
    printf("enqueued 40, 50, 60 (60 wraps around the array internally)\n");

    /* Drain the rest in FIFO order to prove correctness despite wrap */
    printf("\nDraining the queue (should print 30, 40, 50, 60 in order):\n");
    while (dequeue(&q, &out)) {
        printf("dequeued: %d\n", out);
    }

    if (!dequeue(&q, &out)) {
        printf("\nQueue is empty, dequeue() correctly failed.\n");
    }

    /* Fill to capacity and try to overfill */
    printf("\nFilling to capacity (%d):\n", CAPACITY);
    for (int i = 1; i <= CAPACITY; i++) {
        enqueue(&q, i * 100);
        printf("enqueued %d\n", i * 100);
    }
    if (!enqueue(&q, 999)) {
        printf("Queue is full, enqueue(999) correctly failed.\n");
    }

    destroy(&q);
    printf("\nQueue destroyed (reset). is_empty: %s\n",
           is_empty(&q) ? "true" : "false");

    return 0;
}
```


### Linked list-based implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int VALUE;

/* Each node in this queue is doubly-linked (next AND prev), which is
 * what lets us add to the rear and remove from the front in O(1) --
 * without a 'prev' pointer, removing from the front is easy, but a
 * singly-linked list can't cheaply find "the node before the tail"
 * if it ever needed to shrink from that end.
 *
 * Note: unlike the array-based version, there's no separate "queue"
 * struct holding metadata -- each node doubles as a piece of the
 * queue itself. Because of that, we need to track the FRONT and REAR
 * pointers *outside* the nodes (in main, passed around by reference),
 * since no single node knows where the whole queue begins and ends. */
typedef struct _queue {
    VALUE val;
    struct _queue *prev;
    struct _queue *next;
} queue;


/* ------------------------------------------------------------------
 * CREATE a single new node.
 *
 * Steps:
 * a. Dynamically allocate space for a new node.
 * b. Check to make sure we didn't run out of memory.
 * c. Initialize the node's val field.
 * d. Initialize both next and prev to NULL.
 * e. Return a pointer to the newly created node.
 * ------------------------------------------------------------------ */
queue *create(VALUE val) {
    queue *new = malloc(sizeof(queue));   // a. allocate

    if (new == NULL) {                     // b. check for out-of-memory
        printf("Error: out of memory\n");
        exit(1);
    }

    new->val = val;    // c. initialize val
    new->next = NULL;  // d. initialize next
    new->prev = NULL;  // d. initialize prev

    return new;        // e. return the new node
}


/* ------------------------------------------------------------------
 * ENQUEUE a value (add to the rear of the queue).
 *
 * We take 'front' and 'rear' as pointers-to-pointers (queue**) because
 * this function may need to change what the CALLER's front/rear
 * variables point to (e.g. enqueueing into an empty queue sets both).
 *
 * Steps:
 * a. Create the new node.
 * b. If the queue is currently empty, the new node becomes both
 *    the front and the rear.
 * c. Otherwise, link the new node in after the current rear:
 *    old rear's next -> new node, new node's prev -> old rear.
 * d. Update rear to point at the new node.
 * ------------------------------------------------------------------ */
void enqueue(queue **front, queue **rear, VALUE val) {
    queue *new = create(val);        // a. build the new node

    if (*front == NULL) {            // b. queue was empty
        *front = new;
        *rear = new;
        return;
    }

    (*rear)->next = new;             // c. link old rear -> new node
    new->prev = *rear;               // c. new node -> old rear
    *rear = new;                     // d. new node is the new rear
}


/* ------------------------------------------------------------------
 * DEQUEUE a value (remove from the front of the queue).
 *
 * Steps:
 * a. If the queue is empty, report failure.
 * b. Read the front node's val out through the out-parameter.
 * c. Advance front to the next node.
 * d. If the queue is now empty (front became NULL), also clear rear.
 *    Otherwise, clear the new front's prev pointer (it has no
 *    predecessor anymore).
 * e. Free the old front node and report success.
 * ------------------------------------------------------------------ */
bool dequeue(queue **front, queue **rear, VALUE *val) {
    if (*front == NULL) {            // a. nothing to remove
        return false;
    }

    queue *old_front = *front;
    *val = old_front->val;           // b. hand back the value

    *front = old_front->next;        // c. advance front

    if (*front == NULL) {            // d. queue is now empty
        *rear = NULL;
    } else {
        (*front)->prev = NULL;       // d. new front has no predecessor
    }

    free(old_front);                 // e. free the removed node
    return true;                     // e. success
}


/* ------------------------------------------------------------------
 * PEEK at the front value without removing it.
 * ------------------------------------------------------------------ */
bool peek(queue *front, VALUE *val) {
    if (front == NULL) {
        return false;
    }

    *val = front->val;
    return true;
}


/* ------------------------------------------------------------------
 * DESTROY the entire queue.
 *
 * Steps:
 * a. Walk the list one node at a time from the front.
 * b. Save a pointer to the next node before freeing the current one.
 * c. Free the current node.
 * d. Advance and repeat until the list is empty.
 * ------------------------------------------------------------------ */
void destroy(queue *front) {
    queue *cur = front;

    while (cur != NULL) {
        queue *next = cur->next;   // b. save next before freeing
        free(cur);                 // c. free current node
        cur = next;                // d. advance
    }
}


/* -------------------------- helper for demo -------------------------- */
void print_queue(queue *front) {
    queue *cur = front;
    printf("front -> ");
    while (cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
    printf("rear\n");
}


int main(void) {
    /* An empty queue is represented by two NULL pointers */
    queue *front = NULL;
    queue *rear = NULL;

    printf("New queue created (front and rear are NULL).\n");

    /* Enqueue some values */
    enqueue(&front, &rear, 10);
    enqueue(&front, &rear, 20);
    enqueue(&front, &rear, 30);
    printf("\nEnqueued 10, 20, 30:\n");
    print_queue(front);

    VALUE front_val;
    if (peek(front, &front_val)) {
        printf("peek(): %d\n", front_val);   // should be 10 (FIFO)
    }

    /* Dequeue a couple, then enqueue more, to prove front/rear
     * bookkeeping stays correct as the queue changes shape */
    VALUE out;
    dequeue(&front, &rear, &out);
    printf("\ndequeued: %d\n", out);
    print_queue(front);

    enqueue(&front, &rear, 40);
    printf("\nenqueued 40:\n");
    print_queue(front);

    /* Drain the queue completely */
    printf("\nDraining the queue:\n");
    while (dequeue(&front, &rear, &out)) {
        printf("dequeued: %d\n", out);
    }

    if (!dequeue(&front, &rear, &out)) {
        printf("\nQueue is empty, dequeue() correctly failed.\n");
    }

    /* Rebuild it and then destroy it wholesale */
    enqueue(&front, &rear, 100);
    enqueue(&front, &rear, 200);
    enqueue(&front, &rear, 300);
    printf("\nRebuilt queue:\n");
    print_queue(front);

    destroy(front);
    front = NULL;
    rear = NULL;
    printf("\nQueue destroyed. front and rear reset to NULL.\n");

    return 0;
}
```


## Hash Tables


• Hash tables combine the random access ability of an array with the dynamism of a linked list. 
• This means (assuming we define our hash table well): • Insertion can start to tend toward q(1)
• Deletion can start to tend toward q(1) 
• Lookup can start to tend toward q(1) 
• We’re gaining the advantages of both types of data structure, while mitigating the disadvantages.

• To get this performance upgrade, we create a new structure whereby when we insert data into the structure, the data itself gives us a clue about where we will find the data, should we need to later look it up. 

• The trade off is that hash tables are not great at ordering or sorting data, but if we don’t care about that, then we’re good to go!

• A hash table amounts to a combination of two things with which we’re quite familiar. 
• First, a hash function, which returns an nonnegative integer value called a hash code. 
• Second, an array capable of storing data of the type we wish to place into the data structure. 
• The idea is that we run our data through the hash function, and then store the data in the element of the array represented by the returned hash code.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_MAX 10   // number of buckets in the table

typedef int VALUE;

/* Each bucket is a linked list of entries. When two different keys
 * hash to the same bucket index (a "collision"), we just chain them
 * together in that bucket's list instead of overwriting each other. */
typedef struct _entry {
    char *key;
    VALUE val;
    struct _entry *next;
} entry;

/* The table itself: an array of bucket "head" pointers. Each slot
 * either points to NULL (empty bucket) or the first entry in that
 * bucket's chain. */
typedef struct _hashtable {
    entry *buckets[HASH_MAX];
} hashtable;


/* ------------------------------------------------------------------
 * HASH a string into a bucket index.
 *
 * This is a simple additive hash: sum up every character's value,
 * then take it mod HASH_MAX so the result always fits within the
 * bucket array's bounds (0 .. HASH_MAX-1).
 * ------------------------------------------------------------------ */
unsigned int hash(char *str) {
    int sum = 0;
    for (int j = 0; str[j] != '\0'; j++) {
        sum += str[j];
    }
    return sum % HASH_MAX;
}


/* ------------------------------------------------------------------
 * CREATE / initialize a hash table.
 *
 * Every bucket starts out empty (NULL), meaning no entries hash to
 * it yet.
 * ------------------------------------------------------------------ */
void init(hashtable *t) {
    for (int i = 0; i < HASH_MAX; i++) {
        t->buckets[i] = NULL;
    }
}


/* ------------------------------------------------------------------
 * INSERT a key/value pair into the table.
 *
 * Steps:
 * a. Compute which bucket this key belongs in.
 * b. Allocate and check a new entry node.
 * c. Copy the key (so the table owns its own memory for it) and
 *    store the value.
 * d. Insert at the FRONT of that bucket's chain (O(1), and simplest --
 *    order within a bucket doesn't matter for correctness).
 * ------------------------------------------------------------------ */
void insert(hashtable *t, char *key, VALUE val) {
    unsigned int idx = hash(key);           // a. find the bucket

    entry *new = malloc(sizeof(entry));     // b. allocate
    if (new == NULL) {
        printf("Error: out of memory\n");
        exit(1);
    }

    new->key = malloc(strlen(key) + 1);     // c. copy the key string
    strcpy(new->key, key);
    new->val = val;

    new->next = t->buckets[idx];            // d. push to front of chain
    t->buckets[idx] = new;
}


/* ------------------------------------------------------------------
 * FIND a value by key.
 *
 * Steps:
 * a. Compute the bucket this key would be in.
 * b. Walk that bucket's chain comparing keys with strcmp.
 * c. If found, hand the value back through the out-parameter.
 * d. If we reach the end of the chain without a match, report failure.
 * ------------------------------------------------------------------ */
bool find(hashtable *t, char *key, VALUE *val) {
    unsigned int idx = hash(key);           // a. locate the bucket
    entry *cur = t->buckets[idx];

    while (cur != NULL) {                   // b. walk the chain
        if (strcmp(cur->key, key) == 0) {   // c. match found
            *val = cur->val;
            return true;
        }
        cur = cur->next;
    }

    return false;                           // d. not found
}


/* ------------------------------------------------------------------
 * DELETE a key/value pair from the table.
 *
 * Steps:
 * a. Compute the bucket.
 * b. Walk the chain with a "prev" tracking pointer (same pattern as
 *    singly-linked list deletion) until we find a matching key.
 * c. Unlink the entry: either it's the head of the bucket (update
 *    the bucket pointer itself) or it's mid-chain (update prev->next).
 * d. Free the entry's key string and the entry itself.
 * ------------------------------------------------------------------ */
bool delete_key(hashtable *t, char *key) {
    unsigned int idx = hash(key);           // a. locate the bucket
    entry *cur = t->buckets[idx];
    entry *prev = NULL;

    while (cur != NULL) {                   // b. search the chain
        if (strcmp(cur->key, key) == 0) {
            if (prev == NULL) {             // c. deleting the bucket's head
                t->buckets[idx] = cur->next;
            } else {                        // c. deleting mid-chain
                prev->next = cur->next;
            }
            free(cur->key);                 // d. free the key string
            free(cur);                      // d. free the entry
            return true;
        }
        prev = cur;
        cur = cur->next;
    }

    return false;                           // key not found
}


/* ------------------------------------------------------------------
 * DESTROY the entire table: free every entry in every bucket.
 * ------------------------------------------------------------------ */
void destroy(hashtable *t) {
    for (int i = 0; i < HASH_MAX; i++) {
        entry *cur = t->buckets[i];
        while (cur != NULL) {
            entry *next = cur->next;
            free(cur->key);
            free(cur);
            cur = next;
        }
        t->buckets[i] = NULL;
    }
}


/* -------------------------- helper for demo -------------------------- */
void print_table(hashtable *t) {
    for (int i = 0; i < HASH_MAX; i++) {
        printf("bucket[%d]: ", i);
        entry *cur = t->buckets[i];
        while (cur != NULL) {
            printf("(%s, %d) -> ", cur->key, cur->val);
            cur = cur->next;
        }
        printf("NULL\n");
    }
}


int main(void) {
    hashtable t;
    init(&t);

    printf("Empty table:\n");
    print_table(&t);

    /* Insert some key/value pairs */
    insert(&t, "apple", 1);
    insert(&t, "banana", 2);
    insert(&t, "cherry", 3);
    insert(&t, "date", 4);

    printf("\nAfter inserting apple, banana, cherry, date:\n");
    printf("hash(\"apple\") = %u\n", hash("apple"));
    printf("hash(\"banana\") = %u\n", hash("banana"));
    printf("hash(\"cherry\") = %u\n", hash("cherry"));
    printf("hash(\"date\") = %u\n", hash("date"));
    print_table(&t);

    /* Look up some keys */
    VALUE v;
    printf("\nfind(\"banana\"): %s", find(&t, "banana", &v) ? "found, " : "not found\n");
    if (find(&t, "banana", &v)) printf("val = %d\n", v);

    printf("find(\"grape\"): %s\n", find(&t, "grape", &v) ? "found" : "not found");

    /* Delete a key and confirm it's gone */
    delete_key(&t, "banana");
    printf("\nAfter deleting \"banana\":\n");
    print_table(&t);
    printf("find(\"banana\"): %s\n", find(&t, "banana", &v) ? "found" : "not found");

    /* Demonstrate a real collision: "cat", "act", and "tac" all hash
     * to the same bucket, since this hash function just sums
     * character values (order doesn't matter, so anagrams collide) */
    insert(&t, "cat", 100);
    insert(&t, "act", 200);
    insert(&t, "tac", 300);
    printf("\nAfter inserting cat, act, tac (all hash to bucket %u):\n", hash("cat"));
    print_table(&t);

    printf("find(\"act\"): %s, ", find(&t, "act", &v) ? "found" : "not found");
    printf("val = %d\n", v);

    delete_key(&t, "act");
    printf("After deleting \"act\" (middle of the chain):\n");
    print_table(&t);
    printf("find(\"cat\"): %s -- still reachable despite deleting a chain-mate\n",
           find(&t, "cat", &v) ? "found" : "not found");

    /* Clean up */
    destroy(&t);
    printf("\nTable destroyed.\n");
    print_table(&t);

    return 0;
}
```

• A collision occurs when two pieces of data, when run through the hash function, yield the same hash code. 
• Presumably we want to store both pieces of data in the hash table, so we shouldn’t simply overwrite the data that happened to be placed in there first. 
• We need to find a way to get both elements into the hash table while trying to preserve quick insertion and lookup.

• Resolving collisions: Linear probing
• In this method, if we have a collision, we try to place the data in the next consecutive element in the array (wrapping around to the beginning if necessary) until we find a vacancy. 
• That way, if we don’t find what we’re looking for in the first location, at least hopefully the element is somewhere nearby.

• Resolving collisions: Linear probing 
• Linear probing is subject to a problem called clustering. Once there’s a miss, two adjacent cells will contain data, making it more likely in the future that the cluster will grow. 
• Even if we switch to another probing technique, we’re still limited. We can only store as much data as we have locations in our array.

• Resolving collisions: Chaining 
• Let’s start to pull it all together. 
• What if instead of each element of the array holding just one piece of data, it held multiple pieces of data?
• If each element of the array is a pointer to the head of a linked list, then multiple pieces of data can yield the same hash code and we’ll be able to store it all!

• Resolving collisions: Chaining 

• We’ve eliminated clustering.
• We know from experience with linked lists that insertion (and creation, if necessary) into a linked list is an O(1) operation.
• For lookup, we only need to search through what is hopefully a small list, since we’re distributing what would otherwise be one huge list across n lists.


### Tries 

• We have seen a few data structures that handle the mapping of key-value pairs. 

• Arrays: The key is the element index, the value is the data at that location. 

• Hash tables: The key is the hash code of the data, the value is a linked list of data hashing to that hash code. 

• What about a slightly different kind of data structure where the key is guaranteed to be unique, and the value could be as simple as a Boolean that tells you whether the data exists in the structure?

• Tries combine structures and pointers together to store data in an interesting way. 
• The data to be searched for in the trie is now a roadmap. 
• If you can follow the map from beginning to end, the data exists in the trie.
• If you can’t, it doesn’t. 
• Unlike with a hash table, there are no collisions, and no two pieces of data (unless they are identical) have the same path.

• Let’s map key-value pairs where the keys are four-digit years (YYYY) and the values are names of universities founded during those years. 
• In a trie, the paths from a central root node to a leaf node (where the school names would be), would be labeled with digits of the year.
• Each node on the path from root to leaf could have 10 pointers emanating from it, one for each digit.

To insert an element into the trie, simply build the correct path from the root to the leaf.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* A trie (aka "prefix tree") stores keys one character at a time,
 * where each character selects which child pointer to follow next.
 * Here, each node has 10 possible children -- one per digit '0'-'9' --
 * so this trie is meant to be keyed by strings of digits, e.g. a
 * student/campus ID number that maps to a university name.
 *
 * 'university' holds the name associated with the digit-string that
 * leads to this node. An empty string means "no key ends here" --
 * this node might just be a waypoint on the way to a longer key. */
typedef struct _trie {
    char university[20];
    struct _trie *paths[10];
} trie;


/* ------------------------------------------------------------------
 * CREATE a single new trie node.
 *
 * Steps:
 * a. Dynamically allocate space for a new node.
 * b. Check to make sure we didn't run out of memory.
 * c. Initialize 'university' to empty (no key ends here yet).
 * d. Initialize every entry in 'paths' to NULL (no children yet).
 * e. Return a pointer to the newly created node.
 * ------------------------------------------------------------------ */
trie *create(void) {
    trie *new = malloc(sizeof(trie));   // a. allocate

    if (new == NULL) {                   // b. check for out-of-memory
        printf("Error: out of memory\n");
        exit(1);
    }

    new->university[0] = '\0';           // c. empty = "not a terminal node"

    for (int i = 0; i < 10; i++) {       // d. no children yet
        new->paths[i] = NULL;
    }

    return new;                          // e. return the new node
}


/* ------------------------------------------------------------------
 * INSERT a digit-string key with its associated university name.
 *
 * Steps:
 * a. Start a traversal pointer at the root.
 * b. For each character in the key, convert it to a digit index (0-9).
 * c. If the child for that digit doesn't exist yet, create it.
 * d. Move the traversal pointer down into that child.
 * e. After consuming every character, store the university name at
 *    the node we've landed on -- this node now marks the END of a key.
 * ------------------------------------------------------------------ */
void insert(trie *root, char *key, char *university) {
    trie *cur = root;                       // a. start at the root

    for (int i = 0; key[i] != '\0'; i++) {
        int idx = key[i] - '0';             // b. char '0'-'9' -> index 0-9

        if (cur->paths[idx] == NULL) {      // c. create the path if missing
            cur->paths[idx] = create();
        }

        cur = cur->paths[idx];              // d. descend into that child
    }

    strncpy(cur->university, university, sizeof(cur->university) - 1);
    cur->university[sizeof(cur->university) - 1] = '\0';   // e. mark the end
}


/* ------------------------------------------------------------------
 * FIND the university name associated with a digit-string key.
 *
 * Steps:
 * a. Start a traversal pointer at the root.
 * b. For each character in the key, follow the corresponding path.
 * c. If a needed path doesn't exist, the key was never inserted --
 *    report failure immediately.
 * d. After consuming every character, check whether this node is
 *    actually a terminal node (non-empty university) -- we might have
 *    landed on a valid PATH that was only ever a prefix of a longer
 *    key, never inserted as a key itself.
 * e. If terminal, hand back the university name and report success.
 * ------------------------------------------------------------------ */
bool find(trie *root, char *key, char *university_out) {
    trie *cur = root;                       // a. start at the root

    for (int i = 0; key[i] != '\0'; i++) {
        int idx = key[i] - '0';             // b. char -> digit index

        if (cur->paths[idx] == NULL) {      // c. path doesn't exist
            return false;
        }

        cur = cur->paths[idx];
    }

    if (cur->university[0] == '\0') {       // d. reached a node, but it's
        return false;                       //    only a prefix, not a key
    }

    strcpy(university_out, cur->university); // e. success
    return true;
}


/* ------------------------------------------------------------------
 * DESTROY an entire trie.
 *
 * Tries are naturally recursive structures, so destruction is
 * recursive too:
 * a. For each of the 10 possible children, if it exists, recursively
 *    destroy that subtree first.
 * b. Once all children are freed, free this node itself.
 * ------------------------------------------------------------------ */
void destroy(trie *root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < 10; i++) {   // a. destroy every child subtree
        if (root->paths[i] != NULL) {
            destroy(root->paths[i]);
        }
    }

    free(root);                       // b. free this node
}


int main(void) {
    trie *root = create();

    /* Insert a few "ID -> university" mappings */
    insert(root, "123", "Stanford");
    insert(root, "124", "Berkeley");
    insert(root, "1250", "MIT");
    insert(root, "9", "Yale");

    char name[20];

    printf("find(\"123\"): %s\n",
           find(root, "123", name) ? name : "not found");

    printf("find(\"124\"): %s\n",
           find(root, "124", name) ? name : "not found");

    printf("find(\"1250\"): %s\n",
           find(root, "1250", name) ? name : "not found");

    /* "125" was never inserted as a key itself -- only as a PREFIX
     * of "1250" -- so it should correctly report "not found" */
    printf("find(\"125\"): %s\n",
           find(root, "125", name) ? name : "not found (it's only a prefix)");

    /* A key that was never inserted at all */
    printf("find(\"999\"): %s\n",
           find(root, "999", name) ? name : "not found");

    printf("find(\"9\"): %s\n",
           find(root, "9", name) ? name : "not found");

    destroy(root);
    printf("\nTrie destroyed.\n");

    return 0;
}
```

- `insert` walks character-by-character, creating a new child only when a path is missing.
- `find` has to check _two_ separate things at the end: did every step of the path exist (`paths[idx] != NULL`), _and_ is this specific node actually marked as the end of a key (`university[0] != '\0'`)? Missing either check gives you a bug — the first misses keys that were never inserted, the second wrongly accepts prefixes of longer keys as if they were keys themselves.
- `destroy` is naturally recursive, since a trie is a tree of up to 10 children per node rather than a single `next` pointer — you have to free every subtree before freeing the node that owns them.


#### To search for an element in the trie, use successive digits to navigate from the root, and if you can make it to the end without hitting a dead end (a NULL pointer), you’ve found it.

