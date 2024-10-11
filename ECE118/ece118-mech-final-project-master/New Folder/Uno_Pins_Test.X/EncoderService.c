/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "EncoderService.h"
#include <stdio.h>
#include "Motor_Driver.h"



// TICK MACROS FOR PREDETERMINED DRIVES // EXPERIMENTALLY FOUND ->WILL REQUIRE EDITING 
#define FULL_ROT 508 
#define HALF_ROT 254
#define DEG_300 1750 
#define DEG_90 650

#define OFF 0

// SPEEDS FOR THESE PREDETERMINED DRIVE 
// Range is ~300-900. Below 300 and not sure will turn
#define FULL_ROT_SPEED DRIVE_HIGH
#define HALF_ROT_SPEED DRIVE_HIGH
#define DEG_300_SPEED DRIVE_MED
#define DEG_90_SPEED DRIVE_MED

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
// Un-Comment To Test
//#define ENCODERSERVICE_TEST
//#define BATTERY_DISCONNECT_THRESHOLD 175

// mask the MSB 8 to be the left number of ticks and the left to be the
// Done with 



// so we can use the IO macros
#ifdef ENCODERSERVICE_TEST
//#include <xc.h>
//#include "IO_Ports.h"
#endif




/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;
// t
static int tick_count_right;
static int tick_count_left;
// the mark at which we send an event back to the HSM
static int tick_goal_right;
static int tick_goal_left;
// so that we only go over once, and can still count if we want to? eventually?
static int tick_goal_done_lt;
static int tick_goal_done_rt;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitEncoderService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
<<<<<<< HEAD
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        printf("\r\nDELETE ---Encoder Service Launched Successfully");
        return TRUE;
    } else {
        printf("\r\nDELETE ---Encoder Service Failed to Launch Successfully");
=======

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
>>>>>>> d429440fe5571abb86d586b13aa2bb4a0a52513a
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostEncoderService(ES_Event ThisEvent) {
    //    printf("\r\nPosted to the service"); // shits itself when we do this?
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunEncoderService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    switch (ThisEvent.EventType) {
        case ES_INIT:
            // No hardware initialization or single time setups, those
            // go in the init function above.
            //
            // This section is used to reset service for some reason
            break;

            // can either set number of ticks in event parameters or use predefined macros
            // lol or both. We could do back up ___ or turn Right ___
            // as well as set ticks -> we only have ...
            // nvm we have 16 bits. 8 for each right. 8 on left, 8 on right. 
        case DRIVE_FORWARD_FULL:
            // Set tick goals
            tick_goal_left = FULL_ROT;
            tick_goal_right = FULL_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(FULL_ROT_SPEED);
            // Let SM know?
            ReturnEvent.EventType = DRIVING;
            ReturnEvent.EventParam = BOTH_TICK;
            break;
        case DRIVE_FORWARD_HALF:
            // Set tick goals
            tick_goal_left = HALF_ROT;
            tick_goal_right = HALF_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(HALF_ROT_SPEED);
            // Let SM know?
            ReturnEvent.EventType = DRIVING;
            ReturnEvent.EventParam = BOTH_TICK;
            break;
        case DRIVE_REVERSE_FULL:
            // Set tick goals
            tick_goal_left = FULL_ROT;
            tick_goal_right = FULL_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-FULL_ROT_SPEED);
            // Let SM know?
            ReturnEvent.EventType = DRIVING;
            ReturnEvent.EventParam = BOTH_TICK;
            break;
        case DRIVE_REVERSE_HALF:
            // Set tick goals
            tick_goal_left = HALF_ROT;
            tick_goal_right = HALF_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-HALF_ROT_SPEED);
            // Let SM know?
            ReturnEvent.EventType = DRIVING;
            ReturnEvent.EventParam = BOTH_TICK;
            break;
        case TANK_TURN_LEFT_90:
            // Set tick goals
            tick_goal_left = DEG_90;
            tick_goal_right = DEG_90;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Left(DEG_90_SPEED);
            // Let SM know?
            ReturnEvent.EventType = DRIVING;
            ReturnEvent.EventParam = BOTH_TICK;
            break;
        case PIVOT_TURN_LEFT_300:
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_300;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Left(DEG_90_SPEED);
            // Let SM know?
            ReturnEvent.EventType = DRIVING;
            ReturnEvent.EventParam = BOTH_TICK;
            break;

        case ENCODER_SET_TICKS: // NOT USED?
            // when setting the same 
            tick_goal_left = ThisEvent.EventParam * ENCODER_SCALER;
            tick_goal_right = ThisEvent.EventParam * ENCODER_SCALER;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;

            break;

        case ENCODER_TICK:
            if (ThisEvent.EventParam & RIGHT_TICK == RIGHT_TICK) { // right tick occured
                printf("we ticking right");
                tick_count_right++;
                // when we hit goal, let the HSM know!
                if (tick_count_right > tick_goal_right && tick_goal_done_rt == FALSE) {
                    // post event ENCODER_DONE? to HSM?
                    tick_goal_done_rt = TRUE;
                    // Turn off motors?        
                    Drive_Stop(RIGHT);
                    ReturnEvent.EventType = ENCODER_DONE;
                    ReturnEvent.EventParam = RIGHT_TICK;
                    //                PostHSM(ReturnEvent);
                }

            } else if (ThisEvent.EventParam & LEFT_TICK == LEFT_TICK) { // left tick occured
                printf("we ticking left");
                tick_count_right++;
                // when we hit goal, let the HSM know!
                if (tick_count_left > tick_goal_left && tick_goal_done_lt == FALSE) {
                    // post event ENCODER_DONE? to HSM?
                    tick_goal_done_lt = TRUE;
                    // Turn off motors?
                    Drive_Stop(LEFT);
                    ReturnEvent.EventType = ENCODER_DONE;
                    ReturnEvent.EventParam = LEFT_TICK;
                    //                PostHSM(ReturnEvent);
                }
            }
            if (curEvent != lastEvent) { // check for change from last time
                ReturnEvent.EventType = curEvent;
                ReturnEvent.EventParam = batVoltage;
                lastEvent = curEvent; // update history
#ifndef ENODERSERVICE_TEST           // keep this as is for test harness
                PostEncoderService(ReturnEvent);
#else
                PostEncoderService(ReturnEvent);
#endif   
            }
            break;





#ifdef ENCODERSERVICE_TEST     // keep this as is for test harness      
        default:
            printf("\r\nEvent: %s\tParam: 0x%X",
                    EventNames[ThisEvent.EventType], ThisEvent.EventParam);
            break;
#endif
    }

    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

