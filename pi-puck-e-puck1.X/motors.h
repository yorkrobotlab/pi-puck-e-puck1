/********************************************************************************

Control motor of e-puck with timer 4 and 5
December 2004: first version
Lucas Meier & Francesco Mondada  
Version 1.0 november 2005
Michael Bonani


This file is part of the e-puck library license.
See http://www.e-puck.org/index.php?option=com_content&task=view&id=18&Itemid=45

(c) 2005-2007 Michael Bonani, Francesco Mondada, Lucas Meier

Robotics system laboratory http://lsro.epfl.ch
Laboratory of intelligent systems http://lis.epfl.ch
Swarm intelligent systems group http://swis.epfl.ch
EPFL Ecole polytechnique federale de Lausanne http://www.epfl.ch

Modified version for Pi-puck library: 2019 Russell Joyce, University of York

**********************************************************************************/

#ifndef MOTORS_H
#define MOTORS_H

#include <xc.h>
#include <stdint.h>

#define OUTPUT_PIN 0

#define MOTOR1_PHA _LATD0
#define MOTOR1_PHB _LATD1
#define MOTOR1_PHC _LATD2
#define MOTOR1_PHD _LATD3
#define MOTOR2_PHA _LATD4
#define MOTOR2_PHB _LATD5
#define MOTOR2_PHC _LATD6
#define MOTOR2_PHD _LATD7

#define MOTOR1_PHA_DIR _TRISD0
#define MOTOR1_PHB_DIR _TRISD1
#define MOTOR1_PHC_DIR _TRISD2
#define MOTOR1_PHD_DIR _TRISD3
#define MOTOR2_PHA_DIR _TRISD4
#define MOTOR2_PHB_DIR _TRISD5
#define MOTOR2_PHC_DIR _TRISD6
#define MOTOR2_PHD_DIR _TRISD7

void motors_init(void); // init to be done before using the other calls
void motors_set_speed_left(int motor_speed); // motor speed in steps/s
void motors_set_speed_right(int motor_speed); // motor speed in steps/s
uint16_t motors_get_steps_left(void); // motors steps done left
uint16_t motors_get_steps_right(void); // motors steps done right

#endif /* MOTORS_H */
