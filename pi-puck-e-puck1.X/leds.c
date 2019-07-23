#include "leds.h"

void leds_init() {
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
