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
#include "TowerScopeSubHSM.h"
#include "CircleTowerSubHSM.h"
#include "CorrectSideFoundSubHSM.h"
#include "CorrectHoleFoundSubHSM.h"
#include "DeadBotAvoidSubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    ApproachTowerState,
    AlignWithTowerState,
    CircleTowerState,
    ReverseCircleTowerState,
    DeadBotAvoidState,
    CorrectSideFoundState,
    CorrectHoleFoundState,
    ShootBallState,
    DriveAwayState,
    // back bumpers caught
    // tape? -- ignore
    // side beacon detects? -- could 


} TowerSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "ApproachTowerState",
    "AlignWithTowerState",
    "CircleTowerState",
    "ReverseCircleTowerState",
    "DeadBotAvoidState",
    "CorrectSideFoundState",
    "CorrectHoleFoundState",
    "ShootBallState",
    "DriveAwayState",
};

#define ABANDONE_TOWER_MS 7000 // if we tried to score already, wait 30 seconds and if we don't score again, go right into next tower
#define ABANDONE_SIDE_MS  10000
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

static TowerSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static uint8_t shoot_again = TRUE;


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
uint8_t InitTowerSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    //if (InitTowerScopeSubHSM()) { // if sub sub hsm init returns true, init this one
    returnEvent = RunTowerSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    //}

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
ES_Event RunTowerSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TowerSubHSMState_t nextState; // <- change type to correct enum
    ES_Event DriveEvent;
    ES_Tattle(); // trace call stack
    //    ThisEvent = RunTowerScopeSubHSM(ThisEvent);
    //    if(ThisEvent.EventType == BEACON_WITHIN_DIGITAL_RANGE || ThisEvent.EventType == BEACON_NOT_WITHIN_DIGITAL_RANGE){
    //        ThisEvent.EventType = ES_NO_EVENT;
    //    }

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = ApproachTowerState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case ApproachTowerState: // in the first state, replace this with correct names
            ThisEvent = RunTowerApproachSubHSM(ThisEvent); // run sub event 
            switch (ThisEvent.EventType) {
                    //                case ES_ENTRY:
                    //B-Line the tower
                    //                    Drive_Stop(BOTH); // reset any encoder stuff for now.
                    //                    break;

                    // if either front bumper is pressed we want to go into Tower Scope Sub HSM    
                case FL_PRESSED: // BK 9pm 5/30/2022          
                    nextState = DeadBotAvoidState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    DriveEvent.EventType = REVERSE_TOWER;
                    PostEncoderService(DriveEvent);
                    break;
                case FR_PRESSED: // This is intentionally both without a break btn the two
                    nextState = DeadBotAvoidState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    DriveEvent.EventType = REVERSE_TOWER;
                    PostEncoderService(DriveEvent);
                    break;
                case RR_PRESSED:
                    // TESTING ONLY FIXZ MEEEEEEEEEEEEEEEEEEEE PLEASEE
                    //                    Solenoid_Fire();
                    break;
                    // BVK 5pm 3/31 we need to start the encoder event. can do it up here^ or in here. In here is closer to the Encoder Done state in the next FSM. I don't want to miss the event. 
                    //                case ES_EXIT: // FIX ME!!!!!!! IDK IF IM SUPPOSED TO BE HERE (referring to this test case)
                    //                    DriveEvent.EventType = REVERSE_TOWER;
                    //                    PostEncoderService(DriveEvent);
                    //                    break;

                case BEACON_NOT_WITHIN_ANALOG_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
            //            NOT USED ANYMORE cuz changing HSM
            // Align perpendicular to thing we bumped into    
            //        case AlignWithTowerState:
            //            ThisEvent = RunTowerScopeSubHSM(ThisEvent);
            //            switch (ThisEvent.EventType) {
            //                case FLOOR_LIGHT_CHANGE: // do we just back up a little and keep turning? 
            //
            //                    break; // 
            //                case BEACON_WITHIN_ANALOG_RANGE: // after side aligning we see the beacon up close!
            //                    nextState = CircleTowerState; //  
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                    // actually not sure it will enter here...   
            //                case BEACON_NOT_WITHIN_ANALOG_RANGE: // after side aligning we do not see beacon -- dead bot
            //                    nextState = DeadBotAvoidState; //  
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                default:
            //                    break;
            //            }
            //            break;
            //            NOT USED ANYMORE cuz changing HSM
        case CircleTowerState:

            ThisEvent = RunCircleTowerSubHSM(ThisEvent); // run sub event 
            //            Drive_Stop(BOTH);
            switch (ThisEvent.EventType) {
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TW_DETECTED: // ** FOUND SIDE!! :)
                    // ONLY TRIGGER WHEN BOTH?
                    //                    if(ThisEvent.EventParam == A_TW_MASK &)
//                    ES_Timer_StopTimer(BREAKOUTIMER);  // should stop timer when this hsm runs exit on the sub sub hsm 
                    nextState = CorrectSideFoundState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    if() // conditional that reads the parameter? and makes an intelligent movement?
                    // Start Encoder Event for checking if rear is also detected?
                    DriveEvent.EventType = TW_ALIGN_PT_LEFT_REV;
                    PostEncoderService(DriveEvent);
                    
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case ReverseCircleTowerState:

            break;


        case DeadBotAvoidState:
            ThisEvent = RunDeadBotAvoidSubHSM(ThisEvent); // run sub event 
            switch (ThisEvent.EventType) {
                    //                case ES_ENTRY:
                    //                    ES_Init_Timer(TowerHelperTimer, )
                    //                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_ANALOG_RANGE: // im here just in case --> delete me if u want
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE:
                    nextState = CircleTowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    DriveEvent.EventType = REVERSE_TOWER;
                    PostEncoderService(DriveEvent);
                    break;
                case FIND_NEXT_TOWER:
                    nextState = ApproachTowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = FIND_NEXT_TOWER;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case CorrectSideFoundState:
            ThisEvent = RunCorrectSideFoundSubHSM(ThisEvent); // run sub event 
            //            Drive_Stop(BOTH);
            ES_Tattle();
            switch (ThisEvent.EventType) {
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    // we may accidentally square up on the wrong side, don't want to shoot there. this adds security
                case SQUARE_ON_CORRECT_SIDE: // should b tape detected // or do we pass up SQUARE_ON_CORRECT_SIDE from lower states? 
                    //                    Solenoid_Fire(); // for shits, giggles, and minspec

                    nextState = CorrectHoleFoundState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    DriveEvent.EventType = DRIVE_REVERSE_QTR; // just go back another inch
                    PostEncoderService(DriveEvent);
                    ES_Timer_InitTimer(FINDHOLETIMEOUTTIMER, ABANDONE_SIDE_MS); // start timer to give up on the tower if we don't find the correct hole in 10 seconds. 
                    break;
                case FOUND_CORRECT_HOLE_EARLY:
                    // fire solenoid. 
                    Drive_Stop(BOTH);
                    Solenoid_Fire();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case SHOT_BALL_MOVE_ON: // WHEN WE FINISH SHOOTING
                    
                    // init timer to move onto next tower if we can't score on this one. // bvk 6/5/2022 9:30pm
                    ES_Timer_InitTimer(SHOT_EARLY_MOVEON, ABANDONE_TOWER_MS);
                    nextState = CorrectHoleFoundState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    DriveEvent.EventType = DRIVE_REVERSE_QTR; // just go back another inch
                    PostEncoderService(DriveEvent);
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }

            break;
        case CorrectHoleFoundState: // searching for correct hole. misnomer
            //            Drive_Stop(BOTH);
            //            DriveEvent.EventType = DRIVE_REVERSE_QTR; // just go back another inch
            //            PostEncoderService(DriveEvent);
            // start timeout to give up on trying to find the correct hole. a backup in case we go nuts shuffling forwards and backwards
            ThisEvent = RunCorrectHoleFoundSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = DRIVE_FORWARD_HALF; // consider taking this out
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ENCODER_DONE:
                    //                    nextState = DriveAwayState; //  
                    //                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    //                case TW_NOT_DETECTED:
                    //                    //6/2/22 Potentially Add in state transition to go back to CorrectSideFound 
                    //                    break;
                case FOUND_HOLE:
                    ES_Timer_StopTimer(FINDHOLETIMEOUT);
                    Drive_Stop(BOTH);
                    nextState = ShootBallState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    
                case FINDHOLETIMEOUT:// we took too long. re init to re set the initial conditions of the sub HSM and move onto find next tower
                    InitCorrectHoleFoundSubHSM(); // 6/6/ 11:36pm idk why this is here 6/7 12:45 - re
                    nextState = DriveAwayState; //  actually transition to drive away
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT; // drive forward and get outta here
                    break;
                case ES_TIMEOUT:
                    // get on outta there tbh it's been too long
                    if (ThisEvent.EventParam == SHOT_EARLY_MOVEON) { // idk if this will work or not. 
                        nextState = DriveAwayState; //  actually transition to drive away
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    //                    else if(ThisEvent.EventParam == FINDHOLETIMEOUT){ 
                    //                        
                    //                    }
                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case ShootBallState:
            //            ThisEvent = RunCircleTowerSubHSM(ThisEvent); // run sub event 
            Drive_Stop(BOTH);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Solenoid_Fire();
                    shoot_again = TRUE;
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case SHOT_BALL:
                    if (shoot_again) {
                        shoot_again = FALSE;
                        Solenoid_Fire();
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else {
                        // going to wait 2 seconds before driving away
                        //                        nextState = DriveAwayState; //  
                        //                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;
                case SHOT_BALL_MOVE_ON:
                    nextState = DriveAwayState; //  actually transition to drive away
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }

            break;
        case DriveAwayState:
            //            Drive_Stop(BOTH);//FIX MEEE!!!!! keep driving away
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DriveEvent.EventType = DRIVE_FORWARD_FULL;
                    PostEncoderService(DriveEvent);
                    break;
                case FLOOR_LIGHT_CHANGE: // what if we drive forward and see tape? need to drive backwards right? what if we hit bumpers??? a lotta cases here smh
                    if (ThisEvent.EventParam == (FRONT_TS)) {
                        DriveEvent.EventType = DRIVE_REVERSE_FULL;
                        PostEncoderService(DriveEvent);
                    }
                    break;
                case BEACON_WITHIN_DIGITAL_RANGE:
                    nextState = ApproachTowerState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = FIND_NEXT_TOWER;
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    nextState = ApproachTowerState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = FIND_NEXT_TOWER;
                    break;
                case ENCODER_DONE:
                    nextState = ApproachTowerState; //  
                    makeTransition = TRUE;
                    ThisEvent.EventType = FIND_NEXT_TOWER;
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
        RunTowerSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTowerSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

