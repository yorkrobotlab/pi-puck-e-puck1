#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include <libpic30.h>
#include "adc.h"
#include "leds.h"
#include <uart.h>
#include <stdio.h>

// Use UART2 for stdio
int __C30_UART = 2;

int16_t main(void)
{
    // Set up UART2
    U2BRG = 7; // 115200 bps
    U2MODE = UART_EN & UART_IDLE_STOP & UART_DIS_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_NO_PAR_8BIT & UART_1STOPBIT;
    U2STA = UART_INT_TX_BUF_EMPTY & UART_TX_PIN_NORMAL & UART_TX_ENABLE & UART_INT_RX_BUF_FUL & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR;

    printf("I am an e-puck.\n");
    
    adc_init();
    
    while(1)
    {
        unsigned int result = adc_read(5);
        printf("%d\n", result);
        __delay_ms(100);
    }
    
//    leds_init();
//    unsigned long delay = 1000/8;
//    while(1)
//    {        
//        // Loop through LEDs
//        LED0 = 1;
//        __delay_ms(delay);
//        LED0 = 0;
//        LED1 = 1;
//        __delay_ms(delay);
//        LED1 = 0;
//        LED2 = 1;
//        __delay_ms(delay);
//        LED2 = 0;
//        LED3 = 1;
//        __delay_ms(delay);
//        LED3 = 0;
//        LED4 = 1;
//        __delay_ms(delay);
//        LED4 = 0;
//        LED5 = 1;
//        __delay_ms(delay);
//        LED5 = 0;
//        LED6 = 1;
//        __delay_ms(delay);
//        LED6 = 0;
//        LED7 = 1;
//        __delay_ms(delay)
//        LED7 = 0;
//    }
}
