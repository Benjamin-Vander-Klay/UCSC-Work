/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
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
#include "TowerSubHSM.h"
#include "TowerApproachSubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    ApproachTowerState,
    RealignBeaconLeftState,
    RealignBeaconRightState,
    BreakoutAndReturnState,

} TowerApproachSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "ApproachTowerState",
    "RealignBeaconLeftState",
    "RealignBeaconRightState",
    "BreakoutAndReturnState",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TowerApproachSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static TowerApproachSubHSMState_t PreviousState;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTowerApproachSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunTowerApproachSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
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
ES_Event RunTowerApproachSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TowerApproachSubHSMState_t nextState; // <- change type to correct enum
    uint8_t turnAgain = TRUE;
    ES_Tattle(); // trace call stack
    int8_t encoder_sum;
    ES_Event DriveEvent;

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                // now put the machine into the actual initial state
                nextState = ApproachTowerState;
                PreviousState = ApproachTowerState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ApproachTowerState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY: // *** maybe when we reset this will cause us to start moving when we dont want to... 
                    //B-Line the tower
                    Drive_Stop(BOTH); // reset any encoder stuff for now. // bvk 6pm 6/4 -likely unnecessary
                    Drive_Straight(DRIVE_HIGH); // go right to it
                    ES_Timer_InitTimer(BREAKOUTIMER, BREAKOUT_DURATION); // this is to try and prevent getting stuck oon stuff!
                    //                ThisEvent.EventType = ES_NO_EVENT;? perhaps'
                    //                    ES_Timer_StopTimer(TempTurnTimer);
                    break;
                case FLOOR_LIGHT_CHANGE: // absorb this? we cross center tape
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE: // drive straight and keep driving straight?   ** THIS MAY BE WEIRD. If we receive an event that says we see it we go here first...
                    Drive_Straight(DRIVE_HIGH); // go right to it
                    ThisEvent.EventType = ES_NO_EVENT; // stay here.. 
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE: // we lost it. Wiggle to realign
                    Drive_Stop(BOTH);
                    // Tank turn left a wiggle
                    // Tank turn right a wiggle an a half to check the right side
                    nextState = RealignBeaconLeftState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    //                case FIND_NEXT_TOWER: //  FIX ME and TEST ME!! For some reason im having this event in the loader
                    //                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    break;
                    // we have done nothin in 4 seconds 
                    //                case BREAKOUT:
                    //                  
                    //                    break;
                    // Front bumper responses handled in TowerSubHSM 
                case ES_EXIT:
                    // shouldn't impact the 
                    ES_Timer_StopTimer(BREAKOUTIMER); // stop the timer so when we exit this state we don't trigger it in other FSM's when it times out

                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case RealignBeaconLeftState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // start tank turning left and set timer for 200 ms?
                    // stop first? 
                    Drive_Tank_Turn_Left(DRIVE_LOW);
                    // timer is going to be a new, tower finding adjustment timer?
                    // or use the other ones fuck it reuse reduce recycl3e
                    ES_Timer_InitTimer(APPROACH_ADJUST_TIMER, APPROACH_ADJUST_LEFT);
                    //                                        ES_Timer_InitTimer(BREAKOUTIMER, BREAKOUT_DURATION);
                    // stop so we don't interrupt the search for the beacon
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    Drive_Stop(BOTH);
                    // adjusting worked, approach now
                    nextState = ApproachTowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT: // timeout on adjust left move to adjust right
                    if (ThisEvent.EventParam == APPROACH_ADJUST_TIMER) {
                        // tranisiton to adjust right
                        nextState = RealignBeaconRightState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    }
                    // don't worry abt setting no event, a timeout that does not belong to this FSM should not be altered here
                    break;
                case ES_EXIT:
                    //                    ES_Timer_StopTimer(APPROACH_ADJUST_TIMER);
                    break;

                default:
                    break; // end of realign beacon left internal switch
            }
            break;
        case RealignBeaconRightState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // start tank turning left and set timer for 200 ms?
                    // stop first? 
                    Drive_Tank_Turn_Right(DRIVE_LOW);
                    // timer is going to be a new, tower finding adjustment timer?
                    // or use the other ones fuck it reuse reduce recycl3e
                    ES_Timer_InitTimer(APPROACH_ADJUST_TIMER, APPROACH_ADJUST_RIGHT);

                    //                                        ES_Timer_InitTimer(BREAKOUTIMER, BREAKOUT_DURATION);
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    Drive_Stop(BOTH);
                    // adjusting worked, approach now
                    nextState = ApproachTowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT: // timeout on adjust right -- exit to find tape
                    if (ThisEvent.EventParam == APPROACH_ADJUST_TIMER) {
                        // tranisiton to beacon, and return a tower not detected event to leave
                        
                        nextState = ApproachTowerState; // will cause us to start driving forward when we dont want to? altho here we're going to 
                        // search for tape which is default drive straight. 
                        makeTransition = TRUE;
                        ThisEvent.EventType = FIND_NEXT_TOWER; // a separate event to be passed up so the top level HSM transitions to findTape state
                        
                    }
                    // don't worry abt setting no event, a timeout that does not belong to this FSM should not be altered here
                    break;
                case ES_EXIT:
                    // stop both timers so we don't cause unintended stuff in other FSM's
                    //                    ES_Timer_StopTimer(TempTurnTimer);
                    ES_Timer_StopTimer(BREAKOUTIMER); // already happens, but i'm being safe

                    break;

                case ES_NO_EVENT:
                default:
                    break; // end of Realign beacon right internal switch 
            }
            break;
        case BreakoutAndReturnState:
            // 4.5 second timer elapsed without reseting anythere. means we have to reset everywhere
            // tank turn left and then right and return
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turnAgain = TRUE; // only turn once
                    DriveEvent.EventType = PIVOT_TURN_LEFT_15;
                    PostEncoderService(DriveEvent);
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 1) {
                        if (turnAgain) {
                            turnAgain = FALSE;
                            DriveEvent.EventType = PIVOT_TURN_RIGHT_15;
                            PostEncoderService(DriveEvent);
                        } else { // exit
                            nextState = PreviousState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                    }
                    //                    makeTransition = TRUE;

                    ThisEvent.EventType = ES_NO_EVENT;

                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }



            break;
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTowerApproachSubHSM(EXIT_EVENT); // <- rename to your own Run function
        PreviousState = CurrentState;
        CurrentState = nextState;
        RunTowerApproachSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

