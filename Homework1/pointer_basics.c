#include <stdio.h>
#include <string.h>
#include "hwlib.h"


void my_memcpy(void* dest, const void* src, size_t size) {
    // =================> TODO: Implement byte-by-byte memory copy using uint8_t*
    const uint8_t* src_add = (const uint8_t*)src;
    uint8_t* dest_add = (uint8_t*)dest;
    for (size_t i = 0; i < size; i++) {
        *dest_add = *src_add;
        src_add++;
        dest_add++;
    }
}

void run_pointer_basics() {

    // Step 1
    // =================> TODO: Declare and initialize an int[5] array
    int arr[5] = {10, 20, 30, 40, 50};
    // =================> TODO: Declare and initialize a char[5] array
    char text[5] = {'A', 'B', 'C', 'D', 'E'};
    // =================> TODO: Print value and address of each element using a for loop
    printf("Integer array:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d, address: %p\n", i, arr[i], (void*)&arr[i]);
    }
    printf("\n\nChar array:\n");
    for (int i = 0; i < 5; i++) {
        printf("text[%d] = %c, address: %p\n", i, text[i], (void*)&text[i]);
    }
    // Step 2
    // =================> TODO: Declare source string and destination buffer
    const char src[20] = "hello world";
    char dest[20];
    // =================> TODO: Use my_memcpy() to copy string
    my_memcpy(dest, src, (size_t)20);
    // =================> TODO: Print copied string
    printf("\n\nCopied string: %s\n", dest);
}
