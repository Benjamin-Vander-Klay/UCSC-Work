/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopHSM.h"
#include "Bumpers_Gen_v1SubHSM.h"
#include "ActiveSearchSubHSM.h"
#include "FindTapeSubHSM.h"
#include "TowerSubHSM.h"
#include <stdio.h>
#include "LED.h"
#include "TowerScopeSubHSM.h"
#include "TowerApproachSubHSM.h"
#include "CircleTowerSubHSM.h"
#include "CorrectSideFoundSubHSM.h"
#include "DeadBotAvoidSubHSM.h"
#include "CorrectHoleFoundSubHSM.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define MIN_SPEC_OCLOCK 115000
#define It_Begins TRUE
typedef enum {
    InitPState,
    ActiveSearch,
    FindTape,
    TowerInSight,

} TopHSMState_t;

static const char *StateNames[] = {
    "InitPState",
    "ActiveSearch",
    "FindTape",
    "TowerInSight",
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine
   Example: char RunAway(uint_8 seconds);*/
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TopHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTopHSM(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTopHSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunTopHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TopHSMState_t nextState; // <- change type to correct enum 

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Pseudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                // Initialize all sub-state machines
                InitBumpers_GenSubHSM();
                InitActiveSearchSubHSM();
                InitFindTapeSubHSM();
                InitTowerSubHSM();
                InitTowerApproachSubHSM();
                //                InitTowerScopeSubHSM();
                InitCircleTowerSubHSM();
                InitCorrectSideFoundSubHSM();
                InitDeadBotAvoidSubHSM();
                InitCorrectHoleFoundSubHSM();

                // now put the machine into the actual initial state
                nextState = FindTape;
                //                nextState = ActiveSearch;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            }
            break;

        case ActiveSearch: // in the first state, replace this with correct names
            //            LED_SetBank(LED_BANK1, ST1_LED); 6/2/22 This dont even work  --Amber
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            //        ThisEvent = RunBumpers_GenSubHSM(ThisEvent);
#ifdef HAILMARY

            if (ThisEvent.EventType == BATTERY_CONNECTED) {
                if (It_Begins) { // only start timer once
                    ES_Timer_InitTimer(WHOLETTHEDOGSOUT, MIN_SPEC_OCLOCK);
                }
            }
#endif
            ThisEvent = RunActiveSearchSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case BEACON_WITHIN_DIGITAL_RANGE:
                    //When Beacon is Detected by Long Range Beacon Transition to TowerInSight
//                    Drive_Stop(BOTH); // this will reset the encoders to 0 and stop encoder done events from posting// bvk 6/6 1:10pm need to make the B-line to the tower more consistent from far away, and get off tape to do it
                    Drive_Straight(DRIVE_HIGH);
                    nextState = TowerInSight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT; // pass it to the tower active search?
                    break;
                case DF_NONE_DETECTED:
                    nextState = FindTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;
        case FindTape: // look for the tape!! (or beacon)
            //            LED_SetBank(LED_BANK1, ST2_LED); 6/2/22 This dont even work ---Amber
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
#ifdef HAILMARY

            if (ThisEvent.EventType == BATTERY_CONNECTED) {
                if (It_Begins) { // only start timer once
                    ES_Timer_InitTimer(WHOLETTHEDOGSOUT, MIN_SPEC_OCLOCK);
                }
            }
#endif
            ThisEvent = RunFindTapeSubHSM(ThisEvent); //-----------------------UNCOMMENT THIS!!!!!!!!!!!! 6/2/22 AMBER
            switch (ThisEvent.EventType) {
                case BEACON_WITHIN_DIGITAL_RANGE:
                    //When Beacon is Detected by Long Range Beacon Transition to TowerInSight
//                    Drive_Stop(BOTH); // bvk 6/6 1:10pm need to make the B-line to the tower more consistent from far away, and get off tape to do it
                    Drive_Straight(DRIVE_HIGH);
                    nextState = TowerInSight;
                    makeTransition = TRUE; //-----------------------UNCOMMENT THIS!!!!!!!!!!!! 6/2/22 AMBER -----------------------------------------
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    //        case FL_PRESSED:
                case FLOOR_LIGHT_CHANGE:
                    //Return to Active Search once timer Ends again
                    if (ThisEvent.EventParam) {
                        nextState = ActiveSearch;
                        makeTransition = TRUE; //-----------------------UNCOMMENT THIS!!!!!!!!!!!! 6/2/22 AMBER -----------------------------------------
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;
        case TowerInSight:
            //            LED_SetBank(LED_BANK1, ST3_LED); 6/2/22 This dont even work --Amber
            // we go into tower mode. 
#ifdef HAILMARY

            if (ThisEvent.EventType == BATTERY_CONNECTED) {
                if (It_Begins) { // only start timer once
                    ES_Timer_InitTimer(WHOLETTHEDOGSOUT, MIN_SPEC_OCLOCK);
                }
            }
#endif
            if(ThisEvent.EventType == ES_TIMERACTIVE){// throw this out. don't need it. alternatively have the timer post to simple servicer
                ThisEvent.EventType = ES_NO_EVENT;
            }
            ThisEvent = RunTowerSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case BEACON_WITHIN_DIGITAL_RANGE: // when we first enter tower in sight from another top level HSM
//                    Drive_Straight(DRIVE_HIGH); // idk why this is here, probably just from when we started the HSM. bvk 6pm 6/5
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
//                case BEACON_NOT_WITHIN_DIGITAL_RANGE: // bvk 3:40pm takin out because we are goin into find tape too esily?
//                    nextState = FindTape; // find tape is where we search for tape and or beacon. active search is where we are on tape
//                    makeTransition = TRUE;
//                    ThisEvent.EventType = ES_NO_EVENT;
//                    //No current Exit Conditions    
//                    break;
                case FIND_NEXT_TOWER: // exit condition 
                    Drive_Straight(DRIVE_HIGH);
                    nextState = FindTape; // find tape is where we search for tape and or beacon. active search is where we are on tape
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;
            //Will be getting rid of this event
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTopHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTopHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
