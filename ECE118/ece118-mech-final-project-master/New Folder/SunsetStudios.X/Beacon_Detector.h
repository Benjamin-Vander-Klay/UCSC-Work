/* 
 * File:   Beacon_Detector.h
 * Author: Abner
 * Description: Sensor Library for Beacon Detector Digital and Analog Outputs 
 * Created on May 17, 2022, 7:51 PM
 */

#ifndef BEACON_DETECTOR_H
#define	BEACON_DETECTOR_H

#include <BOARD.h>
#include "AD.h"
#include "pwm.h"
#include <stdlib.h>
#include <stdio.h>
#include "xc.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"

//Analog Port To Read From 
#define ALOG_BEACON AD_PORTW5

//Digital Pin to read from
#define DIG_BEACON PORTY10_BIT 
//Used to set Digital Port Direction
#define DIG_TRIS PORTY10_TRIS 


/**
 * Function  Beacon_Init(void)
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Initialize AD pins for Analog Beacon and Digital Pins for other Beacon 
 * @author Amber Patino
 * @date 5/16/2022 */
char Beacon_Init(void);

/**
 * Function  Read_Analog_Beacon(void)
 * @param 
 * @return returns 10 bit value for output from analog beacon detector
 * @remark Returns the current reading from the analog beacon detector
 * @author Amber Patino
 * @date 5/16/2022 */
unsigned int Read_Analog_Beacon(void);
/**
 * Function  Read_Digital_Beacon(void)
 * @param 
 * @return High/LOW
 * @remark Returns the current reading from the Digital Beacon Detector
 * @author Amber Patino
 * @date 5/16/2022 */
char Read_Digital_Beacon(void);



#endif	/* BEACON_DETECTOR_H */

