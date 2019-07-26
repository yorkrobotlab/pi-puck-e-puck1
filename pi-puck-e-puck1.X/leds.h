#ifndef LEDS_H
#define LEDS_H

#include <xc.h>
#include "system.h"

// LED0 is front, incrementing clockwise
#define LED0 _LATA6
#define LED1 _LATA7
#define LED2 _LATA9
#define LED3 _LATA12
#define LED4 _LATA10
#define LED5 _LATA13
#define LED6 _LATA14
#define LED7 _LATA15

#define LED0_DIR _TRISA6
#define LED1_DIR _TRISA7
#define LED2_DIR _TRISA9
#define LED3_DIR _TRISA12
#define LED4_DIR _TRISA10
#define LED5_DIR _TRISA13
#define LED6_DIR _TRISA14
#define LED7_DIR _TRISA15

#define FRONT_LED _LATC1
#define FRONT_LED_DIR _TRISC1

#define BODY_LED _LATC2
#define BODY_LED_DIR _TRISC2


void leds_init();
void leds_set_outer(uint8_t value);
void leds_set_front_body(uint8_t value);


#endif /* LEDS_H */
