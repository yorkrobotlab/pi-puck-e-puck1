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
    
    uint8_t ir_control = 0;
    
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
        
        if (ir_control != i2c_data[6].u_low) {
            // Valid values are 0x0000 to 0x0001
            i2c_data[6].u &= 0x0001;
            ir_control = i2c_data[6].u_low;
            if (ir_control & 1) {
                ir_sensors_start();
            }
            else {
                ir_sensors_stop();
            }
//            printf("Set IR control register to 0x%02x\n", ir_control);
        }
        
        i2c_data[7].s = ir_sensors_get_reflected(0);
        i2c_data[8].s = ir_sensors_get_reflected(1);
        i2c_data[9].s = ir_sensors_get_reflected(2);
        i2c_data[10].s = ir_sensors_get_reflected(3);
        i2c_data[11].s = ir_sensors_get_reflected(4);
        i2c_data[12].s = ir_sensors_get_reflected(5);
        i2c_data[13].s = ir_sensors_get_reflected(6);
        i2c_data[14].s = ir_sensors_get_reflected(7);
        
        i2c_data[15].s = ir_sensors_get_ambient(0);
        i2c_data[16].s = ir_sensors_get_ambient(1);
        i2c_data[17].s = ir_sensors_get_ambient(2);
        i2c_data[18].s = ir_sensors_get_ambient(3);
        i2c_data[19].s = ir_sensors_get_ambient(4);
        i2c_data[20].s = ir_sensors_get_ambient(5);
        i2c_data[21].s = ir_sensors_get_ambient(6);
        i2c_data[22].s = ir_sensors_get_ambient(7);
        
        __delay_ms(1);
    }
}
