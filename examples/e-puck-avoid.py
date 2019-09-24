#!/usr/bin/env python3

import time
# import sys
import smbus
import signal

I2C_CHANNEL = 4
EPUCK_I2C_ADDR = 0x1f

# Register addresses
OUTER_LEDS = 0
INNER_LEDS = 1
LEFT_MOTOR_SPEED = 2
RIGHT_MOTOR_SPEED = 3
LEFT_MOTOR_STEPS = 4
RIGHT_MOTOR_STEPS = 5
IR_CONTROL = 6
IR0_REFLECTED = 7
IR1_REFLECTED = 8
IR2_REFLECTED = 9
IR3_REFLECTED = 10
IR4_REFLECTED = 11
IR5_REFLECTED = 12
IR6_REFLECTED = 13
IR7_REFLECTED = 14
IR0_AMBIENT = 15
IR1_AMBIENT = 16
IR2_AMBIENT = 17
IR3_AMBIENT = 18
IR4_AMBIENT = 19
IR5_AMBIENT = 20
IR6_AMBIENT = 21
IR7_AMBIENT = 22

MAX_SPEED = 500
weights_left = [-10, -10, -5, 0, 0, 5, 10, 10]
weights_right = [-1 * x for x in weights_left]

ir_led_mapping = [0b00000001,
				  0b00000010,
				  0b00000100,
				  0b00011000,
				  0b00110000,
				  0b01000000,
				  0b10000000,
				  0b00000001]

print('e-puck obstacle avoidance')

print('Initialising I2C...')

bus = smbus.SMBus(I2C_CHANNEL)

# Register signal handler for Ctrl+C
def signal_handler(sig, frame):
	print('Ctrl+C pressed')
	bus.write_word_data(EPUCK_I2C_ADDR, IR_CONTROL, 0) # Stop IR
	bus.write_word_data(EPUCK_I2C_ADDR, LEFT_MOTOR_SPEED, 0) # Stop motors
	bus.write_word_data(EPUCK_I2C_ADDR, RIGHT_MOTOR_SPEED, 0)
	bus.close()
	sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

print('Starting controller...')

bus.write_word_data(EPUCK_I2C_ADDR, IR_CONTROL, 1) # Turn IR sensors on

delay = 0.1

while True:

	ir = [0] * 8

	# Get IR sensor readings
	for i in range(8):
		ir[i] = bus.read_word_data(EPUCK_I2C_ADDR, IR0_REFLECTED + i)

	print(ir)

	left = right = MAX_SPEED / 2

	leds_on = 0

	# Obstacle avoidance
	for i, reading in enumerate(ir):
		if(reading > 300):
			# leds_on |= 1 << i
			leds_on |= ir_led_mapping[i]
			left += weights_left[i] * reading
			right += weights_right[i] * reading

	bus.write_word_data(EPUCK_I2C_ADDR, OUTER_LEDS, leds_on) # Turn LEDs next to IR sensors that detect obstacles

	if(leds_on == 0):
		bus.write_word_data(EPUCK_I2C_ADDR, INNER_LEDS, 0b10)
	else:
		bus.write_word_data(EPUCK_I2C_ADDR, INNER_LEDS, 0b00)

	if left > MAX_SPEED:
		left = MAX_SPEED
	elif left < -MAX_SPEED:
		left = -MAX_SPEED

	if right > MAX_SPEED:
		right = MAX_SPEED
	elif right < -MAX_SPEED:
		right = -MAX_SPEED

	# Set wheel speeds
	bus.write_word_data(EPUCK_I2C_ADDR, LEFT_MOTOR_SPEED, int(left))
	bus.write_word_data(EPUCK_I2C_ADDR, RIGHT_MOTOR_SPEED, int(right))

	time.sleep(delay)

bus.close()
