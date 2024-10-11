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
#include "CircleTowerSubHSM.h"
#include "TowerSubHSM.h"
#include "EncoderService.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

typedef enum {
    InitPSubState,
    TowerHitReverseState,
    ReverseArcState, // back pivot average case ~50 degrees ?
    ForwardAdvanceState, // advance ~ 4-5 inches. We will hit the tower if we hit the face earlier
    //    HitTower, //nvm
    ArcTurnAdvanceState, // pivot forward left to hit tower again ( or perhaps round corner)
    //    ReverseArcState, // reverse pivot  
    FreeFrontBumpers,
    FreeRearBumpers,

} CircleTowerSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "TowerHitReverseState",
    "ReverseArcState",
    "ForwardAdvance",
    "ArcTurnAdvanceState",
    "FreeFrontBumpers",
    "FreeRearBumpers",
};

#define BUMPER_STUCK_DURATION 4000 // 4 seconds for now

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

static CircleTowerSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static CircleTowerSubHSMState_t PreviousState;
static uint8_t MyPriority;



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
uint8_t InitCircleTowerSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunCircleTowerSubHSM(INIT_EVENT);
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
ES_Event RunCircleTowerSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    CircleTowerSubHSMState_t nextState; // <- change type to correct enum
    ES_Event DriveEvent;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = TowerHitReverseState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case TowerHitReverseState: // we are already reversing 
            switch (ThisEvent.EventType) {
                    //                case ES_ENTRY:
                    //                                        DriveEvent.EventType = REVERSE_TOWER;
                    //                                        PostEncoderService(DriveEvent);
                    //                    break;
                case ENCODER_DONE: // backed up desired amount. now turn desired angle pivot reverse turn 
                    nextState = ArcTurnAdvanceState; // changed to ArcTurnAdvanceState cuz too much rotation after deadbot
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                    // BUMPERS STUCK - FREE SELF BY advancing FOR 2 INCHES. MAYBE J 1? 
                    // here we are already reversing. need to advance
                case RR_PRESSED: // start breakout timer
                    ES_Timer_InitTimer(BREAKOUTIMER, BUMPER_STUCK_DURATION);
                    break;
                case RR_UNPRESSED: // stop breakout timer
                    ES_Timer_StopTimer(BREAKOUTIMER);
                    break;
                case RL_PRESSED: // start breakout timer
                    ES_Timer_InitTimer(BREAKOUTIMER, BUMPER_STUCK_DURATION);
                    break;

                case RL_UNPRESSED: // stop breakout timer
                    ES_Timer_StopTimer(BREAKOUTIMER);
                    break;
                case BREAKOUT: // go to breakout forward
                    nextState = FreeRearBumpers;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_EXIT: // stop timer so undefined shit doesn't happen and confuse us -- will 
                    ES_Timer_StopTimer(BREAKOUTIMER);
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case ReverseArcState: // < 90 deg
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = REVERSE_ARC_LEFT;
                    PostEncoderService(DriveEvent);
                    ES_Timer_InitTimer(BREAKOUTIMER, BUMPER_STUCK_DURATION);
                    break;
                case RR_PRESSED: // what if we hit back bumpers?
                    break;
                case RL_PRESSED: // BVK 11:55pm 6/5/2022 we get stuck trying to reverse in reverse arc state. adding this to free self
                    // go on to arc advance I suppose
                    nextState = ArcTurnAdvanceState; // rive event on entry  
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case FR_PRESSED:

                    break;

                case FL_PRESSED:

                    break;
                case ENCODER_DONE: // finished reverse arc, now arc advance forward or drive straight
                    nextState = ArcTurnAdvanceState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                case BREAKOUT: // go to breakout forward
                    nextState = FreeRearBumpers;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // stop timer so undefined shit doesn't happen and confuse us -- will 
                    ES_Timer_StopTimer(BREAKOUTIMER);
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case ArcTurnAdvanceState: // < 90 deg
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = FORWARD_ARC_LEFT;
                    PostEncoderService(DriveEvent);
                    ES_Timer_InitTimer(BREAKOUTIMER, BUMPER_STUCK_DURATION);
                    break;
                case RR_PRESSED: // what if we hit back bumpers?
                    break;
                case RL_PRESSED:
                    break;

                case FR_PRESSED: // what to do. reverse and advance again. 
                    nextState = ReverseArcState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    // Send drive event to encoder
                    DriveEvent.EventType = REVERSE_TOWER;
                    PostEncoderService(DriveEvent);
                    break;

                case FL_PRESSED:
                    nextState = ReverseArcState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    // Send drive event to encoder
                    DriveEvent.EventType = REVERSE_TOWER;
                    PostEncoderService(DriveEvent);

                    break;
                case ENCODER_DONE: // WE FINISHED BACKING UP WE NOW DRIVE FORWARD // testing w/0 for now // update: leave this by resetting encoder to repeat action cuz it stops if this not here
                    //                    nextState = TowerHitReverseState;
                    //                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    // Send drive event to encoder
                    //                    DriveEvent.EventType = REVERSE_TOWER;
                    //                    PostEncoderService(DriveEvent);
                    DriveEvent.EventType = FORWARD_ARC_LEFT;
                    PostEncoderService(DriveEvent);
                    break;
                case BREAKOUT: // go to breakout reverse - to freee front bumpers. 
                    nextState = FreeFrontBumpers;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // stop timer so undefined shit doesn't happen and confuse us -- will 
                    ES_Timer_StopTimer(BREAKOUTIMER);
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case FreeFrontBumpers: // front bumpers were pressed but never unpressed
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // start encoders to go just an inch or two reverse
                    DriveEvent.EventType = DRIVE_REVERSE_THREE_QTR;
                    PostEncoderService(DriveEvent);
                    break;
                case ENCODER_DONE:
                    // encoder finished adjustment to free self from the wall
                    // return to previous state. 
                    nextState = PreviousState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
            }
            break;

        case FreeRearBumpers: // rear bumpers were pressed but never unpressed
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    // start encoders to go just an inch or two forward
                    DriveEvent.EventType = DRIVE_FORWARD_QTR;
                    PostEncoderService(DriveEvent);
                    break;
                case ENCODER_DONE:
                    // encoder finished adjustment to free self from the wall
                    // return to previous state. 
                    nextState = PreviousState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
            }
            break;
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunCircleTowerSubHSM(EXIT_EVENT); // <- rename to your own Run function
        PreviousState = CurrentState;
        CurrentState = nextState;
        RunCircleTowerSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/