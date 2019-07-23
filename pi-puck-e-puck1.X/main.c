/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC30F__)
        #include <p30Fxxxx.h>
    #endif
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

#include <libpic30.h>

#include "leds.h"


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

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
