/* 
 * File:   airDrums.c
 * Author: jgaml
 *
 * Created on June 4, 2023, 6:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "AD.h"
#include "Adc.h"
#include "BNO055.h"
#include "pwm.h"
#include "timers.h"
#include "ToneGeneration.h"
#include "serial.h"
#include "Buttons.h"
#include "HardwareDefs.h"

// Custom headers.
#include "MIDI_Interface.h"
#include "HitDetectorLib.h"
#include "quadrant.h"

// DEFINES
// all times in ms unless stated
#define POLLING_WAIT 16  //sample rate for IMU
#define KICK_PIN AD_A1
#define STOMP_THRESHOLD 30
#define INT8_MAX 127
/** BNO055 Address A: when ADR (COM3) pin is tied to ground (default) **/
#define BNO055_ADDRESS_A (0x28)
/** BNO055 Address B: when ADR (COM3) pin is tied to +3.3V **/
#define BNO055_ADDRESS_B (0x29)

// HELPER FUNCTIONS
uint8_t drumHit(int hit, int drum);
int noteGeneration(uint8_t stick);
void delay(int milliSeconds);

int main(int argc, char** argv) {
    
    BOARD_Init();
    TIMERS_Init();
    MIDI_Init();
    HitDetector_Init();
    AD_Init();

    printf("\r\nUCSC ECE167 Air Drums final project. Compiled on %s, at %s.\r\n", __DATE__, __TIME__);
    
    // initialize both IMUs
    if (BNO055_Init(BNO055_ADDRESS_A) == FALSE) {
        MIDI_send_string("\nBNO055 A Init Fail.", NULL);
    }
    delay(300);
    if (BNO055_Init(BNO055_ADDRESS_B) == FALSE) {
        MIDI_send_string("\nBNO055 B Init Fail.", NULL);
    }
    
    // add piezo kick drum pin
    AD_AddPins(KICK_PIN);
    
    int waitTime = TIMERS_GetMilliSeconds() + POLLING_WAIT;
    int hitA;
    int hitB;
    int drum = 0;
    uint8_t stomping = FALSE;
    
    // main loop
    while (1) {
        hitA = 0;
        hitB = 0;
        //check stomp kick drum
        int16_t stomp = AD_ReadADPin(AD_A1);
        if(stomp != ERROR){
            uint16_t stomp_strength = (stomp >> 3) + 50;
            if (stomp_strength > INT8_MAX) stomp_strength = INT8_MAX;
            if (stomp > STOMP_THRESHOLD && !stomping){
                MIDI_send_packet(MIDI_build_packet(
                        NOTE_ON,
                        DRUM_CHANNEL,
                        DRUM_KICK,
                        stomp_strength
                        ));
                stomping = TRUE;
            }else if(stomping && stomp < STOMP_THRESHOLD){
                MIDI_send_packet(MIDI_build_packet(NOTE_OFF, DRUM_CHANNEL, DRUM_KICK, 0));
                stomping = FALSE;
            }
        }
        //poll IMU
        if (TIMERS_GetMilliSeconds() >= waitTime) {
            printf("POLL\r\n");
            hitA = HitDetector(BNO055_ReadAccelY(BNO055_ADDRESS_A), 
                    BNO055_ReadAccelZ(BNO055_ADDRESS_A), BNO055_ADDRESS_A); //change to hit detection function/s
            hitB = HitDetector(BNO055_ReadAccelY(BNO055_ADDRESS_B), 
                    BNO055_ReadAccelZ(BNO055_ADDRESS_B), BNO055_ADDRESS_B);
            waitTime = TIMERS_GetMilliSeconds() + POLLING_WAIT;
            if (hitA) {
                drum = noteGeneration(BNO055_ADDRESS_A);
                drumHit(hitA, drum);
            }    
            if (hitB) {
                drum = noteGeneration(BNO055_ADDRESS_B);
                drumHit(hitB, drum);
            }
        }
        
    }
    
    while (1);
    return (EXIT_SUCCESS);
}

uint8_t drumHit(int hit, int drum) {
    //hit has magnitude so send over MIDI with volume info
    MIDI_send_packet(MIDI_build_packet(NOTE_ON, DRUM_CHANNEL, drum, hit));
    return SUCCESS;
}

int noteGeneration(uint8_t stick) {
    int drum = 0;
    switch (getBNOQuadrant(stick)) {
        case 0 : 
            drum = DRUM_HIHAT;
            break;
        case 1 : 
            drum = DRUM_CRASH1;
            break;
        case 2 : 
            drum = DRUM_SNARE;
            break;
        case 3 : 
            drum = DRUM_COWBELL;
            break;
        default: break;
    }
    return drum;
}

void delay(int milliSeconds){
    int start = TIMERS_GetMilliSeconds();
    while(TIMERS_GetMilliSeconds() < start + milliSeconds);
}