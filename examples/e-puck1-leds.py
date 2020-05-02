#!/usr/bin/env python3

import time
import sys
import signal
import epuck1


# Register signal handler for Ctrl+C
def signal_handler(sig, frame):
	epuck.set_inner_leds(False, False)  # Turn off LEDs
	epuck.set_outer_leds_byte(0)  # Turn off LEDs
	sys.exit(0)


print('e-puck LEDs test')

print('Initialising I2C...')

epuck = epuck1.Epuck1()
signal.signal(signal.SIGINT, signal_handler)

print('Cycling LEDs...')

delay = 0.1

while True:
	epuck.set_inner_leds(True, False)
	epuck.set_outer_leds(True, False, False, False, False, False, False, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, False, False, False, False, False, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, True, False, False, False, False, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, True, True, False, False, False, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, True, True, True, False, False, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, True, True, True, True, False, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, True, True, True, True, True, False)
	time.sleep(delay)
	epuck.set_outer_leds(True, True, True, True, True, True, True, True)
	time.sleep(delay)
	epuck.set_inner_leds(False, True)
	epuck.set_outer_leds(False, True, True, True, True, True, True, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, True, True, True, True, True, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, False, True, True, True, True, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, False, False, True, True, True, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, False, False, False, True, True, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, False, False, False, False, True, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, False, False, False, False, False, True)
	time.sleep(delay)
	epuck.set_outer_leds(False, False, False, False, False, False, False, False)
	time.sleep(delay)
