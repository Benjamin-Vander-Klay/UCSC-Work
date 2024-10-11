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
#include "TopHSM.h"
#include "CorrectHoleFoundSubHSM.h"
#include "Tape_Sensors.h"
#include "Solenoid_Driver.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    FindWhiteTower,
    ScootRight,
    SearchForward,
    SearchBackward,
    //    GoCloserLeft,
    //    GoCloserRight,

    //    RearLostTower,
    //    BothDetectBlack,
    //    BothDetectWhite,
    //    ConfirmTapeFound,
    //    DetectedOpenAirReverse,
    //    DetectedWhiteAfterOpenAir,
} CorrectHoleFoundSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "FindWhiteTower",
    "ScootRight",
    "SearchForward",
    "SearchBackward",
    //    "GoCloserLeft",
    //    "GoCloserRight",

    //    "RearLostTower",
    //    "BothDetectBlack",
    //    "BothDetectWhite",
    //    "ConfirmTapeFound",
    //    "DetectedOpenAirReverse",
    //    "DetectedWhiteAfterOpenAir",
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

static CorrectHoleFoundSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
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
uint8_t InitCorrectHoleFoundSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunCorrectHoleFoundSubHSM(INIT_EVENT);
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
ES_Event RunCorrectHoleFoundSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    static int8_t encoder_sum, square_up_complete;
    CorrectHoleFoundSubHSMState_t nextState; // <- change type to correct enum
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
                nextState = SearchBackward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
//                DriveEvent.EventType = DRIVE_REVERSE_QTR; // just go back another inch
//                PostEncoderService(DriveEvent);
            }
            break;
            //Amber -- Using this state to Advance Forward
            //--Exit When Both Detect Black OR Exit if the Rear Reads Black and the Front Reads white 
        case FindWhiteTower: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //Align With Tower Wall
                    Drive_Stop(BOTH);
                    DriveEvent.EventType = DRIVE_REVERSE_THREE_QTR; //Originally Had at Half... bvk 6.6.22 2pm was drive forward Qtr. but we still keep going too far forward so here we are
                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case DW_DETECTED:
                    if (ThisEvent.EventParam == TOWER_TAPE_REAR) { // just rear reads blck --> front = 1 + mid = 2 = 3 compared to binary 011
                        nextState = SearchBackward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        // BVK 11:41pm we go too far forward. maybe if this is going backwards a little and then forwards we'll get a better shot
                        DriveEvent.EventType = DRIVE_REVERSE_QTR; // just go back another inch
                        PostEncoderService(DriveEvent);
                    } else if (ThisEvent.EventParam == TOWER_TAPE_FRONT) { // just front reads black .. .// either on front edge of tower, or front edge of tape --> mid = 2 + rear = 4 = 110
                        nextState = SearchForward; // 
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        // BVK 11:41pm we go too far forward. maybe if this is going backwards a little and then forwards we'll get a better shot
                        DriveEvent.EventType = DRIVE_FORWARD_QTR; // BVk 2pm 6.6.22. changed from 
                        PostEncoderService(DriveEvent);
                    } else if (ThisEvent.EventParam == TOWER_TAPE_MID) { // W D W shut the ball!!!
                        //                        nextState = FindWhiteTower; // 
                        //                        makeTransition = TRUE;
                        Drive_Stop(BOTH);
                        ThisEvent.EventType = FOUND_HOLE;

                    } else { // they both read back. could be far off tower or tape. hard to say  
                        //                        nextState = SearchForward;
                        //                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        Drive_Stop(BOTH);
                    }
                    break;
                case LW_DETECTED:
                    //                    nextState = GoCloserLeft; // entry encoder event in goCloserLeft Change to correct state
                    //                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    Drive_Stop(BOTH);
                    break;
                case FL_PRESSED:
                    nextState = ScootRight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TW_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TW_NOT_DETECTED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    Drive_Stop(BOTH);
                    nextState = ScootRight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case ScootRight: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //Align With Tower Wall
                    DriveEvent.EventType = SCOOT_RIGHT; //Originally Had at Half
                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RL_PRESSED:
                    nextState = FindWhiteTower;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case DW_DETECTED:
                    if (ThisEvent.EventParam == TOWER_TAPE_REAR) { // just rear reads blck --> front = 1 + mid = 2 = 3 compared to binary 011
                        nextState = SearchForward; // entry encoder event in scoot right
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        DriveEvent.EventType = DRIVE_FORWARD_THREE_QTR; // originally half. we may want to change it up. maybe we only go 2 inches more and after that we transition
                        PostEncoderService(DriveEvent);
                    } else if (ThisEvent.EventParam == TOWER_TAPE_FRONT) { // just front reads black .. .// either on front edge of tower, or front edge of tape --> mid = 2 + rear = 4 = 110
                        nextState = SearchForward; // 
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        DriveEvent.EventType = DRIVE_FORWARD_THREE_QTR; // originally half. we may want to change it up. maybe we only go 2 inches more and after that we transition
                        PostEncoderService(DriveEvent);
                    } else if (ThisEvent.EventParam == TOWER_TAPE_MID) { // W D W shut the ball!!!
                        Drive_Stop(BOTH); // stop bc we are aligned!
                        nextState = FindWhiteTower; // reset to initial state
                        makeTransition = TRUE;
                        ThisEvent.EventType = FOUND_HOLE;
                    } else { // they both read back. could be far off tower or tape. hard to say  
                        //                        nextState = SearchForward;
                        //                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        Drive_Stop(BOTH);
                    }
                    break;
                case ENCODER_DONE:
                    nextState = FindWhiteTower;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case SearchBackward:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    DriveEvent.EventType = DRIVE_REVERSE_THREE_QTR; //Originally Had at Half
                    //                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case DW_DETECTED:
                    //                    //Both Tape Sensors Detect Tape
                    //                    if (ThisEvent.EventParam == TOWER_TAPE_REAR) { // just rear reads blck --> front = 1 + mid = 2 = 3 compared to binary 011
                    //                        nextState = SearchForward; // entry encoder event in scoot right
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                    } else if (ThisEvent.EventParam == TOWER_TAPE_FRONT) { // just front reads black .. .// either on front edge of tower, or front edge of tape --> mid = 2 + rear = 4 = 110
                    //                        nextState = SearchForward; // 
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                    } else 
                    if (ThisEvent.EventParam == TOWER_TAPE_MID) { // W D W shut the ball!!!
                        Drive_Stop(BOTH);
//                        nextState = SearchBackward; // 
//                        makeTransition = TRUE;
                        ThisEvent.EventType = FOUND_HOLE;
                    } else if (ThisEvent.EventParam == TOWER_TAPE_ALL) { // all black, go forward again, silly
                        nextState = SearchForward; // reset FSM
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        DriveEvent.EventType = DRIVE_FORWARD_THREE_QTR; // originally half. we may want to change it up. maybe we only go 2 inches more and after that we transition
                        PostEncoderService(DriveEvent);
                    } else if (ThisEvent.EventParam == DDW) { // we see Dark in the REAR and in the Center -> go another inch and if it is the Tape-> gucci. if we see air, we go forwards. if encoder out, we go forwards
                        DriveEvent.EventType = DRIVE_REVERSE_EIGHTH;
                        PostEncoderService(DriveEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam == WDD) {
                        nextState = SearchForward;
                        makeTransition = TRUE;
                        DriveEvent.EventType = DRIVE_FORWARD_EIGHTH;
                        PostEncoderService(DriveEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam == TOWER_TAPE_ALL_WHITE) { // reset encoder for another 2 inches
                        DriveEvent.EventType = DRIVE_REVERSE_FULL; // if on the front corner we need to go all the way back 
                        PostEncoderService(DriveEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else { // they both read back. could be far off tower or tape. hard to say  
                        //                        nextState = SearchForward;
                        //                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        Drive_Stop(BOTH);
                    }
                    break;
                case ENCODER_DONE:
                    //Keep Inching Forward
                    nextState = SearchForward; // 
                    makeTransition = TRUE;
                    DriveEvent.EventType = DRIVE_FORWARD_THREE_QTR; // originally half. we may want to change it up. maybe we only go 2 inches more and after that we transition
                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RL_PRESSED:
                    // resetting encoder event to adjust very slightly from collision.
                    //                    nextState = SearchForward; // keep getting stuck in bumper loops right next to the tower
                    //                    makeTransition = TRUE;
                    //                    DriveEvent.EventType = DRIVE_FORWARD_QTR;
                    Drive_Stop(BOTH); // give it a few microseconds to stop. 
                    DriveEvent.EventType = PIVOT_TURN_LEFT_10; // stay in this state but adjust j a lil. DECREASED FROM 15 TO 10 3:20PM BVK 6/6/2022
                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case SearchForward: // in the first state, replace this with correct names This is Assuming We start off with Both Tapes Reading White
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //                    DriveEvent.EventType = DRIVE_FORWARD_THREE_QTR; //Originally Had at Half
                    //                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case DW_DETECTED:
                    //Both Tape Sensors Detect Tape
                    if (ThisEvent.EventParam == TOWER_TAPE_MID) { // W D W shut the ball!!!
                        Drive_Stop(BOTH);
                        nextState = FindWhiteTower; // reset FSM
                        makeTransition = TRUE;
                        ThisEvent.EventType = FOUND_HOLE;
                    } else if (ThisEvent.EventParam == TOWER_TAPE_ALL) { // sees all black
                        nextState = SearchBackward; // reset FSM
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        DriveEvent.EventType = DRIVE_REVERSE_FULL; // originally half. we may want to change it up. maybe we only go 2 inches more and after that we transition
                        PostEncoderService(DriveEvent);
                        //                    } else if (ThisEvent.EventParam == WDD) { // we see Dark in the front and in the Center -> go another inch and if it is the Tape-> gucci. if we see air, we go backwards. if encoder out, we go backwards
                        //                        DriveEvent.EventType = DRIVE_FORWARD_EIGHTH;
                        //                        PostEncoderService(DriveEvent);
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam == DDW) { // we see Dark in the REAR and in the Center -> go another inch and if it is the Tape-> gucci. if we see air, we go forwards. if encoder out, we go forwards
                        DriveEvent.EventType = DRIVE_REVERSE_EIGHTH;
                        PostEncoderService(DriveEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                        nextState = SearchBackward;
                        makeTransition = TRUE;
                    } else if (ThisEvent.EventParam == WDD) {
                        DriveEvent.EventType = DRIVE_FORWARD_EIGHTH;
                        PostEncoderService(DriveEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam == TOWER_TAPE_ALL_WHITE) { // reset encoder for another 2 inches
                        DriveEvent.EventType = DRIVE_FORWARD_FULL; // if on the front corner we need to go all the way back 
                        PostEncoderService(DriveEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                    } else if(ThisEvent.EventParam == )    
                    } else { // they both read back. could be far off tower or tape. hard to say  
                        //                        nextState = SearchForward;
                        //                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        Drive_Stop(BOTH);
                    }
                    break;
                case ENCODER_DONE:
                    //Keep Inching Forward
                    nextState = SearchBackward; // 
                    makeTransition = TRUE;
                    DriveEvent.EventType = DRIVE_REVERSE_THREE_QTR; // originally half. we may want to change it up. maybe we only go 2 inches more and after that we transition
                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FL_PRESSED:
                    // resetting encoder event to adjust very slightly from collision.
                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_10; // stay in this state but adjust j a lil
                    PostEncoderService(DriveEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            //        case GoCloserLeft:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    //Align With Tower Wall
            //                    DriveEvent.EventType = SCOOT_LEFT; //Originally Had at Half
            //                    PostEncoderService(DriveEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case DW_DETECTED:
            //                    ThisEvent.EventType = ES_NO_EVENT; //DELETE ME LATER PLS FIX ME -- i thin u r staying here
            //                    break;
            //                case LW_DETECTED:
            //                    nextState = SearchForward;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    //                    Drive_Stop(BOTH);
            //                    break;
            //                case FL_PRESSED:
            //                    nextState = GoCloserRight;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ENCODER_DONE:
            //                    nextState = GoCloserRight;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //        case GoCloserRight:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    //Align With Tower Wall
            //                    DriveEvent.EventType = SCOOT_RIGHT; //Originally Had at Half
            //                    PostEncoderService(DriveEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case RL_PRESSED:
            //                    nextState = SearchForward;
            //                    makeTransition = TRUE;
            //                    Drive_Stop(BOTH);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case LW_DETECTED:
            //                    nextState = SearchForward;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    //                    Drive_Stop(BOTH);
            //                    break;
            //                case ENCODER_DONE:
            //                    nextState = SearchForward;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;

            //        case RearLostTower: // For Use when The Back Tape Sensor Reads Black first... This will occur if the back of the bot is not aligned with tower
            //            //---Not Currently In Use, can be implemented if it becomes an issue
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    DriveEvent.EventType = SCOOT_LEFT;
            //                    PostEncoderService(DriveEvent);
            //                    //                    ThisEvent.EventType = ES_NO_EVENT; // perhaps. 
            //                    break;
            //                case ENCODER_DONE:
            //                    nextState = SearchForward;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                    //                case TW_NOT_DETECTED:
            //                    //                    nextState = SearchForward;
            //                    //                    makeTransition = TRUE;
            //                    //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //        case BothDetectBlack: // in the first state, replace this with correct names
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    DriveEvent.EventType = DRIVE_FORWARD_HALF; //Originally Had at QTR   // half for now? 
            //                    PostEncoderService(DriveEvent);
            //                    //                    ThisEvent.EventType = ES_NO_EVENT; // perhaps. 
            //                    break;
            //                case LW_DETECTED: //Both Detected White So we know that the black we detected is the Tape and Not Negative Space 
            //                    nextState = BothDetectWhite;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                    //Bot did not detect White in Time
            //                case ENCODER_DONE:
            //                    nextState = DetectedOpenAirReverse;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    //                    DriveEvent.EventType = DRIVE_REVERSE_QTR;
            //                    //                    PostEncoderService(DriveEvent); //Don't drive any more little one
            //                    break;
            //                    //                case TW_NOT_DETECTED:
            //                    //                    nextState = SearchForward;
            //                    //                    makeTransition = TRUE;
            //                    //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //        case BothDetectWhite: // in the first state, replace this with correct names
            //            switch (ThisEvent.EventType) {
            //                    //Will Exit State Once Both Tape Sensors Detect Black.
            //                    //Now that the Tape Sensor detects White again
            //                    //we know that the last dark event was for tape 
            //                case ES_ENTRY:
            //                    DriveEvent.EventType = DRIVE_REVERSE_HALF; // 4ppm changed to half 
            //                    PostEncoderService(DriveEvent);
            //                    //                    ThisEvent.EventType = ES_NO_EVENT; // perhaps. 
            //                    break;
            //                case DW_DETECTED:
            //                    if (ThisEvent.EventParam == TOWER_TAPE_BOTH) {
            //                        nextState = ConfirmTapeFound;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case ENCODER_DONE:
            //                    DriveEvent.EventType = DRIVE_REVERSE_HALF; // 4ppm changed to half 
            //                    PostEncoderService(DriveEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //        case ConfirmTapeFound: // in the first state, replace this with correct names
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    printf("\r\nTapeSensor Found tape\r\n");
            //                    Drive_Stop(BOTH);
            //                    ThisEvent.EventType = FOUND_HOLE; // FIX ME!!! I added this assuming this is when hole/wall tape is found
            //                    //                    Solenoid_Fire();
            //                    break;
            //                    //                case ENCODER_DONE:
            //                    //                    DriveEvent.EventType = DRIVE_FORWARD_QTR;
            //                    //                    PostEncoderService(DriveEvent);
            //                    //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //
            //        case DetectedOpenAirReverse: // in the first state, replace this with correct names
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    DriveEvent.EventType = DRIVE_REVERSE_QTR; // previously FULL rotation // 4ppm changed to half 
            //                    PostEncoderService(DriveEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case LW_DETECTED:
            //                    nextState = DetectedWhiteAfterOpenAir;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ENCODER_DONE:
            //                    DriveEvent.EventType = DRIVE_REVERSE_HALF; // previously go back full  // 4ppm changed to half 
            //                    PostEncoderService(DriveEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //        case DetectedWhiteAfterOpenAir:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    DriveEvent.EventType = DRIVE_REVERSE_HALF; // 4ppm changed to half 
            //                    PostEncoderService(DriveEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case DW_DETECTED:
            //                    printf("STOPPED - HERE");
            //                    if (ThisEvent.EventParam == TOWER_TAPE_BOTH) {
            //                        Drive_Stop(BOTH);
            //                        nextState = ConfirmTapeFound;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case ENCODER_DONE:
            //                    nextState = SearchForward;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    //                    ThisEvent.EventType = FOUND_HOLE; // FIX ME!! I commented this out since it seems in wrong case
            //                    //                    Solenoid_Fire();
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunCorrectHoleFoundSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunCorrectHoleFoundSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

