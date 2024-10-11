/*
 * File:   Part5_main.c
 * Author: bcvander
 *
 * Created on April 25, 2022, 6:11 PM
 */


#include "xc.h"
#include <stdlib.h>
#include <stdio.h>
#include "BOARD.h"
#include "xc.h"
#include "AD.h"
#include "pwm.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"
#include "Stepper.h"

#define STEP_RATE 700


int main(void) {
    
     // Init required Modules
    BOARD_Init();
    AD_Init();
    PWM_Init();
    LED_Init();
    Stepper_Init();
    
    // Print out compilation statement
    printf("\r\nECE 118 Lab3 Part 5. Compiled %s, %s    \n", __DATE__, __TIME__);
    
    Stepper_SetRate(STEP_RATE);
    Stepper_InitSteps(FORWARD, 6400);
//    Stepper_InitSteps(REVERSE, 400);
            
    
    
    
    while(1){
        
    }
    
    return 0;
}
