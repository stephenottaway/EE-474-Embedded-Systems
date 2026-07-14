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
A 2D array is laid out in memory row-by-row (e.g. row major order). Therefore, the linear/flattened address of a given element is i * cols + j 
where i * cols gives the row offset and j gives the desired column in that specific row.
- Why might you flatten a 2D array in embedded code?
Flattening a 2D array makes the code/array data structure simpler to understand (only one index variable to track/only one pointer to dereference)
and more efficient for reading from or writing to the array due to only one pass needed for the for loop (compared to two for a 2D non-flattened array).
- What’s the difference between matrix[i][j] and *(&matrix[0][0] + i * cols + j)?
The former uses standard indexing and is how a 2D non-flattened array would be written to or read from in a nested for loop, while the latter uses
a dereferenced flattened pointer to access a flattened 1D/linear array, which can be written to or read from in just a single loop.

Part III:
- What’s the purpose of the head and tail indices?
- Why do we leave one slot empty in a circular buffer?
- What is the benefit of using modulo arithmetic?
