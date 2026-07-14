Name: Stephen Ottaway
Date: 7/13/2026
README - Homework 2 Answers

Part I:
- Why use pointer arithmetic instead of array indexing in some cases?
Pointer arithmetic works more universally than array indexing (for example with malloc()) and it helps build the intuition/picture
of arrays being contiguous blocks of memory with the elements addresses being separated by the size of the arrays data type.
- How do you return multiple values from a function in C?
By passing into the function by reference a pointer to some array/data structure containing multiple elements/values and then dereferencing
that pointer/address inside of the function to modify those values (which due to the pass by reference remain modified even after the function returns).
- What challenges arise when skipping elements with pointer arithmetic?
The syntax is a bit less intuitive than the array indexing syntax, and additionally care must be taken to ensure the pointer arithmetic is being incremented
by the desired amount, which changes depending on the type the pointer is pointing to (e.g. addr + 1 when addr is a uint8_t pointer adds 1 byte to addr while
addr + 1 when addr is a uint32_t pointer adds 4 bytes to addr).

Part II:
- How is a 2D array laid out in memory?
- Why might you flatten a 2D array in embedded code?
- What’s the difference between matrix[i][j] and *(&matrix[0][0] + i * cols + j)?

Part III:
- What’s the purpose of the head and tail indices?
- Why do we leave one slot empty in a circular buffer?
- What is the benefit of using modulo arithmetic?
