// Filename: array_ops.c
// Author: Stephen Ottaway
// Date: 7/13/2026
// Description: This file reinforces how to use arrays and pointers for memory access in C by implementing several functions that operate on arrays.

// ============ Includes ============
#include <stdio.h>
#include "hwlib.h"

// ============= Macros =============

// ======== Global Variables ========

// ====== Function Prototypes =======
int sum_array(const int* arr, int size);
int find_max(const int* arr, int size);
int filter_positive(const int* in, int* out, int size);
int find_max_offset(const int* arr, int size, int offset);

// Name: sum_array
// Description: Returns the sum of the size elements stored in the array arr.
int sum_array(const int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Name: find_max
// Description: Returns the element with the largest value (not necessarily unique) from the size elements stored in the array arr.
int find_max(const int* arr, int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Name: filter_positive
// Description: Copies the positive subset of elements from the size elements stored in the input array in to the output array out.
int filter_positive(const int* in, int* out, int size) {
    int out_index = 0;
    for (int i = 0; i < size; i++) {
        if (in[i] > 0) {
            out[out_index] = in[i];
            out_index++;
        }
    }
    return out_index; // After loop has run out_index gives the length of the output array out.
}

// Name: find_max_offset
// Description: Returns the maximum value along every offset-th element (from offset parameter) in the array arr with size elements, starting from index 0.
int find_max_offset(const int* arr, int size, int offset) {
    int max_with_offset = 0;
    for (int i = 0; i < size; i += offset) {
        if (*(arr + i) > max_with_offset) {
            max_with_offset = *(arr + i);
        }
    }
    return max_with_offset;
}


void run_array_ops() {
    const int arr[] = {1, -2, 3, -4, 5, -6};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
    int sum = sum_array(arr, size);
    printf("Sum = %d\n", sum);
    int max = find_max(arr, size);
    printf("Max = %d\n", max);
    int out[size];
    int out_size = filter_positive(arr, out, size);
    printf("Filtered positives (%d): ", out_size);
    for (int i = 0; i < out_size; i++) {
        printf("%d ", *(out + i));
    }
    printf("\n");
    int offset = 2;
    int max_with_offset = find_max_offset(arr, size, offset);
    printf("Max with offset %d: %d\n", offset, max_with_offset);
}
