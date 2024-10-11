/****************************************************************************
 Module
     ES_Configure.h
 Description
     This file contains macro definitions that are edited by the user to
     adapt the Events and Services framework to a particular application.
 Notes
     
 History
 When           Who     What/Why
 -------------- ---     --------
 01/15/12 10:03 jec      started coding
 *****************************************************************************/

#ifndef CONFIGURE_H
#define CONFIGURE_H



//defines for keyboard input
//#define USE_KEYBOARD_INPUT
//What State machine are we testing
//#define POSTFUNCTION_FOR_KEYBOARD_INPUT PostTopHSM

//define for TattleTale
#define USE_TATTLETALE

//uncomment to supress the entry and exit events
//#define SUPPRESS_EXIT_ENTRY_IN_TATTLE

/****************************************************************************/
// Name/define the events of interest
// Universal events occupy the lowest entries, followed by user-defined events

/****************************************************************************/
typedef enum {
    ES_NO_EVENT, ES_ERROR, /* used to indicate an error from the service */
    ES_INIT, /* used to transition from initial pseudo-state */
    ES_ENTRY, /* used to enter a state*/
    ES_EXIT, /* used to exit a state*/
    ES_KEYINPUT, /* used to signify a key has been pressed*/
    ES_LISTEVENTS, /* used to list events in keyboard input, does not get posted to fsm*/
    ES_TIMEOUT, /* signals that the timer has expired */
    ES_TIMERACTIVE, /* signals that a timer has become active */
    ES_TIMERSTOPPED, /* signals that a timer has stopped*/
    /* User-defined events start here */
    BATTERY_CONNECTED, //10
    BATTERY_DISCONNECTED,
    FL_PRESSED, //12
    FL_UNPRESSED,
    FR_PRESSED,
    FR_UNPRESSED, //15
    RL_PRESSED, //16
    RL_UNPRESSED,
    RR_PRESSED,
    RR_UNPRESSED,
    FLOOR_LIGHT_CHANGE, //20
    LF_DETECTED, //21
    DW_DETECTED, //22
    LW_DETECTED, //23
    BEACON_WITHIN_ANALOG_RANGE, //24
    DF_NONE_DETECTED, //25
    LF_NONE_DETECTED, //26
    BEACON_NOT_WITHIN_ANALOG_RANGE, //27
    BEACON_WITHIN_DIGITAL_RANGE, //28
    BEACON_NOT_WITHIN_DIGITAL_RANGE, //29 
    TW_DETECTED, //TRACK WIRE IS DETECTED //30 
    TW_NOT_DETECTED, //TRACK WIRE IS NO LONGER DETECTED //31
    MAR_END, //32
    ENCODER_TICK, // RISING EDGE FOUND ON ENCODER PIN //33
    ENCODER_DONE, // ENCODER COMPLETED DESIRED  //34
    DRIVE_FORWARD_FULL, //36
    DRIVE_FORWARD_THREE_QTR, //37
    DRIVE_FORWARD_HALF, //38
    DRIVE_FORWARD_QTR, // 39
    DRIVE_FORWARD_EIGHTH, //40
    DRIVE_REVERSE_FULL, //41
    DRIVE_REVERSE_FULL_PLUS, //42
    DRIVE_REVERSE_THREE_QTR, //43
    DRIVE_REVERSE_HALF, // 44
    DRIVE_REVERSE_QTR, //45
    DRIVE_REVERSE_EIGHTH, //46
    REVERSE_TOWER, //47
    REVERSE_ARC_LEFT, //48
    FORWARD_ARC_LEFT, //49
    TANK_TURN_LEFT_90, //50
    TANK_TURN_LEFT_180, //51
    TANK_TURN_LEFT_360, //52
    TANK_TURN_RIGHT_90, //53
    PIVOT_TURN_LEFT_300, //54
    PIVOT_TURN_LEFT_REV_30, //55
    PIVOT_TURN_LEFT_REV_15, //56
    PIVOT_TURN_LEFT_REV_10, // 57        
    PIVOT_TURN_LEFT_30, //5
    PIVOT_TURN_LEFT_15, //5
    PIVOT_TURN_LEFT_10,
    PIVOT_TURN_RIGHT_15, //5     
    PIVOT_TURN_RIGHT_10,
    SCOOT_LEFT, //6
    SCOOT_RIGHT, //6
    SCOOT_REVERSE, //6
    TOWER_SQUARE_LEFT, //6
    TW_ALIGN_PT_LEFT_REV, //6
    TANK_TURN_LEFT_ENTRY, //6
    ENCODER_RESET, //6
    FAKE_ENCODER_EVENT, //6 //TimeOut Event to use in place of Encoder_Done when it is in progress
    SQUARE_ON_CORRECT_SIDE, //6
    FIND_NEXT_TOWER, //6 // returns from tower sub hsm to tower in sight to exit tower top level HSM.      
    LOST_BEACON_EVENT, //7
    SHOT_BALL, //7
    SHOT_BALL_MOVE_ON, //7
    FOUND_HOLE, //7
    FOUND_CORRECT_HOLE_EARLY, //7
    BREAKOUT, 
    FINDHOLETIMEOUT,        

    /* User-defined events end here */
    NUMBEROFEVENTS, //76
} ES_EventTyp_t;

static const char *EventNames[] = {
    "ES_NO_EVENT",
    "ES_ERROR",
    "ES_INIT",
    "ES_ENTRY",
    "ES_EXIT",
    "ES_KEYINPUT",
    "ES_LISTEVENTS",
    "ES_TIMEOUT",
    "ES_TIMERACTIVE",
    "ES_TIMERSTOPPED",
    "BATTERY_CONNECTED", //10
    "BATTERY_DISCONNECTED",
    "FL_PRESSED",
    "FL_UNPRESSED",
    "FR_PRESSED",
    "FR_UNPRESSED",
    "RL_PRESSED",
    "RL_UNPRESSED",
    "RR_PRESSED",
    "RR_UNPRESSED",
    "FLOOR_LIGHT_CHANGE", //20
    "LF_DETECTED",
    "DW_DETECTED",
    "LW_DETECTED",
    "BEACON_WITHIN_ANALOG_RANGE",
    "DF_NONE_DETECTED",
    "LF_NONE_DETECTED",
    "BEACON_NOT_WITHIN_ANALOG_RANGE",
    "BEACON_WITHIN_DIGITAL_RANGE",
    "BEACON_NOT_WITHIN_DIGITAL_RANGE",
    "TW_DETECTED", //30
    "TW_NOT_DETECTED",
    "MAR_END",
    "ENCODER_TICK",
    "ENCODER_DONE",
    "DRIVE_FORWARD_FULL",
    "DRIVE_FORWARD_THREE_QTR",
    "DRIVE_FORWARD_HALF",
    "DRIVE_FORWARD_QTR",
    "DRIVE_FORWARD_EIGHTH", //40
    "DRIVE_REVERSE_FULL",
    "DRIVE_REVERSE_FULL_PLUS",
    "DRIVE_REVERSE_THREE_QTR"
    "DRIVE_REVERSE_HALF",
    "DRIVE_REVERSE_QTR",
    "DRIVE_REVERSE_EIGHTH",
    "REVERSE_TOWER",
    "REVERSE_ARC_LEFT",
    "FORWARD_ARC_LEFT",
    "TANK_TURN_LEFT_90", //50
    "TANK_TURN_LEFT_180",
    "TANK_TURN_LEFT_360",
    "TANK_TURN_RIGHT_90",
    "PIVOT_TURN_LEFT_300",
    "PIVOT_TURN_LEFT_REV_30",
    "PIVOT_TURN_LEFT_REV_15",
    "PIVOT_TURN_LEFT_REV_10",
    "PIVOT_TURN_LEFT_30",
    "PIVOT_TURN_LEFT_15",
    "PIVOT_TURN_LEFT_10",
    "PIVOT_TURN_RIGHT_15",
    "PIVOT_TURN_RIGHT_10",
    "SCOOT_LEFT", 
    "SCOOT_RIGHT",
    "SCOOT_REVERSE",
    "TOWER_SQUARE_LEFT",
    "TW_ALIGN_PT_LEFT_REV",
    "TANK_TURN_LEFT_ENTRY",
    "ENCODER_RESET",
    "FAKE_ENCODER_EVENT",
    "SQUARE_ON_CORRECT_SIDE",
    "FIND_NEXT_TOWER",
    "LOST_BEACON_EVENT", 
    "SHOT_BALL",
    "SHOT_BALL_MOVE_ON",
    "FOUND_HOLE",
    "FOUND_CORRECT_HOLE_EARLY",
    "BREAKOUT",
    "FINDHOLETIMEOUT",
    "NUMBEROFEVENTS",
};




/****************************************************************************/
// This are the name of the Event checking function header file.
#define EVENT_CHECK_HEADER "All_Events.h"

/****************************************************************************/
// This is the list of event checking functions
#define EVENT_CHECK_LIST TemplateCheckBattery, CheckEncoderPWM, CheckBottomTapeforDark, CheckforBeaconDigital, CheckforBeaconAnalog, CheckBothTrackWire, CheckTowerTape,

/****************************************************************************/
// These are the definitions for the post functions to be executed when the
// corresponding timer expires. All 16 must be defined. If you are not using
// a timers, then you can use TIMER_UNUSED
#define TIMER_UNUSED ((pPostFunc)0)
#define TIMER0_RESP_FUNC PostSimpleFunctionService
#define TIMER1_RESP_FUNC PostSimpleFunctionService
#define TIMER2_RESP_FUNC PostSimpleFunctionService
#define TIMER3_RESP_FUNC PostSimpleFunctionService
#define TIMER4_RESP_FUNC PostSimpleFunctionService
#define TIMER5_RESP_FUNC PostSimpleFunctionService
#define TIMER6_RESP_FUNC PostSimpleFunctionService
#define TIMER7_RESP_FUNC PostTopHSM
#define TIMER8_RESP_FUNC PostTopHSM
#define TIMER9_RESP_FUNC PostSimpleFunctionService
#define TIMER10_RESP_FUNC TIMER_UNUSED
#define TIMER11_RESP_FUNC TIMER_UNUSED
#define TIMER12_RESP_FUNC TIMER_UNUSED
#define TIMER13_RESP_FUNC PostSimpleFunctionService
#define TIMER14_RESP_FUNC PostSimpleFunctionService
#define TIMER15_RESP_FUNC PostSimpleFunctionService


/****************************************************************************/
// Give the timer numbers symbolc names to make it easier to move them
// to different timers if the need arises. Keep these definitons close to the
// definitions for the response functions to make it easire to check that
// the timer number matches where the timer event will be routed

/*make sure this is enabled above and posting to the correct state machine*/
#define MidAdjustTimer 0 // timer for adjusting when we are searching for tape or beacon. we are also using this for the countdown to adjust. 
#define DebounceTimer 1
#define TempTurnTimer 2
#define TowerHelperTimer 3 // only used in tower scope. smdh 
#define SolenoidTimer 4
#define SolenoidWaitTimer 5
#define STOP_WHILE_SHOOT 6
#define SHOT_EARLY_MOVEON 7
#define APPROACH_ADJUST_TIMER 8
#define FINDHOLETIMEOUTTIMER 9




#define BREAKOUTIMER 13
#define WHOLETTHEDOGSOUT 14 // can live without tbh
#define DeboundTimerBackup 15 // maybe don't need
/****************************************************************************/
// The maximum number of services sets an upper bound on the number of 
// services that the framework will handle. Reasonable values are 8 and 16
// HOWEVER: at this time only a value of 8 is supported.
#define MAX_NUM_SERVICES 8

/****************************************************************************/
// This macro determines that nuber of services that are *actually* used in
// a particular application. It will vary in value from 1 to MAX_NUM_SERVICES
#define NUM_SERVICES 4

/****************************************************************************/
// These are the definitions for Service 0, the lowest priority service
// every Events and Services application must have a Service 0. Further 
// services are added in numeric sequence (1,2,3,...) with increasing 
// priorities
// the header file with the public fuction prototypes
#define SERV_0_HEADER "ES_KeyboardInput.h"
// the name of the Init function
#define SERV_0_INIT InitKeyboardInput
// the name of the run function
#define SERV_0_RUN RunKeyboardInput
// How big should this service's Queue be?
#define SERV_0_QUEUE_SIZE 9

/****************************************************************************/
// These are the definitions for Service 1
#if NUM_SERVICES > 1
// the header file with the public fuction prototypes
#define SERV_1_HEADER "TopHSM.h"
// the name of the Init function
#define SERV_1_INIT InitTopHSM
// the name of the run function
#define SERV_1_RUN RunTopHSM
// How big should this services Queue be?
#define SERV_1_QUEUE_SIZE 3
#endif

// These are the definitions for Service 2
#if NUM_SERVICES > 2
// the header file with the public fuction prototypes
#define SERV_2_HEADER "SimpleFunctionService.h"
// the name of the Init function
#define SERV_2_INIT InitSimpleFunctionService
// the name of the run function
#define SERV_2_RUN RunSimpleFunctionService
// How big should this services Queue be?
#define SERV_2_QUEUE_SIZE 4
#endif



/****************************************************************************/
// These are the definitions for Service 3
#if NUM_SERVICES > 3
// the header file with the public fuction prototypes
#define SERV_3_HEADER "EncoderService.h"
// the name of the Init function
#define SERV_3_INIT InitEncoderService
// the name of the run function
#define SERV_3_RUN RunEncoderService
// How big should this services Queue be?
#define SERV_3_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 4
#if NUM_SERVICES > 4
// the header file with the public fuction prototypes
#define SERV_4_HEADER "TestService.h"
// the name of the Init function
#define SERV_4_INIT TestServiceInit
// the name of the run function
#define SERV_4_RUN TestServiceRun
// How big should this services Queue be?
#define SERV_4_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 5
#if NUM_SERVICES > 5
// the header file with the public fuction prototypes
#define SERV_5_HEADER "TestService.h"
// the name of the Init function
#define SERV_5_INIT TestServiceInit
// the name of the run function
#define SERV_5_RUN TestServiceRun
// How big should this services Queue be?
#define SERV_5_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 6
#if NUM_SERVICES > 6
// the header file with the public fuction prototypes
#define SERV_6_HEADER "TestService.h"
// the name of the Init function
#define SERV_6_INIT TestServiceInit
// the name of the run function
#define SERV_6_RUN TestServiceRun
// How big should this services Queue be?
#define SERV_6_QUEUE_SIZE 3
#endif

/****************************************************************************/
// These are the definitions for Service 7
#if NUM_SERVICES > 7
// the header file with the public fuction prototypes
#define SERV_7_HEADER "TestService.h"
// the name of the Init function
#define SERV_7_INIT TestServiceInit
// the name of the run function
#define SERV_7_RUN TestServiceRun
// How big should this services Queue be?
#define SERV_7_QUEUE_SIZE 3
#endif

/****************************************************************************/
// the name of the posting function that you want executed when a new 
// keystroke is detected.
// The default initialization distributes keystrokes to all state machines
#define POST_KEY_FUNC ES_PostAll



/****************************************************************************/
// These are the definitions for the Distribution lists. Each definition
// should be a comma seperated list of post functions to indicate which
// services are on that distribution list.
#define NUM_DIST_LISTS 0
#if NUM_DIST_LISTS > 0 
#define DIST_LIST0 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 1 
#define DIST_LIST1 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 2 
#define DIST_LIST2 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 3 
#define DIST_LIST3 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 4 
#define DIST_LIST4 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 5 
#define DIST_LIST5 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 6 
#define DIST_LIST6 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 7 
#define DIST_LIST7 PostTemplateFSM
#endif



#endif /* CONFIGURE_H */
