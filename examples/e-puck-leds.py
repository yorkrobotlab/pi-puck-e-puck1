#!/usr/bin/env python3

import time
import sys
import smbus

I2C_CHANNEL = 4
EPUCK_I2C_ADDR = 0x1e

print('e-puck RGB LEDs test')

print('Initialising I2C...')

bus = smbus.SMBus(I2C_CHANNEL)

print('Cycling LEDs...')

delay = 0.1

while True:
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x01, 0x01)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x01)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x03)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x07)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x0f)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x1f)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x3f)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x7f)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xff)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x01, 0x02)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xfe)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xfc)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xf8)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xf0)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xe0)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0xc0)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x80)
    time.sleep(delay)
    bus.write_byte_data(EPUCK_I2C_ADDR, 0x00, 0x00)
    time.sleep(delay)

