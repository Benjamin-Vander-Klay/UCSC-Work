/*
 * File:   Part4_Main.c
 * Author: bcvander/ Sindukar 
 *
 * Created on April 25, 2022, 12:19 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include "BOARD.h"
#include "xc.h"
#include "AD.h"
#include "pwm.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"

#define TOLERANCE 0

int main(void) {
    // Init required Modules
    BOARD_Init();
    AD_Init();
    PWM_Init();
    LED_Init();
    // No IO Init() dummy
    
    //--------------------------------------------------------------------------
    // Variables
    unsigned int ad_value = 0;
    unsigned int prev_ad = 0;
    unsigned int led_value = 0;
    unsigned char led_b1, led_b2, led_b3;
    unsigned int pwm_input = 0;
    unsigned int prev_pwm = 0;
    uint16_t switch_input = 0;
    uint16_t prev_switch = 0;
    
    //--------------------------------------------------------------------------
    // Add Pins / Set-up
    // Add pins -- PWM outputs and AD inputs 
    if(AD_AddPins(AD_PORTV5) == ERROR){// Pin V5 on I/O shield
        printf("ERROR in AD Add pins\n");
    } 
    
    if(PWM_AddPins(PWM_PORTY10) == ERROR){// Pin Z6 on I/O shield
        printf("ERROR in PWM Add pins\n");
    }
    
    if(LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3) == ERROR){
        printf("ERROR in LED AddBanks\n");
    }
    
    
    if(IO_PortsSetPortInputs(PORTX, PIN3) == ERROR){// Pin X3 on I/O shield
        printf("ERROR in PWM Add pins\n");
    }
//    
//    if(IO_PortsSetPortOutputs(PORTY, PIN5 | PIN6) == ERROR){// Pin X5 & X6 on I/O shield
//        printf("ERROR in PWM Add pins\n");
//    }
    // Print out compilation statement
    printf("ECE 118 Lab3 Part 4. Compiled %s, %s\n", __DATE__, __TIME__);
    
//    IO_PortsClearPortBits(PORTX, 0xFFFF); //clear all the bits
    
    //set initial DC motor direction
    //set the two IN1 & IN2
//    IO_PortsWritePort(PORTX, PIN5);
    //set the PWM ENA
//    PWM_SetDutyCycle(PWM_PORTY04, 500);
    PORTY07_TRIS = 0;
    PORTY06_TRIS = 0;
    
    PORTY07_LAT = 0;
    PORTY06_LAT = 1;
//    PWM_SetDutyCycle(PWM_PORTY04, 500);
    
//    PWM_SetFrequency(MAX_PWM_FREQ);
    
    //--------------------------------------------------------------------------
    // Never Exit on Embedded
    while(1){
        
        //--------------------------------------------------------------------------
        // Switch Functionality
        switch_input = IO_PortsReadPort(PORTX) & PIN3;
//        printf("switch input (X03) = %d\n", switch_input);
        if(prev_switch != switch_input){
//            printf("switch input (X03) = %d\n", switch_input);
            prev_switch = switch_input;
            
            // OUTPUTS TO IN1 AND IN2 ON H-BRIDGE
            IO_PortsTogglePortBits(PORTY, PIN7 | PIN6);
//            PORTY06_LAT = 0;
//            PORTY05_LAT = 1;
           
        }
        
//        if ( switch_input ){
//            PORTY06_LAT = 0;
//            PORTY05_LAT = 1;
//        }else{
//            PORTY05_LAT = 0;
//            PORTY06_LAT = 1;
//        }
        
        
        //--------------------------------------------------------------------------
        // Potentiometer varies motor speed - pwm
        //Check for change in AD pin input 
        if(AD_IsNewDataReady()){
            // Read AD pin
            ad_value = AD_ReadADPin(AD_PORTV5);
            
            // Value has changed -- Hysteresis? 
            if(abs(prev_ad - ad_value) > TOLERANCE){
                prev_ad = ad_value;
                // scale input to LEDS
                led_value = (4096 / 1023) * ad_value;
                // Set LED banks
                led_b1 = ((led_value & 0x0F00) >> 8);
                led_b2 = (led_value & 0x00F0) >> 4;
                led_b3 = (led_value & 0x000F);
                
                LED_SetBank(LED_BANK1, led_b1);
                LED_SetBank(LED_BANK2, led_b2);
                LED_SetBank(LED_BANK3, led_b3);
                
                // scale input to pulse time. 
                //pwm_input = (ad_value*1000)/1024;
                // cap it at 1k 
                pwm_input = ad_value;
                if(pwm_input > MAX_PWM){
                    pwm_input = MAX_PWM;
                }
                if(pwm_input < 100){
//                  printf("AD VALUE OFF\n\n\n");
                    pwm_input = MIN_PWM;
                    
//                    printf("Duty Cycle = %d\n",PWM_GetDutyCycle(PWM_PORTZ06));
//                    printf("pwm input = %d", pwm_input);
                }
                
                // Set duty cycle              
                if(PWM_SetDutyCycle(PWM_PORTY10, pwm_input) == ERROR){// Pin Z6 on I/O shield
                    printf("ERROR in PWM Set Duty Cycle\n");
                }
            }
        }
        
        //--------------------------------------------------------------------------
       
        
       

    }
    return 0;
}
