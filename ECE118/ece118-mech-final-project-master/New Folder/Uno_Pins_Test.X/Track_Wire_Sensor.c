/*
 * File:   Track_Wire_Sensor.c
 * Author: abner
 *
 * Created on May 17, 2022
 */

#include "Track_Wire_Sensor.h"
/**
 * Function  char TrackWire_Init(void)
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Initialize AD pins for TrackWire
 * @author Amber Patino
 * @date 5/16/2022 */

//#define TRACK_WIRE_TEST
#define FULLBANK 0x0F
#define EMPTYBANK 0x00
char TrackWire_Init(void){
    // Edited by BVK 5/19/2022 -- using digital inputs to Uno for this. Thus we use IO_Ports.h MACROS
    //Assigns defined pins
    A_TW_TRIS = INPUT;
    B_TW_TRIS = INPUT;
    return SUCCESS;
}
/**
 * Function  Read_TrackWire(char)
 * @param TrackWire A or TrackWire B
 * @return Returns High/Low Value corresponding to Track Wire 
 * @remark Used to determine whether the Track Wire has been detected
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned int Read_TrackWire(unsigned int TrackWireSensor){
    // bvk this is interesting? pass in the macro for the PORT Bit only to return the same thing? 
    // seems unneccessary/ No debouncing 
    return TrackWireSensor;
}

/**
 * Function  Read_All_TrackWire(void)
 * @param N/A
 * @return Returns two bit value showing current state of Track Wires A and B,   
 * @remark Reads both track wire sensors at once. Defined bit masks can be used to isolate specific track wires 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned int Read_All_TrackWire(void){
         
     int16_t portReading;
     //Use Defined Masks to Get Specific Bumper Values
     portReading = A_TW | (B_TW<<1);
    return portReading;
}


#ifdef TRACK_WIRE_TEST
    int main(void){
        
        /**
        *Description: Analog Track Wire Detectors A and B readings will be printed. The current reading
         * will be displayed on the LED banks 1 & 2 with 1 being the lowest value
        **/
        //Init Functions
        
        BOARD_Init();
        LED_Init();
        TrackWire_Init();
        
        // Print out compilation statement
        printf("/r/nECE 118 Final Project Solder Slugs Track Wire Detector Testing. Compiled %s, %s", __DATE__, __TIME__);
//        
//        //Adding Bank 1 and 2 to display the value of Track Wire A and B on a scale of 1-4
//        
        LED_AddBanks(LED_BANK1 | LED_BANK2);
        int TW_State; 

        while(1){
            //Turns on all LEDs on Bank 1 if Track Wire A is High
            if(Read_TrackWire(A_TW)){
                LED_SetBank(LED_BANK1 , FULLBANK);
            }
            else{
            //Turns off all LEDs in Bank 1 when Track Wire A is low
                LED_SetBank(LED_BANK1, EMPTYBANK);
            }
            //Turns on all LEDs on Bank 2 if Track Wire B is High
            if(Read_TrackWire(A_TW)){
                LED_SetBank(LED_BANK1 , FULLBANK);
            }
            else{
            //Turns off all LEDs in Bank 2 if Track Wire B is Low
                LED_SetBank(LED_BANK1, EMPTYBANK);
            }
            TW_State = Read_All_TrackWire();
            printf("\r\nCurrent State of all Track Wires: %d", TW_State);
        }
        return 0;
    } 
#endif