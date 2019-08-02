# e-puck1 Firmware for the Pi-puck

This repository contains firmware sources for the dsPIC30F6014A on the e-puck1 robot for use with the Pi-puck extension board.

See https://github.com/yorkrobotlab/pi-puck for more information on the Pi-puck, as well as compiled firmware HEX files and programming information.


## Bootloader

The included bootloader project can be used to program the dsPIC so any further firmware can be uploaded directly from the Raspberry Pi, in a similar way to using the e-puck Bluetooth bootloader.
See https://github.com/yorkrobotlab/pi-puck/blob/master/e-puck1/e-puck-program for more details.
Note that R30/R31 must be removed from the Pi-puck board for this to work, which will disable the Bluetooth UART on the dsPIC.


## Main Firmware

The main purpose of the Pi-puck firmware is to provide an I2C interface for the Raspberry Pi to control the e-puck robot hardware.
Additional functionality can be written into the dsPIC code, but the default assumption is that the majority of processing and control is to be performed by the Raspberry Pi, besides processing data into a format that is suitable for communication.


### I2C Register Map

The firmware exposes a number of 8-bit or 16-bit I2C registers at slave address `0x1e`.

| Register | Length (bits) | Read/Write | Description                                        | Data                                            |
|---------:|--------------:|------------|----------------------------------------------------|-------------------------------------------------|
|        0 |             8 | R/W        | Outer ring of LEDs control                         | One bit per LED; order (high to low) `76543210` |
|        1 |             8 | R/W        | Front and body LEDs control                        | One bit per LED; order (high to low) `xxxxxxbf` |
|        2 |            16 | R/W        | Left motor velocity (steps per second)             | Signed value; -1000 to 1000                     |
|        3 |            16 | R/W        | Right motor velocity (steps per second)            | Signed value; -1000 to 1000                     |
|        4 |            16 | RO         | Left motor total steps count                       | Unsigned value; 0 to 65535 (overflows)          |
|        5 |            16 | RO         | Right motor total steps count                      | Unsigned value; 0 to 65535 (overflows)          |
|        6 |             8 | R/W        | IR sensors control; enable or disable measurements | Set bit 0 to enable, clear to disable           |
|     7-14 |            16 | RO         | IR proximity (0-7); higher is closer               | Unsigned value; 0 to 4095                       |
|    15-22 |            16 | RO         | IR ambient light (0-7); higher is brighter         | Unsigned value; 0 to 4095                       |
