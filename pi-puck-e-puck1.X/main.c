#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include <libpic30.h>
#include "leds.h"
#include "uart2.h"
#include <stdio.h>
#include "i2c_slave.h"

int16_t main(void)
{
    int i;
    for (i = 0; i < 256; i++) {
        i2c_data[i] = 0;
    }
    
    uart2_init();
    i2c_slave_init();
    leds_init();
    
    printf("I am an e-puck.\n");
    
    uint8_t leds_outer = 0;
    uint8_t leds_front_body = 0;
    leds_set_outer(leds_outer);
    leds_set_front_body(leds_front_body);

    while (1) {
        if (leds_outer != i2c_data[0]) {
            leds_outer = i2c_data[0];
            leds_set_outer(leds_outer);
        }
        if (leds_front_body != i2c_data[1]) {
            leds_front_body = i2c_data[1];
            leds_set_front_body(leds_front_body);
        }
        __delay_ms(1);
    }
}
