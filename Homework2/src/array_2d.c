// Filename: array_2d.c
// Author: Stephen Ottaway
// Date: 7/14/2026
// Description: This file works with 2D arrays to help build intuition for memory layout in C and understand multiple memory accesses with pointers.

// ============ Includes ============
#include <stdio.h>
#include "hwlib.h"

// ============= Macros =============

// ======== Global Variables ========

// ====== Function Prototypes =======
void zero_2d(int* data, int rows, int cols);

// Name: zero_2d
// Description: Zeros out a 2D array passed as a flattened pointer.
void zero_2d(int* data, int rows, int cols) {
    int flattened_size = rows*cols;
    for (int i = 0; i < flattened_size; i++) {
        *(data + i) = 0;
    }
}

void run_array_2d() {
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("Printing using standard indexing:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("matrix[%d][%d] = %d at %x\n", i, j, matrix[i][j], (*(matrix + i) + j));
        }
    }
    printf("Printing using flattened pointer:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("matrix[%d][%d] = %d at %x\n", i, j, *(*(matrix + i) + j), (*(matrix + i) + j));
        }
    }
    zero_2d((int*) matrix, 2, 3);
    printf("Zeroed matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
