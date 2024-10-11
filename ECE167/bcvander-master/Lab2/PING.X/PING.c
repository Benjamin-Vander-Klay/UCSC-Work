/* ************************************************************************** */
/** Descriptive File Name

  @Company
 UCSC

  @File Name
    PING.c

  @Summary
 Library for Ping sensor BVK bcvander

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "PING.h"
#include "BOARD.h"
#include <stdlib.h>
#include "serial.h"
#include <xc.h>
#include <stdio.h>
#include "timers.h"
#include "ToneGeneration.h"

// 1.6 us per tick? from ece 121. couldn't find today
#define PING_TEST
#define PERIOD_60_MS 37500
#define PERIOD_10_US 7   
#define SPEED_OF_SOUND 34300
#define MIN_TONE_CHANGE 4


unsigned int us_time_start, us_time_end;
uint16_t int_flag = 0;

/**
 * @function    PING_Init(void)
 * @brief       Sets up both the timer and Change notify peripherals along with their
 *              respective interrupts.  Also handles any other tasks needed such as pin 
 *              I/O directions, and any other things you need to initialize the sensor.
 *              TIMERS library must be inited before this library.
 * @return      SUCCESS or ERROR (as defined in BOARD.h)
 */
char PING_Init(void) {
    TIMERS_Init();


    // Using pin5 as Trigger
    TRISFbits.TRISF1 = 0; // clear bit 1 of Reg D -> output
    LATFbits.LATF1 = 0; // set bit 1 as 0 -> initialize to 0. triggers starts low.

    // following block inits the timer
    T4CON = 0;
    T4CONbits.TCKPS = 0b110;
    PR4 = PERIOD_60_MS; // this is not the timer value wanted
    T4CONbits.ON = 1;
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 3;
    IEC0bits.T4IE = 1;

    //    CN14 or pin 34 
    TRISDbits.TRISD4 = 1; // input for echo

    // following block inits change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN14 = 1;
    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; //set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify
    //Anything else that needs to occur goes here

    temp++;


    return EXIT_SUCCESS;
}

/**
 * @function    PING_GetDistance(void)
 * @brief       Returns the calculated distance in mm using the sensor model determined
 *              experimentally. 
 *              No I/O should be done in this function
 * @return      distance in mm
 */
unsigned int PING_GetDistance(void) {
    // okay distance is TOF * speed of sound / 2 // d = r * t /2 (two way) 
    if (us_time_start > us_time_end) {
        // we are in the middle of one.
        return 0; // maybe previous value
    } else {
        // end time - start time gives duration. 
        unsigned int tof = us_time_end - us_time_start;
        //        return tof / 58 ; // changed from 2 e6 to 1e6
        return (((tof / 58) * 872) / 1000) - 7;
    }
}

/**
 * @function    PING_GetTimeofFlight(void)
 * @brief       Returns the raw microsecond duration of the echo from the sensor.
 *              NO I/O should be done in this function.
 * @return      time of flight in uSec
 */
unsigned int PING_GetTimeofFlight(void) {
    // use us_time
    if (us_time_start > us_time_end) {
        // we are in the middle of one.
        return 0; // maybe previous value
    } else {
        // end time - start time gives duration. 
        unsigned int tof = us_time_end - us_time_start;
        return tof;
    }
}

void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
    //Anything else that needs to occur goes here
    readPort++;
    if (PORTDbits.RD4) { // pin 34
        us_time_end = TIMERS_GetMicroSeconds();
    } // else do nothing? 

    // we just need to grab the time. 
}

void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void) {

    //Anything else that needs to occur goes here

    // needs to set trigger pin high. and change the period of the timer. to be 10us

    if (PORTFbits.RF1) { // try using PORT as well. PORT should be the actual values
        // Set pin low again
        LATFINV = 2; // This might do nothing... lol 
        LATFbits.LATF1 = 0;

        // Set period back to 60ms
        PR4 = PERIOD_60_MS;
        // grab FRT time in microseconds
        us_time_start = TIMERS_GetMicroSeconds();
        int_flag++;
        //        LATEINV = 2;
        //        rising_bool = FALSE;
    } else {

        // Set trigger pin high
        //        LATFINV = 2;
        LATFbits.LATF1 = 1;

        // Set period to 10us
        PR4 = PERIOD_10_US;
        //        LATEINV = 1;
    }


    IFS0bits.T4IF = 0;
}


// Testing Main / Application
#ifdef PING_TEST

int main(void) {
    BOARD_Init();
    PING_Init();
    SERIAL_Init();
    ToneGeneration_Init();

    TRISFbits.TRISF4 = 0;
    TRISFbits.TRISF3 = 0;
    TRISFbits.TRISF2 = 0;
    TRISFbits.TRISF6 = 0;
    LATFbits.LATF2 = 1;
    //    LATFbits.LATF5 = 1;
    LATFbits.LATF4 = 1;
    LATFbits.LATF3 = 1;

    unsigned int new_tone = 0;
    unsigned old_tone = 0;
    uint16_t poll_time = 0;
    poll_time = TIMERS_GetMilliSeconds() + 10;
    while (1) {

        if (TIMERS_GetMilliSeconds() >= poll_time) {
            //            printf("\r\ndistance microseconds: %d", PING_GetTimeofFlight());
            printf("\r\ndistance : %d", PING_GetDistance());


            // Tone Generator Application
            new_tone = PING_GetDistance() + TONE_196;
            printf("\r\n new tone : %d", new_tone);
            if (abs(new_tone - old_tone) > MIN_TONE_CHANGE) {
                ToneGeneration_ToneOff();
                ToneGeneration_SetFrequency(new_tone);
                ToneGeneration_ToneOn();
                old_tone = new_tone;
            }
            poll_time = TIMERS_GetMilliSeconds() + 500;
        }
    }

}

#endif


/* *****************************************************************************
 End of File
 */
