
## Hexadecimal

- base-10
	0 1 2 3 4 5 6 7 8 9

- base-2
	0  1


- hexadecimal system - base-16
	0 1 2 3 4 5 6 7 8 9 a b c d e f

	Makes this mapping easy because a group of four binary digits (bits) is able has 16 different combinations, and each of those combinations maps to a single hexadecimal digit.

![[Screenshot from 2026-05-04 06-37-44.png]]

To convert a binary number to hexadecimal, group four binary
digits (bits) together from right to left.

• Pad the leftmost group with extra 0 bits at the front if necessary.

01000110101000101011100100111101

0100  0110  1010  0010  1011  1001  0011  1101


# 46A2B93D

0x46A2B93D


## Pointers


• Pointers provide an alternative way to pass data between functions. 
	• Recall that up to this point, we have passed all data by value, with one exception. 
	• When we pass data by value, we only pass a copy of that data.

• If we use pointers instead, we have the power to pass the actual variable itself. 
	• That means that a change that is made in one function can impact what happens in a different function. 
	• Previously, this wasn’t possible!


Every file on your computer lives on your disk drive, be it a hard disk drive (HDD) or a solid-state drive (SSD). Disk drives are just storage space; we can’t directly work there. Manipulation and use of data can only take place in RAM, so we have to move data there.

Memory is basically a huge array of 8-bit wide bytes. • 512 MB, 1GB, 2GB, 4GB…

![[Screenshot from 2026-05-04 06-53-42.png]]

• Back to this idea of memory as a big array of byte-sized cells.

• Recall from our discussion of arrays that they not only are useful for storage of information but also for so-called random access. 
	• We can access individual elements of the array by indicating which index location we want. 
	
• Similarly, each location in memory has an address

![[Screenshot from 2026-05-04 06-55-57.png]]


![[Screenshot from 2026-05-04 06-57-03.png]]

![[Screenshot from 2026-05-04 07-10-14.png]]![[Screenshot from 2026-05-04 07-10-30.png]]![[Screenshot from 2026-05-04 07-10-59.png]]
![[Screenshot from 2026-05-04 07-11-21.png]]![[Screenshot from 2026-05-04 07-11-35.png]]![[Screenshot from 2026-05-04 07-12-08.png]]
There’s only one critical thing to remember as we start working with pointers: 


					POINTERS ARE JUST ADDRESSES


[Animated explanation](memory_layout_interactive.html)

**Image 1** — An empty block of RAM, 19 bytes wide, all uninitialized.

**Image 2** — Declaring `char c = 'H'` places the character at address 4, taking up exactly 1 byte (shown in amber). Then `int speedlimit = 65` occupies 4 bytes at addresses 8–11 (shown in green), because an `int` is 32 bits wide.

**Images 3 & 4** — Zooming into the binary representation. `'H'` is ASCII 72 = `01001000`. The integer 65 = `00000000 00000000 00000000 01000001`, spread across 4 bytes.

**Images 5–7** — Adding `string surname = "Lloyd"` places 6 bytes starting at address 12: one byte per character (`L`, `l`, `o`, `y`, `d`) plus a null terminator `\0` that signals the string's end.

**Image 8** — The addresses switch from decimal (0, 1, 2…)
to hexadecimal (0x0, 0x1, 0x2…), 
which is how programmers usually read memory dumps.

![[Screenshot from 2026-05-04 07-21-03.png]]
![[Screenshot from 2026-05-04 07-21-25.png]]
![[Screenshot from 2026-05-04 07-22-27.png]]![[Screenshot from 2026-05-04 07-22-41.png]]

A pointer, then, is a data item whose
	• value is a memory address
	• type describes the data located at that memory address

As such, pointers allow data structures and/or variables to be shared among functions.

• The simplest pointer available to us in C is the NULL pointer.
	• As you might expect, this pointer points to nothing (a fact which can actually come in handy!)
	• When you create a pointer and you don’t set its value immediately, you should always set the value of the pointer to NULL.
	
• You can check whether a pointer is NULL using the equality
operator (==). 

• Another easy way to create a pointer is to simply extract the address of an already existing
variable. We can do this with the address extraction operator (&).

• If x is an int-type variable, then &x is a pointer-to-int whose
value is the address of x.

• If arr is an array of doubles, then &arr[i] is a pointer-to- double who value is the address of the ith element of arr.

• An array’s name, then, is actually just a pointer to its first element –
you’ve been working with pointers all along!

• The main purpose of a pointer is to allow us to modify or inspect the location to which it points.
• We do this by dereferencing the pointer.
• If we have a pointer-to-char called pc, then *pc is the data that lives at the memory address stored inside the variable pc.

• Used in this context, * is known as the dereference operator.
• It “goes to the reference” and accesses the data at that memory location, allowing you to manipulate it at will.

• Can you guess what might happen if we try to dereference a pointer whose value is NULL?
					Segmentation fault
					
• Surprisingly, this is actually good behaviour! It defends against accidental dangerous manipulation of unknown pointers.

• That’s why we recommend you set your pointers to NULL immediately if you aren’t setting them to a known, desired value.

![[Screenshot from 2026-05-04 07-35-07.png]]

One more annoying thing with those *s. They’re an important part of both the type name and the variable name.

• Best illustrated with an example.
### int* px, py, pz;

![[Screenshot from 2026-05-04 07-36-35.png]]

Best to declare individual pointers, 
![[Screenshot from 2026-05-04 07-37-42.png]]

In C you don't get strings, - strings are referred to as pointer char * ![[Screenshot from 2026-05-04 07-38-31.png]]
![[Screenshot from 2026-05-04 07-40-03.png]]
