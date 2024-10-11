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
#include "FindTapeSubHSM.h"
#include "Sense_EventChecker.h"
#include "SimpleFunctionService.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitFindTapeSubState,
    FindTapeIdle,
    PivotReverseRight,
    PivotForwardRight,
    PivotReverseLeft,
    PivotForwardLeft,
    MidAdjustRotate,
    Exit, // FIX ME: delete after testing this specific sub hsm
} FindTapeSubHSMState_t;

static const char *StateNames[] = {
    "InitFindTapeSubState",
    "FindTapeIdle",
    "PivotReverseRight",
    "PivotForwardRight",
    "PivotReverseLeft",
    "PivotForwardLeft",
    "MidAdjustRotate",
    "Exit", // FIX ME: delete after testing this specific sub hsm
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

static FindTapeSubHSMState_t CurrentState = InitFindTapeSubState; // <- change name to match ENUM check
static uint8_t MyPriority;
//#define NUM_OF_TURNS 3

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
uint8_t InitFindTapeSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitFindTapeSubState;
    returnEvent = RunFindTapeSubHSM(INIT_EVENT);
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

ES_Event RunFindTapeSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    FindTapeSubHSMState_t nextState; // <- change type to correct enum
    //    int count = 0;
    ES_Tattle(); // trace call stack
    ES_Event DriveEvent;
    switch (CurrentState) {
        case InitFindTapeSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                // starts the 3.5 second timer that when in this subhsm adds a small tank turn adjustment to prevent getting stuck. Is reinitialized when the timer expires
                ES_Timer_InitTimer(MidAdjustTimer, ACTIVE_DURATION);
                nextState = FindTapeIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

            // Checking if bumpers are pressed -> bumpers ARE pressed, we 
            // checking if tape sensors go off
            // FIND TAPE 
        case FindTapeIdle: // FIX ME!!!!! NEED TO ADD TIMER IN THIS STATE TO GO TO MIDADJUST AFTER CERTAIN TIME
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // when enter the Find Tape Idle, start timer to count seconds before stopping and adjusting
                    // adjust only if we don't find tape. We could stop the timer if something else happens
//                    ES_Timer_InitTimer(MidAdjustTimer, ACTIVE_DURATION);
                    Drive_Straight(DRIVE_HIGH);
                    /*---------------------------------------------------------------------*/
                    // Simple Service function will return a MAR_END event when this timer is finished. 
                    // 
                    //                    nextState = PivotReverseRight;
                    //                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case FL_PRESSED:
                    /*-------------------Replace with Encoder Events------------------------*/
                    Drive_Stop(BOTH);
                    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    /*---------------------------------------------------------------------*/
                    nextState = PivotReverseRight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case RL_PRESSED:
                    /*-------------------Replace with Encoder Events------------------------*/
                    ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    Drive_Stop(BOTH);
                    /*----------------------------------------------------------------------*/
                    //Testing the rotating tower encoder rn pls uncomment Pivot Forward Right
                    nextState = PivotForwardRight;
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
                    //                    Dont think we need the stuff below in this state machine
                    //                case FLOOR_LIGHT_CHANGE: // FIX ME!!!!: idk if i should be here
                    //                    if (ThisEvent.EventType == FAKE_ENCODER_EVENT) { // FIX ME!!!!: idk if i should be here
                    //                        Drive_Stop(BOTH); //Remove when Encoder is implemented  // FIX ME!!!!: idk if i should be here
                    //                        nextState = Exit; // FIX ME!!!!: idk if i should be here
                    //                        makeTransition = TRUE; // FIX ME!!!!: idk if i should be here
                    //                        ThisEvent.EventType = ES_NO_EVENT; // FIX ME!!!!: idk if i should be here
                    //                    } // FIX ME!!!!: idk if i should be here
                    //                    break; // FIX ME!!!!: idk if i should be here
                    //                    if (ThisEvent.EventParam == R2Q_ENTRY) { // reached the corner of the tape field
                    //                        /*-------------------Replace with Encoder Events------------------------*/
                    //                        ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    //                        Drive_Stop(BOTH);
                    //                        /*----------------------------------------------------------------------*/
                    //                        nextState = SearchRotation;
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //
                    //                    }
                    //                    if (ThisEvent.EventParam == MAR_ENTRY) { // reset the bot to align with the tape 
                    //                        /*-------------------Replace with Encoder Events------------------------*/
                    //                        ES_Timer_InitTimer(TempTurnTimer, TEMP_DRIVE_DURATION);
                    //                        Drive_Stop(BOTH);
                    //                        /*----------------------------------------------------------------------*/
                    //                        nextState = MidAdjustRotate;
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //
                    //                    } else {
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                    }
                    //                    break;
                    //                    Dont think we need the stuff above in this state machine
                case MAR_END: // timeout on mid adjust rotate timer. transition to MidAdjust Rotate
                    nextState = MidAdjustRotate;
                    ES_Timer_InitTimer(MidAdjustTimer, MIDROTATE_DURATION);
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            // END OF IDLE
            //NOTE: IT IS NOT NECESSARY FOR THESE TO BE SEPARATE STATES AS THE PIVOT MOTOR FUNCTIONS ARE CALLED BY ACTIVE IDLE 
            //Keeping as separate cases in case there is need to add more transitions later down the line     
        case PivotReverseRight:
            //----5/27/22--- Fake Encoder Event is used in place of the 
            //-------------- The ENCODER_DONE event for the time being
            //-------------- Replace with ENCODER_DONE------------Amber
            //            Drive_Stop(BOTH);
            Drive_Pivot_Right(-DRIVE_HIGH);
            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) { // finished turning. return to idle
                Drive_Stop(BOTH); //Remove when Encoder is implemented 
                nextState = FindTapeIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == MAR_END) { // the 3.5 second timeout occured, tank turn right.. for now
                nextState = MidAdjustRotate;
                ES_Timer_InitTimer(MidAdjustTimer, MIDROTATE_DURATION);
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
                nextState = FindTapeIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == MAR_END) { // the 3.5 second timeout occured, tank turn right.. for now
                nextState = MidAdjustRotate;
                ES_Timer_InitTimer(MidAdjustTimer, MIDROTATE_DURATION);
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
                nextState = FindTapeIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                
            } else if (ThisEvent.EventType == MAR_END) { // the 3.5 second timeout occured, tank turn right.. for now
                nextState = MidAdjustRotate;
                ES_Timer_InitTimer(MidAdjustTimer, MIDROTATE_DURATION);
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
        case PivotReverseLeft:
            //----5/27/22--- FAKE_ENCODER_EVENT is used in place of the 
            //-------------- The ENCODER_DONE event for the time being
            //-------------- Replace with ENCODER_DONE------------Amber
            //            if (ThisEvent.EventType == ES_ENTRY) {
            Drive_Pivot_Left(-DRIVE_HIGH);
            //            }
            if (ThisEvent.EventType == FAKE_ENCODER_EVENT) {
                Drive_Stop(BOTH); //Remove when Encoder is implemented 

                nextState = FindTapeIdle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == MAR_END) { // the 3.5 second timeout occured, tank turn right.. for now
                Drive_Stop(BOTH); //Added Drive Stop ---5/30/22 --Amber
                nextState = MidAdjustRotate;
                ES_Timer_InitTimer(MidAdjustTimer, MIDROTATE_DURATION);
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
        case MidAdjustRotate:
            Drive_Tank_Turn_Right(DRIVE_HIGH); // FIX ME: can be changed to another rotation type
            if (ThisEvent.EventType == MAR_END) {
                Drive_Stop(BOTH); //Remove when Encoder is implemented 
                nextState = FindTapeIdle;
                //Reset Mid Adjust Timer left
//                ES_Timer_InitTimer(MidAdjustTimer, ACTIVE_DURATION);
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
            //        case(Exit):
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFindTapeSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFindTapeSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

