/* 
 * File:   Solenoid_Driver.h
 * Author: bcvander
 *
 * Created on May 15, 2022, 8:03 PM
 */

#ifndef SOLENOID_DRIVER_H
#define	SOLENOID_DRIVER_H

#include "IO_Ports.h"

#define SOL_TIME_MS 75
#define SOL_BTN_MS 500
#define STOP_AND_SHOOT_DURATION 1500
#define SOL_DRIVER_PIN PIN8
#define SOL_DRIVER_PORT PORTY
/**
 *  Solenoid_Init(void) 
 *  Uses IO Ports.h Defines to set a pin as solenoid trigger pin
 *  Pin and Port is defined in Macros above
 * 
 */
char Solenoid_Init(void);

/**
 * Solenoid_Add(int8_t port, uint16_t pattern);
 * Uses IO Ports.h Defines to set s
 * @param port
 * @param pattern
 * @return SUCCESS or ERROR depending on IO_PortsSetPortOutputs
 * @author bcvander 6/16/2022
 * @Note NO LONGER USED.USE Solenoid_Init()
 */
//char Solenoid_Add(int8_t port, uint16_t pattern);


/**
 * @param port/pattern - the pin which the solenoid is connected to. Y08 is the plan - 5/16/2022
 * 
 * @return SUCCESS or ERROR depending on whether or not the solenoid was successfully
 * activated and turned off
 * 
 * Uses FRT for now to ensure we don't fire more than once every 300 ms. less than this is possible\
 *  but generally unnecessary 
 * @author bcvander 6/16/2022
 * 
 */
char Solenoid_Fire(void);



// returns true if at least 300ms have passed since last fired
char Solenoid_Ready(/*int8_t whenready*/);
/**
 * Solenoid_Fire(int8_t port, uint16_t pattern);
 * Uses IO Ports.h Defines to set s
 * @param port
 * @param pattern
 * @return 
 */

#endif	/* SOLENOID_DRIVER_H */
