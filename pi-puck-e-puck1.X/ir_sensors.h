#ifndef IR_SENSORS_H
#define	IR_SENSORS_H

// ADC channels for IR sensors
// IR0 is the front-right sensor, and the rest are numbered clockwise
#define IR0 8
#define IR1 9
#define IR2 10
#define IR3 11
#define IR4 12
#define IR5 13
#define IR6 14
#define IR7 15

// Pulse IR emitter pairs
#define PULSE_IR0 _LATF7 // Emitters 0 and 4
#define PULSE_IR1 _LATF8 // Emitters 1 and 5
#define PULSE_IR2 _LATG0 // Emitters 2 and 6
#define PULSE_IR3 _LATG1 // Emitters 3 and 7

void ir_sensors_init();
int ir_sensors_get_ambient(unsigned int sensor_number);
int ir_sensors_get_reflected(unsigned int sensor_number);

#endif