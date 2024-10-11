/*
 * File:   Part2_Main.c
 * Author: bcvander, Sam Indukar
 *
 * Created on April 24, 2022, 5:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "BOARD.h"
#include "AD.h"
#include "pwm.h"
#include "LED.h"
#include "serial.h"

//--------------------------------------------------------------------------
// Defines
#define TOLERANCE 50

int main(void) {
    // Init Required Libraries
    BOARD_Init();
    LED_Init();
    PWM_Init();
    AD_Init();
    
    //--------------------------------------------------------------------------
    // Variables
    unsigned int ad_value = 0;
    unsigned int prev_ad = 0;
    unsigned int led_value = 0;
    unsigned char led_b1, led_b2, led_b3;
    unsigned int pwm_input = 0;
    unsigned int prev_pwm = 0;
    
    
    //--------------------------------------------------------------------------
    // Add pins -- PWM outputs and AD inputs 
    if(AD_AddPins(AD_PORTV5) == ERROR){// Pin V4 on I/O shield
        printf("ERROR in AD Add pins\n");
    } 
    
    if(PWM_AddPins(PWM_PORTY10) == ERROR){// Pin Z6 on I/O shield
        printf("ERROR in PWM Add pins\n");
    }
    
    if(LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3) == ERROR){// Pin V3 on I/O shield
        printf("ERROR in LED AddBanks\n");
    }
    
    // not sure what to set the F to, keeping it slow for now
//    if(PWM_SetFrequency(PWM_5KHZ) == ERROR){
//        printf("ERROR in PWM Set Frequency");
//    }
    
    
    // Print out compilation statement
    printf("ECE 118 Lab3 Part 2/3. Compiled %s, %s\n", __DATE__, __TIME__);
    
    //--------------------------------------------------------------------------
    // 
    
    //--------------------------------------------------------------------------
    // Never Exit on Embedded
    while(1){
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
                    
                    printf("Duty Cycle = %d\n",PWM_GetDutyCycle(PWM_PORTY10));
                    printf("pwm input = %d", pwm_input);
                }
                
                // Set duty cycle 
                if(PWM_SetDutyCycle(PWM_PORTY10, pwm_input) == ERROR){// Pin Z6 on I/O shield
                    printf("ERROR in PWM Set Duty Cycle\n");
                }
                
                
//                if(PWM_GetDutyCycle(PWM_PORTZ06) == ERROR){// Pin Z6 on I/O shield
//                    printf("ERROR in PWM Set Duty Cycle\n");
//                }
                // Set duty cycle 
//                if(PWM_SetDutyCycle(PWM_PORTZ06, MIN_PWM) == ERROR){// Pin Z6 on I/O shield
//                    printf("ERROR in PWM Set Duty Cycle\n");
//                }
                
            }
        }
        
    }
    return 0;
}
