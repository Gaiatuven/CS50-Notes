

What are the key trade-offs between data structures we should consider in decisions about which to use? 

● What are some of the primary operations we should know how to do on a linked list? 

● How can we build our very own hash table?

## Choosing Data Structures

Imagine you work for a company that has created a digital assistant running on a mobile device.

Customer reports indicate people have trouble activating the assistant with its "wake word."

Customer reports indicate people have trouble activating the assistant with its "wake word."

What data structure would you propose the team build to store these words?

Deletion 
Insertion 
Search![[Screenshot from 2026-07-10 07-00-06.png]]

![[Screenshot from 2026-07-10 07-00-56.png]]![[Screenshot from 2026-07-10 07-01-22.png]]![[Screenshot from 2026-07-10 07-01-47.png]]

### Creating a Linked List

```c
typedef struct node 
{ 
	string phrase; 
	struct node *next; 
} 
node ;

node *list = NULL;
node *n = malloc(sizeof(node));
n->phrase = "Hi!";
n->next = NULL;

```