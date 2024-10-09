/* 
 * File:   lab0_main.c
 * Author: Ben Vander Klay
 * Class: UCSC ECE121/L Microcontroller System Design
 * Prof: Stephen Petersen
 * Due: 1/14/2022
 *
 * Created on January 9, 2022, 9:14 PM
 */

// Some includes 
#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include <xc.h>
/*
 * Assignment:
 * Lab0 -> Hello, Embedded World!
 * Need to ensure toolchain is working correctly
 * First need to connect LED's to the buttons, Push buttons, turn on LED's
 * 
 * 
 */

// function declaration 
void NOP_delay_5ms ();

// Some Macros so we don't use magic numbers
#define MASK_ONE 0x02 // actually 
#define MASK_FIVE 0x20
#define MASK_SIX 0x40
#define MASK_SEVEN 0x80
#define MASK_FSS 0xe0 // FIVE SIX SEVEN
#define NOPS_FOR_5_MS 250 // 
#define NOPS_FOR_250_MS 12500

// ********************************************************
// define for part 1, undefine for part 2
#define PART_ONE

// ********************************************************

int main(int argc, char** argv)
{
    // some declarations
    uint8_t button_pattern, LED_pattern;
    
    // for counting to 250ms 
    int i; 

    // Set each D pin to input mode for Button's to be inputs
    TRISF = 0x02; // btn1
    TRISD = 0xe0; // btn2-3-4
     // Set each E pin to output mode f or the LED's to be output 
    TRISE = 0x00;
    LATE = 0x00;
    
    LED_pattern = 0;
    
#ifdef PART_ONE
    // some declarations
//    uint8_t button_pattern, LED_pattern;

//    // Set each D pin to input mode for Button's to be inputs
//    TRISF = 0x02; // btn1
//    TRISD = 0xe0; // btn2-3-4
//     // Set each E pin to output mode f or the LED's to be output 
//    TRISE = 0x00;
//    LATE = 0x00;
    
    // continously re-read the value on the pins
    while(1) {
    // bitwise mask so we only take the pins that we are going to use
    button_pattern = (PORTD & MASK_FSS) + (PORTF & MASK_ONE); // RF1

    LED_pattern = 0; // reset the led pattern so does not stay illuminated 
    // button 1 -> LED's 1 & 2
    if(button_pattern & MASK_ONE){
        LED_pattern+=3;
    }
    // button 2 -> LED's 3 & 4
    if(button_pattern & MASK_FIVE){
        LED_pattern+=12;
    }
    // button 3 -> LED's 5 & 6
    if(button_pattern & MASK_SIX){
        LED_pattern+=48;
    }
    // button 4 -> LED's 7 & 8
    if(button_pattern & MASK_SEVEN){
        LED_pattern+=(64+128);
    }
    LATE = LED_pattern;
    
    };
#else // PART_TWO
    
    // GIVEN PSUEDO CODE
//    while 1 do 
//write LEDbits to LEDs ; 
//increment LEDbits ; 
//if button pressed then 
//reset LEDbits ; 
//end 
//if LEDbits > 0xFF then 
//reset LEDbits ; 
//end 
//Delay using NOP loop ; 
//end 
    
    while(1){
   
        LATE = LED_pattern;
        LED_pattern++;
        
        // 5ms goes into 250ms 50 times
        // count to 50 sets of 5ms before increasing LED bit pattern
        for(i = 0; i < 49; i++) {
            // continuously poll the ports to the buttons
            button_pattern = (PORTD & MASK_FSS) | (PORTF & MASK_ONE); // RF1
            if((button_pattern & (MASK_ONE | MASK_FSS)) || LED_pattern == 0xff){
                LED_pattern = 0;
            }
                
            NOP_delay_5ms();
                      
        }
        
    }
#endif
    
    while(1); // never exit on embedded

}

void NOP_delay_5ms () {
    int i;
    for (i = 0; i < NOPS_FOR_5_MS; i++) { 
            asm ("NOP");   
    }
}

