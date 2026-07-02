// Filename: sensor_structs.c
// Author: Stephen Ottaway
// Date: 7/2/2026
// Description: This file introduces the concept  of structs (which arrays and pointers are a prerequisite to be able to understand), as well as the idea of dynamic memory allocation.  This is done by first creating
// a single struct on the stack (static memory) and reassigning the field values using the arrow pointer dereferencing syntax, and then creating multiple structs stored on the heap using malloc() (dynamic memory allocation),
// assigning the fields values, and then freeing the memory used to store the structs once done.  

#include <stdio.h>
#include <string.h>
#include "hwlib.h"

struct Sensor {
    int id;
    char label[10];
    float reading;
};
void run_sensor_structs() {
    struct Sensor sensor = {1, "TEMP", 25.6};
    printf("Sensor ID: %d, Label: %s, Reading: %.1f\n", sensor.id, sensor.label, sensor.reading);
    struct Sensor* sensor_ptr = &sensor;
    sensor_ptr->reading = 42.9;
    printf("Updated reading via pointer: %.1f\n\n\n", sensor_ptr->reading);
    struct Sensor* sensors = (struct Sensor*) malloc(3 * sizeof(struct Sensor));
    printf("Allocated %d sensors...\n", 3);
    struct Sensor* sensors_incr = sensors; // Variable used for pointer arithmetic inside loop in order to keep sensors address fixed so it can be freed at the end.
    for (int i = 0; i < 3; i++) {
        sensors_incr->id = 100 + i;
        snprintf(sensors_incr->label, sizeof(sensors_incr->label), "T%d", i);
        sensors_incr->reading = 20.1 + 1.4*i;
        printf("Sensor %d - ID: %d, Label: %s, Reading: %.1f\n", i, sensors_incr->id, sensors_incr->label, sensors_incr->reading);
        sensors_incr++;
    }
    free(sensors);
}
