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
    adc_init();
    leds_init();
    
    while(1)
    {
        printf("I am an e-puck.\n");
        
        __delay_ms(1000);
    }
}
