#!/usr/bin/env python3

import time
import sys
import signal
import epuck1


# Register signal handler for Ctrl+C
def signal_handler(sig, frame):
	epuck.enable_ir_sensors(False)  # Stop IR
	epuck.set_motor_speeds(0, 0)  # Stop motors
	epuck.set_inner_leds(False, False)  # Turn off LEDs
	epuck.set_outer_leds_byte(0)  # Turn off LEDs
	sys.exit(0)


MAX_SPEED = 500
weights_left = [-10, -10, -5, 0, 0, 5, 10, 10]
weights_right = [-1 * x for x in weights_left]
ir_led_mapping = [0b00000001, 0b00000010, 0b00000100, 0b00011000, 0b00110000, 0b01000000, 0b10000000, 0b00000001]
delay = 0.1

print('e-puck obstacle avoidance')

print('Initialising I2C...')

epuck = epuck1.Epuck1()
signal.signal(signal.SIGINT, signal_handler)

print('Starting controller...')

epuck.enable_ir_sensors(True)  # Turn IR sensors on

while True:
	ir = [0] * 8

	# Get IR sensor readings
	for i in range(8):
		ir[i] = epuck.get_ir_reflected(i)

	print(ir)

	left = right = MAX_SPEED / 2

	leds_on = 0

	# Obstacle avoidance
	for i, reading in enumerate(ir):
		if reading > 300:
			leds_on |= ir_led_mapping[i]
			left += weights_left[i] * reading
			right += weights_right[i] * reading

	epuck.set_outer_leds_byte(leds_on)  # Turn LEDs next to IR sensors that detect obstacles

	if leds_on == 0:
		epuck.set_inner_leds(True, False)
	else:
		epuck.set_inner_leds(False, False)

	if left > MAX_SPEED:
		left = MAX_SPEED
	elif left < -MAX_SPEED:
		left = -MAX_SPEED

	if right > MAX_SPEED:
		right = MAX_SPEED
	elif right < -MAX_SPEED:
		right = -MAX_SPEED

	# Set wheel speeds
	epuck.set_motor_speeds(left, right)

	time.sleep(delay)
