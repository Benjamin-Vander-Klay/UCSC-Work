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
#include "TowerScopeSubHSM.h"
#include "Sense_EventChecker.h" // oop yoink
#include "AD.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    DriveReverseState, // back up so we can rotate
    AlignOnSideState, // align with left side facing tower so we can look at object
    LookWithSideBeaconState, // read AD Beacon on side and see if we see a beacon
    ScootCloserLeftState,
    ScootCloserRightState,
    FindCenterState,
    TowerFoundState, // we determine it is a tower after searching for the beacon
    DeadBotFoundState,
    RealignToTower,

} TowerScopeSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "DriveReverseState",
    "AlignOnSideState",
    "LookWithSideBeacon",
    "ScootCloserStateLeft",
    "ScootCloserRightState",
    "FindCenterState",
    "TowerFoundState",
    "DeadBotFoundState",
    "RealignToTower",
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

static TowerScopeSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static int16_t max_beacon_ad; // 0 - 1023? actually only top half!
static int16_t current_beacon_ad;

// if we do not need to be in this state then we just return the event to the tower HSM 


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
uint8_t InitTowerScopeSubHSM(void) {
    ES_Event returnEvent;
    CurrentState = InitPSubState;
    RunTowerScopeSubHSM(INIT_EVENT);
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
ES_Event RunTowerScopeSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TowerScopeSubHSMState_t nextState; // <- change type to correct enum
    ES_Event DriveEvent;
    ES_Tattle(); // trace call stack
    static uint8_t encoder_sum; // default 0
    static int8_t checked_front = TRUE; // should default to 0 but not taking chances
    static uint8_t tower_found = FALSE; // flag raised if we see the beacon with the analog beacon detector

    if ((ThisEvent.EventType == BEACON_NOT_WITHIN_DIGITAL_RANGE) || (ThisEvent.EventType == BEACON_WITHIN_DIGITAL_RANGE)) {
        ThisEvent.EventType = ES_NO_EVENT;
    }

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = DriveReverseState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case DriveReverseState: // drive backwards like 3 inches to have space to tank turn right
            switch (ThisEvent.EventType) {
                    // can either set encoder drive in entry and init this fsm when we call it a new time, or we can do encoder when we exit tower approach   <<-- on ApproachTowerState EXIT
                case ES_ENTRY: // drive backwards qtr rotation
                    //                    DriveEvent.EventType = DRIVE_REVERSE_HALF; // backs up specific amount. Amount to be determined soon. 4pm 5/30 bvk
                    //                    PostEncoderService(DriveEvent);
                    // return no event?
                    break;
                case FL_PRESSED:
                    DriveEvent.EventType = DRIVE_REVERSE_QTR; // backs up specific amount. Amount to be determined soon. 4pm 5/30 bvk
                    PostEncoderService(DriveEvent);
                    break;
                case FR_PRESSED:
                    DriveEvent.EventType = DRIVE_REVERSE_QTR; // backs up specific amount. Amount to be determined soon. 4pm 5/30 bvk 5/31/21 Changed to qtr rather than half ---K
                    PostEncoderService(DriveEvent);
                    break;

                case ENCODER_DONE: // previous encoder drive complete
                    // simple solution -- Drive_Stop(BOTH) resets both encoder ticks and turns the rt and lt off. (Sends a ENCODER_RESET event)
                    //Drive_Stop(BOTH);
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 1 + 2 == 3 
                    printf("encoder sum: %d", encoder_sum);
                    if (encoder_sum >= 3) { // we have backed up exactly this many clicks 
                        encoder_sum = 0; // reset sum 
                        // don't need to stop motors(hopefully)
                        // transition to next state
                        //                        printf("\r\n move to align");
                        nextState = AlignOnSideState; // align on side 
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        return ThisEvent;
                    }
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE: // so that we complete our maneuver
                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    return ThisEvent;
                    break;
                case ES_NO_EVENT:
                    break;
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case AlignOnSideState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY: // [perform encoder event]
                    //                    Drive_Stop(BOTH); // for now. change later to be 90 degree tank turn right
                    DriveEvent.EventType = TANK_TURN_RIGHT_90;
                    PostEncoderService(DriveEvent);
                    break;
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
                        encoder_sum = 0; // reset sum 
                        // don't need to stop motors(hopefully)
                        // transition to next state
                        nextState = LookWithSideBeaconState; // align on side 
                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                    } //else {
                    ThisEvent.EventType = ES_NO_EVENT;
                    //                        return ThisEvent;
                    //                  }
                    break;
                case BEACON_NOT_WITHIN_DIGITAL_RANGE: // eat the event so that we complete our turn
                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    return ThisEvent;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE: // not entirely sure we want to do this here but just in case
                    tower_found = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT; // hope this don't break it? we don't want to stop and move state when we do this. we want to finish the turn

                    break;
                case FR_PRESSED: // if we hit the front right bumper while doing this -- dead bot or anoher tower? 
                    Drive_Stop(BOTH_NO_RESET); // instead of doing both. this should not reset motor
                    Drive_Stop(RIGHT); // weird that we dont j stop the right one? tf. bvk 6pm 5/31
                default:
                    break;
            }
            break;

        case LookWithSideBeaconState: // tbd if needed
            //            Drive_Stop(BOTH); // for now. change later to be 90 degree tank turn right

            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            // WHY NOT JUST CALL THE EVENT CHECKER? 
            //            CheckforBeaconAnalog();

            // fuck it just check manually, and if within hysteresis bound we count it? -- BVK 6:15 5/31 CRASHED 6:30PM 5/31 BVK
            //            if (AD_IsNewDataReady()) {
            //                current_beacon_ad = Read_Analog_Beacon(); // don't crash uno 
            //            }
            //            //    unsigned int beaconReading = Read_Analog_Beacon();
            //
            //            if (current_beacon_ad < BEACON_RANGE_LOW) {
            //                //        cur_beac_state = NO_BEAC;
            //                ThisEvent.EventType = BEACON_NOT_WITHIN_ANALOG_RANGE; // may cause us to transition still tbh
            //            }                // hopefully more secure
            //            else if (current_beacon_ad > BEACON_RANGE_HIGH) {
            //                //        cur_beac_state = YES_BEAC;
            //                ThisEvent.EventType = BEACON_WITHIN_ANALOG_RANGE; 
            //            }
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // drive forward 4 inches and then back 8 inches
                    DriveEvent.EventType = DRIVE_FORWARD_HALF;
                    PostEncoderService(DriveEvent);
                    break;
                case BEACON_WITHIN_ANALOG_RANGE: // we see it on the side
                    Drive_Stop(BOTH); // gonna do more in a second
                    // we're gonna scoot closer!!
                    // pivot 
                    // tank turn right
                    // save current AD value? perhaps
                    //                    max_beacon_ad = current_beacon_ad; // first look

                    //                    DriveEvent.EventType = SCOOT_LEFT;
                    //                    PostEncoderService(DriveEvent);

                    // new version 6pm 5/31 bvk
                    ThisEvent.EventType = ES_NO_EVENT; // not 100% sure abt this but don't transistion to circle tower yet
                    nextState = ScootCloserLeftState; // align on side 
                    makeTransition = TRUE;

                    // old version
                    // stop motors and reset encoders
                    //                    Drive_Stop(BOTH);
                    //                    ThisEvent.EventType = BEACON_WITHIN_ANALOG_RANGE; // change state in mid level tower sub HSM
                    //                    return ThisEvent;
                    break; // we wont break we'll just return but fuck it
                case BEACON_NOT_WITHIN_DIGITAL_RANGE:
                    // eat the event. we dont care, we have found the tower
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                    // we 
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
                        encoder_sum = 0; // reset sum
                        // check when we finish this too
                        //                        CheckforBeaconAnalog(); // maybe will post event in time to catch it later? -- did not work. 6:15pm 5/31 bvk
                        // initially true. 
                        if (checked_front) {
                            checked_front = FALSE; // fuck this sheit
                            // now we set the encoder up to check here -- note how we don't transition to this state again. that would cause re-entry ***
                            // if we re-entered we would drive forward again. 
                            DriveEvent.EventType = DRIVE_REVERSE_FULL;
                            PostEncoderService(DriveEvent);
                        } else { // we now use rotary encoder to check behind us
                            // we now have checked front and rear, we did not see ... move out of this FSM and into DEAD BOT AVOID I guess
                            printf("\r\n done checking, should exit tower scope");
                            Drive_Tank_Turn_Right(DRIVE_MED);
                            nextState = DriveReverseState; // RESET FOR NEXT TIME 
                            makeTransition = TRUE;
                            ThisEvent.EventType = BEACON_NOT_WITHIN_ANALOG_RANGE; // so higher level will deal with it. 
                        }
                        //                        // transition to next state
                        //                        nextState = DriveReverseState; // align on side 
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                    } else {
                        ThisEvent.EventType = ES_NO_EVENT;
                        //return ThisEvent;
                    }
                    break;
                    // 1:00 pm 5/31/22--Amber While Aligning with tower one of the bumpers is triggered 
                    // For all cases the bot will adjust a minor amount based off of a timer 
                case RL_PRESSED: // pivot forward left a tiny bit? 
                    // 5-31 Amber //Keeping the Init Timer Functions in each case, can be set ES_EXIT
                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
                    Drive_Pivot_Left(DRIVE_MED);
                    break;

                case RR_PRESSED:
                    //                    (ThisEvent.EventParam == TempTurnTimer)
                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
                    Drive_Pivot_Left(DRIVE_MED); // 5-31-22 Please Change motor function prolly chose wrong direction !!!!!!!!!
                    break;

                case FL_PRESSED:
                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
                    Drive_Pivot_Left(-DRIVE_MED); // 5-31-22 Please Change motor function!!!!!!!!!
                    break;

                case FR_PRESSED:
                    ES_Timer_InitTimer(TowerHelperTimer, MINOR_ALIGN_ADJUST);
                    Drive_Pivot_Left(-DRIVE_MED); // 5-31-22 Please Change motor function!!!!!!!!!
                    break;
                case FLOOR_LIGHT_CHANGE:

                    break;
                case ES_NO_EVENT:
                    break;
            }
            break;

        case ScootCloserLeftState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // perform scoot!
                    DriveEvent.EventType = SCOOT_LEFT;
                    PostEncoderService(DriveEvent);
                    break;
                    // finished scoot left -> scoot right (tank turn for now?)
                case ENCODER_DONE:
//                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
//                    if (encoder_sum >= 1) { // we have backed up exactly this many clicks // -------------------------------------------- <<< 2!! only works for PIVOTING!!!!
//                        encoder_sum = 0; // reset sum

                        // go to scoot right
                        nextState = ScootCloserRightState;
                        makeTransition = TRUE;
//                        break;
//                    }
                    ThisEvent.EventType = ES_NO_EVENT; // pass nothing up the chain
                    // we hit something oml hopefully tower 
                    break;
                case FR_PRESSED: // then we know we 
                    Drive_Stop(BOTH); // reset encoders and tank turn to try and hit other ones? maybe just straighten out! we are squarish and don't want to get stuck. 

                    break;
                case BEACON_NOT_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }

            break;
        case ScootCloserRightState: // to straighten out and maybe hit a bumper tho I am worried abt getting stuck.
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // perform scoot!
                    DriveEvent.EventType = SCOOT_RIGHT;
                    PostEncoderService(DriveEvent);
                    break;
                    // finished scoot left -> scoot right (tank turn for now?)
                case ENCODER_DONE:
                    encoder_sum += ThisEvent.EventParam; // 1 if right, 2 if left, 3 if both. 
                    if (encoder_sum == 3) { // we have backed up exactly this many clicks 
                        encoder_sum = 0; // reset sum
                        
                        // go to scoot right
                        nextState = ScootCloserLeftState;
                        makeTransition = TRUE;
                        break;
                    }
                    ThisEvent.EventType = ES_NO_EVENT; // pass nothing up the chain
                    // we hit something oml hopefully tower 
                    break;
                case FR_PRESSED: // then we know we 
                    Drive_Stop(BOTH); // reset encoders and tank turn to try and hit other ones? maybe just straighten out! we are squarish and don't want to get stuck. 

                    break;

                case BEACON_NOT_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BEACON_WITHIN_ANALOG_RANGE: // WILL happen. need to eat this event
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;
            //This case is only to Receive Timeout Events And then for now being returned to the previous state 
            //        case RealignToTower:
            //            
            //            break;
        case FindCenterState:
            Drive_Stop(BOTH); // for now. will go forwards and backwards to find max of beacon. maybe also scooting? 
            break;
        case ES_TIMEOUT:
            if (ThisEvent.EventParam == TowerHelperTimer) {
            }
            // transition to next state
            nextState = LookWithSideBeaconState; // align on side 
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTowerScopeSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTowerScopeSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

