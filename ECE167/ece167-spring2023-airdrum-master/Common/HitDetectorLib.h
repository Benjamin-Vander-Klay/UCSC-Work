/* 
 * File:   HitDetectorLib.h
 * Author: bcvander
 *
 * Created on May 30, 2023, 10:29 AM
 * Designed to output a high value -- to be exported as MIDI, 
 * when the accelerometer detects a sharp increase in acceleration as the air drum
 * stick swings towards the flat x/y plane, followed by an intense decceleration
 * in the Z direction. 
 * 
 * At the end of the swing the Z direction accelerometer will spike from maybe zero
 * -- close to freefall, or more 
 * 
 * 
 * 
 */

#ifndef HITDETECTORLIB_H
#define	HITDETECTORLIB_H


// how many elements in moving average used to determine magnitude of swing

#define SAMPLES_HELD 10 // sampling every 16ms. 

/**
 * Say a slow roll is 8 hits per second, 
 * .125 sec in between hits, 
 * sampling .016 seconds apart
 * only 7.8 samples in btn hits
 * don't want to hold on to too many samples.  
 */

// which velocity function we're using. 
#define MOVING_AVERAGE // works the best ATM
//#define MAX_SWING
//#define RECOIL_STRENGTH 
//#define TOTAL_Z_VELOCTY

// max/min we will scale the MIDI input to
#define MIDI_MAX 255 // uint8_t
#define MIDI_MIN 0
#define HIT_MAX 8000
#define HIT_MIN 50 // try 


//#define Z-INVERTED // to be used if we install it upside down for some reason
//     as of 6/5/23 not implemented

/**
 * Init function mostly just initializes the moving average array
 * @return Size of moving average array: Macro defined in .h file
 * Turns on 2 LED's mostly for fun 
 */
int HitDetector_Init();


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
 * if return value is -1, error occurred -- if needed
 */

int HitDetector(int acc_y, int acc_z, int addr);


#endif	/* HITDETECTORLIB_H */

