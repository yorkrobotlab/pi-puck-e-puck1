/* Based on Microchip code example CE145 (Using I2C module as Slave device on dsPIC33F) */

#include <xc.h>
#include <i2c.h>
#include "i2c_slave.h"

uint8_t i2c_data[256]; // Data area for I2C device
uint8_t register_addr; // Pointer to current I2C memory location
struct I2CFlagType flag;


void i2c_slave_init(void)
{
    // Set up and enable I2C module
    I2CCON = I2C_ON &
             I2C_IDLE_CON &
             I2C_CLK_HLD &
             I2C_IPMI_DIS &
             I2C_7BIT_ADD &
             I2C_SLW_DIS &
             I2C_SM_EN &
             I2C_GCALL_DIS &
             I2C_STR_DIS & I2C_ACK &
             I2C_ACK_DIS &
             I2C_RCV_DIS &
             I2C_STOP_DIS &
             I2C_RESTART_DIS &
             I2C_START_DIS;
    
    // Set 7-bit I2C slave address
    I2CADD = 0x1e;
    
    // Clear interrupt status flag register
    IFS1 = 0;
    
    // Initialise data pointer and flags
    register_addr = 0;
    flag.AddrFlag = 0;
    flag.DataFlag = 0;
    
    // Enable Slave I2C Transfer Complete Interrupt
    IEC0bits.SI2CIE = 1;
}


// ISR for I2C Slave interrupt.
void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void)
{
    uint8_t temp; // Used for dummy read
    
    if ((I2CSTATbits.R_W == 0) && (I2CSTATbits.D_A == 0)) {
        // Address write from master
        temp = I2CRCV; // Dummy read to clear register
        flag.AddrFlag = 1; // Next byte will be address
    }
    else if ((I2CSTATbits.R_W == 0) && (I2CSTATbits.D_A == 1)) {
        // Data write from master
        if (flag.AddrFlag) {
            // Received register address
            register_addr = I2CRCV; // Read register address
            flag.AddrFlag = 0;
            flag.DataFlag = 1; // Next byte will be data
        }
        else if (flag.DataFlag) {
            // Received register data
            i2c_data[register_addr] = I2CRCV; // Store data into RAM
            flag.AddrFlag = 0;
            flag.DataFlag = 0;
        }
    }
    else if ((I2CSTATbits.R_W == 1) && (I2CSTATbits.D_A == 0)) {
        // Data read from master
        I2CTRN = i2c_data[register_addr]; // Set data to send to I2C master
        temp = I2CRCV; // Dummy read to clear register
        I2CCONbits.SCLREL = 1; // Release SCL line
        while(I2CSTATbits.TBF); // Wait for data transmission to complete
    }
    
    I2CSTATbits.I2COV = 0; // Clear any potential overflow flag
    _SI2CIF = 0; // Clear I2C Slave interrupt flag
}
