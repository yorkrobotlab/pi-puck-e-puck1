#include "leds.h"

void leds_init()
{
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
    
    LED0_DIR = OUTPUT_PIN;
    LED1_DIR = OUTPUT_PIN;
    LED2_DIR = OUTPUT_PIN;
    LED3_DIR = OUTPUT_PIN;
    LED4_DIR = OUTPUT_PIN;
    LED5_DIR = OUTPUT_PIN;
    LED6_DIR = OUTPUT_PIN;
    LED7_DIR = OUTPUT_PIN;

    FRONT_LED = 0;
    FRONT_LED_DIR = OUTPUT_PIN;

    BODY_LED = 0;
    BODY_LED_DIR = OUTPUT_PIN;
}

void leds_set_outer(uint8_t value)
{
    LED0 = value;
    LED1 = value >> 1;
    LED2 = value >> 2;
    LED3 = value >> 3;
    LED4 = value >> 4;
    LED5 = value >> 5;
    LED6 = value >> 6;
    LED7 = value >> 7;
}

void leds_set_front_body(uint8_t value)
{
    FRONT_LED = value;
    BODY_LED = value >> 1;
}
