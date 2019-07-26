#include "ir_sensors.h"

#include <xc.h>
#include "system.h"
#include "adc.h"

#include "leds.h"

static int ambient_ir[8];  // Ambient IR light measurement
static int ambient_and_reflected_ir[8]; // IR light when IR LEDs are on
static int reflected_ir[8]; // Variation of IR light

void __attribute__((interrupt, auto_psv))
_T1Interrupt(void)
{    
    // Read ambient IR light and switch on LEDs in first phase
    // Wait 350 us to allow the phototransistor time to react
    // Read reflected IR light and switch off the LEDs in second phase
    // Wait 3 ms before stating again
    // Repeat these two steps for the four pairs of IR sensors

    static int ir_phase = 0;  // Phase can be 0 (ambient) or 1 (reflected)	
    static int ir_number = 0; // Number goes from 0 to 3 (4 pairs of sensors)	

    IFS0bits.T1IF = 0; // Clear Timer1 interrupt flag

    // TODO: Use inline function instead?
    switch(ir_number)
    {
        case 0: // IR sensors 0 and 4
        {
            if(ir_phase == 0)
            {
                PR1 = (350.0 * MICROSECOND) / 8.0; // Next interrupt in 350 us
                ambient_ir[0] = adc_read(IR0);
                ambient_ir[4] = adc_read(IR4);
                PULSE_IR0 = 1; // Turn IR LEDs on for next measurement
                ir_phase = 1;  // Next phase
            }
            else
            {
                PR1 = (2100.0 * MICROSECOND) / 8.0; // Next interrupt in 3 ms
                ambient_and_reflected_ir[0] = adc_read(IR0);
                ambient_and_reflected_ir[4] = adc_read(IR4);
                reflected_ir[0] = ambient_ir[0] - ambient_and_reflected_ir[0];
                reflected_ir[4] = ambient_ir[4] - ambient_and_reflected_ir[4];
                PULSE_IR0 = 0; // Turn IR LEDs off
                ir_phase = 0;  // Reset phase
                ir_number = 1; // Next two sensors
            }
            break;
        }
        case 1: // IR sensors 1 and 5
        {
            if(ir_phase == 0)
            {
                PR1 = (350.0 * MICROSECOND) / 8.0; // Next interrupt in 350 us
                ambient_ir[1] = adc_read(IR1);
                ambient_ir[5] = adc_read(IR5);
                PULSE_IR1 = 1; // Turn IR LEDs on for next measurement
                ir_phase = 1;  // Next phase
            }
            else
            {
                PR1 = (2100.0 * MICROSECOND) / 8.0;  // Next interrupt in 3 ms
                ambient_and_reflected_ir[1] = adc_read(IR1);
                ambient_and_reflected_ir[5] = adc_read(IR5);
                reflected_ir[1] = ambient_ir[1] - ambient_and_reflected_ir[1];
                reflected_ir[5] = ambient_ir[5] - ambient_and_reflected_ir[5];
                PULSE_IR1 = 0; // Turn IR LEDs off
                ir_phase = 0;  // Reset phase
                ir_number = 2; // Next two sensors
            }
            break;
        }
        case 2: // IR sensors 2 and 6
        {
            if(ir_phase == 0)
            {
                PR1 = (350.0 * MICROSECOND) / 8.0; // Next interrupt in 350 us
                ambient_ir[2] = adc_read(IR2);
                ambient_ir[6] = adc_read(IR6);
                PULSE_IR2 = 1; // Turn IR LEDs on for next measurement
                ir_phase = 1;  // Next phase
            }
            else
            {
                PR1 = (2100.0 * MICROSECOND) / 8.0; // Next interrupt in 3 ms
                ambient_and_reflected_ir[2] = adc_read(IR2);
                ambient_and_reflected_ir[6] = adc_read(IR6);
                reflected_ir[2] = ambient_ir[2] - ambient_and_reflected_ir[2];
                reflected_ir[6] = ambient_ir[6] - ambient_and_reflected_ir[6];
                PULSE_IR2 = 0; // Turn IR LEDs off
                ir_phase = 0;  // Reset phase
                ir_number = 3; // Next sensor
            }
            break;
        }
        case 3: // IR sensors 3 and 7
        {
            if(ir_phase == 0)
            {
                PR1 = (350.0 * MICROSECOND) / 8.0; // Next interrupt in 350 us
                ambient_ir[3] = adc_read(IR3);
                ambient_ir[7] = adc_read(IR7);
                PULSE_IR3 = 1; // Turn IR LEDs on for next measurement
                ir_phase = 1;  // Next phase
            }
            else
            {
                PR1 = (2100.0 * MICROSECOND) / 8.0; // Next interrupt in 3 ms
                ambient_and_reflected_ir[3] = adc_read(IR3);
                ambient_and_reflected_ir[7] = adc_read(IR7);
                reflected_ir[3] = ambient_ir[3] - ambient_and_reflected_ir[3];
                reflected_ir[7] = ambient_ir[7] - ambient_and_reflected_ir[7];
                PULSE_IR3 = 0; // Turn IR LEDs off
                ir_phase = 0;  // Reset phase
                ir_number = 0; // Next sensor (back to start)
            }
            break;
        }
    }
}


void ir_sensors_init()
{
    T1CON = 0; // Clear the Timer1 control register
    T1CONbits.TCKPS = 1; // Timer Input Clock Prescale Select bit set to 1:8 prescale value
    TMR1 = 0; // Clear Timer1
    PR1 = (350.0 * MICROSECOND) / 8.0; // Set Timer1 period register such that the first interrupt occurs after 350 us with a 1:8 prescaler
    IFS0bits.T1IF = 0; // Clear Timer1 interrupt flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupts
    T1CONbits.TON = 1; // Start Timer1
}

void ir_sensors_stop()
{
	 T1CONbits.TON = 0; // Disable Timer1
	 PULSE_IR0 = PULSE_IR1 = PULSE_IR2 = PULSE_IR3 = 0; // Turn off IR LEDs
}

int ir_sensors_get_ambient(unsigned int sensor_number)
{
	if(sensor_number > 7)
        return 0;
	else
        return ambient_ir[sensor_number];
}

// To estimate the proximity of an obstacle, we do the following:
// 1. Measure the ambient IR light
// 2. Turn on the IR LED of the sensor
// 3. Measure the reflected IR light + ambient IR light
// 4. Calculate: reflected IR light = (reflected IR light + ambient IR light) - ambient IR light
// 5. Turn off the IR LED of the sensor
// The resulting value will be greater, the nearer an obstacle is
int ir_sensors_get_reflected(unsigned int sensor_number)
{
    if(sensor_number > 7)
        return 0;
	else
        return reflected_ir[sensor_number];
}