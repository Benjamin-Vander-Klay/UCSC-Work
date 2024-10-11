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

#define A_TS_MASK 0x01 // rear right
#define B_TS_MASK 0x02 // rear center
#define C_TS_MASK 0x04 // rear left 
#define D_TS_MASK 0x08 // front right
#define E_TS_MASK 0x10 // front center
#define F_TS_MASK 0x20 // front left

// TBH i needed to know which were which in the code.  bvk 6.5.22 10pm
#define FRONT_TS (D_TS_MASK | E_TS_MASK | F_TS_MASK)
#define REAR_TS  (A_TS_MASK | B_TS_MASK | C_TS_MASK) 

#define ALL_TAPE_HIGH (A_TS_MASK | B_TS_MASK | C_TS_MASK | D_TS_MASK | E_TS_MASK | F_TS_MASK)

#define NOT_TS_MASK_A (B_TS_MASK | C_TS_MASK | D_TS_MASK |E_TS_MASK | F_TS_MASK)
#define NOT_TS_MASK_B (A_TS_MASK | C_TS_MASK | D_TS_MASK |E_TS_MASK | F_TS_MASK) 
#define NOT_TS_MASK_C (A_TS_MASK | B_TS_MASK | D_TS_MASK |E_TS_MASK | F_TS_MASK)
#define NOT_TS_MASK_D (A_TS_MASK | B_TS_MASK | C_TS_MASK |E_TS_MASK | F_TS_MASK)
#define NOT_TS_MASK_E (A_TS_MASK | B_TS_MASK | C_TS_MASK |D_TS_MASK | F_TS_MASK)
#define NOT_TS_MASK_F (A_TS_MASK | B_TS_MASK | C_TS_MASK |D_TS_MASK | E_TS_MASK)

#define TOWER_TAPE_FRONT 1
#define TOWER_TAPE_MID 2
#define TOWER_TAPE_REAR 4
#define TOWER_TAPE_ALL 7 

// to make some of this negation logic easier. bvk 5.6.2022 7pm
#define TAPE_ON_WALL (TOWER_TAPE_MID)                                                                   // (REAR  CENTER  FRONT)
#define DDW (TOWER_TAPE_ALL - TOWER_TAPE_FRONT) // 0 is white wall, 1 is dark. this will give us 0x110
#define WDD (TOWER_TAPE_ALL - TOWER_TAPE_REAR)   // 0 is white wall, 1 is dark. this will give us 0x011 // changed name to WDD
#define TOWER_TAPE_ALL_WHITE 0 // no tape, just wall


//6/1/22 Changed Naming Convention // for tower!
#define TS_Front PORTY09_BIT  
#define TS_Mid PORTY11_BIT // Changed to Y11 from Y05 cuz relocating them in the robot
#define TS_Rear PORTY05_BIT // Changed to Y05 from Y11 cuz relocating them in the robot

#define TS_Front_TRIS PORTY09_TRIS 
#define TS_Mid_TRIS PORTY11_TRIS
#define TS_Rear_TRIS PORTY05_TRIS

#define TS_FRONT_AD AD_PORTW3
#define TS_MID_AD AD_PORTW4
#define TS_REAR_AD AD_PORTW6

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

unsigned int Read_Top_Tape_AD(unsigned int TapeSensor);
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