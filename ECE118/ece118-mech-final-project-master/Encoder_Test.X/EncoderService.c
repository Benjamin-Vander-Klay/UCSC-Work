/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "EncoderService.h"
#include <stdio.h>
#include "Motor_Driver.h"

// 1 in = 270 ticks
// 0.5 in = 

// TICK MACROS FOR PREDETERMINED DRIVES // EXPERIMENTALLY FOUND ->WILL REQUIRE EDITING 
#define FULL_ROT_PLUS 2700 // running more than full rot                                  10 inches
#define FULL_ROT 2160 // = 540 * 4 // one rotation from amazon webpage                     8 inches
#define THREE_QTR_ROT 1620 // 6 ICHES// was previous 810. not sure why                     6 inches
#define HALF_ROT 1080 // = 270 * 4 // half rotation base on this^^                         4 inches
#define QTR_ROT 540 //   = whaterver man. =^^^/2                                           2 inches
#define EIGHTH_ROT 270 // One eighth of a roateion is                                      1 inch 
#define DEG_300 6500  // pivot !// = 1700 * 4  // guessing lol
#define DEG_30 600   // pivot! 
#define DEG_15 300   // pivot!
#define DEG_10 200   // pivot! Slightly!
#define DEG_90 3250  //2600  // Guessing // 3250 from kaixin n amber last nihgt. previously 1800
#define DEG_65 1200 // 60-90 degrees??? Guessing not accurate but for sure is less than 90 lol
#define DEG_180 DEG_90*2  
#define DEG_360 DEG_90 * 4 // dependent on 90 degree turn 
#define DEG_ENTRY 750
#define SCOOT_LEFT_TICKS_1ST 450 // pivot for now --> 6/3/22 K - no i changed it to tank turn
#define DEG_SCOOT_RIGHT_1ST 200 //  tank turn
#define REV_B4_SCOOT_AGAIN_TICKS 500 // ABT 2 INCHES?
#define TOWER_REVERSE_TICKS 675 
#define TOWER_REVERSE_ARC_LEFT_TICKS 800
#define TOWER_FORWARD_ARC_LEFT_TICKS 1100 // ~4inches
#define TOWER_SQUARE_LEFT_TICKS 100  
#define TW_ALIGN_PT_LEFT_TICKS 1000 // to get acround corner for TW detection

#define OFF 0

// SPEEDS FOR THESE PREDETERMINED DRIVE 
// Range is ~300-900. Below 300 and not sure will turn // barely turns at 500 pmw ** and not evenly
#define FULL_ROT_SPEED DRIVE_HIGH
#define THREE_QTR_ROT_SPEED DRIVE_HIGH
#define HALF_ROT_SPEED DRIVE_HIGH // amber has drive medium here
#define QTR_ROT_SPEED DRIVE_HIGH
#define EIGHTH_ROT_SPEED DRIVE_HIGH
#define DEG_300_SPEED DRIVE_HIGH
#define DEG_90_SPEED DRIVE_HIGH
#define DEG_65_SPEED DRIVE_HIGH
#define DEG_180_SPEED DRIVE_HIGH
#define DEG_360_SPEED DRIVE_HIGH
#define DEG_ENTRY_SPEED DRIVE_HIGH
#define SCOOT_LEFT_SPEED DRIVE_HIGH
#define SCOOT_RIGHT_SPEED DRIVE_HIGH
#define TOWER_REVERSE_SPEED DRIVE_MAX
#define TOWER_REVERSE_ARC_LEFT_SPEED DRIVE_HIGH
#define TOWER_FORWARD_ARC_LEFT_SPEED DRIVE_HIGH // high when battery high and max when battery low
#define TOWER_SQUARE_LEFT_SPEED DRIVE_HIGH
#define TW_ALIGN_PT_LEFT_SPEED DRIVE_MAX
#define DEG_30_SPEED DRIVE_HIGH
#define DEG_15_SPEED DRIVE_HIGH
#define DEG_10_SPEED DRIVE_HIGH
#define REV_B4_SCOOT_AGAIN_SPEED DRIVE_HIGH
//#define TOWER_REV

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
// Un-Comment To Test
//#define ENCODERSERVICE_TEST
//#define BATTERY_DISCONNECT_THRESHOLD 175

// mask the MSB 8 to be the left number of ticks and the left to be the
// Done with 



// so we can use the IO macros
#ifdef ENCODERSERVICE_TEST
//#include <xc.h>
//#include "IO_Ports.h"
#endif




/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;
// t
static int tick_count_right;
static int tick_count_left;
// the mark at which we send an event back to the HSM
static int tick_goal_right;
static int tick_goal_left;
// so that we only go over once, and can still count if we want to? eventually?
static int tick_goal_done_lt = TRUE; // so we don't genearte an event right off the bat // **********************************
static int tick_goal_done_rt = TRUE;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitEncoderService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostEncoderService(ES_Event ThisEvent) {
    //    printf("\r\nPosted to the service"); // shits itself when we do this?
    int8_t error = ES_PostToService(MyPriority, ThisEvent);
    if (error == FALSE) {
        printf("Post Encoder Service Returned an error");
    }
    return error;
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunEncoderService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    ReturnEvent.EventParam = 0;
    // Only Post if something interesting Occured
    int8_t post = FALSE;

    /********************************************
     in here you write your service code
     *******************************************/
    //    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    //    ES_EventTyp_t curEvent;
    //    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    switch (ThisEvent.EventType) {
        case ES_INIT:
            // No hardware initialization or single time setups, those
            // go in the init function above.
            //
            // This section is used to reset service for some reason
            break;

            // can either set number of ticks in event parameters or use predefined macros
            // lol or both. We could do back up ___ or turn Right ___
            // as well as set ticks -> we only have ...
            // nvm we have 16 bits. 8 for each right. 8 on left, 8 on right. 
        case DRIVE_FORWARD_FULL:
            // Set tick goals
            tick_goal_left = FULL_ROT;
            tick_goal_right = FULL_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(FULL_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_FORWARD_THREE_QTR:
            // Set tick goals
            tick_goal_left = THREE_QTR_ROT;
            tick_goal_right = THREE_QTR_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(THREE_QTR_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_FORWARD_HALF:
            // Set tick goals
            tick_goal_left = HALF_ROT;
            tick_goal_right = HALF_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(HALF_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_FORWARD_QTR:
            // Set tick goals
            tick_goal_left = QTR_ROT;
            tick_goal_right = QTR_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(QTR_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;

        case DRIVE_FORWARD_EIGHTH:
            // Set tick goals
            tick_goal_left = EIGHTH_ROT;
            tick_goal_right = EIGHTH_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(EIGHTH_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
            //  --------------------------------------------------------------------    
        case DRIVE_REVERSE_FULL:
            // Set tick goals
            tick_goal_left = FULL_ROT;
            tick_goal_right = FULL_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            printf("\r\ntick goals: \r\nLeft:%d\r\nRight:%d", tick_goal_right, tick_goal_left);
            // set motors to go
            if (Drive_Straight(-FULL_ROT_SPEED) == ERROR) {
                printf("\r\nError in Setting motorspeed (Encoder)");
            }
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;

        case DRIVE_REVERSE_FULL_PLUS:
            // Set tick goals
            tick_goal_left = FULL_ROT_PLUS;
            tick_goal_right = FULL_ROT_PLUS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            printf("\r\ntick goals: \r\nLeft:%d\r\nRight:%d", tick_goal_right, tick_goal_left);
            // set motors to go
            if (Drive_Straight(-FULL_ROT_SPEED) == ERROR) {
                printf("\r\nError in Setting motorspeed (Encoder)");
            }
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_REVERSE_THREE_QTR:
            // Set tick goals
            tick_goal_left = THREE_QTR_ROT;
            tick_goal_right = THREE_QTR_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-THREE_QTR_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_REVERSE_HALF:
            // Set tick goals
            tick_goal_left = HALF_ROT;
            tick_goal_right = HALF_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;

            // set motors to go
            Drive_Straight(-HALF_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_REVERSE_QTR:
            // Set tick goals
            tick_goal_left = QTR_ROT;
            tick_goal_right = QTR_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-QTR_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case DRIVE_REVERSE_EIGHTH:
            // Set tick goals
            tick_goal_left = EIGHTH_ROT;
            tick_goal_right = EIGHTH_ROT;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-EIGHTH_ROT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case REVERSE_TOWER:
            // Set tick goals
            tick_goal_left = TOWER_REVERSE_TICKS;
            tick_goal_right = TOWER_REVERSE_TICKS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-TOWER_REVERSE_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;


            //  --------------------------------------------------------------------      
        case REVERSE_ARC_LEFT: // 
            // Set tick goals
            tick_goal_left = OFF; // pivot turn -> zerpo ticks
            tick_goal_right = TOWER_REVERSE_ARC_LEFT_TICKS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE; // pivot
            tick_goal_done_lt = TRUE;
            //             printf("\r\ntick goals: \r\nLeft:%d\r\nRight:%d", tick_goal_right, tick_goal_left);
            // set motors to go
            //            Drive_Pivot_Left(-TOWER_REVERSE_ARC_LEFT_SPEED); // needs to be pivot back right
            Drive_Tank_Turn_Left(-TOWER_REVERSE_ARC_LEFT_SPEED); //< ---------------------------------- tesin rn
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;

        case FORWARD_ARC_LEFT:
            // Set tick goals
            tick_goal_left = OFF; // pivot turn -> zerpo ticks
            tick_goal_right = TOWER_FORWARD_ARC_LEFT_TICKS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = TRUE; // p
            // set motors to go
            Gradual_Turn_Left(TOWER_FORWARD_ARC_LEFT_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;

        case TANK_TURN_LEFT_90:
            // Set tick goals
            tick_goal_left = DEG_90;
            tick_goal_right = DEG_90;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Left(DEG_90_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
        case TANK_TURN_RIGHT_90:
            // Set tick goals
            tick_goal_left = DEG_90;
            tick_goal_right = DEG_90;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Right(DEG_90_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            post = TRUE;
            break;
         // ---------------------------------------------------------------------       
        case PIVOT_TURN_LEFT_300:
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_300;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = TRUE;
            // set motors to go
            Drive_Pivot_Left(DEG_300_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;
            break;
        case PIVOT_TURN_LEFT_REV_30:
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_30;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE; // only based on right encoder
            tick_goal_done_lt = TRUE;
            // set motors to go
            Drive_Pivot_Left(-DEG_30_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;

            break;

        case PIVOT_TURN_LEFT_REV_15:
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_15;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE; // only based on right encoder
            tick_goal_done_lt = TRUE;
            // set motors to go
            Drive_Pivot_Left(-DEG_15_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;

            break;
            
        case PIVOT_TURN_LEFT_REV_10: // FOR VERY SMALL CHANGES
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_10;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE; // only based on right encoder
            tick_goal_done_lt = TRUE;
            // set motors to go
            Drive_Pivot_Left(-DEG_10_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;

            break;            
        case PIVOT_TURN_LEFT_30:
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_30;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE; // only based on right encoder
            tick_goal_done_lt = TRUE;
            // set motors to go
            Drive_Pivot_Left(DEG_30_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;

            break;
        case PIVOT_TURN_LEFT_15:
            // Set tick goals
            tick_goal_left = DEG_15;
            tick_goal_right = OFF;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = TRUE;
            tick_goal_done_lt = FALSE; // only based on right encoder
            // set motors to go
            Drive_Pivot_Left(DEG_15_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;
            break;
        case PIVOT_TURN_LEFT_10:
            // Set tick goals
            tick_goal_left = DEG_10;
            tick_goal_right = OFF;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = TRUE;
            tick_goal_done_lt = FALSE; // only based on right encoder
            // set motors to go
            Drive_Pivot_Left(DEG_10_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;
            break;    
            
        // ---------------------------------------------------------------------    
                    
        case PIVOT_TURN_RIGHT_15:
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = DEG_15;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE; // only based on left encoder
            tick_goal_done_lt = TRUE; 
            // set motors to go
            Drive_Pivot_Left(DEG_15_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;
            break;   
        case PIVOT_TURN_RIGHT_10:
            // Set tick goals
            tick_goal_left = DEG_10;
            tick_goal_right = OFF;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = TRUE;
            tick_goal_done_lt = FALSE; // only based on right encoder
            // set motors to go
            Drive_Pivot_Right(DEG_10_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = RIGHT_TICK;
            post = TRUE;
            break;        
        // ---------------------------------------------------------------------        
        case TANK_TURN_LEFT_360:
            // Set tick goals
            tick_goal_left = DEG_360;
            tick_goal_right = DEG_360;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Left(DEG_360_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            break;

        case TANK_TURN_LEFT_180:
            // Set tick goals
            tick_goal_left = DEG_180;
            tick_goal_right = DEG_180;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Left(DEG_180_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            break;
        case TANK_TURN_LEFT_ENTRY:
            // Set tick goals
            tick_goal_left = DEG_ENTRY;
            tick_goal_right = DEG_ENTRY;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Left(DEG_ENTRY_SPEED);
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            break;
        // ---------------------------------------------------------------------        
        case SCOOT_LEFT: // for scooting closer to the tower!! // pivot left for now/
            // Set tick goals
            tick_goal_left = OFF; //                                                     <-- OOOO baby this one's OFF! Z E R O. PIVOT ONLY MY FRIEND
            tick_goal_right = SCOOT_LEFT_TICKS_1ST; // PIVOT LEFT, TURN RIGHT MOTOR FORWARDS
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = TRUE; // for pivoting only // ----------------============------------------
            // set motors to go
            Drive_Tank_Turn_Left(SCOOT_LEFT_SPEED); //              6/3/22 5:00 AMBER --Changed from Pivot to Tank Turn '3'                       <-- hey buddy make sure u want to scoot like this <3 GL out there
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;

            break;

        case SCOOT_RIGHT: // for scooting close to the tower! bvk // tt right for now
            // Set tick goals
            tick_goal_left = DEG_SCOOT_RIGHT_1ST;
            tick_goal_right = DEG_SCOOT_RIGHT_1ST;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Tank_Turn_Right(SCOOT_RIGHT_SPEED); //                                     <-- pal, we're doing_____________ is that what you wanted?    
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            break;

        case SCOOT_REVERSE: // for scooting close to the tower! reverse a small amount before going into the align with center so that we are actually parallel parking
            // Set tick goals
            tick_goal_left = REV_B4_SCOOT_AGAIN_TICKS;
            tick_goal_right = REV_B4_SCOOT_AGAIN_TICKS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Straight(-REV_B4_SCOOT_AGAIN_SPEED); //                                     <-- pal, we're doing_____________ is that what you wanted?    
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;
            break;
        // ---------------------------------------------------------------------        
        case TOWER_SQUARE_LEFT: // turn left to square up w tower -- pivoting now 7pm 6/2/2022
            // Set tick goals
            tick_goal_left = OFF;
            tick_goal_right = TOWER_SQUARE_LEFT_TICKS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = FALSE;
            // set motors to go
            Drive_Pivot_Left(TOWER_SQUARE_LEFT_SPEED); //                                    <-- pal, we're doing_____________ is that what you wanted?    
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;

            break;
        case TW_ALIGN_PT_LEFT_REV: //
            // Set tick goals
            tick_goal_left = OFF; // left pivot - 0ff
            tick_goal_right = TW_ALIGN_PT_LEFT_TICKS;
            tick_count_right = 0;
            tick_count_left = 0;
            tick_goal_done_rt = FALSE;
            tick_goal_done_lt = TRUE; // left pivot, left wheel doesn't move
            // set motors to go
            Drive_Pivot_Left(-TW_ALIGN_PT_LEFT_SPEED); //                                     <-- pal, we're doing_____________ is that what you wanted?    
            // Let SM know?
            //            ReturnEvent.EventType = DRIVING;
            //            ReturnEvent.EventParam = BOTH_TICK;

            break;



            //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        case ENCODER_RESET:

            tick_goal_left = OFF;
            tick_goal_right = OFF;
            tick_count_right = 0;
            tick_count_left = 0;
            // So that it won't send an event 
            tick_goal_done_rt = TRUE;
            tick_goal_done_lt = TRUE;

            break;

        case ENCODER_TICK:
            if ((ThisEvent.EventParam == RIGHT_TICK) || (ThisEvent.EventParam == BOTH_TICK)) { // right tick occured
                //                                printf("\r\nwe ticking right");
                tick_count_right++;
                //                printf("\r\nright tick count: %d", tick_count_right);
                // when we hit goal, let the HSM know!
                if ((tick_count_right >= tick_goal_right) && (tick_goal_done_rt == FALSE)) {
                    printf("\r\ncounted to %d on right side", tick_goal_right);
                    // post event ENCODER_DONE? to HSM?
                    tick_goal_done_rt = TRUE;
                    // Turn off motors?        
                    Drive_Stop(RIGHT);
                    ReturnEvent.EventType = ENCODER_DONE;
                    ReturnEvent.EventParam |= RIGHT_TICK;
                    //                PostHSM(ReturnEvent);
                    post = TRUE;

                    //                } else { // IF NOT A RIGHT TICK, A LEFT TICK!!! IF NOT A LEFT TICK DONT SET IT AS NO EVENT, IT WAS A RIGHT TICK BVK!!! 8:33PM 5/31
                    //                    ReturnEvent.EventType = ES_NO_EVENT;
                    //                    ReturnEvent.EventParam = 0;
                }

            }

            if ((ThisEvent.EventParam == LEFT_TICK) || (ThisEvent.EventParam == BOTH_TICK)) { // left tick occured
                //                                printf("\r\nwe ticking left");
                tick_count_left++;
                //                printf("\r\nleft tick count: %d", tick_count_left);
                // when we hit goal, let the HSM know!
                if ((tick_count_left >= tick_goal_left) && (tick_goal_done_lt == FALSE)) {
                    printf("\r\ncounted to %d on left side", tick_goal_left);
                    // post event ENCODER_DONE? to HSM?
                    tick_goal_done_lt = TRUE;
                    // Turn off motors?
                    Drive_Stop(LEFT);

                    ReturnEvent.EventType = ENCODER_DONE;
                    ReturnEvent.EventParam |= LEFT_TICK;
                    post = TRUE;
                    //                    printf("\r\nevent param = (left?) %d", ReturnEvent.EventParam);
                }

            }
            //            PostTopHSM(ReturnEvent);
            break;
        default:

            //            if (curEvent != lastEvent) { // check for change from last time
            //                ReturnEvent.EventType = curEvent;
            //                ReturnEvent.EventParam = batVoltage;
            //                lastEvent = curEvent; // update history
#ifndef ENCODERSERVICE_TEST           // keep this as is for test harness
            PostTopHSM(ReturnEvent);
            // post = TRUE; // Perhaps instead?
#else
            PostEncoderService(ReturnEvent);
#endif   
            //            }
            break;





#ifdef ENCODERSERVICE_TEST     // keep this as is for test harness      
        default:
            printf("\r\nEvent: %s\tParam: 0x%X",
                    EventNames[ThisEvent.EventType], ThisEvent.EventParam);
            break;
#endif
    } // End of Main Switch Statement
    if (post) { // check for change from last time
        PostTopHSM(ReturnEvent);
    }

    //    PostTopHSM(ReturnEvent);
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

