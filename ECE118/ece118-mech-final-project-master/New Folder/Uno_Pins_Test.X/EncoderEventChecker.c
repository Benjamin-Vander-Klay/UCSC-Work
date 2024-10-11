/*
 * File:   TemplateEventChecker.c
 * Author: Gabriel Hugh Elkaim
 *
 * Template file to set up typical EventCheckers for the  Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the
 * names will have to be changed to match your code.
 *
 * This EventCheckers file will work with both FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This file includes a test harness that will run the event detectors listed in the
 * ES_Configure file in the project, and will conditionally compile main if the macro
 * EVENTCHECKER_TEST is defined (either in the project or in the file). This will allow
 * you to check you event detectors in their own project, and then leave them untouched
 * for your project unless you need to alter their post functions.
 *
 * Created on September 27, 2013, 8:37 AM
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "EncoderEventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "Motor_Driver.h"
#include "stdlib.h"
#include "stdio.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//#define BATTERY_DISCONNECT_THRESHOLD 175


/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef ENCODER_EVENTCHECKER_TEST
#include <stdio.h>
#include "xc.h"
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
static uint8_t prev_hall_right;
static uint8_t prev_hall_left;
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
uint8_t CheckEncoderPWM(void) {

    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    // only post event if at least one tick has occured
    int8_t post = FALSE;
    
    // set up the right side
    uint8_t cur_hall_right = HALL_IN_RIGHT; // read the pwm input pin for right side
    uint8_t cur_hall_left = HALL_IN_LEFT; // read the pwm in-put pin for the left side
    printf("\r\nPrevious hall right = %d", prev_hall_right);
    printf("\r\ncurrent hall right = %d", cur_hall_right);
//    printf("\r\nPrevious hall right = %d", prev_hall_right);
//    printf("\r\ncurrent hall left = %d", cur_hall_left);
 
    // set the tick count to be passed as a parameter to 0, neither side has a rising edge
    int8_t tick = NO_TICK;
    // check the right PWM for a rising edge
    if (prev_hall_right == 0 && cur_hall_right == 1) {
        curEvent = ENCODER_TICK;
        
        //note a rising edge on the right side
        tick = tick | RIGHT_TICK;
        
        post = TRUE; // post an event
//        printf("posted right");
    }
    prev_hall_right = cur_hall_right; // update history

    // Left in the same checker?
    // check the left PWM for a rising edge
    if (prev_hall_left == 0 && cur_hall_left == 1) {
        curEvent = ENCODER_TICK;
        //note a rising edge on the left side
        tick = tick | LEFT_TICK;
        
        post = TRUE; // post an event
//        printf("posted left");
    }
    prev_hall_left = cur_hall_left; // update history
//    else {
//        curEvent = NO_EVENT;
//        returnVal = FALSE;
//    }
    if(post) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = tick;
        returnVal = TRUE;
//        post = FALSE; // only post once! // we do this at the beginning 
        
        
        
#ifndef ENCODER_EVENTCHECKER_TEST           // keep this as is for test harness
//        printf("\r\n Post the Tick!!!!!!!!!!!!!!! ");
        PostEncoderService(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
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
#ifdef ENCODER_EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */
    Drive_Init();
    
    Drive_Straight(-1000);
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

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif