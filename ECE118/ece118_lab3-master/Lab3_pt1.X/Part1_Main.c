/*
 * File:   Part1_Main.c
 * Author: bcvander
 *
 * Created on April 23, 2022, 3:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "xc.h"
#include "BOARD.h"
#include "RC_Servo.h"
#include "pwm.h"
#include "IO_Ports.h"
#include "LED.h"
#include "AD.h"


#define TOLERANCE 50

int main(void) {
    // -------------------------------------------------------------------------
    // init Board and required peripherals
    BOARD_Init();
    RC_Init();
    AD_Init();
    LED_Init();
    
    // -------------------------------------------------------------------------
    // Variables
    unsigned int ad_value = 0;
    unsigned int prev_ad = 0;
    unsigned int led_value = 0;
    unsigned char led_b1, led_b2, led_b3;
    unsigned short int rc_input = 0;
    unsigned short int prev_rc  = 0;
    
    
    // -------------------------------------------------------------------------
    // Set up pin config ## On Uno 32 #4,PINS X7 && X9 ARE BROKEN (CROSSED OUT)##
    if(AD_AddPins(AD_PORTV5) == ERROR){// Pin V3 on I/O shield
        printf("ERROR in AD Add pins");
    } 
    
    if(RC_AddPins(RC_PORTX04) == ERROR){// Pin V3 on I/O shield
        printf("ERROR in RC Add pins");
    }
    if(LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3) == ERROR){// Pin V3 on I/O shield
        printf("ERROR in LED AddBanks");
        
    }
    
    // Print out compilation statement
    printf("ECE 118 Lab3 Part 1. Compiled %s, %s", __DATE__, __TIME__);
//    PWM_AddPins();
    // -------------------------------------------------------------------------
    // while loop
    while(1){
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

        // Check AD
        if(AD_IsNewDataReady()){
//            prev_ad = ad_value;
            ad_value = AD_ReadADPin(AD_PORTV5);
            
            // Value has changed -- Hysteresis? 
            if(abs(prev_ad - ad_value) > TOLERANCE){
                prev_ad = ad_value;
//            if(prev_ad != ad_value){
                // scale input to LEDS
                // 10 bit from ad to 12 bit.
                led_value = (4096 / 1023) * ad_value;
//                printf("AD_PORTV3 value = %d\n\n", ad_value);
//                printf("LED value = %d\n\n", led_value);
                
                led_b1 = ((led_value & 0x0F00) >> 8);
                led_b2 = (led_value & 0x00F0) >> 4;
                led_b3 = (led_value & 0x000F);
                
                LED_SetBank(LED_BANK1, led_b1);
                LED_SetBank(LED_BANK2, led_b2);
                LED_SetBank(LED_BANK3, led_b3);
                
                // scale input to pulse time. 
//                prev_rc = rc_input; 
                // Send current Input value to RC Servo
                // MINPULSE and MAXPULSE defined in RC_Servo.h
                rc_input = ad_value + MINPULSE;
                // if above max, set as max. limits last 23 
                if(rc_input > MAXPULSE){
                    rc_input = MAXPULSE;
                }

//                printf("diff = %d", abs(prev_rc - rc_input));
//                if(abs(prev_rc - rc_input) > TOLERANCE){
                    printf("RC servo pulse: %d", rc_input);
                    // Set rc pulse
                    if(RC_SetPulseTime(RC_PORTX04, rc_input) == ERROR){
                        printf("ERROR in RC Set pulse time");
                        
                    } 
                    prev_rc = rc_input;
//                }
                
            }
            
        }
        
    }
 
    // Never Return
    while(1);
    return 0;
}
