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
#include "ActiveSearchSubHSM.h"
#include "Sense_EventChecker.h"
#include "SimpleFunctionService.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPActiveSubState,
    RotateFirst,
    ActiveIdle,
    MoveForward2In,
    PivotReverseRight,
    PivotForwardRight,
    PivotReverseLeft,
    PivotForwardLeft,
    MidAdjustRotateLeft,
    MidAdjustRotateRight,
    Rotate2Face,
    Move2Mid,
    Rotate360,
    Move2Corner,
    Rotate2Next,
    SearchRotation,
    DangerZone,
    Reverse_Buffer,
    ReverseAfterFrontTripped,
} ActiveSearchSubHSMState_t;

static const char *StateNames[] = {
    "InitPActiveSubState",
    "RotateFirst",
    "ActiveIdle",
    "MoveForward2In",
    "PivotReverseRight",
    "PivotForwardRight",
    "PivotReverseLeft",
    "PivotForwardLeft",
    "MidAdjustRotateLeft",
    "MidAdjustRotateRight",
    "Rotate2Face",
    "Move2Mid",
    "Rotate360",
    "Move2Corner",
    "Rotate2Next",
    "SearchRotation",
    "DangerZone",
    "Reverse_Buffer",
    "ReverseAfterFrontTripped",
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

static ActiveSearchSubHSMState_t CurrentState = InitPActiveSubState; // <- change name to match ENUM check
static uint8_t MyPriority;
#define NUM_OF_TURNS 1

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
uint8_t InitActiveSearchSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPActiveSubState;
    returnEvent = RunActiveSearchSubHSM(INIT_EVENT);
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

ES_Event RunActiveSearchSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    ActiveSearchSubHSMState_t nextState; // <- change type to correct enum
    int count = 0;
    uint8_t EntryCondition, EnterDangerZoneCondition;
    static int8_t encoder_side_sum;
    ES_Tattle(); // trace call stack
    ES_Event DriveEvent;
    switch (CurrentState) {
        case InitPActiveSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                /*5/30/22 3:28 pm {Amber} Adding a Drive_Stop here so that when the state machine is initially entered the bot will not be moving until 
                 *  the event has a chance to be handled 
                 */
                //                Drive_Stop(BOTH);
                // now put the machine into the actual initial state
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case RotateFirst:

            if (ThisEvent.EventType == ES_ENTRY) {
                Drive_Tank_Turn_Left(DRIVE_HIGH);
                // define encoder ticks for rotation enter from findTape
                DriveEvent.EventType = TANK_TURN_LEFT_ENTRY; // rotates 90 degrees to move to next quadrant
                PostEncoderService(DriveEvent);
            } else if (ThisEvent.EventType == ENCODER_DONE) {
                // move to ActiveIdle.
                // Encoder event defined in entry
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }

            break;
        case ActiveIdle:
            /*5/30/22 3:28 pm {Amber} Adding Different Entry/Exit Conditions 
             *  Will only Drive High When there are no Other events. 
             */
            //            Drive_Straight(DRIVE_HIGH); 
            switch (ThisEvent.EventType) {
                case FL_PRESSED:
                    /*-------------------Replace with Encoder Events------------------------*/
                    Drive_Stop(BOTH);
                    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    /*---------------------------------------------------------------------*/
                    nextState = PivotReverseLeft;
                    //                    nextState = PivotReverseRight;  7:27 pm 5/30/22 --A&K Changing all bumper responses to Left
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RL_PRESSED:
                    /*-------------------Replace with Encoder Events------------------------*/
                    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    Drive_Stop(BOTH);
                    /*----------------------------------------------------------------------*/
                    //Testing the rotating tower encoder rn pls uncomment Pivot Forward Right
                    //                    nextState = SearchRotation; // FIX ME: just for testing the rotations 7:27 pm 5/30/22 Changed it back 
                    nextState = PivotForwardLeft;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RR_PRESSED:
                    /*-------------------Replace with Encoder Events------------------------*/
                    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    Drive_Stop(BOTH);
                    /*----------------------------------------------------------------------*/
                    nextState = PivotForwardLeft;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case FR_PRESSED:
                    /*-------------------Replace with Encoder Events------------------------*/
                    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    Drive_Stop(BOTH);
                    /*----------------------------------------------------------------------*/
                    nextState = PivotReverseLeft;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FLOOR_LIGHT_CHANGE:
                    //Should probably put this in 
                    //Sets entry condition to OR the different entry conditions for the state machine
                    // no tape on front and rear right, or no tape on Front right, or no tape on front center, front right, and rear right
                    EntryCondition = CompareToEventParam(MAR_ENTRY_1, ThisEvent.EventParam) | CompareToEventParam(MAR_ENTRY_2, ThisEvent.EventParam) | CompareToEventParam(MAR_ENTRY_3, ThisEvent.EventParam);
                    if (ThisEvent.EventParam == FALSE) { // == 0// exit to find tape // Not worrygin abt exit condition rn 5/29/2022 ***************************************************************************************
                        // 

                        nextState = ActiveIdle;
                        makeTransition = TRUE;
                        ThisEvent.EventType = DF_NONE_DETECTED; //  Need to reorient ourselves.

                    } else if (ThisEvent.EventParam & F_TS_MASK) { //Adjusts Until the Front Left is low
                        nextState = Reverse_Buffer;
                        makeTransition = TRUE;
                        Drive_Stop(BOTH);
                        //                        Drive_Tank_Turn_Left(DRIVE_MED);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }//                    else if (CompareToEventParam(RR_ONLY_ADJUST, ThisEvent.EventParam)) {
                        //                        nextState = MidAdjustRotatet;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT; //  Need to reorient ourselves.
                        //                        
                        //                    }
                        //                    else if (CompareToEventParam(FR_ONLY_ADJUST, ThisEvent.EventParam)) {
                        //                        nextState = PivotForwardLeft;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT; //  Need to reorient ourselves.
                        //                        
                        //                    }
                        //Compares the SR_ENTRY condition with the current EventParam
                    else if (CompareToEventParam(SR_ENTRY, ThisEvent.EventParam)) { // reached the corner of the tape field
                        /*-------------------Replace with Encoder Events------------------------*/
                        //                        ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION); //Should Not be on a timer 
                        Drive_Stop(BOTH);
                        /*----------------------------------------------------------------------*/

                        // maybe needs to be forward 2 inches?
                        nextState = SearchRotation;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;


                        //                        // Going to go forward 2 in and then go into SearchRotation
                        //                        nextState = SearchRotation;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;

                    } else if (EntryCondition) { // reset the bot to align with the tape 
                        /*-------------------Replace with Encoder Events------------------------*/
                        //                        ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION_2); Moved Init Timer from
                        ES_Timer_InitTimer(TempTurnTimer, LINE_CORRECT_LEFT_DURATION);
                        Drive_Stop(BOTH);
                        /*----------------------------------------------------------------------*/
                        nextState = MidAdjustRotateLeft;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    } else if (CompareToEventParam(RAFC_ENTRY, ThisEvent.EventParam)) {
                        nextState = ReverseAfterFrontTripped;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    Drive_Straight(DRIVE_HIGH); // 5/30/22 Will Only drive forward if enters no other conditions 
                    break;
            }
            break;
            //NOTE: IT IS NOT NECESSARY FOR THESE TO BE SEPARATE STATES AS THE PIVOT MOTOR FUNCTIONS ARE CALLED BY ACTIVE IDLE 
            //Keeping as separate cases in case there is need to add more transitions later down the line     
        case MoveForward2In:
            if (ThisEvent.EventType == ES_ENTRY) {
                DriveEvent.EventType = DRIVE_FORWARD_QTR; // advances another 2 inches before searching the quadrant
                PostEncoderService(DriveEvent);
            }// Going to go forward 2 in and then go into SearchRotation
            else if (ThisEvent.EventType == ENCODER_DONE) {
                Drive_Stop(BOTH);
                nextState = SearchRotation;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
        case PivotReverseRight:
            //----5/27/22--- Fake Encoder Event is used in place of the 
            //-------------- The ENCODER_DONE event for the time being
            //-------------- Replace with ENCODER_DONE------------Amber
            //            Drive_Stop(BOTH);
            Drive_Pivot_Right(-DRIVE_HIGH);
            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                Drive_Stop(BOTH); //Remove when Encoder is implemented 
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                // another bumper event *****************************************
            } else if (ThisEvent.EventType == FL_PRESSED) {
                /*-------------------Replace with Encoder Events------------------------*/
                Drive_Stop(BOTH);
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                /*---------------------------------------------------------------------*/
                nextState = PivotReverseRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == RL_PRESSED) {

                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                //Testing the rotating tower encoder rn pls uncomment Pivot Forward Right
                nextState = PivotForwardRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            } else if (ThisEvent.EventType == RR_PRESSED) {

                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                nextState = PivotForwardLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            } else if (ThisEvent.EventType == FR_PRESSED) {
                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                nextState = PivotReverseLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case PivotForwardRight:
            //----5/27/22--- FAKE_ENCODER_EVENT is used in place of the 
            //-------------- The ENCODER_DONE event for the time being
            //-------------- Replace with ENCODER_DONE------------Amber
            Drive_Pivot_Right(DRIVE_HIGH);
            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                Drive_Stop(BOTH); //Remove when Encoder is implemented 
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                // another bumper event *****************************************
            } else if (ThisEvent.EventType == FL_PRESSED) {
                /*-------------------Replace with Encoder Events------------------------*/
                Drive_Stop(BOTH);
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                /*---------------------------------------------------------------------*/
                nextState = PivotReverseRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == RL_PRESSED) {

                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                //Testing the rotating tower encoder rn pls uncomment Pivot Forward Right
                nextState = PivotForwardRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            } else if (ThisEvent.EventType == RR_PRESSED) {

                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                nextState = PivotForwardLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            } else if (ThisEvent.EventType == FR_PRESSED) {
                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                nextState = PivotReverseLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case PivotForwardLeft:
            //----5/27/22--- FAKE_ENCODER_EVENT is used in place of the 
            //-------------- The ENCODER_DONE event for the time being
            //-------------- Replace with ENCODER_DONE------------Amber
            Drive_Pivot_Left(DRIVE_HIGH);
            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                Drive_Stop(BOTH); //Remove when Encoder is implemented 
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case PivotReverseLeft:
            //----5/27/22--- FAKE_ENCODER_EVENT is used in place of the 
            //-------------- The ENCODER_DONE event for the time being
            //-------------- Replace with ENCODER_DONE------------Amber
            //            if (ThisEvent.EventType == ES_ENTRY) {
            Drive_Pivot_Left(-DRIVE_HIGH);
            //            }
            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                Drive_Stop(BOTH); //Remove when Encoder is implemented 

                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                // another bumper event *****************************************
            } else if (ThisEvent.EventType == FL_PRESSED) {
                /*-------------------Replace with Encoder Events------------------------*/
                Drive_Stop(BOTH);
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                /*---------------------------------------------------------------------*/
                nextState = PivotReverseRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == RL_PRESSED) {

                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                //Testing the rotating tower encoder rn pls uncomment Pivot Forward Right
                nextState = PivotForwardRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            } else if (ThisEvent.EventType == RR_PRESSED) {

                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                nextState = PivotForwardLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            } else if (ThisEvent.EventType == FR_PRESSED) {
                /*-------------------Replace with Encoder Events------------------------*/
                ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                Drive_Stop(BOTH);
                /*----------------------------------------------------------------------*/
                nextState = PivotReverseLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case MidAdjustRotateLeft:
            //            ES_Timer_InitTimer(TempTurnTimer, LINE_CORRECT_LEFT_DURATION); //Moved timer init to 
            Drive_Tank_Turn_Left(DRIVE_MED);
            if (ThisEvent.EventType == FLOOR_LIGHT_CHANGE) {
                if (CompareToEventParam(FT_ENTRY, ThisEvent.EventParam)) {
                    //            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) { //Should not be on a timer should rotate until no longer reading front center tape --Amber 
                    // FIX ME: add motor adjustment to align with the tape field ....NO! bvk n kaixin
                    Drive_Stop(BOTH); //Remove when Encoder is implemented 
                    nextState = ActiveIdle;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                } else if (CompareToEventParam(SR_ENTRY, ThisEvent.EventParam)) { // reached the corner of the tape field
                    /*-------------------Replace with Encoder Events------------------------*/
                    //                        ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION); //Should Not be on a timer 
                    Drive_Stop(BOTH);
                    /*----------------------------------------------------------------------*/

                    // maybe needs to be forward 2 inches?
                    nextState = SearchRotation;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                }

            } else if (ThisEvent.EventType == FAKE_ENCODER_EVENT) { // timeout on re adjust to stay on line timeout
                Drive_Stop(BOTH);
                nextState = MidAdjustRotateRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(TempTurnTimer, LINE_CORRECT_RIGHT_DURATION);
            } else {
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case MidAdjustRotateRight:
            //Moving this to wherever there is a transition to MidAdjustRotateRight
            //            ES_Timer_InitTimer(TempTurnTimer, LINE_CORRECT_RIGHT_DURATION);
            Drive_Tank_Turn_Right(DRIVE_MED);
            if (ThisEvent.EventType == FLOOR_LIGHT_CHANGE) {
                if (CompareToEventParam(FT_ENTRY, ThisEvent.EventParam)) {
                    //            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) { //Should not be on a timer should rotate until no longer reading front center tape --Amber 
                    // FIX ME: add motor adjustment to align with the tape field ....NO! bvk n kaixin
                    Drive_Stop(BOTH); //Remove when Encoder is implemented 
                    nextState = ActiveIdle;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                } else if (CompareToEventParam(SR_ENTRY, ThisEvent.EventParam)) { // reached the corner of the tape field
                    /*-------------------Replace with Encoder Events------------------------*/
                    //                        ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION); //Should Not be on a timer 
                    Drive_Stop(BOTH);
                    /*----------------------------------------------------------------------*/

                    // maybe needs to be forward 2 inches?
                    nextState = SearchRotation;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                }
            } else if (ThisEvent.EventType == FAKE_ENCODER_EVENT) { // timeout on re adjust to stay on line timeout
                Drive_Stop(BOTH);
                nextState = ActiveIdle; // 6/7 Kaixin: maybe rotate before deciding that we are our of tape line --> changed from ActiveIdle to Rotate2Next
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else {
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case SearchRotation:
            if (ThisEvent.EventType == ES_ENTRY) {
                DriveEvent.EventType = TANK_TURN_LEFT_180; // rotates 180 degrees to search for tower in that specific quadrant ** will need 
                PostEncoderService(DriveEvent);
            }//Changed to else if instead of if 5/30/22 Amber
            else if (ThisEvent.EventType == ENCODER_DONE) { // previous encoder complete
                // simple solution -- Drive_Stop(BOTH) resets both encoder ticks and turns the rt and lt off. (Sends a ENCODER_RESET event)
                Drive_Stop(BOTH);
                nextState = Rotate2Next;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
            //            Below is changed base don the state machine since we looking for tower from corner of the field
            //        case Rotate2Face:
            //            //----5/27/22--- FAKE_ENCODER_EVENT is used in place of the 
            //            //-------------- The ENCODER_DONE event for the time being
            //            //-------------- Replace with ENCODER_DONE------------Amber
            //            Gradual_Turn_Left(DRIVE_HIGH);
            //            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
            //                Drive_Stop(BOTH); //Remove when Encoder is implemented 
            //                DriveEvent.EventType = DRIVE_FORWARD_FULL;
            //                PostEncoderService(DriveEvent);
            //                nextState = Move2Mid;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //            break;
            //        case Move2Mid:
            //            if (ThisEvent.EventType == ENCODER_DONE) {
            //                DriveEvent.EventType = TANK_TURN_LEFT_90;
            //                PostEncoderService(DriveEvent);
            //                nextState = Rotate360;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //            break;
            //        case Rotate360:
            //            // post event to rotate 360 degrees // I guess we aren't stopping before we change directions or anything? could b implemented in the motor driver or smtg
            //            if (ThisEvent.EventType == ES_ENTRY) {
            //                DriveEvent.EventType = TANK_TURN_LEFT_360;
            //                PostEncoderService(DriveEvent);
            //            }
            //            if (ThisEvent.EventType == ES_EXIT) {
            ////                DriveEvent.EventType = TANK_TURN_LEFT_360;
            ////                PostEncoderService(DriveEvent);
            //                Drive_Stop(BOTH);
            //            }
            //            if (ThisEvent.EventType == ENCODER_DONE) {
            //                // problem is that encoder does not count ticks from both motors
            //                // in unison, typically slightly off. 
            //                // BVK re-writing by checking the event-parameters
            //                // ENCODER_DONE param is 1 -> right motor
            //                //                       2 -> left motor
            //                //                       3 -> both. 
            //                // check for sum of 3. when sum = 3, either from a single event
            //                //       or from 2 separate events, we should have gone 90 degrees
            //
            //                // changed my mind. easier to make a single case in encoder where
            //                // we turn 360 degrees. Still need to account for both motors being done
            //
            //
            //
            //                //                if (count != NUM_OF_TURNS) {
            //                // going to need to reset this guy when we finish
            ////                encoder_side_sum += ThisEvent.EventParam;
            //                
            //                    // send another eent to keep turning.
            ////                    DriveEvent.EventType = TANK_TURN_LEFT_360;
            ////                    PostEncoderService(DriveEvent);
            //                    // increment count so we go around 4 times. 
            //                    
            //                    //                    }
            //                encoder_side_sum += ThisEvent.EventParam;
            //                if (encoder_side_sum == 3) {
            //                    DriveEvent.EventType = DRIVE_REVERSE_FULL;
            //                    PostEncoderService(DriveEvent);
            //                    nextState = Move2Corner;
            //                    makeTransition = TRUE;
            //                    count = 0;
            //                }
            //                else{
            //                    // only return when we know both are done. 
            //                    break;
            //                }
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //
            //            break;
            //        case Move2Corner:
            //            if (ThisEvent.EventType == ENCODER_DONE) {
            //                DriveEvent.EventType = TANK_TURN_LEFT_90;
            //                PostEncoderService(DriveEvent);
            //                nextState = Rotate2Next;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //            break;
            //            Above is changed base don the state machine since we looking for tower from corner of the field
        case Rotate2Next:
            if (ThisEvent.EventType == ES_ENTRY) {
                // 90 degree turn right to reposition on the Tape to follow tape CCW (counter clock wise)
                DriveEvent.EventType = TANK_TURN_RIGHT_90; // rotates 90 degrees to move to next quadrant
                PostEncoderService(DriveEvent);
            }
            if (ThisEvent.EventType == ENCODER_DONE) {
                // encoder finished.
                // simple solution -- Drive_Stop(BOTH) resets both encoder ticks and turns the rt and lt off. (Sends a ENCODER_RESET event)
                Drive_Stop(BOTH);
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
            //Reverse before pivot turn
        case Reverse_Buffer:
            if (ThisEvent.EventType == ES_ENTRY) {
                Drive_Straight(-DRIVE_HIGH);
                ES_Timer_InitTimer(TempTurnTimer, REVERSE_DURATION);

            } else if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                nextState = DangerZone;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                Drive_Stop(BOTH);
            }
            break;
            //Handles event when FCT and FRT is High but RRT is Low
        case ReverseAfterFrontTripped:
            if (ThisEvent.EventType == ES_ENTRY) {
                Drive_Tank_Turn_Right(-DRIVE_HIGH);
                ES_Timer_InitTimer(TempTurnTimer, REVERSE_DURATION);

            } else if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                Drive_Stop(BOTH);
            }
            break;
        case DangerZone:
            if (ThisEvent.EventType == ES_ENTRY) {
                DriveEvent.EventType = TANK_TURN_LEFT_90;
                PostEncoderService(DriveEvent);
            } else if (ThisEvent.EventType == ENCODER_DONE) {
                //                Drive_Stop(BOTH);
                Drive_Straight(DRIVE_HIGH);
                nextState = ActiveIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunActiveSearchSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunActiveSearchSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

