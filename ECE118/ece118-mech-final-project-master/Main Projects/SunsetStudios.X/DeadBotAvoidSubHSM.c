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
#include "TowerSubHSM.h"
#include "DeadBotAvoidSubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitDeadBotAvoidSubState,
    ReverseState,
    PositioningSearchState,
    SearchBeaconForwardState,
    SearchBeaconBackwardState,
    SearchBeaconForwardState2,
    SearchBeaconBackwardState2,
    ExitNoBeaconState,
} DeadBotAvoidSubHSMState_t;

static const char *StateNames[] = {
    "InitDeadBotAvoidSubState",
    "ReverseState",
    "PositioningSearchState",
    "SearchBeaconForwardState",
    "SearchBeaconBackwardState",
    "SearchBeaconForwardState2",
    "SearchBeaconBackwardState2",
    "ExitNoBeaconState",
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

static DeadBotAvoidSubHSMState_t CurrentState = InitDeadBotAvoidSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static uint8_t analogBeaconDetectedBefore = FALSE;

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
uint8_t InitDeadBotAvoidSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitDeadBotAvoidSubState;
    returnEvent = RunDeadBotAvoidSubHSM(INIT_EVENT);
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
ES_Event RunDeadBotAvoidSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    DeadBotAvoidSubHSMState_t nextState; // <- change type to correct enum
    ES_Event DriveEvent;
    static int8_t encoder_sum;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitDeadBotAvoidSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = ReverseState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ReverseState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    DriveEvent.EventType = REVERSE_TOWER;
                    //                    PostEncoderService(DriveEvent);
                    analogBeaconDetectedBefore = FALSE;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE: //                ////////////////////////////////////// BEACON_WITHIN_ANALOG_RANGE < -- ? EXIt condition?? 
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 3) { // both wheels finished turning
                        encoder_sum = 0; // reset encoder sum
                        nextState = PositioningSearchState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case PositioningSearchState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = TANK_TURN_RIGHT_90;
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_ANALOG_RANGE: //////////////////////////////////// BEACON_WITHIN_ANALOG_RANGE < - exit condition??? 
                    ThisEvent.EventType = ES_NO_EVENT;
                    analogBeaconDetectedBefore = TRUE;
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 3) { // both wheels finished turning
                        encoder_sum = 0; // reset encoder sum
                        if (analogBeaconDetectedBefore == TRUE) {
                            nextState = ReverseState; // reset FSM 
                            makeTransition = TRUE;
                            ThisEvent.EventType = BEACON_WITHIN_ANALOG_RANGE; // exit this FSM
                            analogBeaconDetectedBefore = FALSE;
                        } else {
                            nextState = SearchBeaconForwardState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }

                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }


                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case SearchBeaconForwardState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = DRIVE_FORWARD_QTR;
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FL_PRESSED:
                    nextState = SearchBeaconBackwardState; // going reverse after hitting back cuz dont no if rotating or reversing // BVK 12pm 6/6/22 need to react at least somehow to bumper events. can correct and return to original movement or j do thuis
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FR_PRESSED:
                    nextState = SearchBeaconBackwardState; // going reverse after hitting back cuz dont no if rotating or reversing // BVK 12pm 6/6/22 need to react at least somehow to bumper events. can correct and return to original movement or j do thuis
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE:
                    nextState = ReverseState;
                    makeTransition = TRUE;
                    //                        ThisEvent.EventType = FOUND_BEACON;
                    break;
                case FLOOR_LIGHT_CHANGE: // what if the bottom front tape sensors reads tape? go backwards dummy!
                    if (ThisEvent.EventParam == E_TS_MASK) {
                        nextState = SearchBeaconBackwardState;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 3) { // both wheels finished turning
                        encoder_sum = 0; // reset encoder sum
                        nextState = SearchBeaconBackwardState;
                        makeTransition = TRUE;

                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case SearchBeaconBackwardState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = DRIVE_REVERSE_HALF;
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE:
                    nextState = ReverseState;
                    makeTransition = TRUE;
                    //                                            ThisEvent.EventType = FOUND_BEACON; // we need this too? bvk 6/6 12 noon // BEACON_WITHIN_ANALOG_RANGE triggers leaving deadbot 
                    break;
                case FLOOR_LIGHT_CHANGE: // what if the bottom front tape sensors reads tape? go forwards! dummy!
                    if (ThisEvent.EventParam == B_TS_MASK) {
                        nextState = SearchBeaconForwardState2;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RL_PRESSED:
                    nextState = SearchBeaconForwardState; // going forward after hitting back cuz dont no if rotating or forwarding // BVK 12pm 6/6/22 need to react at least somehow to bumper events. can correct and return to original movement or j do thuis
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RR_PRESSED:
                    nextState = SearchBeaconForwardState; // going forward after hitting back cuz dont no if rotating or forwarding // BVK 12pm 6/6/22 need to react at least somehow to bumper events. can correct and return to original movement or j do thuis
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 3) { // both wheels finished turning
                        encoder_sum = 0; // reset encoder sum
                        nextState = SearchBeaconForwardState2;
                        makeTransition = TRUE;
                    }

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case SearchBeaconForwardState2: // SECOND TIME IT GOES FORWARD
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = DRIVE_FORWARD_FULL;
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FL_PRESSED:
                    nextState = SearchBeaconBackwardState2; // going reverse after hitting back cuz dont no if rotating or reversing // BVK 12pm 6/6/22 need to react at least somehow to bumper events. can correct and return to original movement or j do thuis
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FR_PRESSED:
                    nextState = SearchBeaconBackwardState2; // going reverse after hitting back cuz dont no if rotating or reversing // BVK 12pm 6/6/22 need to react at least somehow to bumper events. can correct and return to original movement or j do thuis
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE:
                    nextState = ReverseState; // back to initial state of this FSM
                    makeTransition = TRUE;
                    //                        ThisEvent.EventType = FOUND_BEACON; // don't change event. 
                    break;
                case FLOOR_LIGHT_CHANGE: // what if the bottom front tape sensors reads tape? go backwards dummy!
                    if (ThisEvent.EventParam == E_TS_MASK) {
                        nextState = SearchBeaconBackwardState2;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 3) { // both wheels finished turning
                        encoder_sum = 0; // reset encoder sum
                        nextState = SearchBeaconBackwardState2;
                        makeTransition = TRUE;
                    }

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case SearchBeaconBackwardState2: // SECOND TIME IT GOES BACKWARD
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = DRIVE_REVERSE_FULL_PLUS;
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE:
                    nextState = ReverseState;
                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = FOUND_BEACON; // we need this ! was commented! 12pm bvk BEACON_WITHIN_ANALOG_RANGE

                    break;
                case RL_PRESSED:
                    nextState = SearchBeaconForwardState2; // going forward after hitting back cuz dont no if rotating or forwarding // wtf does this mean? we need to react to bumper events!
                    makeTransition = TRUE;
                    //                        ThisEvent.EventType = FOUND_BEACON;
                    break;
                case RR_PRESSED:
                    nextState = SearchBeaconForwardState2; // going forward after hitting back cuz dont no if rotating or forwarding
                    makeTransition = TRUE;
                    //                        ThisEvent.EventType = FOUND_BEACON;
                    break;
                case FLOOR_LIGHT_CHANGE: // what if the bottom front tape sensors reads tape? go forwards! dummy!
                    if (ThisEvent.EventParam == B_TS_MASK) {
                        nextState = FIND_NEXT_TOWER;
                        makeTransition = TRUE;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam;
                    if (encoder_sum >= 3) { // both wheels finished turning
                        encoder_sum = 0; // reset encoder sum
                        nextState = ReverseState;
                        makeTransition = TRUE;

                    }

                    ThisEvent.EventType = FIND_NEXT_TOWER;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case ExitNoBeaconState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    nextState = ReverseState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = FIND_NEXT_TOWER;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunDeadBotAvoidSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunDeadBotAvoidSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

