/* 
 * File:   Sense_EventChecker.h
 * Description: This is an event checker that will return T/F when a state transition event 
 * has occurred
 * Note: For Digital Sensor inputs such as the Track Wire Circuits, Bumpers, and Beacon Detector, de-bouncing will be handled by
 * a simple service which will de-bounce the input using a timer. For Analog inputs, such as the Bottom Tape Sensors, the hysteresis 
 * bounds will be set in #defines in the .c file of the Event checker 
 * Author: Amber   
 * 
 */

#ifndef SENSE_EVENTCHECKER_H
#define	SENSE_EVENTCHECKER_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "BOARD.h"
#include "Bumpers.h"
#include "Beacon_Detector.h"
#include "Motor_Driver.h"
#include "Solenoid_Driver.h"
#include "Tape_Sensors.h"
#include "Track_Wire_Sensor.h"
#include "TopHSM.h"
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define BEACON_RANGE_HIGH 700 // BVK 6:19pm 5/31 ya imma use this in the tower scope sub hsm right quick hope its ok
#define BEACON_RANGE_LOW 575
/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t TemplateCheckBattery(void);

/**
 * @Function CheckFLBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether the front left bumper was tripped. The function
 *        will post an event FL_PRESSED or FL_UNPRESSED if the bumper is tripped or released.
 *        Returns TRUE if there was an event, FALSE otherwise 
 * @author Amber */
uint8_t CheckFLBumper(void);
/**
 * @Function CheckFRBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether the front left bumper was tripped. The function
 *        will post an event FR_PRESSED or FR_UNPRESSED if the bumper is tripped or released.
 *        Returns TRUE if there was an event, FALSE otherwise 
 * @author Amber */
uint8_t CheckFRBumper(void);
/**
 * @Function CheckRLBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether the rear left bumper was tripped. The function
 *        will post an event RL_PRESSED or RL_UNPRESSED if the bumper is tripped or released.
 *        Returns TRUE if there was an event, FALSE otherwise 
 * @author Amber */
uint8_t CheckRLBumper(void);
/**
 * @Function CheckRRBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether the rear left bumper was tripped. The function
 *        will post an event RR_PRESSED or RR_UNPRESSED if the bumper is tripped or released.
 *        Returns TRUE if there was an event, FALSE otherwise 
 * @author Amber */
uint8_t CheckRRBumper(void);
/**
 * @Function CheckBottomTape(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether any of the bottom tape sensors has detected darkness/light. 
 *        The function will post an event DARK_FLOOR_DETECTED or LIGHT_FLOOR_DETECTED if there is a transition between light and dark 
 *        Returns TRUE if there was an event, FALSE otherwise 
 *        The event param will be used to 
 * @author Amber */
uint8_t CheckBottomTapeforDark(void);
uint8_t CheckBottomTapeforLight(void);
/**
 * @Function CheckTowerTape(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether both of the bottom tape sensors has detected darkness/light. 
 *        The function will post an event DARK_WALL_DETECTED or LIGHT_WALL_DETECTED if there is a transition between light and dark 
 *        Returns TRUE if there was an event, FALSE otherwise 
 *        The event param will be used to 
 * @author Amber */
uint8_t CheckTowerTape(void);

//6/1/22 Combining Track Wire A and B event Checkers ---Amber 
uint8_t CheckBothTrackWire(void);
/**
 * @Function CheckTrackWireA(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the track wire is within range. Will post event TW_DETECTED and 
 * TW_NOT_DETECTED when the robot enters/exits range of Track Wire Sensor A. The event parameter will be the specific track wire detected
 * @author Amber */
uint8_t CheckforTrackWireA(void);
/**
 * @Function CheckTrackWireB(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the track wire is within range. Will post event TW_DETECTED and 
 * TW_NOT_DETECTED when the robot enters/exits range of Track Wire Sensor B. The event parameter will be the specific track wire detected
 * @author Amber */
uint8_t CheckforTrackWireB(void);
/**
 * @Function CheckforBeaconDigital(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the beacon is within range. Will post event BEACON_DETECTED 
 * and BEACON_NOT_DETECTED when the robot enters/exits range of the beacon. 
 * @author Amber */
uint8_t CheckforBeaconDigital(void);
/**
 * @Function CheckforBeaconAnalog(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the beacon is within a specific range according to defined bounds. 
 * Will return BEACON_WITHIN_RANGE and BEACON_OUTSIDE_RANGE. Event param will be the analog reading from the sensor.
 * @author Amber */
uint8_t CheckforBeaconAnalog(void);

/**
 * @Function char CompareToEventParam(uint8_t Reading, uint8_t EventParam)
 * @param none
 * @return TRUE or FALSE
 * @brief Helper Function that receives uint8_t value, ignores all values except for TapeSensor A , D, E. Returns whether those value match with the event parameter 
 * Will return T/F depending on if number sequence appears in the event param
 * Suggested to be used with NOT_TS_MASKS and TS_MASKS
 * @author Amber */
char CompareToEventParam(uint8_t Reading, uint8_t EventParam);

/*  Example Use
 * //For A = 0, D = 1, E =1
 * Reading = (D_TS_MASK | E_TS_MASK) &  A_NOT_TS_MASK
 *  CompareToEventParam (Reading, ThisEvent.EventParam)
 */
#endif	/* SENSE_EVENTCHECKER_H */

