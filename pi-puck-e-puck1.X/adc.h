#ifndef ADC_H
#define	ADC_H

#include <xc.h>
//#include <adc12.h>
#include "system.h"

void adc_init();
unsigned int adc_read(unsigned int channel);

#endif