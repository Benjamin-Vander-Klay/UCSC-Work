/* 
 * File:   TrackWire.h
 * Author: Abner
 *
 * Created on May 17, 2022, 4:42 PM
 */

#ifndef TRACK_WIRE_SENSOR_H
#define	TRACK_WIRE_SENSOR_H

#include <BOARD.h>
#include "AD.h"
#include "pwm.h"
#include <stdlib.h>
#include <stdio.h>
#include "xc.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"

#define INPUT 1

//Ports to be read from for each Track Wire
//#define A_TW AD_PORTV3
//#define B_TW AD_PORTV4

// Using Digital input
#define A_TW PORTZ11_BIT
#define B_TW PORTY07_BIT

// BVK added here
#define A_TW_TRIS PORTV03_TRIS
#define B_TW_TRIS PORTV04_TRIS


//Track Wire Mask
#define A_TW_MASK 0x01
#define B_TW_MASK 0x02

/**
 * Function  char TrackWire_Init(void)
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Initialize AD pins for TrackWire
 * @author Amber Patino
 * @date 5/16/2022 */
char TrackWire_Init(void);

/**
 * Function  Read_TW_Analog(char)
 * @param TrackWire A or TrackWire B
 * @return 10-bit value for the current reading of the Track Wire Detector
 * @remark Returns the light level from specified sensor 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned int Read_TW_Analog(unsigned int TrackWireSensor);


// ? 
unsigned int Read_TrackWire(unsigned int TrackWireSensor);
#endif	/* TRACK_WIRE_SENSOR_H */

