/* 
 * File:   Lab1.c
 * Author: bcvander
 *
 * Created on April 11, 2023, 2:42 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <xc.h>
#include "BOARD.h"
#include "serial.h"
#include "AD.h"
#include "serial.h"
#include "ToneGeneration.h"
#include "timers.h"

#define SAMPLE_PERIOD_MS 50
#define MIN_FLEX_CHANGE 30 // took AD reading -> max - min / 90. ~4.5 per degree. see notebook
#define MIN_PIEZO 50
#define HALF_SEC 500

#define F_2 175 //196 G
#define A_2 220//293 D -- should be 294?
#define C_2 262 //440 A 
#define Bb_2 233 //

/*
 * 
 */
int main(void) {
    BOARD_Init();
    SERIAL_Init();
    ToneGeneration_Init();
    TIMERS_Init();
    AD_Init();

    // AD_1 is ...,.
    AD_AddPins(AD_A1);
    AD_AddPins(AD_A2);
    
    
//    AD
            
    uint32_t raw_flex_cur = 0;
    uint32_t raw_flex_prev = 0;
    uint32_t piezo = 0;
    
    
    // init our counter
    unsigned int wait_ms = TIMERS_GetMilliSeconds() + SAMPLE_PERIOD_MS;
    unsigned int hold_tone = 0;
    while (1) {

        //        -raw_flex_cur) >= MIN_FLEX_CHANGE
        if (AD_IsNewDataReady() && (TIMERS_GetMilliSeconds() >= wait_ms)) {

            raw_flex_cur = AD_ReadADPin(AD_A1);
            printf("\r\nAD_value is: %d", raw_flex_cur);
            // reset ms tracker
            wait_ms = TIMERS_GetMilliSeconds() + SAMPLE_PERIOD_MS;

            if (abs(raw_flex_cur - raw_flex_prev) >= MIN_FLEX_CHANGE) {
                printf("\r\n setting tone");
                // update prev
                raw_flex_prev = raw_flex_cur;
                // turn off before chaning. Tone during set is undefined.
                ToneGeneration_ToneOff();
                ToneGeneration_SetFrequency(raw_flex_cur);
                   
            }
            
            
            piezo = AD_ReadADPin(AD_A2);
            // check the mf piezo now!
            
            if (piezo >= MIN_PIEZO){
                printf("\r\n piezo AD reading: %d", piezo);
                ToneGeneration_ToneOn();
                hold_tone = TIMERS_GetMilliSeconds() + HALF_SEC;
            }
            
            else if(TIMERS_GetMilliSeconds() >= hold_tone) {
                ToneGeneration_ToneOff();
            }
        }
    }

    // back up while 1 lol
    while (1);
}

