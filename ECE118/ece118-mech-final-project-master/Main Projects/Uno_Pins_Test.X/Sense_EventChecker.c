/* 
 * File:   Sense_EventChecker.c
 * Description: This is an event checker that will return T/F when a state transition event 
 * has occurred
 * Note: For Digital Sensor inputs such as the Track Wire Circuits, Bumpers, and Beacon Detector, de-bouncing will be handled by
 * a simple service which will de-bounce the input using a timer. For Analog inputs, such as the Bottom Tape Sensors, the hysteresis 
 * bounds will be set in #defines in the .c file of the Event checker 
 * Author: Amber   
 * 
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "Sense_EventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "Bumpers.h"
#include "Beacon_Detector.h"
#include "Motor_Driver.h"
#include "Solenoid_Driver.h"
#include "Tape_Sensors.h"
#include "Track_Wire_Sensor.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define BEACON_RANGE_HIGH 600
#define BEACON_RANGE_LOW 400
/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
//#define EVENTCHECKER_TEST

#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
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
uint8_t TemplateCheckBattery(void)
{
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

/**
 * @Function CheckFLBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether the front bumper was tripped. The function
 *        will post an event FL_PRESSED or FL_UNPRESSED if the bumper is tripped or released.
 *        Returns TRUE if there was an event, FALSE otherwise 
 * @author Amber */
uint8_t CheckFLBumper(void)
{
    //Default State is FL unpressed
    static ES_EventTyp_t lastEvent = FL_UNPRESSED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    //Get current State of Front Left Bumper 
    char bumpState = Read_FL_Bumper();

    //When Bump State is HIGH set current event to PRESSED
    if (bumpState) {
        curEvent = FL_PRESSED;
    }//Set Current Event to UNPRESSED when Bump State is LOW
    else {
        curEvent = FL_UNPRESSED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = bumpState;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //PostGenericService(thisEvent);


#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return returnVal;

}

uint8_t CheckFRBumper(void)
{
    //Default State is FL unpressed
    static ES_EventTyp_t lastEvent = FR_UNPRESSED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;
    //    uint32_t currentTime =  ES_Timer_GetTime();
    //    printf("\r\n Current State of Front Right Bumper: %d", bumpState);

    //Get current State of Front Right Bumper 
    //    printf("\r\nChecking Bump state");
    char bumpState = Read_FR_Bumper();

    //When Bump State is HIGH set current event to PRESSED
    if (bumpState) {
        //        printf("\r\nEntered high bumper");
        curEvent = FR_PRESSED;
    }//Set Current Event to UNPRESSED when Bump State is LOW
    else {
        curEvent = FR_UNPRESSED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = bumpState;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //Uncomment and change Name of Service function once Service file is created 
        //PostGenericService(thisEvent);

    }

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
    PostTemplateHSM(thisEvent);
#else
    SaveEvent(thisEvent);
#endif
    return returnVal;
}

uint8_t CheckRLBumper(void)
{
    //Default State is FL unpressed
    static ES_EventTyp_t lastEvent = RL_UNPRESSED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;
    //    uint32_t currentTime =  ES_Timer_GetTime();
    //    printf("\r\n Current State of Rear Left Bumper: %d", bumpState);

    //Get current State of Rear Left Bumper 
    char bumpState = Read_RL_Bumper();

    //When Bump State is HIGH set current event to PRESSED
    if (bumpState) {
        curEvent = RL_PRESSED;
    }//Set Current Event to UNPRESSED when Bump State is LOW
    else {
        curEvent = RL_UNPRESSED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = bumpState;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //Uncomment and change Name of Service function once Service file is created 
        //PostGenericService(thisEvent);

    }

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
    PostTemplateHSM(thisEvent);
    //    SaveEvent(thisEvent);
#else
    SaveEvent(thisEvent);
#endif
    return returnVal;
}

uint8_t CheckRRBumper(void)
{
    //Default State is FL unpressed
    static ES_EventTyp_t lastEvent = RR_UNPRESSED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    //Get current State of Rear Left Bumper 
    char bumpState = Read_RR_Bumper();

    //When Bump State is HIGH set current event to PRESSED
    if (bumpState) {
        curEvent = RR_PRESSED;
    }//Set Current Event to UNPRESSED when Bump State is LOW
    else {
        curEvent = RR_UNPRESSED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = bumpState;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //Uncomment and change Name of Service function once Service file is created 
        //PostGenericService(thisEvent);

    }

    //    return returnVal;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
    PostTemplateHSM(thisEvent);
    //    SaveEvent(thisEvent);
#else
    SaveEvent(thisEvent);
#endif
    return returnVal;
}

/**
 * @Function CheckBottomTape(uint8_t TapeSensor)
 * @param Takes in Tape Sensor value
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether the specified  sensors has detected darkness/light. 
 *        The function will post an event DARK_DETECTED or LIGHT_DETECTED if there is a transition between light and dark 
 *        Returns TRUE if there was an event, FALSE otherwise 
 * @author Amber */

#define NUM_TAPE_SENSORS 6

#define TAPE_DARK_THRESHOLD_A 800
#define TAPE_DARK_THRESHOLD_B 700
#define TAPE_DARK_THRESHOLD_C 600
#define TAPE_DARK_THRESHOLD_D 800
#define TAPE_DARK_THRESHOLD_E 700
#define TAPE_DARK_THRESHOLD_F 800

#define TAPE_LIGHT_THRESHOLD_A 100
#define TAPE_LIGHT_THRESHOLD_B 400
#define TAPE_LIGHT_THRESHOLD_C 200
#define TAPE_LIGHT_THRESHOLD_D 200
#define TAPE_LIGHT_THRESHOLD_E 100
#define TAPE_LIGHT_THRESHOLD_F 100

#define DEFAULT_STATE 0x0

//Planning on changing this -Amber
//static uint16_t lastLightState;
//static uint16_t lastDarkState;

uint8_t CheckBottomTapeforDark(void)
{
    //Default State is DARK_DETECTED unpressed
    static ES_EventTyp_t lastEvent = DF_NONE_DETECTED;
    static uint16_t lastDarkState = DEFAULT_STATE;
    //Defining this event 
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    uint16_t currentLightState = DEFAULT_STATE;
    //Get current value of the Specified Tape Sensor
    //    unsigned int tapeReading = Read_Bottom_Tape(TapeSensor);
    //Polling each tape sensor 

    unsigned int tapeReading = Read_Bottom_Tape(A_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading > TAPE_DARK_THRESHOLD_A) {
        //                printf("\r\nEntered Here in event A Statement");
        curEvent = DF_DETECTED;
        currentLightState = currentLightState | A_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(B_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading > TAPE_DARK_THRESHOLD_B) {
        curEvent = DF_DETECTED;
        currentLightState = currentLightState | B_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(C_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading > TAPE_DARK_THRESHOLD_C) {
        //        printf("\r\nEntered Here in event C Statement");
        curEvent = DF_DETECTED;
        currentLightState = currentLightState | C_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(D_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading > TAPE_DARK_THRESHOLD_D) {
        curEvent = DF_DETECTED;
        currentLightState = currentLightState | D_TS_MASK;
    }
    //Set Current Event to UNPRESSED when Bump State is LOW
    tapeReading = Read_Bottom_Tape(E_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading > TAPE_DARK_THRESHOLD_E) {
        curEvent = DF_DETECTED;
        currentLightState = currentLightState | E_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(F_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading > TAPE_DARK_THRESHOLD_F) {
        curEvent = DF_DETECTED;
        currentLightState = currentLightState | F_TS_MASK;
    }

    if (curEvent != lastEvent || (currentLightState != lastDarkState)) {
        //        printf("\r\nEntered Here in final If Statement");
        //        printf("\r\ncurrentLightState: %x: ", currentLightState);
        //        printf("\r\nlastDarkState: %x: ", lastDarkState);
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = currentLightState;
        returnVal = TRUE;

        //Set lastEvent to current Event
        //Set lastDarkState to currentLight State
        lastEvent = curEvent;
        lastDarkState = currentLightState;

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        //        PostGenericService(thisEvent);
        //    SaveEvent(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
        return returnVal;
    }

}

uint8_t CheckBottomTapeforLight(void)
{
    static uint16_t lastLightState = DEFAULT_STATE;
    //Default State is DARK_DETECTED unpressed
    static ES_EventTyp_t lastEvent = LF_NONE_DETECTED;
    //Defining this event 
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    uint16_t currentLightState = DEFAULT_STATE;
    //Get current value of the Specified Tape Sensor
    //    unsigned int tapeReading = Read_Bottom_Tape(TapeSensor);
    //Polling each tape sensor 

    unsigned int tapeReading = Read_Bottom_Tape(A_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading < TAPE_LIGHT_THRESHOLD_A) {
        curEvent = LF_DETECTED;
        currentLightState = currentLightState | A_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(B_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading < TAPE_LIGHT_THRESHOLD_B) {
        curEvent = LF_DETECTED;
        currentLightState = currentLightState | B_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(C_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading < TAPE_LIGHT_THRESHOLD_C) {
        curEvent = LF_DETECTED;
        currentLightState = currentLightState | C_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(D_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading < TAPE_LIGHT_THRESHOLD_D) {
        curEvent = LF_DETECTED;
        currentLightState = currentLightState | D_TS_MASK;
    }
    //Set Current Event to UNPRESSED when Bump State is LOW
    tapeReading = Read_Bottom_Tape(E_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading < TAPE_LIGHT_THRESHOLD_E) {
        curEvent = LF_DETECTED;
        currentLightState = currentLightState | E_TS_MASK;
    }
    tapeReading = Read_Bottom_Tape(F_TS);
    //Compares each reading to the Dark and Light Threshold
    if (tapeReading < TAPE_LIGHT_THRESHOLD_F) {
        curEvent = LF_DETECTED;
        currentLightState = currentLightState | F_TS_MASK;
    }

    if (curEvent != lastEvent || (currentLightState != lastLightState)) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = currentLightState;
        returnVal = TRUE;
        lastEvent = curEvent;
        lastLightState = currentLightState;

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
        //        PostGenericService(thisEvent);
        //    SaveEvent(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
        return returnVal;
    }

}

/**
 * @Function CheckTrackWireA(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the track wire is within range of Track Wire Sensor A. Will post event TW_DETECTED and 
 * TW_NOT_DETECTED when the robot enters/exits range of the TrackWire. The event parameter will be the specific track wire detected
 * @author Amber */

/**
 * @Function CheckTowerTape(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check for whether both of the bottom tape sensors has detected darkness/light. 
 *        The function will post an event DARK_WALL_DETECTED or LIGHT_WALL_DETECTED if there is a transition between light and dark 
 *        Returns TRUE if there was an event, FALSE otherwise 
 *        The event param will be used to 
 * @author Amber */
uint8_t CheckTowerTape(void)
{
    //Default State for Tower Tape is

    static ES_EventTyp_t lastEvent = LW_DETECTED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    char topTapeState;
    topTapeState = Read_Top_Tape();
    //When both Tape Sensors are High
    if (topTapeState) {
        curEvent = DW_DETECTED; //DARK_WALL_DETECTED;
    }        //If one of the Tape Sensors is not high
    else {

        curEvent = LW_DETECTED; //LIGHT_WALL_DETECTED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = topTapeState;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //Uncomment and change Name of Service function once Service file is created 
        //PostGenericService(thisEvent);



#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
        //        PostGenericService(thisEvent);
        //    SaveEvent(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return returnVal;
}

uint8_t CheckforTrackWireA(void)
{
    //Default State for TrackWire is 
    static ES_EventTyp_t lastEvent = TW_NOT_DETECTED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    //When current State of A_TW is high, set current event to TW_DETECTED
    if (A_TW) {
        curEvent = TW_DETECTED;
    }        //When current State of A_TW is low, set current event to TW_NOT_DETECTED
    else {
        curEvent = TW_NOT_DETECTED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = A_TW_MASK;
        returnVal = TRUE;
        lastEvent = curEvent;
    }

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
    PostTemplateHSM(thisEvent);
    //        PostGenericService(thisEvent);
    //    SaveEvent(thisEvent);
#else
    SaveEvent(thisEvent);
#endif
    return returnVal;
}

/**
 * @Function CheckTrackWireB(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the track wire is within range of Track Wire Sensor B. Will post event TW_DETECTED and 
 * TW_NOT_DETECTED when the robot enters/exits range of the TrackWire. The event parameter will be the specific track wire detected
 * @author Amber */
uint8_t CheckforTrackWireB(void)
{
    //Default State for TrackWire is 
    static ES_EventTyp_t lastEvent = TW_NOT_DETECTED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    //When current State of A_TW is high, set current event to TW_DETECTED
    if (B_TW) {
        curEvent = TW_DETECTED;
    }        //When current State of A_TW is low, set current event to TW_NOT_DETECTED
    else {
        curEvent = TW_NOT_DETECTED;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        //Set Current Event to 
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = B_TW_MASK;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //Uncomment and change Name of Service function once Service file is created 
        //PostGenericService(thisEvent);

    }

    //    return returnVal;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
    PostTemplateHSM(thisEvent);
    //        PostGenericService(thisEvent);
    //    SaveEvent(thisEvent);
#else
    SaveEvent(thisEvent);
#endif
    return returnVal;
}

/**
 * @Function CheckforBeaconDigital(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the beacon is within range. Will post event BEACON_DETECTED 
 * and BEACON_NOT_DETECTED when the robot enters/exits range of the beacon. 
 * @author Amber */
uint8_t CheckforBeaconDigital(void)
{
    //Default State for TrackWire is 
    static ES_EventTyp_t lastEvent = TW_NOT_DETECTED;

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    //When current State of DIG_BEACON is HIGH, return event TW_DETECTED
    if (DIG_BEACON) {
        curEvent = BEACON_NOT_WITHIN_DIGITAL_RANGE;
    }        //When current State of A_TW is low, set current event to TW_NOT_DETECTED
    else {
        curEvent = BEACON_WITHIN_DIGITAL_RANGE;
    }
    /*If there is a state transition, set thisEvent to curEvent
     **/

    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = A_TW_MASK;
        returnVal = TRUE;
        lastEvent = curEvent;
        //        SaveEvent(thisEvent);
        //Uncomment and change Name of Service function once Service file is created 
        //PostGenericService(thisEvent);



        //    return returnVal;

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
        //        PostGenericService(thisEvent);
        //    SaveEvent(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return returnVal;

}

/**
 * @Function CheckforBeaconAnalog(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that will check whether the beacon is within a specific range according to defined bounds. 
 * Will return BEACON_WITHIN_RANGE and BEACON_OUTSIDE_RANGE. Event param will be the analog reading from the sensor.
 * @author Amber */
uint8_t CheckforBeaconAnalog(void)
{ //Default State is BEACON_NOT_WTITHIN_ANALOG_RANGE
    static ES_EventTyp_t lastEvent = BEACON_NOT_WITHIN_ANALOG_RANGE;

    //Defining this event 
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;

    //Initialize retun value as FALSE
    uint8_t returnVal = FALSE;

    //Get current value of the Beacon Detector
    unsigned int beaconReading = Read_Analog_Beacon();

    //Compares reading to the Low and High Threshold
    if (beaconReading > BEACON_RANGE_HIGH) {
        curEvent = BEACON_WITHIN_ANALOG_RANGE;
    }//Set Current Event to UNPRESSED when Bump State is LOW
    else if (beaconReading < BEACON_RANGE_LOW) {
        curEvent = BEACON_NOT_WITHIN_ANALOG_RANGE;
    }


    if (curEvent != lastEvent) {
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = beaconReading;
        returnVal = TRUE;
        lastEvent = curEvent;
        //beaconLightReading = beaconReading;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
        //        PostGenericService(thisEvent);
        //    SaveEvent(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return returnVal;

}
/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void)
{
    BOARD_Init();
    /* user initialization code goes here */
    Bumper_Init();
    Tape_Init();
    Beacon_Init();
    TrackWire_Init();
    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }

            }
        }
    }
}

void PrintEvent(void)
{
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif