#include <stdio.h>
#include <string.h>
#include "hwlib.h"

// Step 1
// =================> TODO: Define a Sensor struct with int id, char label[10], float reading
struct Sensor {
    int id;
    char label[10];
    float reading;
};
void run_sensor_structs() {
    // Step 1 Continued
    // =================> TODO: Declare a Sensor instance and set its fields
    struct Sensor sensor = {1, "TEMP", 25.6};
    // =================> TODO: Print its values
    printf("Sensor ID: %d, Label: %s, Reading: %.1f\n", sensor.id, sensor.label, sensor.reading);
    // Step 2
    // =================> TODO: Declare a Sensor pointer pointing to the struct from Step 1
    struct Sensor* sensor_ptr = &sensor;
    // =================> TODO: Use the pointer to modify reading and print again
    sensor_ptr->reading = 42.9;
    printf("Updated reading via pointer: %.1f\n\n\n", sensor_ptr->reading);
    // Step 3
    // =================> TODO: Allocate memory for 3 Sensor structs
    struct Sensor* sensors = (struct Sensor*) malloc(3 * sizeof(struct Sensor));
    printf("Allocated %d sensors...\n", 3);
    // Variable used for pointer arithmetic inside loop in order to keep sensors address fixed so it can be freed at the end.
    struct Sensor* sensors_incr = sensors;
    // =================> TODO: Fill in ids, labels (T0, T1, T2), and readings
    for (int i = 0; i < 3; i++) {
        sensors_incr->id = 100 + i;
        snprintf(sensors_incr->label, sizeof(sensors_incr->label), "T%d", i);
        sensors_incr->reading = 20.1 + 1.4*i;
        printf("Sensor %d - ID: %d, Label: %s, Reading: %.1f\n", i, sensors_incr->id, sensors_incr->label, sensors_incr->reading);
        sensors_incr++;
    }
    // =================> TODO: Print all sensor info using pointer
    // Done above.
    // =================> TODO: Free memory
    free(sensors);
}
