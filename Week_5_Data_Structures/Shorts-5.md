
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