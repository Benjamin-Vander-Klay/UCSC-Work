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
#include "CorrectSideFoundSubHSM.h"
#include "Track_Wire_Sensor.h"
#include "Tape_Sensors.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    TurnToCheckIfCornerState, // assuming we lead with our front sensor we need to make sure we're not on the corner. we are going to tank turn right for a bit un
    StraightenOutState, // drive straight until rear detects TW, front bumper is hit -- front right re adjusts to left?  or encoder finishes
    ReverseAndCheck,
    PivotForward,
    PivotAroundCornerState, //  Front TW lost the TW, need to turn corner. Pivot turn Left? until front bumper hits? 
    RearTWDetectedState, // check for white on tape or side beacon? 
    CorrectFLCollison,
    //    ScootCloserLeftState,
    //    ScootCloserRightState, //
    //    CenterOnBeaconState, // reused from old scope tower sm centers bot to tower with side beacon detector. not super accurate but a reference point nonetheless
    //    AdjustSquareLeftState,
    //    AdjustAndReturnState,
    //    CheckRearTW,
    //    TwoInchRevFourInchForwardState,
    //    TwoInchReverseState,
    //    AdjustWallPivotRevLeft,
    //    ReverseBeforeScootAgain,

} CorrectSideFoundSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "TurnToCheckIfCornerState",
    "StraightenOutState",
    "ReverseAndCheck", // aslso was not here bfore 2:22pm
    "PivotForward", // don't think it had this either
    "PivotAroundCornerState",
    "RearTWDetectedState", // found was not ghere
    "CorrectFLCollison",
    //    "ScootCloserLeftState",
    //    "ScootCloserRightState",
    //    "CenterOnBeaconState",
    //    "AdjustSquareLeftState",
    //    "AdjustAndReturnState",
    //    "CheckRearTW",
    //    "TwoInchRevFourInchForwardState",
    //    "TwoInchReverseState",
    //    "AdjustWallPivotRevLeft",
    //    "ReverseBeforeScootAgain",
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

static CorrectSideFoundSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static CorrectSideFoundSubHSMState_t PreviousState = InitPSubState;
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
uint8_t InitCorrectSideFoundSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunCorrectSideFoundSubHSM(INIT_EVENT);
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
ES_Event RunCorrectSideFoundSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    CorrectSideFoundSubHSMState_t nextState; // <- change type to correct enum
    ES_Event DriveEvent;
    static int8_t encoder_sum, square_up_complete;
    static int8_t check_reverse = TRUE;
    static int8_t check_front = TRUE;
    static uint8_t AD_Beacon_InSight = FALSE;
    static uint8_t currentTW = FALSE;
    DriveEvent.EventType = ES_NO_EVENT;
    ES_Tattle(); // trace call stack

    // we keep track of whether or not we can currently see the analog beacon
    if (ThisEvent.EventType == BEACON_WITHIN_ANALOG_RANGE) {
        // we see the beacon. make note and move it on
        AD_Beacon_InSight = TRUE;
    } else if (ThisEvent.EventType == BEACON_NOT_WITHIN_ANALOG_RANGE) {
        // we DO NOT! see the beacon. make note and move it on
        AD_Beacon_InSight = FALSE;
    }
    if (ThisEvent.EventType == TW_DETECTED) {
        currentTW = ThisEvent.EventParam;
    } else if (ThisEvent.EventType == TW_NOT_DETECTED) {
        currentTW = FALSE;
    }
    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = TurnToCheckIfCornerState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case TurnToCheckIfCornerState: // we finish pivoting back left to check if rear tw detects it

            switch (ThisEvent.EventType) {
                    // ALREADY STARTED THE ENCODER EVENT. IF THE NEXT TW DETECTED EVENT HAS BOTH, SHUFFLE IN?
                    // IF THE 

                    // BOTH!
                case TW_DETECTED:
                    // front TW detected which is how we arrived here. if another change is posted, it is becase the rear is also detected

                    // both TW detected
                    if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))) { // B A <- both == 3 // implicit OR
                        // start encoder event and move onto the 
                        //                        Drive_Stop(BOTH); //
                        // shuffle closer? 
                        // maybe center to tower? 

                        // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
                        //                        nextState = CenterOnBeaconState;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        Drive_Stop(BOTH);
                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
                    } else {
                        //                    else if((ThisEvent.EventParam == A_TW_MASK))){
                        //                        Drive_Stop(BOTH);
                        //                        
                        //                    }
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;

                    //                case TW_NOT_DETECTED: // lost the front one, we are on the corner
                    //                    // to go around the bend. maybe drive forward a little before pivot turning?
                    //                    // go to corner case. 
                    //
                    //
                    //                    // should likely be its own state lets test it first
                    //                    nextState = StraightenOutState;
                    //                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    //
                    //                    DriveEvent.EventType = DRIVE_FORWARD_QTR; // 2 inches forward. just to get around tower
                    //                    PostEncoderService(DriveEvent);
                    //
                    //                    //                    Drive_Pivot_Left(DRIVE_MED); 
                    //                    break;

                case ENCODER_DONE: // We still detect the other 
                    // we are likely on side but are behind the tower?
                    // going to drive forward 
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 1 + 2 == 3 
                    printf("encoder sum: %d", encoder_sum);
                    if (encoder_sum >= 1) { // we have backed up exactly this many clicks  // should be a tak turn still rihgt?
                        encoder_sum = 0; // reset sum 

                        nextState = StraightenOutState;
                        makeTransition = TRUE;
                        DriveEvent.EventType = DRIVE_FORWARD_HALF; // changed encoder ticks from 810 to 1620 which is actually 3/4 of a wheel rotation. may break things // CHANGED FROM 3/4 TO HALF BC 3/4 WAS ORIGINALLY 810 WHEN THIS WORKED 7:50PM BVK
                        PostEncoderService(DriveEvent);
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;
                case RL_PRESSED: // TT right to correct
                    nextState = StraightenOutState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    DriveEvent.EventType = DRIVE_FORWARD_HALF; // changed encoder ticks from 810 to 1620 which is actually 3/4 of a wheel rotation. may break things // CHANGED FROM 3/4 TO HALF BC 3/4 WAS ORIGINALLY 810 WHEN THIS WORKED 7:50PM BVK
                    PostEncoderService(DriveEvent);
                    break;
                    //Dark Wall Detected 
                case DW_DETECTED:
                    //                    if (ThisEvent.EventParam &)

                    break;
                case LW_DETECTED: // can add if DW_detected and param is only front wall 

                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case StraightenOutState: // forward 4 inches to clear corner if we're there or hit front left bumper
            switch (ThisEvent.EventType) {
                case FL_PRESSED:
                    //                    Drive_Stop(BOTH); // reset encoder ticks 
                    // back pivot LEFT? 
                    //                    Drive_Pivot_Left(-DRIVE_MED); // for now                                < -- will back pivot left forever
                    //                    nextState = CheckRearTW; // maybe pivot back left
                    nextState = TurnToCheckIfCornerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_15; // just scooting this, not going into the scooting states tied together
                    PostEncoderService(DriveEvent);
                    break;


                    // drove straight and found no change in the 
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 1 + 2 == 3 
                    printf("encoder sum: %d", encoder_sum);
                    if (encoder_sum >= 3) { // we have backed up exactly this many clicks 
                        encoder_sum = 0; // reset sum 
                        // TBD maybe pivot left
                        //                        nextState = PivotAroundCornerState                                                                          // 11pm
                        nextState = ReverseAndCheck;
                        makeTransition = TRUE;

                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                        DriveEvent.EventType = DRIVE_REVERSE_HALF; //back up and see if we see  // CHANGED FROM 3/4 TO HALF BC 3/4 WAS ORIGINALLY 810 WHEN THIS WORKED 7:50PM BVK
                        PostEncoderService(DriveEvent);
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case TW_DETECTED:
                    //                    if(ThisEvent.EventParam == B_TW_MASK){ // rear only because we drove forward on the tower. We need to pivot left a little more than usual prob like 300 degrees
                    //                        
                    //                    }
                    // both TW detected                                       // bvk 8:30PM 6/4 THIS STOPS IN AND DOESN'T DO ANYTHING. 
                    if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))/* || (ThisEvent.EventParam == B_TW_MASK)*/) { // B A <- both == 3 
                        // start encoder event and move onto the 
                        //                        Drive_Stop(BOTH); //
                        // shuffle closer? 
                        // maybe center to tower? 

                        // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
                        //                        nextState = CenterOnBeaconState;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        Drive_Stop(BOTH);
                        nextState = TurnToCheckIfCornerState; // return to initial state
                        makeTransition = TRUE;
                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
                        //                    } else if ((ThisEvent.EventParam == (A_TW_MASK))) { // A only                                                          // 11pm 
                        //                        nextState = CheckRearTW;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        //
                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_REV_15;
                        //                        PostEncoderService(DriveEvent);
                        //                    }else if ((ThisEvent.EventParam == (B_TW_MASK))) { // A only
                        //                        nextState = CheckRearTW;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        //
                        //                        DriveEvent.EventType = DRIVE_REVERSE_QTR;
                        //                        PostEncoderService(DriveEvent);    
                        //                    } else { // B track wire only -> back up 
                        //
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    //                    DriveEvent.EventType = SCOOT_LEFT; // or maybe find center? Start looking for tape? or 
                    //                    PostEncoderService(DriveEvent);
                    //                    DriveEvent.EventType = PIVOT_TURN_LEFT_300; // or maybe find center? Start looking for tape? or 
                    //                    PostEncoderService(DriveEvent);
                    break;
                    // bvk added 6:45pm 6/4 to try and get aligned with wall better
                case LW_DETECTED:
                    if (currentTW == A_TW_MASK) { // we are right on the wall and we detect white tower, go forward another 2inchs
                        // actually don't need to transition, we j reset encoder. 
                        //                        nextState = StraightenOutState;
                        //                        makeTransition = TRUE;
                        DriveEvent.EventType = DRIVE_FORWARD_HALF; /// 4 inches
                        PostEncoderService(DriveEvent);
                    } else if (currentTW = B_TW_MASK) { // we are going forward and only reading the rear tw, then we need to back up - go right into reverse
                        nextState = ReverseAndCheck;
                        makeTransition = TRUE;

                        // REVERSE MORE THAN GO FORWARD BC WE ARE CHANGING DIRECTIONS.     
                        DriveEvent.EventType = DRIVE_REVERSE_FULL; //back up and see if we see both now // CHANGED FROM 3/4 TO HALF BC 3/4 WAS ORIGINALLY 810 WHEN THIS WORKED 7:50PM BVK
                        PostEncoderService(DriveEvent);
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case DW_DETECTED:

                    if (ThisEvent.EventParam == TOWER_TAPE_MID) { // if we find it here, might as well stop and see!!
                        Drive_Stop(BOTH);
                        // SHOOTS SOLENOID IN TowerSubHSM
                        nextState = TurnToCheckIfCornerState; // return to initial state
                        makeTransition = TRUE;
                        ThisEvent.EventType = FOUND_CORRECT_HOLE_EARLY;

                    } else if (currentTW == A_TW_MASK) { // only rear track wire detected. front TW won't detect it if sticking out from the corner of the correct side
                        // this could be when the tape sensors read white tower and tape, or white tower and open air -this could be due to our position being at an angle to the wall 
                        // if we are at an angle then we keep going forward until we hit a wall I suppose. if we encoder out, we will back up again
                        // or if we are parallel, then we just need to keep going forward
                        // tower tape front is true if we see black, meaning this will occur when we see white on the front and middle, or the rear and middle 
                        // DDW was fucking up the corner. 
                        if (/*(ThisEvent.EventParam == DDW) || */(ThisEvent.EventParam == WDD)) { // bvk made these macros 7:30p to try and simplify this negation logic 
                            // keep going forward
                            DriveEvent.EventType = DRIVE_FORWARD_HALF; /// 4 inches
                            PostEncoderService(DriveEvent);
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else if (ThisEvent.EventParam == (TOWER_TAPE_FRONT | TOWER_TAPE_REAR)) { // we see white in the middle and black on either side. Likely we're at a corner and need to pivot turn left forward
                            // reusing this state! may need to add one for this ~corner~ case
                            nextState = PivotForward;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                            //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                            DriveEvent.EventType = PIVOT_TURN_LEFT_30; /// 4 inches
                            PostEncoderService(DriveEvent);
                            break;

                        } // only center reads white. we presume to be on the corner? 
                        //                        add else statement??
                    } else if (currentTW == B_TW_MASK) { // only the rear track wire detected
                        // FIX MEE!!! WHAT HAPPENS HERE???????
                        if ((ThisEvent.EventParam == DDW)/* || (ThisEvent.EventParam == WHITE_WALL_REAR)*/) { // [REAR CENTER FRONT] - only white tower on the front
                            // not sure we need this rn
//                            nextState = ReverseAndCheck; // BVK 11:45am 6/7/22 I think this is causing us to get stuck on the corner, and not fix anything else. maybe it helped to not over shoot the side. let's find out
//                            makeTransition = TRUE;
                            // BVK 11:45am changing this to drive forward QTR. I am not sure how this is getting triggered as it requires us to 
//                            DriveEvent.EventType = DRIVE_REVERSE_HALF; //back up and see if we see both now // CHANGED FROM 3/4 TO HALF BC 3/4 WAS ORIGINALLY 810 WHEN THIS WORKED 7:50PM BVK
                            DriveEvent.EventType = DRIVE_FORWARD_QTR;
                            PostEncoderService(DriveEvent);
                            
                        }
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            } // end of straighten out state
            break;

        case ReverseAndCheck:
            switch (ThisEvent.EventType) {
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 1 + 2 == 3 
                    printf("encoder sum: %d", encoder_sum);
                    if (encoder_sum >= 3) { // we have backed up exactly this many clicks 
                        encoder_sum = 0; // reset sum 
                        Drive_Stop(BOTH);
                        nextState = PivotForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                        DriveEvent.EventType = PIVOT_TURN_LEFT_30; //pivot forward and look
                        PostEncoderService(DriveEvent);
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    // see both track wires, exit
                case TW_DETECTED:
                    if (ThisEvent.EventParam == A_TW_MASK + B_TW_MASK) {
                        Drive_Stop(BOTH);
                        nextState = TurnToCheckIfCornerState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
                        // see only from rear track wire, pivot forward left
                    } else if (ThisEvent.EventParam == B_TW_MASK) {
                        //                        Drive_Stop(BOTH); // 4:45pm bvk & kaixin, taking this out so we don't freeze this FSM
                        //                        nextState = ;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_30; //pivot forward and look
                        //                        PostEncoderService(DriveEvent);
                        //                        nextState = TurnToCheckIfCornerState; // same with this. 4:50pm bvjk
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;               <<-- bvk 7:30 NOT SURE WHY THIS IS HERE. WE DON'T SEE BOTH YET. IDK IF THE HOLE FINDING FSM CAN HANDLE THAT
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case RL_PRESSED:
                    nextState = PivotForward;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                    DriveEvent.EventType = PIVOT_TURN_LEFT_30; /// changed from 30 - 15, BVK 3:18pm 6/6/2022 NVM WRONG FILE. OOPS
                    PostEncoderService(DriveEvent);
                    break;

                    // bvk added 6:45pm 6/4 to try and get aligned with wall better
                case LW_DETECTED: // will this lead us in loops?
                    if (currentTW == A_TW_MASK) { // we are right on the wall and we detect white tower, start going forward again 2inchs
                        // actually don't need to transition, we j reset encoder. 
                        nextState = StraightenOutState;
                        makeTransition = TRUE;
                        DriveEvent.EventType = DRIVE_FORWARD_FULL; /// 4 inches
                        PostEncoderService(DriveEvent);
                    } else if (currentTW = B_TW_MASK) { // we are going forward and only reading the rear tw, then we need to back up - go right into reverse
                        //                        nextState = ReverseAndCheck;
                        //                        makeTransition = TRUE;

                        DriveEvent.EventType = DRIVE_REVERSE_HALF; //back up and see if we see both now // CHANGED FROM 3/4 TO HALF BC 3/4 WAS ORIGINALLY 810 WHEN THIS WORKED 7:50PM BVK
                        PostEncoderService(DriveEvent);
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case DW_DETECTED:
                    if (ThisEvent.EventParam == TOWER_TAPE_MID) { // if we find it here, might as well stop and see!!
                        Drive_Stop(BOTH);

                        nextState = TurnToCheckIfCornerState; // return to initial state
                        makeTransition = TRUE;
                        ThisEvent.EventType = FOUND_CORRECT_HOLE_EARLY; // WE FIND IT BY CHANGE. START 30 SECOND(TBD) TIMER TILL WE ABANDONE TOWER AND MOVE ON AND HOPE FOR THE BEST. 

                    } else if (currentTW == A_TW_MASK) { // only rear track wire detected. front TW won't detect it if sticking out from the corner of the correct side
                        // this could be when the tape sensors read white tower and tape, or white tower and open air -this could be due to our position being at an angle to the wall 
                        // if we are at an angle then we keep going forward until we hit a wall I suppose. if we encoder out, we will back up again
                        // or if we are parallel, then we just need to keep going forward
                        // tower tape front is true if we see black, meaning this will occur when we see white on the front and middle, or the rear and middle 
                        if ((ThisEvent.EventParam == DDW)/* || (ThisEvent.EventParam == WHITE_WALL_REAR)*/) { // bvk made these macros 7:30p to try and simplify this negation logic 
                            // keep going forward
                            DriveEvent.EventType = DRIVE_REVERSE_EIGHTH; /// 1 inch. currently backing up. we see Dark Dark Light. either on corner or see tape. go another 1 inch to determine if tape or not. 
                            PostEncoderService(DriveEvent);
                        }/*else if ((ThisEvent.EventParam == WHITE_WALL_FRONT)){
                            
                        }*/
                        else if (ThisEvent.EventParam == (TOWER_TAPE_FRONT | TOWER_TAPE_REAR)) { // we see white in the middle and black on either side. Likely we're at a corner and need to pivot turn left forward
                            // reusing this state! may need to add one for this ~corner~ case
                            nextState = PivotForward;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                            //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                            DriveEvent.EventType = PIVOT_TURN_LEFT_30; /// 4 inches
                            PostEncoderService(DriveEvent);
                            break;
                        }
                        //                        add else statement??
                    } else if (currentTW == B_TW_MASK) { // only the rear track wire detected
                        // FIX MEE!!! WHAT HAPPENS HERE???????
                        if ((ThisEvent.EventParam == DDW)/* || (ThisEvent.EventParam == WHITE_WALL_REAR)*/) { // not sure we need this rn
                            nextState = ReverseAndCheck;
                            makeTransition = TRUE;

                            DriveEvent.EventType = DRIVE_REVERSE_EIGHTH; //back up and see if we see both now
                            PostEncoderService(DriveEvent);
                        }
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;
        case PivotForward:
            switch (ThisEvent.EventType) {
                case ENCODER_DONE:
                    // BACK TO STRAIGHT
                    nextState = StraightenOutState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                    DriveEvent.EventType = DRIVE_FORWARD_HALF; /// 4 inches
                    PostEncoderService(DriveEvent);
                    break;
                case FL_PRESSED:
                    nextState = CorrectFLCollison;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                    DriveEvent.EventType = SCOOT_RIGHT; /// 300 ticks rn
                    PostEncoderService(DriveEvent);
                    break;
                case FR_PRESSED:
                    nextState = StraightenOutState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                    DriveEvent.EventType = DRIVE_FORWARD_HALF; /// 4 inches
                    PostEncoderService(DriveEvent);
                    break;

                case TW_DETECTED:
                    if (ThisEvent.EventParam == A_TW_MASK + B_TW_MASK) {
                        Drive_Stop(BOTH);
                        nextState = TurnToCheckIfCornerState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
                        // see only from rear track wire, pivot forward left
                        //                    } else if (ThisEvent.EventParam == B_TW_MASK) {
                        //                        Drive_Stop(BOTH);
                        //                        //                        nextState = ;
                        //                        //                        makeTransition = TRUE;
                        //                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        //                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well                                       // 11pm
                        //                        //                        DriveEvent.EventType = PIVOT_TURN_LEFT_30; //pivot forward and look
                        //                        //                        PostEncoderService(DriveEvent);
                        //                        nextState = TurnToCheckIfCornerState;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    break;

            }

            break;
        case CorrectFLCollison: // tank turning right to correcty bumper collision and then going to straight
            switch (ThisEvent.EventType) {
                case ENCODER_DONE:

                    nextState = StraightenOutState; // maybe try and pivot more? if we have cleared it and are too far this will be a probelm 
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    DriveEvent.EventType = DRIVE_FORWARD_HALF; // MAYBE CHANGE THIS. TRY 30 PERHAPS?
                    PostEncoderService(DriveEvent);
                    break;

                case RL_PRESSED: // encoder went too far
                    nextState = StraightenOutState; // maybe try and pivot more? if we have cleared it and are too far this will be a probelm 
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    DriveEvent.EventType = DRIVE_FORWARD_HALF; // pivot right an see if going forwards helps us see it, maybe also go back?
                    PostEncoderService(DriveEvent);
                    break;

                case TW_DETECTED:
                    if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))) { // B A <- both == 3 
                        // start encoder event and move onto the 
                        //                        Drive_Stop(BOTH); //
                        // shuffle closer? 
                        // maybe center to tower? 

                        // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
                        //                        nextState = CenterOnBeaconState;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        Drive_Stop(BOTH);
                        nextState = TurnToCheckIfCornerState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;


            // previous version
            //                    case CheckRearTW: // tank turning right and hoping for a 
            //                        switch (ThisEvent.EventType) {
            //                            case ENCODER_DONE:
            //                                nextState = TurnToCheckIfCornerState; // maybe try and pivot more? if we have cleared it and are too far this will be a probelm 
            //                                makeTransition = TRUE;
            //                                ThisEvent.EventType = ES_NO_EVENT;
            //            
            //                                DriveEvent.EventType = PIVOT_TURN_LEFT_15; // MAYBE CHANGE THIS. TRY 30 PERHAPS?
            //                                PostEncoderService(DriveEvent);
            //                                break;
            //            
            //                            case RL_PRESSED: // encoder went too far
            //                                nextState = TurnToCheckIfCornerState; // maybe try and pivot more? if we have cleared it and are too far this will be a probelm 
            //                                makeTransition = TRUE;
            //                                ThisEvent.EventType = ES_NO_EVENT;
            //            
            //                                DriveEvent.EventType = PIVOT_TURN_LEFT_15; // pivot right an see if going forwards helps us see it, maybe also go back?
            //                                PostEncoderService(DriveEvent);
            //                                break;
            //            
            //                            case TW_DETECTED:
            //                                if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))) { // B A <- both == 3 
            //                                    // start encoder event and move onto the 
            //                                    //                        Drive_Stop(BOTH); //
            //                                    // shuffle closer? 
            //                                    // maybe center to tower? 
            //            
            //                                    // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
            //                                    //                        nextState = CenterOnBeaconState;
            //                                    //                        makeTransition = TRUE;
            //                                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                                    Drive_Stop(BOTH);
            //                                }
            //                                ThisEvent.EventType = ES_NO_EVENT;
            //                                break;
            //                            case ES_NO_EVENT:
            //                            default: // all unhandled events pass the event back up to the next level
            //                                break;
            //                        }
            //                        break;
            //            // assume we are on corner and if we hit the bumper we need to tank turn right to correct and then go straight again. which smells like 
            //        case PivotAroundCornerState:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    //                    DriveEvent.EventType = PIVOT_TURN_LEFT_300; // pivots left so might as well
            //                    //                    PostEncoderService(DriveEvent);
            //                    break;
            //                case ENCODER_DONE:
            //                    // pivot is done
            //                    //                    DriveEvent.EventType = SCOOT_LEFT; // pivots left so might as well
            //                    //                    PostEncoderService(DriveEvent);
            //
            //                    nextState = StraightenOutState;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    makeTransition = TRUE;
            //
            //                    DriveEvent.EventType = DRIVE_FORWARD_HALF; // four inches forward. Less than half the tower.
            //                    PostEncoderService(DriveEvent);
            //                    break;
            //                case FL_PRESSED:
            //                    nextState = AdjustWallPivotRevLeft;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //
            //                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_30; // axis of rot on left wheel, should get more snug to the wall after bumping -> find TW 
            //                    PostEncoderService(DriveEvent);
            //                    break;
            //                case TW_DETECTED:
            //                    if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))) { // B A <- both == 3 
            //                        // start encoder event and move onto the 
            //                        //                        Drive_Stop(BOTH); //
            //                        // shuffle closer? 
            //                        // maybe center to tower? 
            //
            //                        // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
            //                        //                        nextState = CenterOnBeaconState;
            //                        //                        makeTransition = TRUE;
            //                        //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        Drive_Stop(BOTH);
            //                        //                        Drive_Stop(BOTH);
            //                    } else if ((ThisEvent.EventParam == (A_TW_MASK))) { // just A, we going to go back into initial for this
            //                        nextState = TurnToCheckIfCornerState;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //
            //                        DriveEvent.EventType = TW_ALIGN_PT_LEFT_REV;
            //                        PostEncoderService(DriveEvent);
            //                    }
            //                    //                    else {// just B
            //                    //                        // tank turn left // or maybe pivot?
            //                    //                        AdjustSquareLeftState
            //                    //                    }
            //                    break;
            //
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //            // just go a little forward so we don't over shoot side
            //        case TwoInchRevFourInchForwardState:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    DriveEvent.EventType = DRIVE_REVERSE_QTR;
            //                    PostEncoderService(DriveEvent);
            //                    check_front = TRUE; // reset it for next time
            //                    break;
            //                case ENCODER_DONE:
            //                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
            //                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
            //                        encoder_sum = 0; // reset sum
            //
            //                        // if we finished checking front, check back
            //                        if (check_front) {
            //                            check_front = FALSE;
            //                            // RESET ENCODER FOR FORWARD
            //                            DriveEvent.EventType = DRIVE_FORWARD_HALF; // four inches forward now
            //                            PostEncoderService(DriveEvent);
            //
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //
            //                        } else {
            //
            //                            // go into pivot 300 is current idea. 
            //                            nextState = PivotAroundCornerState;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //
            //                            // set encoder for pivot turn aroun corner state
            //                            DriveEvent.EventType = PIVOT_TURN_LEFT_300;
            //                            PostEncoderService(DriveEvent);
            //                        }
            //
            //
            //
            //                    }
            //
            //
            //
            //                    //                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_15;
            //                    //                    PostEncoderService(DriveEvent);
            //                    break;
            //
            //                case FL_PRESSED: // FL hit, need to adjust to wall we just hit.
            //                    nextState = AdjustWallPivotRevLeft; // going backwards? 
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //
            //                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_30;
            //                    PostEncoderService(DriveEvent);
            //
            //                    break;
            //                    // if we find it, snuggle up w center on beacon -> 
            //                case TW_DETECTED:
            //                    if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))) { // B A <- both == 3 
            //                        // start encoder event and move onto the 
            //                        //                        Drive_Stop(BOTH); //
            //                        // shuffle closer? 
            //                        // maybe center to tower? 
            //
            //                        // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
            //                        //                        nextState = CenterOnBeaconState;
            //                        //                        makeTransition = TRUE;
            //                        //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        Drive_Stop(BOTH);
            //                        //                        Drive_Stop(BOTH);
            //                    } else if ((ThisEvent.EventParam == (A_TW_MASK))) { // just A, we going to go back into initial for this
            //                        nextState = TurnToCheckIfCornerState;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //
            //                        DriveEvent.EventType = TW_ALIGN_PT_LEFT_REV;
            //                        PostEncoderService(DriveEvent);
            //                    }
            //                    break;
            //                    // if only rear, back up? 
            //
            //            }
            //        case AdjustWallPivotRevLeft:
            //            switch (ThisEvent.EventType) {
            //                    // adjusted from wall, go back to 2 inch forward
            //                case ENCODER_DONE:
            //                    nextState = TwoInchRevFourInchForwardState;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //
            //                    // drive event on entry to 
            //                    //                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_15;
            //                    //                    PostEncoderService(DriveEvent);
            //                    break;
            //                    // if we find them here, center and scoot
            //                case TW_DETECTED:
            //                    if ((ThisEvent.EventParam == (B_TW_MASK + A_TW_MASK))) { // B A <- both == 3 
            //                        // start encoder event and move onto the 
            //                        //                        Drive_Stop(BOTH); //
            //                        // shuffle closer? 
            //                        // maybe center to tower? 
            //
            //                        // this is already coded to go into shuffle so lets try it. Lets center and then shuffle closer/ 
            //                        //                        nextState = CenterOnBeaconState;
            //                        //                        makeTransition = TRUE;
            //                        //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        Drive_Stop(BOTH);
            //                        //                        Drive_Stop(BOTH);
            //                    } else if ((ThisEvent.EventParam == (A_TW_MASK))) { // just A, we going to go back into initial for this
            //                        nextState = TurnToCheckIfCornerState;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //
            //                        DriveEvent.EventType = TW_ALIGN_PT_LEFT_REV;
            //                        PostEncoderService(DriveEvent);
            //                    }
            //                    break;
            //
            //            }
            //            break;
            //            // so we can check the back and see if we get both 
            //            //        case TwoInchReverseState:
            //
            //            //            break;
            //        case ScootCloserLeftState:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    // perform scoot!
            //                    DriveEvent.EventType = SCOOT_LEFT;
            //                    PostEncoderService(DriveEvent);
            //                    break;
            //                    // finished scoot left -> scoot right (tank turn for now?)
            //                case ENCODER_DONE:
            //                    //                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
            //                    //                    if (encoder_sum >= 1) { // we have backed up exactly this many clicks // -------------------------------------------- <<< 2!! only works for PIVOTING!!!!
            //                    //                        encoder_sum = 0; // reset sum
            //
            //                    // go to scoot right
            //                    nextState = ScootCloserRightState;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT; // pass nothing up the chain
            //                    // we hit something oml hopefully tower 
            //                    break;
            //
            //                case LW_DETECTED: // exit condition - we should be ~1 inch from white wall. we then look for black tape w help from side beacon
            //                    Drive_Stop(BOTH);
            //                    ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
            //                    break;
            //
            //                case FR_PRESSED: // then we know we hit... another bot? unlikely. we'll have to see here
            //                    Drive_Stop(BOTH); // reset encoders and tank turn to try and hit other ones? maybe just straighten out! we are squarish and don't want to get stuck. 
            //                    break; // CHECK ME!!! added this cuz was missing
            //                case FL_PRESSED:
            //                    // we hit the tower, tank turn right to saddle up
            //                    // go to scoot right
            //                    nextState = ScootCloserRightState;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case BEACON_NOT_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case BEACON_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                    //                    case dont recall 
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //
            //            }
            //
            //            break;
            //        case ScootCloserRightState: // to straighten out and maybe hit a bumper tho I am worried abt getting stuck.
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    // perform scoot!
            //                    DriveEvent.EventType = SCOOT_RIGHT;
            //                    PostEncoderService(DriveEvent);
            //                    break;
            //                    // finished scoot left -> scoot right (tank turn for now?)
            //                case ENCODER_DONE:
            //                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
            //                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
            //                        encoder_sum = 0; // reset sum
            //
            //                        // go to scoot right
            //                        nextState = SCOOT_REVERSE; // recenter before 
            //                        makeTransition = TRUE;
            //
            //                        DriveEvent.EventType = SCOOT_REVERSE;
            //                        PostEncoderService(DriveEvent);
            //
            //                        //                        break; // FIX MEEE!!! AM I SUPPOSED TO BE HERE????
            //                    }
            //                    ThisEvent.EventType = ES_NO_EVENT; // pass nothing up the chain
            //                    // we hit something oml hopefully tower 
            //                    break;
            //
            //                case TW_DETECTED: // front track wire goes out, only see rear (B)! -> stop for now.
            //                    if (ThisEvent.EventParam == B_TW_MASK) {
            //                        Drive_Stop(BOTH);
            //                        // go to center on Tower? 
            //                        // go to scoot right
            //                        nextState = SCOOT_REVERSE;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //
            //                        DriveEvent.EventType = SCOOT_REVERSE;
            //                        PostEncoderService(DriveEvent);
            //
            //                    } else if (ThisEvent.EventParam == A_TW_MASK) { // only track wire A
            //                        // in Tank turning right we lost track wire B, implying we are around the corner. 
            //                        // perhaps pivot left again? or drive forward a little bit?
            //                    }
            //                    break;
            //                case LW_DETECTED: // exit condition - we should be ~1 inch from white wall. we then look for black tape w help from side beacon
            //                    Drive_Stop(BOTH);
            //                    ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
            //                    break;
            //                case FR_PRESSED: // then we know we 
            //                    //                    Drive_Stop(BOTH); // reset encoders and tank turn to try and hit other ones? maybe just straighten out! we are squarish and don't want to get stuck. 
            //
            //                    break;
            //
            //                    // we hit rear bumpers, correct a small amount? or just stop for now..
            //                case RL_PRESSED:
            //                    //                    Drive_Stop(BOTH);                                           // < -- Micro adjust tank turn left to reset to square? we only advance horizontally in pivot turn
            //
            //                    // Go to adjust 
            //                    nextState = AdjustSquareLeftState;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    // set up encoders
            //                    DriveEvent.EventType = TOWER_SQUARE_LEFT;
            //                    PostEncoderService(DriveEvent);
            //
            //                    break;
            //                case BEACON_NOT_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case BEACON_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //            // arrives only from scoot right!!    
            //        case AdjustSquareLeftState: // tank turn left so we're square after tank turning left to scoot right
            //            // set encoder as very small. we could also do if unpressed. lol ppl have not been using that. may miss it tho. for now, encoder
            //            //if we hit right then we go back to the scoot right for now. problem if we go in loops, but this is a small adjustment
            //            // if we see both side tape sensors as white then we exit to ... tbd as described in center beacon on state
            //            switch (ThisEvent.EventType) {
            //
            //                case ENCODER_DONE:
            //                    // tank turn left to square. enter center on beacon when this is finished. 
            //                    // REQUIRES A FLAG.
            //                    //                    if (square_up_complete == FALSE) {
            //                    //                        square_up_complete = TRUE;
            //
            //                    // now set incoder to square - tank turn left to adjust after tt right
            //                    // set up encoders
            //                    //                        DriveEvent.EventType = TOWER_SQUARE_LEFT;
            //                    //                        PostEncoderService(DriveEvent);
            //                    //                    }
            //                    // only doing one thing so that's ^^ not necessary
            //                    // just change state to CenterOnBeaconState
            //                    //                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
            //                    //                    if (encoder_sum >= 3) { // we have backed up exactly this many clicks 
            //                    //                        encoder_sum = 0; // reset sum
            //
            //                    nextState = CenterOnBeaconState; // we are super close
            //                    makeTransition = TRUE;
            //                    //     
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case FL_PRESSED: // even tiny correct hit. stop and center, we are very close
            //                    //                    Drive_Stop(BOTH); // stop encoders and go to center on beacon
            //                    nextState = ReverseBeforeScootAgain;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case LW_DETECTED: // exit condition - we should be ~1 inch from white wall. we then look for black tape w help from side beacon
            //                    Drive_Stop(BOTH);
            //                    ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //
            //            break;
            //        case ReverseBeforeScootAgain:
            //            switch (ThisEvent.EventType) {
            //                case ENCODER_DONE:
            //                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
            //                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
            //                        encoder_sum = 0; // reset sum
            //
            //                        ThisEvent.EventType = ES_NO_EVENT; // not 100% sure abt this but don't transistion to circle tower yet
            //                        nextState = ScootCloserLeftState; // align on side 
            //                        makeTransition = TRUE;
            //                    } else {
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //
            //                    break;
            //
            //                default:
            //                    break;
            //            }
            //            break;
            //
            //        case CenterOnBeaconState:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    // drive forward 4 inches and then back 8 inches
            //                    DriveEvent.EventType = DRIVE_FORWARD_HALF;
            //                    PostEncoderService(DriveEvent);
            //                    check_reverse = TRUE;
            //                    break;
            //                case BEACON_WITHIN_ANALOG_RANGE: // we see it on the side
            //                    //                    Drive_Stop(BOTH); // gonna do more in a second
            //                    // we're gonna scoot closer!!
            //                    // pivot 
            //                    // tank turn right
            //                    // save current AD value? perhaps
            //                    //                    max_beacon_ad = current_beacon_ad; // first look
            //
            //                    //                    DriveEvent.EventType = SCOOT_LEFT;
            //                    //                    PostEncoderService(DriveEvent);
            //
            //                    // new version 6pm 5/31 bvk
            //                    ThisEvent.EventType = ES_NO_EVENT; // not 100% sure abt this but don't transistion to circle tower yet
            //                    nextState = ScootCloserLeftState; // align on side 
            //                    makeTransition = TRUE;
            //
            //                    // old version
            //                    // stop motors and reset encoders
            //                    //                    Drive_Stop(BOTH);
            //                    //                    ThisEvent.EventType = BEACON_WITHIN_ANALOG_RANGE; // change state in mid level tower sub HSM
            //                    //                    return ThisEvent;
            //                    break; // we wont break we'll just return but fuck it
            //                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
            //                    // eat the event. we dont care, we have found the tower
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //
            //                    break;
            //                case LW_DETECTED: // EXIT CONDITION is tape sensors on side detect light
            //                    //                    if(ThisEvent.EventParam == TOWER_TAPE_BOTH){ They both detect no tape! we are within one inch of the wall
            //                    Drive_Stop(BOTH);
            //                    ThisEvent.EventType = SQUARE_ON_CORRECT_SIDE;
            //                    //                    }
            //                    break;
            //                    // we 
            //                case ENCODER_DONE: // drive forward and then backwards and if never found it, we ext
            //                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
            //                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
            //                        encoder_sum = 0; // reset sum
            //                        // check when we finish this too
            //                        //                        CheckforBeaconAnalog(); // maybe will post event in time to catch it later? -- did not work. 6:15pm 5/31 bvk
            //                        // initially true. 
            //                        if (check_reverse) {
            //                            check_reverse = FALSE; // fuck this sheit
            //                            // now we set the encoder up to check here -- note how we don't transition to this state again. that would cause re-entry ***
            //                            // if we re-entered we would drive forward again. 
            //                            DriveEvent.EventType = DRIVE_REVERSE_FULL;
            //                            PostEncoderService(DriveEvent);
            //                        } else { // we now use rotary encoder to check behind us
            //                            // we now have checked front and rear, we did not see ... move out of this FSM and into DEAD BOT AVOID I guess
            //                            printf("\r\n done checking, should exit tower scope");
            //                            Drive_Tank_Turn_Right(DRIVE_MED); // ----------------------------------------------------------------------------- <<----- 
            //                            nextState = TurnToCheckIfCornerState; // RESET FOR NEXT TIME 
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = BEACON_NOT_WITHIN_ANALOG_RANGE; // so higher level will deal with it. 
            //                        }
            //                        //                        // transition to next state
            //                        //                        nextState = DriveReverseState; // align on side 
            //                        //                        makeTransition = TRUE;
            //                        //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    } else {
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        //return ThisEvent;
            //                    }
            //                    break;
            //                    // 1:00 pm 5/31/22--Amber While Aligning with tower one of the bumpers is triggered 
            //                    // For all cases the bot will adjust a minor amount based off of a timer 
            //                    //                case RL_PRESSED: // pivot forward left a tiny bit? 
            //                    //                    // 5-31 Amber //Keeping the Init Timer Functions in each case, can be set ES_EXIT
            //                    //                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
            //                    //                    Drive_Pivot_Left(DRIVE_MED);
            //                    //                    break;
            //                    //
            //                    //                case RR_PRESSED:
            //                    //                    //                    (ThisEvent.EventParam == TempTurnTimer)
            //                    //                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
            //                    //                    Drive_Pivot_Left(DRIVE_MED); // 5-31-22 Please Change motor function prolly chose wrong direction !!!!!!!!!
            //                    //                    break;
            //                    //
            //                    //                case FL_PRESSED:
            //                    //                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
            //                    //                    Drive_Pivot_Left(-DRIVE_MED); // 5-31-22 Please Change motor function!!!!!!!!!
            //                    //                    break;
            //                    //
            //                    //                case FR_PRESSED:
            //                    //                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
            //                    //                    Drive_Pivot_Left(-DRIVE_MED); // 5-31-22 Please Change motor function!!!!!!!!!
            //                    //                    break;
            //                    //                case FLOOR_LIGHT_CHANGE:
            //                    //
            //                    //                    break;
            //                case TW_NOT_DETECTED: // go back to **                                                         <-- Exit condition. Goes back out
            //                    nextState = AdjustWallPivotRevLeft; // going backwards? 
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //
            //                    DriveEvent.EventType = PIVOT_TURN_LEFT_REV_30;
            //                    PostEncoderService(DriveEvent);
            //
            //
            //                    break;
            //
            //                case TW_DETECTED: // if only B is detected here, need to Back Up
            //                    if (ThisEvent.EventParam == B_TW_MASK) {
            //                        Drive_Stop(BOTH); // resets the encoders
            //                        // go to center on Tower? 
            //                        // go to scoot right
            //                        nextState = SCOOT_REVERSE;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //
            //                        DriveEvent.EventType = DRIVE_REVERSE_HALF;
            //                        PostEncoderService(DriveEvent);
            //
            //                    } else if (ThisEvent.EventParam == A_TW_MASK) { // only track wire A
            //                        // in Tank turning right we lost track wire B, implying we are around the corner. 
            //                        // perhaps pivot left again? or drive forward a little bit?
            //                    }
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;
            //
            //        case AdjustAndReturnState: // so we correct one was a tiny bit and when encoder event expires we go right back. we could also just pass any other events to that state? perhaps? 
            //            switch (ThisEvent.EventType) { // essentially blocking code
            //                case ENCODER_DONE:
            //                    nextState = PreviousState; //return to state we adjusted from 
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT; // so higher level will deal with it. 
            //                    break;
            //                case TW_DETECTED:
            //                    // if we find the track wire during our small tank turn right we juts go to 
            //                    if (ThisEvent.EventParam == (B_TW_MASK & A_TW_MASK)) {
            //                        nextState = CenterOnBeaconState;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    Drive_Stop(BOTH);
            //                    break;
            //                case ES_NO_EVENT:
            //                default:
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //            }
            //            break;
            //        default: // all unhandled states fall into here
            //            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunCorrectSideFoundSubHSM(EXIT_EVENT); // <- rename to your own Run function
        PreviousState = CurrentState; // BVK << -------------------------------------------------------hey this might be weird idk if this is safe? so we can return to previous after slight encoder adjustment --> idk test it out?
        CurrentState = nextState;
        RunCorrectSideFoundSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

