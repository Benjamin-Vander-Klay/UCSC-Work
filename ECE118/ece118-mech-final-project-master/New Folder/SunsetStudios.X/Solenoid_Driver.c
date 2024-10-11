/*
 * File:   Solenoid_Driver.c
 * Author: bcvander
 *
 * Created on May 15, 2022, 8:01 PM
 */


#include "xc.h"
#include <stdlib.h>
#include <stdio.h>
#include "BOARD.h"
#include "serial.h"
#include "AD.h"
#include "pwm.h"
#include "LED.h"

#include "timers.h"

#include "ES_Configure.h"
#include "ES_Timers.h"
#include "Solenoid_Driver.h"

// UNCOMMENT TO TEST
//#define SOLENOID_TEST
//#define FIRE_WHEN_READY 1
//#define 
static unsigned int min_wait = 0;

/**
 * Solenoid_Init();
 * Uses IO Ports.h Defines to set s
 * @param port
 * @param pattern
 * @return 
 */
char Solenoid_Init(){
    // Set the Macro in 
    if(IO_PortsSetPortOutputs(SOL_DRIVER_PORT, SOL_DRIVER_PIN) == ERROR){
        return ERROR;
    }
    min_wait = 0;
    return SUCCESS;
    
}
/**
 * Solenoid_Init();
 * returns true or false if enough time has passed only really relevant if you want to shoot twice in a row
 * @param port
 * @param pattern
 * @return 
 */
char Solenoid_Ready(/*int8_t whenready*/){
    if(ES_Timer_GetTime() >= min_wait){
        //if()
        return TRUE;
    }
    else{
        return FALSE;
    }
}
/**
 * Solenoid_Add(int8_t port, uint16_t pattern);
 * Uses IO Ports.h Defines macroed into the .h file to set pin as solenoid trigger
 * @param port
 * @param pattern
 * @return 
 */
//char Solenoid_Add(int8_t port, uint16_t pattern){
//    
//    if(IO_PortsSetPortOutputs(port, pattern) == ERROR){
//        return ERROR;
//    }
//    min_wait = 0;
//    return SUCCESS;
//    
//    
//}

/**
 * Solenoid_Fire()
 * Uses macro in Solenoid_Driver.h to fire pin
 * @param port
 * @param pattern
 * @return 
 */
char Solenoid_Fire(){
    
    // longer than minimum wait period between shots
    if(ES_Timer_GetTime() >= min_wait){
        // extend solenoid
//        PORTX03_LAT = 1;
        IO_PortsSetPortBits(SOL_DRIVER_PORT, SOL_DRIVER_PIN);
        // timestamp 50ms in the future -- currently --5/16/2022
//        unsigned int wait = ES_Timer_GetTime() + SOL_TIME_MS; 
        printf("\r\nsolenoid tmr started");
        ES_Timer_InitTimer(SolenoidTimer, SOL_TIME_MS);
        // **** BLOCKING ****
        
        // Wait 50ms and then turn it off
//        while(ES_Timer_GetTime() < wait);
        printf("\r\n solenoid timer started");
//        PORTX03_LAT = 0; 
//        IO_PortsClearPortBits(SOL_DRIVER_PORT, SOL_DRIVER_PIN);
        min_wait = ES_Timer_GetTime() + SOL_BTN_MS + SOL_TIME_MS;
    }
    else{
        printf("\r\n failed to fire solenoid because system did not wait the minimum solenoid cooldown period between calls to Solenoid_Fire()");
        return ERROR;
    }
    return SUCCESS;
}

#ifdef SOLENOID_TEST
int main(void) {
    // init required modules
    BOARD_Init();
    AD_Init();
//    TIMERS_Init();
    
    // Print out compilation statement
    printf("\r\nECE 118 Final Project Solder Slugs Solenoid Testing. Compiled %s, %s", __DATE__, __TIME__);
    
    // Add a solenoid on pin x03
    if(Solenoid_Init() == ERROR){
        printf("\r\nERROR adding solenoid in TEST Harness");
    }
    // fire once
    
    if(Solenoid_Fire() == ERROR){
        printf("\r\nERROR Firing solenoid in TEST Harness");
    }
    if(Solenoid_Fire() == ERROR){
        printf("\r\nERROR Firing solenoid in TEST Harness");
    }
    while(1);
    return 0;
}
#endif
