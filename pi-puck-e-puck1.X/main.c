#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include <libpic30.h>
#include "adc.h"
#include "leds.h"
#include "uart2.h"
#include <stdio.h>


int16_t main(void)
{
    uart2_init();
    
    printf("I am an e-puck.\n");
    
    adc_init();
    
    while(1)
    {
        unsigned int acc_x, acc_y, acc_z;
        
        acc_x = adc_read(5);
        acc_y = adc_read(6);
        acc_z = adc_read(7);
        
        printf("%u, %u, %u\n", acc_x, acc_y, acc_z);
        
        __delay_ms(100);
    }
}
