#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include <libpic30.h>
#include "leds.h"


int16_t main(void)
{
    leds_init();

    unsigned long delay = 1000/8;
    
    while (1)
    {
        // Loop through LEDs
        LED0 = 1;
        __delay_ms(delay);
        LED0 = 0;
        LED1 = 1;
        __delay_ms(delay);
        LED1 = 0;
        LED2 = 1;
        __delay_ms(delay);
        LED2 = 0;
        LED3 = 1;
        __delay_ms(delay);
        LED3 = 0;
        LED4 = 1;
        __delay_ms(delay);
        LED4 = 0;
        LED5 = 1;
        __delay_ms(delay);
        LED5 = 0;
        LED6 = 1;
        __delay_ms(delay);
        LED6 = 0;
        LED7 = 1;
        __delay_ms(delay)
        LED7 = 0;
    }
}
