/* Based on Microchip code example CE145 (Using I2C module as Slave device on dsPIC33F) */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

struct I2CFlagType
{
    uint8_t AddrFlag:1;
    uint8_t DataFlag:1;
};

extern uint8_t i2c_data[256]; // Data area for I2C slave

void i2c_slave_init(void);

#endif /* I2C_SLAVE_H */
