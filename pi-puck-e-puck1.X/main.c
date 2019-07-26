#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "system.h"
#include <libpic30.h>

#include "adc.h"
#include "leds.h"
#include "uart2.h"
#include "i2c_slave.h"
#include "motors.h"
#include "ir_sensors.h"

int16_t main(void)
{
    int i;
    for (i = 0; i < 256; i++) {
        i2c_data[i].u = 0;
    }
    
    uart2_init();
    adc_init();
    i2c_slave_init();
    leds_init();
    motors_init();
    ir_sensors_init();
    
    printf("I am an e-puck.\n");
    
    uint8_t leds_outer = 0;
    uint8_t leds_front_body = 0;
    leds_set_outer(leds_outer);
    leds_set_front_body(leds_front_body);
    
    int16_t motor_left = 0;
    int16_t motor_right = 0;
    motors_set_speed_left(motor_left);
    motors_set_speed_right(motor_right);
    
//    printf("Starting main loop...\n");

    while (1) {
        if (leds_outer != i2c_data[0].u_low) {
            // Valid values are 0x00 to 0xFF
            i2c_data[0].u_high = 0;
            leds_outer = i2c_data[0].u_low;
            leds_set_outer(leds_outer);
//            printf("Set LEDs to 0x%02x\n", leds_outer);
        }
        if (leds_front_body != i2c_data[1].u_low) {
            // Valid values are 0x0000 to 0x0003
            i2c_data[1].u &= 0x0003;
            leds_front_body = i2c_data[1].u_low;
            leds_set_front_body(leds_front_body);
//            printf("Set front/body LEDs to 0x%02x\n", leds_front_body);
        }
        if (motor_left != i2c_data[2].s) {
            // Valid values are -1000 to 1000
            if (i2c_data[2].s > 1000)
                i2c_data[2].s = 1000;
            else if (i2c_data[2].s < -1000)
                i2c_data[2].s = -1000;
            motor_left = i2c_data[2].s;
            motors_set_speed_left(motor_left);
//            printf("Set left motor to %d\n", motor_left);
        }
        if (motor_right != i2c_data[3].s) {
            // Valid values are -1000 to 1000
            if (i2c_data[3].s > 1000)
                i2c_data[3].s = 1000;
            else if (i2c_data[3].s < -1000)
                i2c_data[3].s = -1000;
            motor_right = i2c_data[3].s;
            motors_set_speed_right(motor_right);
//            printf("Set right motor to %d\n", motor_right);
        }
        
        i2c_data[4].u = motors_get_steps_left();
        i2c_data[5].u = motors_get_steps_right();
        
        __delay_ms(1);
    }
}
