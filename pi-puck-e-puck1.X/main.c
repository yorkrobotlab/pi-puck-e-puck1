#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "system.h"
#include <libpic30.h>

#include "adc.h"
#include "leds.h"
#include "uart2.h"
#include "i2c_slave.h"

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
    
    printf("I am an e-puck.\n");
    
    uint8_t leds_outer = 0;
    uint8_t leds_front_body = 0;
    leds_set_outer(leds_outer);
    leds_set_front_body(leds_front_body);
    
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
        }
        __delay_ms(1);
    }
}
