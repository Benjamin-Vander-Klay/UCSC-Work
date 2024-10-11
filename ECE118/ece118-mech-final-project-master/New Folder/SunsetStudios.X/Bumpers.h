/* 
 * File:   Bumpers.h
 * Author: Abner
 *
 * Created on May 16, 2022, 9:08 PM
 */

#ifndef BUMPERS_H
#define	BUMPERS_H

#include <BOARD.h>
#include "AD.h"
#include "pwm.h"
#include <stdlib.h>
#include <stdio.h>
#include "xc.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"

//Used to read pins for each Bumper
#define FR PORTY05_BIT //6/6/22 Changed from W4 to x07
#define FL PORTY06_BIT
#define RR PORTZ08_BIT
#define RL PORTZ09_BIT

//#define BUMP_PINS PIN9 | PIN10 | PIN11 | PIN12

//Used to Set Port Direction

#define FR_TRIS PORTY05_TRIS
#define FL_TRIS PORTY06_TRIS
#define RR_TRIS PORTZ08_TRIS
#define RL_TRIS PORTZ09_TRIS

//Define Port for Bumpers
//#define BUMP_PORT PORTX
/*******************************************************************************
 * FUNCTION PROTOTYPES BUMPER                                             *
 ******************************************************************************/
/**
 * Function Bumper_Init(void);
 * @param n/a
 * @return Returns SUCCESS or FAILURE
 * @remark Sets pins for Bumpers 
 * @author Amber Patino
 * @date 5/16/2022 */


char Bumper_Init(void);
/**
 * Function  Read_FR_Bumper(void);
 * @param n/a
 * @return Returns HIGH/LOW for current state of Front Right Bumper
 * @remark Reads the value from the Front Right Bumper 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned char Read_FR_Bumper(void);
/**
 * Function  Read_FL_Bumper(void);
 * @param n/a
 * @return Returns HIGH/LOW for current state of Front Left Bumper
 * @remark Reads the value from the Front Left Bumper 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned char Read_FL_Bumper(void);
/**
 * Function  Read_RR_Bumper(void);
 * @param n/a
 * @return Returns HIGH/LOW for current state of  Rear Right Bumper
 * @remark Reads the value from the Rear Right Bumper 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned char Read_RR_Bumper(void);
/**
 * Function  Read_RL_Bumper(void);
 * @param n/a
 * @return Returns HIGH/LOW for current state of Rear Left Bumper
 * @remark Reads the value from the Rear Left Bumper 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned char Read_RL_Bumper(void);
/**
 * Function  Read_All_Bumpers(void);
 * @param n/a
 * @return Returns True or False if any Bumpers are triggered
 * @remark Checks if any of the bumpers are triggered
 * @author Amber Patino
 * @date 5/16/2022 */
int16_t Read_All_Bumpers(void);



#endif	/* BUMPERS_H */

