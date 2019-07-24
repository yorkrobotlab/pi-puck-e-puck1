//#include "adc.h"
//
//unsigned int Channel, PinConfig, Scanselect;
//unsigned int Adcon3_reg, Adcon2_reg, Adcon1_reg;
//
//void adc_init()
//{
//    ADCON1bits.ADON = 0; // Disable ADC
//
//    // Configure ADCHS: A/D Input Channel Select Register
//    Channel = ADC_CH0_POS_SAMPLEA_AN5 &  // Select channel 5 (accelerometer x-axis)
//              ADC_CH0_NEG_SAMPLEA_NVREF; // Referenced against -VREF
//    SetChanADC12(Channel);
//    
//    ConfigIntADC12(ADC_INT_DISABLE); // Disable ADC interrupts
//
//    PinConfig  = ENABLE_AN5_ANA; // Set channel 5 as analogue input 
//
//    // Ignore all other input channels
//    Scanselect = SKIP_SCAN_AN0 &
//                 SKIP_SCAN_AN1 &
//                 SKIP_SCAN_AN2 &
//                 SKIP_SCAN_AN3 &
//                 SKIP_SCAN_AN4 &
//                 SKIP_SCAN_AN6 &
//                 SKIP_SCAN_AN7 &
//                 SKIP_SCAN_AN8 &
//                 SKIP_SCAN_AN9 &
//                 SKIP_SCAN_AN10 &
//                 SKIP_SCAN_AN11 &
//                 SKIP_SCAN_AN12 &
//                 SKIP_SCAN_AN13 &
//                 SKIP_SCAN_AN14 &
//                 SKIP_SCAN_AN15 ;
//
////    Adcon3_reg = ADC_SAMPLE_TIME_10 &
////                 ADC_CONV_CLK_SYSTEM &
////                 ADC_CONV_CLK_13Tcy;
////
////    Adcon2_reg = ADC_VREF_AVDD_AVSS &
////                 ADC_SCAN_OFF &
////                 ADC_ALT_BUF_OFF &
////                 ADC_ALT_INPUT_OFF & 
////                 ADC_SAMPLES_PER_INT_16;
////
////    Adcon1_reg = ADC_MODULE_ON &
////                 ADC_IDLE_CONTINUE &
////                 ADC_FORMAT_INTG &
////                 ADC_CLK_MANUAL &
////                 ADC_AUTO_SAMPLING_OFF;
//    
//    Adcon3_reg = 0;
//    Adcon2_reg = 0;
//    Adcon1_reg = 0;
//
//    OpenADC12(Adcon1_reg, Adcon2_reg, Adcon3_reg, PinConfig, Scanselect);
//}
//
//unsigned int adc_read()
//{
//    ADCON1bits.SAMP = 1;
//
//    while(!ADCON1bits.SAMP);
//
//    ConvertADC12();
//
//    while(ADCON1bits.SAMP);
//
////    while(!BusyADC12());
//
//    while(BusyADC12());
//
////    return ReadADC12(5);
//    
//    return 0;
//}

#include "adc.h"

#define	TCY_PIC		(1e9/FCY)		//time instruction cycle in [ns] 

void adc_init()
{
  ADCON1 = ADCON2 = ADCON3 = 0;
  
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
  
  ADCON3 = (2 * 667 / TCY_PIC) - 1; // ADCS sampling time T_AD minimum 667 ns
//  ADCHS = 0x0007;
  ADCHS = 0;
  ADCON1bits.ADON = 1;
}

unsigned int adc_read(unsigned int channel)
{
    int delay;
    
    if(channel > 15)
        return(0);
    
    ADCHS = channel;
    ADCON1bits.SAMP = 1;
    
    for(delay = 0; delay < 40; delay++); // TODO: Replace with  __delay_us()?
    
    IFS0bits.ADIF = 0;
    ADCON1bits.SAMP = 0;
    
    while(!IFS0bits.ADIF);
    
    return(ADCBUF0);
}