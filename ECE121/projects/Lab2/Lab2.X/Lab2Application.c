/*
 * Lab2Application.c
 * Author: Benjamin Vander Klay (bcvander)
 * Class: ECE 121 Prof Petersen Winter 2022
 * Date: 2/25/2022
 * Brief: Uses FreeRunningTimer.c, RCServo.c, RotaryEncoder.c, PingSensor.c libraries
 * to operate the RC servo using either the PingSensor or rotary encoder as inputs
 * 
 * 
 * 
 * 
 */

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "BOARD.h"
#include "MessageIDs.h"
#include "Protocol.h"
#include "FreeRunningTimer.h"
#include "RotaryEncoder.h"
#include "PingSensor.h"
#include "RCServo.h"

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
#define MODE_ENCODER 1
#define MODE_PING 0
#define MODE_LEN 1
// 25 cm for ping sensor minimum distance
#define MIN_DISTANCE 25
// 125 cm for ping sensor max distance
#define MAX_DISTANCE 125
// 360k / 16384 = ~22
#define MILLI_D_CONV 22
// Min
#define MILLI_D_MIN 120000
// MAX
#define MILLI_D_MAX 240000
// 
#define OUT_BOUNDS_UP 4
#define OUT_BOUNDS_DOWN 1
#define IN_BOUNDS 2
// 4 for the int, 1 for the char
#define ANGLE_LENGTH 5
#define PING_SCALER 18
// basically 120k / 1800. 
#define RE_SCALER 65
// found by trial and error. when 120k / 65 = 600 + 1246. sticks out 46 on top, but that is capped]
#define RE_SHIFT 1246

// UNION

struct angle_report {
    signed int milli_d;
    uint8_t data;
    
};

#ifdef LAB2_APPLICATION
int main() {
    
    // -------------------------------------------------------------------------
    // Init the stuff. RC/ping/frt/protocol/roten
    BOARD_Init();
    Protocol_Init();
    FreeRunningTimer_Init();
    RotaryEncoder_Init(ENCODER_BLOCKING_MODE);
    PingSensor_Init();
    RCServo_Init();
    
    TRISE = 0;
    LATE = 0;
    
    // -------------------------------------------------------------------------
    // some variables n stuff
    uint8_t mode_input;
    uint8_t mode = MODE_PING;
    
    unsigned short distance = 0;
    unsigned int ps_pulse = 0;
    unsigned int re_pulse = 0;
    static char *ps_error = "ERROR in Setting RCServo pulse with Ping Sensor Input";
    static char *re_error = "ERROR in Setting RCServo pulse with Rotary Encoder Input";
    
    unsigned short raw_angle = 0;
    unsigned short angle_pulse = 0;
    int millidegrees = 0;
    
    
    // -------------------------------------------------------------------------
    //Send debug message about the date and time n stuff 
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    sprintf(intro_message, "Lab2 Application compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);   
    
    // -------------------------------------------------------------------------
    // FRT timer
    unsigned int timer = FreeRunningTimer_GetMilliSeconds() + 50;
    struct angle_report report;
    report.data = 0;
    report.milli_d = 0;
    // -------------------------------------------------------------------------
    // while one babyy, don't ever exit on embedded
    while(1){
        //----------------------------------------------------------------------
        // Check the Input select. Default is Rotary Encoder
        if(Protocol_ReadNextID() == ID_LAB2_INPUT_SELECT){
            
            // extract payload 
            Protocol_GetPayload(&mode_input);
            // swap the endedness
//            mode_input = Protocol_ShortEndednessConversion(mode_input);
            
            // Set the mode after doing the swap. ID is B8, payload is 00 or 01
            if(mode_input){
                mode = MODE_ENCODER;
//                LATE = 2;
            }
            else{
                mode = MODE_PING;
//                LATE = 4;
            }
            // send it back out
//            uint8_t mode_ret = Protocol_ShortEndednessConversion(mode);
            Protocol_SendMessage(MODE_LEN, ID_LAB2_INPUT_SELECT, &mode);
        }
        //----------------------------------------------------------------------
        
        // Get the angle from the RE
        raw_angle = RotaryEncoder_ReadRawAngle();
//        if(raw_angle <= ){
//            angle_pulse = raw_angle / 9;
        millidegrees = raw_angle * MILLI_D_CONV;
        // scale of 0 - 120 - 240 - 360 (*1000)
        if(millidegrees <= MILLI_D_MIN){
            report.data = OUT_BOUNDS_UP;
//            LATEINV = 4;
            re_pulse = RC_SERVO_MIN_PULSE;
            
        }
        else if(millidegrees >= MILLI_D_MAX){
            report.data = OUT_BOUNDS_DOWN;
//            LATEINV = 8;
            re_pulse = RC_SERVO_MAX_PULSE;
            
        }   
        else{
            report.data = IN_BOUNDS;
//            LATEINV = 16;
            re_pulse = (millidegrees / RE_SCALER) - RE_SHIFT;
            // goes over 
            if(re_pulse >= RC_SERVO_MAX_PULSE){
                re_pulse = RC_SERVO_MAX_PULSE;
            }
        }
        
        // If input is Rotary Encoder
        if(mode){
            //set pulse based on angle
//            LATEINV = 32;
            if(RCServo_SetPulse(re_pulse) == ERROR){
                Protocol_SendDebugMessage(re_error);
            }
            
            
        }
         // if input is Ping Sensor
        else{
            // get the distance 
            distance = PingSensor_GetDistance();
            // check if we're below min
            if(distance <= MIN_DISTANCE){
                ps_pulse = RC_SERVO_MIN_PULSE;
            }
            // check if we're above max
            else if(distance >= MAX_DISTANCE){
                ps_pulse = RC_SERVO_MAX_PULSE;
            }
            // somewhere in between, scale it linearly, baby
            else{
                // 2400 - 600 == 1800 (range of us pulses) (+- 60 deg)
                // 125 - 25   == 100  (range of distances)
                // +18 for each cm between 25 and 125
                
                ps_pulse = (((distance - MIN_DISTANCE) * PING_SCALER) + RC_SERVO_MIN_PULSE);
               
            }
            // set the RCServo pulse;
            if(RCServo_SetPulse(ps_pulse) == ERROR){
                Protocol_SendDebugMessage(ps_error);
            }
        }
        
//        report.data = Protocol_ShortEndednessConversion(report.data);
        millidegrees = Protocol_IntEndednessConversion(millidegrees);
        report.milli_d = millidegrees;
        
                
                
        if(FreeRunningTimer_GetMilliSeconds() >= timer){
            // reset timer for another 50ms
            timer += 50;
            // do thing -> print out angle report
            Protocol_SendMessage(ANGLE_LENGTH, ID_LAB2_ANGLE_REPORT, &report);
//            LATEINV = 1;
        }
//        if()
        
        
       
       
        // Use FRT to send out Rotary Encoder position and status
        
        
        
        
        
        
    }
}
#endif

