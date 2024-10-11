/*
 * File:   Uno_Test.c
 * Author: bcvander
 *
 * Created on May 11, 2022, 6:50 PM
 */


#include "xc.h"
#include "BOARD.h"
#include "LED.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "IO_Ports.h"
#include "AD.h"
#include "timers.h"

#define SOL_TIME_MS 50
#define SOL_BTN_MS 300

#define NOP_COUNT 10000
#define AD_PIN_TO_READ AD_PORTW8

// UNCOMMENT TO RUN MAIN
//#define UNO_TEST










#ifdef UNO_TEST
int main(void) {

    // Init Required Libraries
    BOARD_Init();
    //
    AD_Init();
    TIMERS_Init();
    // Add LED Banks
    //  LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    AD_AddPins(AD_PIN_TO_READ);
    unsigned int ad_val = 0;
    // Variables
    unsigned int ad_value = 0;
    unsigned int prev_ad = 0;
    unsigned int led_value = 0;
    unsigned char led_b1, led_b2, led_b3;
    unsigned short int rc_input = 0;
    unsigned short int prev_rc = 0;
    int delay;
    int i, go;
    int start_it = 0;
    int delay_start = 0;


    // printf("Active pins are: %d", AD_ActivePins());
    //    AD_ActivePins
    // Add IO pins 
    //    IO_PortsSetPortOutputs(PORTX,0);
    //    IO_PortsSetPortBits(PORTX,0);
    //    
    //    IO_PortsSetPortOutputs(PORTY,0);
    //    IO_PortsSetPortBits(PORTY,0);
    //    
    //    IO_PortsSetPortOutputs(PORTZ,0);
    //    IO_PortsSetPortBits(PORTZ,0);
    //    
    //    
    //    IO_PortsSetPortOutputs(PORTW,0xffff);
    //    IO_PortsSetPortBits(PORTW,0xffff);
    //    
    //    IO_PortsSetPortOutputs(PORTV,0xffff);
    //    IO_PortsSetPortBits(PORTV,0xffff);
    //    PORTX03_TRIS = 0;
    //    PORTX03_LAT = 1;
    //    
    //    TRISFbits.TRISF5 = 0;
    //    LATFbits.LATF5 = 1;


    // Print out compilation statement
    printf("/r/nECE 118 Final Proj Uno Stack Testing. Compiled %s, %s", __DATE__, __TIME__);
    // printf("/r/nActive pins are: %d", AD_ActivePins());

    // -------------------------------------------------------------------------
    // Solenoid testing. 

    // output 3.3 v for tip122
//    PORTX03_TRIS = 0;
    IO_PortsSetPortOutputs(PORTX,PIN3);
//    PORTX03_LAT = 1;
//    delay = TIMERS_GetTime() + SOL_TIME_MS;
//    delay = TIMERS_GetTime() + 50;
//    for (i = 0; i < NOP_COUNT; i++) {
//        asm("NOP");
//    }
    
    
//    while(TIMERS_GetTime() < delay){
////            IO_PortsTogglePortBits(PORTX, PIN3);
//            // Reset the timer
////            delay = TIMERS_GetTime() + SOL_TIME_MS;
//        }
//    PORTX03_LAT = 0;
//    delay = TIMERS_GetTime() + SOL_TIME_MS;
    delay_start = TIMERS_GetTime() + SOL_BTN_MS;
    // -------------------------------------------------------------------------
    // Never Exit on Embedded
    while (1) {
        // continuously poll analog input pin for change
        // potentiometer changes voltage in range ~ 0-3.3
        // scale this to the LED's to display on the I/O shield
        // use AD for Analog-> digital conversion
        // use LED for LED
        // use PWM for output to servo 
        // actually just use RC libary for servo I think


        //        if(RC_SetPulseTime(RC_PORTX04, 1500) == ERROR){
        //            printf("ERROR in RC Set pulse time");
        //                        
        //        } 
        if((TIMERS_GetTime() >= delay_start) && (start_it == 0)){
            PORTX03_LAT = 1;
            delay = TIMERS_GetTime() + SOL_TIME_MS;
            start_it = 1;
            go = 1;
            printf("\r\nfirst if");
        }
        
        if((TIMERS_GetTime() >= delay) && (go == 1)){
//            IO_PortsTogglePortBits(PORTX, PIN3);
            PORTX03_LAT = 0;
            // make sure we don't spam
            go = 0;
            start_it = 0;
            // Reset the timer
            delay_start = TIMERS_GetTime() + SOL_BTN_MS;
            printf("\r\nsecond if");
        }
        // Check AD
        //        if(AD_IsNewDataReady()){
        ////            prev_ad = ad_value;
        //            ad_value = AD_ReadADPin(AD_PIN_TO_READ);
        //            
        //            // Value has changed -- Hysteresis? 
        //            if(abs(prev_ad - ad_value) > 1){
        //                prev_ad = ad_value;
        //                
        //                printf("\r\nad:%d", ad_value);
        //            if(prev_ad != ad_value){
        // scale input to LEDS
        // 10 bit from ad to 12 bit.

        // scale input to pulse time. 
        //                prev_rc = rc_input; 
        // Send current Input value to RC Servo
        // MINPULSE and MAXPULSE defined in RC_Servo.h

        // if above max, set as max. limits last 23 


        //                printf("diff = %d", abs(prev_rc - rc_input));
        //                if(abs(prev_rc - rc_input) > TOLERANCE){

        // Set rc pulse

        //                }

        //            }

    }

    //    }


    return 0;
}

#endif