// Filename: pointer_basics.c
// Author: Stephen Ottaway
// Date: 7/2/2026
// Description: This file continues the introduction to pointers by creating arrays and printing the elements out (understanding that arrays are laid out continuously in memory with elements at adjacent memory addresses)
// and implementing a my_memcpy function that copies a specified number of raw bytes from a source buffer to a destination buffer just using pointer dereferencing and pointer arithmetic.

#include <stdio.h>
#include <string.h>
#include "hwlib.h"


void my_memcpy(void* dest, const void* src, size_t size) {
    const uint8_t* src_add = (const uint8_t*)src;
    uint8_t* dest_add = (uint8_t*)dest;
    for (size_t i = 0; i < size; i++) {
        *dest_add = *src_add;
        src_add++;
        dest_add++;
    }
}

void run_pointer_basics() {
    int arr[5] = {10, 20, 30, 40, 50};
    char text[5] = {'A', 'B', 'C', 'D', 'E'};
    printf("Integer array:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d, address: %p\n", i, arr[i], (void*)&arr[i]);
    }
    printf("\n\nChar array:\n");
    for (int i = 0; i < 5; i++) {
        printf("text[%d] = %c, address: %p\n", i, text[i], (void*)&text[i]);
    }
    const char src[20] = "hello world";
    char dest[20];
    my_memcpy(dest, src, (size_t)20);
    printf("\n\nCopied string: %s\n", dest);
}
