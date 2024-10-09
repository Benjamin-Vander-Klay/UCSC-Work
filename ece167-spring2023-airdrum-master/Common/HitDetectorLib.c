/* 
 * File:   HitDetectorLib.c
 * Author: bcvander
 *
 * Created on May 30, 2023, 10:29 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <xc.h>

#include "HitDetectorLib.h"
#include "BOARD.h"
#include "BNO055.h"
#include "serial.h"
#include "timers.h"

#include "MIDI_Interface.h" // for MIDI transmissions
//#include "BNO_Attitude_Position.h"
#include "AD.h"

//#define HIT_DETECTOR_TEST

#define HIT_SCALE 1.5

/** BNO055 Address A: when ADR (COM3) pin is tied to ground (default) **/
#define BNO055_ADDRESS_A (0x28)
/** BNO055 Address B: when ADR (COM3) pin is tied to +3.3V **/
#define BNO055_ADDRESS_B (0x29)

int8_t swinging_previously_0 = FALSE;
int8_t swinging_previously_1 = FALSE;

int swing_mag_0 = 0;
int swing_mag_1 = 0;
int average_array_0 [SAMPLES_HELD];
int average_array_1 [SAMPLES_HELD];
uint8_t i_0 = 0;
uint8_t i_1 = 0;
int ave_neg_0;
int ave_neg_1;
int sum_neg_0;
int sum_neg_1;


//void delay(int milliSeconds){
//    int start = TIMERS_GetMilliSeconds();
//    while(TIMERS_GetMilliSeconds() < start + milliSeconds);
//}


/**
 * Init function mostly just initializes the moving average array
 * @return Size of moving average array: Macro defined in .h file
 */
int HitDetector_Init() {
    LATE += 0x01;
    for (int i = 0; i < SAMPLES_HELD; i++) {
        average_array_0[i] = 0; // naive init
        average_array_1[i] = 0; // naive init

        //        printf("\r\ni:%d", i);
    }
    LATE += 0x02;
    //    for (i = 0; i < SAMPLES_HELD; i++) {
    //        printf("\r\narray @ %d = %d", i, average_array[i]); // naive init
    //
    //    }
    ave_neg_0 = 0;
    sum_neg_0 = 0;
    ave_neg_1 = 0;
    sum_neg_1 = 0;
    // checking work

    return SAMPLES_HELD;
}

/**
 * HitDetector() 
 * @param y_acc post calibrated Y axis accelerometer reading from BNO055
 * @param z_acc post calibrated Z axis accelerometer reading from BNO055
 * 
 * @return int value corresponding to the magnitude of the hit, 0 being no
 *         hit detected
 * 
 * @author BVK
 * 
 * Notes:
 *  This will be ran how often in order to 
 * do this? Bandwidth of the BNO is set to 62.5Hz or sampling every 16ms
 *          This can be edited in configuration/initialization
 * 
 * ** REQUIRES +/- 8 G's ** -- set up to be 0x1A instead of 0x18 (default). 
 * 
 * 
 * 
 * Returns velocity of hit as integer
 * If return value is 0, no hit was detected
 *
 */
int HitDetector(int acc_y, int acc_z, int addr) {
    if(addr == BNO055_ADDRESS_A){
        int hit_mag = 0;
        // case where we are sensing freefall -> positive aceleration
        if (acc_z > 0) {
            // reset the average count
            //        avg_count = 0;

            // we were previously going negative and now going positive - 1G is like 1000
            // now also accounting for Y acceleration
            // very simply still. Y axis is ~ - 1000 when stick is at 90 degrees up -- about to swing. 
            // check if Y acc is positive before recording a swing. 

            if (acc_z > 600 && swinging_previously_0 == TRUE && acc_y > 200) {
                swinging_previously_0 = 0; // reset swing. 
    //                        printf("\r\n**** **** HIT %d ****\r\n", acc_z);
    //            printf("\r\nZ: %d\r\n Y:%d", acc_z, acc_y);
    #ifdef RECOIL_STRENGTH
                hit_mag = acc_z; // corresponds to positive hit value
    #endif

    #ifdef MOVING_AVERAGE 
                hit_mag = swing_mag_0; // negative hit value
                swing_mag_0 = 0; // reset
                //                                printf("\r\n Y mag : %d", max_y);
                //                    max_y = 0;

                // Clear average -> clear sum and ignore the current values in array
                sum_neg_0 = 0;
                for (i_0 = 0; i_0 < SAMPLES_HELD; i_0++) { // a lot, but manageable if we keep array small
                    average_array_0[i_0] = 0; // naive init
                    //                printf("\r\ni:%d", i);
                }
    //            MIDI_send_string("\nHit detected: %d", abs(hit_mag) >> 6);

    #endif

    #ifdef MAX_SWING 
                hit_mag = swing_mag; // negative hit value
                swing_mag = 0; // reset
                //                                printf("\r\n Y mag : %d", max_y);
                //                    max_y = 0;

                // Clear average -> clear sum and ignore the current values in array
                sum_neg = 0;
                for (i = 0; i < SAMPLES_HELD; i++) { // a lot, but manageable if we keep array small
                    average_array[i] = 0; // naive init
                    printf("\r\ni:%d", i);
                }
    #endif


            }
            swinging_previously_0 = 0;
        }// add it to the array of last like 10 terms?
        else if (acc_z <= 0) { // negative acc, 0 G is freefall. 
            swinging_previously_0 = TRUE;
            // this will end up being the magnitude of the sound we generate
            // or the velocity feeding into the MIDI interface.
            // the proper way to perform this calculation would be to 
            // integrate the acceleration to get the velocity 
            // but simplistically, just taking the maximum.

            // alternate idea is to do a sum, (Acc + acc + acc) * time stamp ? or something 
            // add it to an average
    #ifdef MOVING_AVERAGE
            // keep index below array size
            i_0 = i_0 % SAMPLES_HELD;

            // swap value in sum
            sum_neg_0 -= average_array_0[i_0];
            sum_neg_0 += acc_z;
            //        printf("\r\nsum_neg: %d", sum_neg);
            // update ith value and average
            average_array_0[i_0] = acc_z;
            ave_neg_0 = sum_neg_0 / SAMPLES_HELD;
            i_0++;
            swing_mag_0 = ave_neg_0; // average negative acceleration (swinging)
    #endif
            // do we need to reset these values when not swinging negative? 


            // alternatively, take the maximumly negative acceleration. 
            // and correlate this to sound volume
            // works okay. do need to 
    #ifdef MAX_SWING
            // this results in a negative hit value
            if (abs(acc_z) > swing_mag) { // or actusllu <  
                swing_mag = acc_z;
            }

            //                if (abs(acc_y) > max_y) {
            //                    max_y = acc_y;
            //                }
            //        printf("\r\n Y: %d", acc_y);


            printf("\r\nswing! %d", acc_z); // test this. 

            //        hit_mag = 0; // should be redundant
    #endif
        } else {
            // tf happened
        }

        // scale to 0 -> 255
        return (abs(hit_mag) >> 6) * HIT_SCALE > INT8_MAX ? INT8_MAX : (abs(hit_mag) >> 6) * HIT_SCALE;
    }
    
    
    
    
    
    else{
        int hit_mag = 0;
        // case where we are sensing freefall -> positive aceleration
        if (acc_z > 0) {
            // reset the average count
            //        avg_count = 0;

            // we were previously going negative and now going positive - 1G is like 1000
            // now also accounting for Y acceleration
            // very simply still. Y axis is ~ - 1000 when stick is at 90 degrees up -- about to swing. 
            // check if Y acc is positive before recording a swing. 

            if (acc_z > 600 && swinging_previously_1 == TRUE && acc_y < -200) {
                swinging_previously_1 = 0; // reset swing. 
    //                        printf("\r\n**** **** HIT %d ****\r\n", acc_z);
                printf("\r\nZ: %d\r\n Y:%d", acc_z, acc_y);
    #ifdef RECOIL_STRENGTH
                hit_mag = acc_z; // corresponds to positive hit value
    #endif

    #ifdef MOVING_AVERAGE 
                hit_mag = swing_mag_1; // negative hit value
                swing_mag_1 = 0; // reset
                //                                printf("\r\n Y mag : %d", max_y);
                //                    max_y = 0;

                // Clear average -> clear sum and ignore the current values in array
                sum_neg_1 = 0;
                for (i_1 = 0; i_1 < SAMPLES_HELD; i_1++) { // a lot, but manageable if we keep array small
                    average_array_1[i_1] = 0; // naive init
                    //                printf("\r\ni:%d", i);
                }
    //            MIDI_send_string("\nHit detected: %d", abs(hit_mag) >> 6);

    #endif

    #ifdef MAX_SWING 
                hit_mag = swing_mag; // negative hit value
                swing_mag = 0; // reset
                //                                printf("\r\n Y mag : %d", max_y);
                //                    max_y = 0;

                // Clear average -> clear sum and ignore the current values in array
                sum_neg = 0;
                for (i = 0; i < SAMPLES_HELD; i++) { // a lot, but manageable if we keep array small
                    average_array[i] = 0; // naive init
                    printf("\r\ni:%d", i);
                }
    #endif


            }
            swinging_previously_1 = 0;
        }// add it to the array of last like 10 terms?
        else if (acc_z <= 0) { // negative acc, 0 G is freefall. 
            swinging_previously_1 = TRUE;
            // this will end up being the magnitude of the sound we generate
            // or the velocity feeding into the MIDI interface.
            // the proper way to perform this calculation would be to 
            // integrate the acceleration to get the velocity 
            // but simplistically, just taking the maximum.

            // alternate idea is to do a sum, (Acc + acc + acc) * time stamp ? or something 
            // add it to an average
    #ifdef MOVING_AVERAGE
            // keep index below array size
            i_1 = i_1 % SAMPLES_HELD;

            // swap value in sum
            sum_neg_1 -= average_array_1[i_1];
            sum_neg_1 += acc_z;
            //        printf("\r\nsum_neg: %d", sum_neg);
            // update ith value and average
            average_array_1[i_1] = acc_z;
            ave_neg_1 = sum_neg_1 / SAMPLES_HELD;
            i_1++;
            swing_mag_1 = ave_neg_1; // average negative acceleration (swinging)
    #endif
            // do we need to reset these values when not swinging negative? 


            // alternatively, take the maximumly negative acceleration. 
            // and correlate this to sound volume
            // works okay. do need to 
    #ifdef MAX_SWING
            // this results in a negative hit value
            if (abs(acc_z) > swing_mag) { // or actusllu <  
                swing_mag = acc_z;
            }

            //                if (abs(acc_y) > max_y) {
            //                    max_y = acc_y;
            //                }
            //        printf("\r\n Y: %d", acc_y);


            printf("\r\nswing! %d", acc_z); // test this. 

            //        hit_mag = 0; // should be redundant
    #endif
        } else {
            // tf happened
        }

        // scale to 0 -> 255
    
        return (abs(hit_mag) >> 6) * HIT_SCALE > INT8_MAX ? INT8_MAX : (abs(hit_mag) >> 6) * HIT_SCALE;
    }
}






#ifdef HIT_DETECTOR_TEST

#define WAIT_PERIOD 10 // ms
#define MIDI_TOO 

int main(void) {
    BOARD_Init();
    AD_Init();
    AD_AddPins(AD_A1);
    MIDI_Init();
    MIDI_send_string("\nWelcome to the Hit Detector Testbench.", NULL);

//    SERIAL_Init();
    TIMERS_Init();
//    printf("\r\nWelcome to the Hit Detector Testbench. Compiled on %s, at %s.", __DATE__, __TIME__);

    TRISE = 0x00;
    //    LATE = 0xFF;
    LATE = 0x00;
    //    printf("PORTE = %d", PORTE);

    //    BNO055_Init(BNO055_ADDRESS_A);
    if (BNO055_Init(BNO055_ADDRESS_A) == FALSE) {
        MIDI_send_string("\nBNO055 Init Fail.", NULL);
//        return ERROR;
        // error occured in I2C setup - print error
//        printf("\r\n\r\nerror in BNO055 Init");
        //        fprintf(stderr, "\r\n ERROR occured in BNO055_Init() :(");

    }
//    BNO055_Init(BNO055_ADDRESS_A);
    delay(300);
    if (BNO055_Init(BNO055_ADDRESS_B) == FALSE) {
        MIDI_send_string("\nBNO055 Init Fail 1.", NULL);
//        return ERROR;
        // error occured in I2C setup - print error
//        printf("\r\n\r\nerror in BNO055 Init");
        //        fprintf(stderr, "\r\n ERROR occured in BNO055_Init() :(");

    }
    delay(300);



    HitDetector_Init();
    // default 0
    int acc_x = 0;
    int acc_y = 0;
    int acc_z = 0;
    int hit = 0; // no hit initially
//    int wait = TIMERS_GetMilliSeconds() + WAIT_PERIOD;
     
     
//#ifdef MIDI_TOO
//    
//    
//#endif 
    
    uint8_t drum = DRUM_HIHAT;
    MIDI_Packet midi_tx; 
    uint8_t stomping = FALSE;
#define STOMP_THRESH 30
    
    
    
    
    //    TRISEbits.TRISE0 = 0; // output? 
    //    LATEbits.LATE0 = 0;

    delay(100);

    // hit is going to be true if there is a large negative spike in the Z direction
    // followed by a return to 1G -> ~ 1000 reading. 

    // for now track last ~3 spikes. Look for largest negative spike in last 10 terms?

   
//    printf("\r\n Y acc: %d", acc_y);
    //    printf("\r\nZ reading: %d", wait);
    while (1) {
        int16_t stomp = AD_ReadADPin(AD_A1);
        if(stomp != ERROR){
//            MIDI_send_string("AD: %d\n", stomp);
            uint16_t stomp_strength = (stomp >> 3) + 50;
            if(stomp_strength > 127) stomp_strength = 127;
            if(stomp > STOMP_THRESH && !stomping){
                midi_tx = MIDI_build_packet(NOTE_ON, DRUM_CHANNEL, DRUM_KICK, stomp_strength);
                MIDI_send_packet(midi_tx);
//                MIDI_send_string("Stomp\n", NULL);
                stomping = TRUE;
            }else if(stomping && stomp < STOMP_THRESH){
                midi_tx = MIDI_build_packet(NOTE_OFF, DRUM_CHANNEL, DRUM_KICK, 0);
//                MIDI_send_packet(midi_tx);
//                MIDI_send_string("Stomp off\n", NULL);

                stomping = FALSE;
            }
        }
        
        delay(1);


        
            acc_x = BNO055_ReadAccelX(BNO055_ADDRESS_A);
            acc_y = BNO055_ReadAccelY(BNO055_ADDRESS_A);
            acc_z = BNO055_ReadAccelZ(BNO055_ADDRESS_A);
//            //            printf("\r\nX reading: %d", acc_x);
////                        printf("\r\nY reading: %d", acc_y);
////                                    printf("\r\nZ reading: %d", acc_z);
//
//            // calibration?
//
//            // actual used function
            hit = HitDetector(acc_y, acc_z, BNO055_ADDRESS_A);
            if (hit != 0) {
//                printf("\r\n Hit detected: %d", hit);
//                MIDI_send_string("\nHit detected: %d", hit);
            
                switch (getBNOQuadrant(BNO055_ADDRESS_A)) {
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
                        drum = DRUM_KICK;
                        break;
                    default: break;
                }
                midi_tx = MIDI_build_packet(NOTE_ON, DRUM_CHANNEL, drum, hit);
                MIDI_send_packet(midi_tx);
//                delay(30);
//                midi_tx = MIDI_build_packet(NOTE_OFF, DRUM_CHANNEL, drum, hit);
//                MIDI_send_packet(midi_tx);
            }
            
            
            
            
            
            
            
            
            acc_x = BNO055_ReadAccelX(BNO055_ADDRESS_B);
            acc_y = BNO055_ReadAccelY(BNO055_ADDRESS_B);
            acc_z = BNO055_ReadAccelZ(BNO055_ADDRESS_B);
            
            hit = HitDetector(acc_x, acc_z, BNO055_ADDRESS_B);
            if (hit != 0) {
//                printf("\r\n Hit detected: %d", hit);
//                MIDI_send_string("\nHit detected 1: %d", hit);
            
                switch (getBNOQuadrant(BNO055_ADDRESS_B)) {
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
                        drum = DRUM_KICK;
                        break;
                    default: break;
                }
                midi_tx = MIDI_build_packet(NOTE_ON, DRUM_CHANNEL, drum, hit);
                MIDI_send_packet(midi_tx);
//                delay(30);
//                midi_tx = MIDI_build_packet(NOTE_OFF, DRUM_CHANNEL, drum, hit);
//                MIDI_send_packet(midi_tx);
            }
            
        }
    
    
    
    
    
    //    }
    // frankly we shouldn't return -- embedded
//    while (1);
    return EXIT_FAILURE;
}
#endif