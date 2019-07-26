/* Based on Microchip code example CE145 (Using I2C module as Slave device on dsPIC33F) */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

typedef union {
    uint16_t u;
    int16_t s;
    struct {
        uint8_t u_low;
        uint8_t u_high;
    };
    struct {
        int8_t s_low;
        int8_t s_high;
    };
} i2c_data_type;

struct I2CFlagType
{
    uint8_t AddrFlag:1;
    uint8_t Data1Flag:1;
    uint8_t Data2Flag:1;
};

extern i2c_data_type i2c_data[256]; // Data area for I2C slave

void i2c_slave_init(void);

#endif /* I2C_SLAVE_H */
