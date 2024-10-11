/* 
 * File:   TapeSensor.h
 * Author: abner
 *
 * Created on May 16, 2022
 */

#ifndef TAPE_SENSORS_H
#define	TAPE_SENSORS_H

#include <BOARD.h>
#include "AD.h"
#include "pwm.h"
#include <stdlib.h>
#include <stdio.h>
#include "xc.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"

//Defines Ports for Tape Sensors 
#define A_TS AD_PORTV3
#define B_TS AD_PORTV4
#define C_TS AD_PORTV5
#define D_TS AD_PORTV6
#define E_TS AD_PORTV7
#define F_TS AD_PORTV8

#define A_TS_MASK 0x01
#define B_TS_MASK 0x02
#define C_TS_MASK 0x04
#define D_TS_MASK 0x08
#define E_TS_MASK 0x10
#define F_TS_MASK 0x20

#define Top_TS_1 PORTY09_BIT 
#define Top_TS_2 PORTY11_BIT 

#define Top_TS_1_TRIS PORTY09_TRIS 
#define Top_TS_2_TRIS PORTY11_TRIS

#define INPUT 1

//TIP 120 Pin
#define SWITCH_PORT PORTY
#define SWITCH_PIN PIN3

//State
#define HIGH 1
#define LOW 0

//Bump Sensor Code


/*******************************************************************************
 * FUNCTION PROTOTYPES TAPE SENSOR                                               *
 ******************************************************************************/

/**
 * Function  Tape_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Initialize AD pins for Tape Sensors, PWM Signal for swtich 
 * @author Amber Patino
 * @date 5/16/2022 */
char Tape_Init(void);
/**
 * Function  Read_Bottom_Tape(char)
 * @param char representing specific tape sensor located on the bottom of the bot 
 * @return 10-bit value corresponding to the light level from the sensor 
 * @remark Returns the light level from specified sensor 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned int Read_Bottom_Tape(unsigned int TapeSensor);
/**
 * Function  Read_Top_Tape(void)
 * @param n/a
 * @return whether both tape sensors are on or off, char 
 * @author Amber Patino
 * @date 5/16/2022 */

char Read_Top_Tape(void);
/**
 * Function  Set_IR_LED(char State)
 * @param HIGH or LOW
 * @return SUCCESS or ERROR
 * @remark Sets the State of the IR LED to ON/OFF for use when determining current noise 
 * @author Amber Patino
 * @date 5/16/2022 */
char Set_IR_LED(char State);



/**
 * Function  Get_IR_LED(char State)
 * @param HIGH or LOW
 * @remark Returns Current State of IR LEDS 
 * @author Amber Patino
 * @date 5/16/2022 */

//Not implemented yet
char Get_IR_LED(void);

#endif	/* TAPE_SENSORS_H */