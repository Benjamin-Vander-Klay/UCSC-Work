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
#include "SimpleFunctionService.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BATTERY_DISCONNECT_THRESHOLD 175
#define BACKUP_TIMER_FREQ 3 // reset the backup timer to elapse if 3 times the debounce timer duration has elapsed without the debounce timer triggering

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
static uint8_t days_until_summer = 8;
static int8_t Kobe = FALSE;
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
uint8_t InitSimpleFunctionService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    ES_Timer_InitTimer(MidAdjustTimer, ACTIVE_DURATION);
    ES_Timer_InitTimer(DebounceTimer, DEBOUNCE_DURATION);
    //    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
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
uint8_t PostSimpleFunctionService(ES_Event ThisEvent) {
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
ES_Event RunSimpleFunctionService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    //        static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    //        ES_EventTyp_t curEvent;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    switch (ThisEvent.EventType) {
        case ES_INIT:
            // No hardware initialization or single time setups, those
            // go in the init function above.
            //
            // This section is used to reset service for some reason
            break;

        case ES_TIMEOUT:
            if (ThisEvent.EventParam == MidAdjustTimer) {
                ES_Timer_InitTimer(MidAdjustTimer, ACTIVE_DURATION);
//                This is reset by the state machine JEEEEEEEEEZE ? 6.5.22 1:30 trying to fix getting stuck in midadjust rotate. 
                        ReturnEvent.EventType = MAR_END;
                PostTopHSM(ReturnEvent);
            }
            //Run When Time Out occurs 
            if ((ThisEvent.EventParam == DebounceTimer)) {
                ES_Timer_InitTimer(DebounceTimer, DEBOUNCE_DURATION);
                ES_Timer_InitTimer(DeboundTimerBackup, DEBOUNCE_DURATION * BACKUP_TIMER_FREQ);
                //Debouncing Period for Digital Inputs 
                CheckFLBumper();
                CheckFRBumper();
                CheckRLBumper();
                CheckRRBumper();
            }
            if (ThisEvent.EventParam == TempTurnTimer) {
                //            ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                ReturnEvent.EventType = FAKE_ENCODER_EVENT;
                PostTopHSM(ReturnEvent);
            }
            if (ThisEvent.EventParam == DeboundTimerBackup) { // might as well check the bumpers I guess... 
                ES_Timer_InitTimer(DebounceTimer, DEBOUNCE_DURATION);
                ES_Timer_InitTimer(DeboundTimerBackup, DEBOUNCE_DURATION * BACKUP_TIMER_FREQ); // if we're being safe might as well be very safe. 
                //                ReturnEvent.EventType = 
                CheckFLBumper();
                CheckFRBumper();
                CheckRLBumper();
                CheckRRBumper();

            } // IDK why we did this twice man. bvk 9:30 6/5/2022 
//            if (ThisEvent.EventParam == SolenoidTimer) {
//                IO_PortsClearPortBits(SOL_DRIVER_PORT, SOL_DRIVER_PIN);
//                printf("\r\n solenoid timer ended");
//            }
            // BVK 2:35pm 5/31/22 else if?
            //            if(ThisEvent.EventParam == TowerDitchTimer){ // to abandone tower?

            //            }
            if (ThisEvent.EventParam == SolenoidTimer) { // 50ms later we turn off solenoid
                IO_PortsClearPortBits(SOL_DRIVER_PORT, SOL_DRIVER_PIN);
                printf("\r\n solenoid timer ended");
                // SEND CONFIRMATION TO HSM
                //                ReturnEvent.EventType = SHOT_BALL;
                //                PostTopHSM(ReturnEvent);
                ES_Timer_InitTimer(SolenoidWaitTimer, SOL_BTN_MS);

                // keep this for now, but likely want to put it when the solenoid starts firing. 
                ES_Timer_InitTimer(STOP_WHILE_SHOOT, STOP_AND_SHOOT_DURATION);
                // 5:42pm bvk - take this out so we only deliver shot ball and shoot the next when both
                // the solenoid high time and the minimum duration between shots has elapsed. 550ms total (maybe )

                //                ReturnEvent.EventType = SHOT_BALL;
                //                PostTopHSM(ReturnEvent);
                //                PostTopHSM();

            }
            
            if (ThisEvent.EventParam == STOP_WHILE_SHOOT) {
                // we've waited 2 seconds. send event to move again
                ReturnEvent.EventType = SHOT_BALL_MOVE_ON;
                PostTopHSM(ReturnEvent);
            }
            if (ThisEvent.EventParam == SolenoidWaitTimer) {
                if (Kobe) {
                    printf("\r\n\r\n*******\r\nKOBE\r\n*******");
                    //                    ES_Timer_InitTimer(SolenoidTimer, SOL_TIME_MS); // reset this bad boy
                    ES_Timer_InitTimer(WHOLETTHEDOGSOUT, SOL_BTN_MS); // mandatory cooldown. reuse reduce recycle
                }
                ReturnEvent.EventType = SHOT_BALL;
                PostTopHSM(ReturnEvent);

            }
            if (ThisEvent.EventParam == BREAKOUTIMER) {
                ReturnEvent.EventType = BREAKOUT;
                PostTopHSM(ReturnEvent);
            }
            if (ThisEvent.EventParam == FINDHOLETIMEOUTTIMER){
                ReturnEvent.EventType = FINDHOLETIMEOUT;
                PostTopHSM(ReturnEvent);
                
            }
#ifdef HAILMARY
            if (ThisEvent.EventParam == WHOLETTHEDOGSOUT) { // say your prayers
                Kobe = TRUE; // all systems ready
                if (Solenoid_Ready()) {
                    // fire solenoid and reset timer
                    if (days_until_summer > 0) {
                        days_until_summer--;
                        Solenoid_Fire();
                    } else {
                        ES_Timer_StopTimer(WHOLETTHEDOGSOUT); // that's it we're out
                    }

                } else {
                    ES_Timer_InitTimer(WHOLETTHEDOGSOUT, SOL_BTN_MS); // might as well wait a little longer
                }

            }
#endif  
            break;
        case ES_TIMERACTIVE:

        case ES_TIMERSTOPPED:
            break;
#ifdef SIMPLESERVICE_TEST     // keep this as is for test harness      
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

