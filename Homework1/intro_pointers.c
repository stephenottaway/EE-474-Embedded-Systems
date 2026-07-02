// Filename: intro_pointers.c
// Author: Stephen Ottaway
// Date: 7/2/2026
// Description: This file introduces the concept of pointers, using them to modify variables values at a certain address in various ways and then printing the result.

#include <stdio.h>
#include <string.h>
#include "hwlib.h"

void run_intro_pointers() {
    int a = 42;
    int* p = &a;
    *p = 100;
    printf("a = %d, *p = %d\n", a, *p);
    printf("Address of a: %p\n", (void*)p);
    int* q = p;
    *q = 77;
    printf("a = %d, *p = %d, *q = %d\n", a, *p, *q);
    int b = 200;
    printf("Original b = %d\n", b);
    p = &b;
    *p = 999;
    printf("New b = %d, and a = %d\n", b, a);
}
