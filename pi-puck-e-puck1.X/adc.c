#include "adc.h"

#include <xc.h>
#include <adc12.h>
#include "system.h"
#include <libpic30.h>

void adc_init()
{
    ADCON1bits.ADON = 0; // Disable the ADC while it's configured
    
    // Clear the ADC interrupt flag and disable interrupts
    IFS0bits.ADIF = 0;
    IEC0bits.ADIE = 0;
    
    // ADPCFGbits.PCFGx 
    // = 0 for Analog input mode, 
    // = 1 for digital input mode (default) 
    ADPCFGbits.PCFG0 =  1; // Programmer PGD
    ADPCFGbits.PCFG1 =  1; // Programmer PGC
    ADPCFGbits.PCFG2 =  0; // Microphone 1
    ADPCFGbits.PCFG3 =  0; // Microphone 2
    ADPCFGbits.PCFG4 =  0; // Microphone 3
    ADPCFGbits.PCFG5 =  0; // Accelerometer x-axis
    ADPCFGbits.PCFG6 =  0; // Accelerometer y-axis
    ADPCFGbits.PCFG7 =  0; // Accelerometer z-axis
    ADPCFGbits.PCFG8 =  0; // IR0
    ADPCFGbits.PCFG9 =  0; // IR1
    ADPCFGbits.PCFG10 = 0; // IR2
    ADPCFGbits.PCFG11 = 0; // IR3
    ADPCFGbits.PCFG12 = 0; // IR4
    ADPCFGbits.PCFG13 = 0; // IR5
    ADPCFGbits.PCFG14 = 0; // IR6
    ADPCFGbits.PCFG15 = 0; // IR7

    // A/D conversion clock select bits ADCS<5:0> = (2 * TAD / TCY) ? 1 (see "Equation 18-1: A/D Conversion Clock Period" in "dsPIC30F Family Reference Manual")
    // The minimum TAD (A/D conversion clock period) is 666.67 ns because VDD is 3.3V (see "18.21 A/D Conversion Speeds" in dsPIC30F Family Reference Manual")
    // We want to use the smallest TAD possible, so ADCS<5:0> = (2 * 666.67 / 67.816841) - 1 = 18.66
    // ADC_CONV_CLK_10Tcy = 0xFFD3 = 19 is the closest value we can use to get a TAD over the minimum 666.67 ns
    // TAD = TCY * (ADCS<5:0> + 1) / 2 = TCY * (19 + 1) / 2 = (20 * TCY) / 2 = = 10 * TCY = 678.16841 ns
    ADCON3 = ADC_SAMPLE_TIME_0 &
             ADC_CONV_CLK_SYSTEM &
             ADC_CONV_CLK_10Tcy; 
  
    ADCON2 = ADC_VREF_AVDD_AVSS &
             ADC_SCAN_OFF &
             ADC_SAMPLES_PER_INT_1 &
             ADC_ALT_BUF_OFF &
             ADC_ALT_INPUT_OFF;
  
    ADCON1 = ADC_MODULE_ON & // Enable the ADC
             ADC_IDLE_STOP &
             ADC_FORMAT_INTG &
             ADC_CLK_MANUAL &
             ADC_AUTO_SAMPLING_OFF &
             ADC_SAMP_OFF;
}

unsigned int adc_read(unsigned int channel)
{
    // Exit if invalid channel specified
    if(channel > 15)
        return(0);
    
    // Configure ADCHS: A/D Input Channel Select Register
    // CH0NA: Channel 0 Negative Input Select for MUX A Multiplexer Setting bit will always be zero, so all analogue inputs will be referenced against -VREF
    ADCHS = channel;
    
    ADCON1bits.SAMP = 1; // Start sampling    
    __delay_us(10);      // TODO: Delay based on TAD instead? "The user software must time the setting and clearing of the SAMP bit to ensure adequate sampling time of the input signal"
    ADCON1bits.SAMP = 0; // Stop sampling and start converting
    
    while(!ADCON1bits.DONE); // Wait until conversion is done. This should take 14 * TAD = 14 * 666.67 ns = 9.33 us
    
    return(ADCBUF0); // Return result in buffer
}