README.txt - HW1: Pointers and Embedded Thinking

Name:  Stephen Ottaway
Date:  6/28/2026

---

General Instructions:

- This file is required as part of your submission.
- Fill in the answers to the questions for each part.
- Use this document to also describe your code and paste output.
- Be clear and concise.

---

Part I: C Basics – Variables and Pointers

1. What is the difference between a pointer and a variable?  
Answer: A variable stores a value in memory while a pointer stores the address where a variable is located in memory (which when dereferenced gives the variables value).

2. What happens when two pointers point to the same variable?  
Answer: The variables value can be read and modified by either pointer, and if modified the change is reflected in the value printed upon dereferencing either pointer.

3. What is the benefit of accessing values through pointers?  
Answer: A pointer to a global variable can be passed to any function and have it's value modified inside the function by simply dereferencing the pointer without having to return it's updated value from the function (unlike what would be needed if the variable was passed by value to that function).

4. Copy your Serial Monitor output from Part I below:  
=================== PART I ======================
a = 100, *p = 100
Address of a: 0x3fca044c
a = 77, *p = 77, *q = 77
Original b = 200
New b = 999, and a = 77
---

Part II: Memory and Arrays

1. How are elements in an array laid out in memory? How do they differ between types (e.g., char vs int)?  
Answer: The elements in an array are laid out contiguously in memory right next to each other. Their addresses differ by the amount of storage the type takes up (e.g. two chars (one byte) could be at addresses 0xFFF0 and 0xFFF1 while two ints (4 bytes) could be at addresses 0xFFF4 and 0xFFF8).

2. How does your my_memcpy() function work under the hood?  
Answer: after storing and casting the void* src and dest pointer to uint8_t* ptrs, inside the loop the data (byte) at the src address is dereferenced and stored at the dest address, then the src and dest addresses are both incremented by one byte using pointer arithmetic. This process is repeated size (the other function parameter) times until each byte of data in the size src addresses are transferred to the corresponding dest addresses.

3. What situations in embedded systems might require memory-level copying?  
Answer: Raw sensor readings may be copied into a different buffer in order to decode the readings and subsequently drive other actuators/functions in the system so that the raw sensor readings themselves don't need to be overwritten. 

4. Copy your Serial Monitor output from Part II below:  
=================== PART II =====================
Integer array:
arr[0] = 10, address: 0x3fca0410
arr[1] = 20, address: 0x3fca0414
arr[2] = 30, address: 0x3fca0418
arr[3] = 40, address: 0x3fca041c
arr[4] = 50, address: 0x3fca0420


Char array:
text[0] = A, address: 0x3fca040b
text[1] = B, address: 0x3fca040c
text[2] = C, address: 0x3fca040d
text[3] = D, address: 0x3fca040e
text[4] = E, address: 0x3fca040f


Copied string: hello world
---

Part III: Structs and Simulated Sensor Records

1. What is a pointer to a struct, and how is it used?  
Answer: A pointer to a struct is the address where the struct is stored in memory (it's first byte, similar to an array).  It is used to read or modify the fields of the struct (using the -> operator and the member name) and for passing a struct by reference to functions.

2. How does dynamic memory allocation work in C?  
Answer: Some integer number of chunks of memory (structs, pointers, arrays, etc.) are temporarily allocated on the heap when malloc() is called with an integer and type passed in as arguments, and a pointer to the start of that chunk of memory is returned. This chunk of memory should be freed from the heap when it is no longer needed, which is done by calling free() with the pointer to the start of the memory chunk passed in as it's only argument.

3. Why is dynamic allocation useful in embedded systems?  
Answer: Dynamic allocation is more flexible than static allocation (e.g. an array) because the memory is allocated at run-time rather than compile time. This is useful in embedded systems for example in the situation where a sensor needs to be read for an unknown time interval in order to collect enough data to trigger some sort of action elsewhere in the system, and that time interval uncertainty would correspond to different sizes of buffers required to handle the amount of data, which could be accounted for using malloc().  

4. Copy your Serial Monitor output from Part III below:  
=================== PART III ====================
Sensor ID: 1, Label: TEMP, Reading: 25.6
Updated reading via pointer: 42.9


Allocated 3 sensors...
Sensor 0 - ID: 100, Label: T0, Reading: 20.1
Sensor 1 - ID: 101, Label: T1, Reading: 21.5
Sensor 2 - ID: 102, Label: T2, Reading: 22.9
---

Anything else you'd like us to know? (bugs, challenges, feedback, etc.):  
(Optional)
N/A
