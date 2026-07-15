// Filename: sensor_buffer.c
// Author: Stephen Ottaway
// Date: 7/14/2026
// Description: This file implements a circular/ring buffer with a SensorBuffer struct and a number of different helper functions that operate on it.

// ============ Includes ============
#include <stdio.h>
#include <stdbool.h>
#include "hwlib.h"

// ============= Macros =============
#define BUFFER_SIZE 5
// ======== Global Variables ========

typedef struct {
    float buffer[BUFFER_SIZE];
    int head;
    int tail;
} SensorBuffer;

// ====== Function Prototypes =======
void init_buffer(SensorBuffer* buf);
bool is_empty(SensorBuffer* buf);
bool is_full(SensorBuffer* buf);
bool push(SensorBuffer* buf, float value); // returns false if full
bool pop(SensorBuffer* buf, float* out); // returns false if empty
void print_buffer(SensorBuffer* buf);

// Name: init_buffer
// Description: Sets head and tail to 0 and zeros out the buffer.
void init_buffer(SensorBuffer* buf) {
    buf->head = 0;
    buf->tail = 0;
    for (int i = 0; i < BUFFER_SIZE-1; i++) {
        buf->buffer[i] = 0;
    }
}

// Name: is_empty
// Description: Checks if the buffer is empty (head index/pointer == tail index/pointer) and if so returns true.
bool is_empty(SensorBuffer* buf) {
    return (buf->head == buf->tail) && (buf->head == 0);
}

// Name: is_full
// Description: Checks if the buffer is full and if so returns true.
bool is_full(SensorBuffer* buf) {
    return buf->head == BUFFER_SIZE - 1 && buf->tail == 0;
}

// Name: push
// Description: Writes the element value into the buffer at the head index as long at the buffer is not full, then updates the head index.
bool push(SensorBuffer* buf, float value) {
    if (is_full(buf)) {
        printf("Buffer full, could not push %.1f\n", value);
        return false;
    }
    if ((buf->head + 1) % BUFFER_SIZE == 0) {
        buf->head = 0;
    }      
    buf->buffer[buf->head] = value;
    buf->head += 1;
    printf("Pushed %.1f\n", value);
    return true;
}

// Name: pop
// Description: Reads the buffer element at the tail index into the out address as long as the buffer is not empty, then updates the tail index.
bool pop(SensorBuffer* buf, float* out) {
    if (is_empty(buf)) {
        printf("Buffer empty, can not read.\n");
        return false;
    }
    if ((buf->tail + 1) % BUFFER_SIZE == 0) {
        buf->tail = 0;
        if (is_empty(buf)) {
            return false;
        }
    }
    *out = buf->buffer[buf->tail];
    buf->tail += 1;
    printf("Popped %.1f\n", *out);
    return true;
}

void print_buffer(SensorBuffer* buf) {
    printf("Buffer contents: ");
    if (!is_empty(buf)) {    
        if (buf->head > buf->tail) {
            for (int i = buf->tail; i < buf->head; i++) {
                printf("%.1f ", buf->buffer[i]);
            }
        } else {
            for (int i = buf->tail; i < BUFFER_SIZE-1; i++) {
                printf("%.1f ", buf->buffer[i]);
            }
            for (int j = 0; j < buf->head; j++) {
                printf("%.1f ", buf->buffer[j]);
            }
        }
    }
    printf("\n");
}

void run_sensor_buffer() {
    SensorBuffer sb;
    SensorBuffer* buf = &sb;
    init_buffer(buf);
    push(buf, 1.0);
    push(buf, 2.0);
    push(buf, 3.0);
    push(buf, 4.0);
    push(buf, 5.0);
    print_buffer(buf);
    float pop_1 = 0;
    float* pop_1_ptr = &pop_1;
    pop(buf, pop_1_ptr);
    float pop_2 = 0;
    float* pop_2_ptr = &pop_2;
    pop(buf, pop_2_ptr);
    push(buf, 5.0);
    push(buf, 6.0);
    print_buffer(buf);
}
