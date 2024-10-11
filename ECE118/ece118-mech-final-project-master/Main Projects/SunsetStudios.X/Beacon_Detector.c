/*
 * File:   Beacon_Detector.c
 * Author: abner
 *
 * Created on May 17, 2022
 */

#include "Beacon_Detector.h"

#define INPUT 1 
#define FULLBANK 0x0F
#define EMPTYBANK 0x00
//Beacon Test
//#define BEACON_TEST

#define OFFSET 1
/**
 * Function  Beacon_Init(void)
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Initialize AD pins for Analog Beacon and Digital Pins for other Beacon 
 * @author Amber Patino
 * @date 5/16/2022 */
char Beacon_Init(void){
    char returnVal = 0;
//    returnVal = AD_Init();
    //Adds Analog Pin
    AD_AddPins(ALOG_BEACON);
    
    //Sets Port Direction to Input for Digital Pin
    DIG_TRIS = INPUT;
    return returnVal;
}

/**
 * Function  Read_Analog_Beacon(void)
 * @param 
 * @return returns 10 bit value for output from analog beacon detector
 * @remark Returns the current reading from the analog beacon detector
 * @author Amber Patino
 * @date 5/16/2022 */
unsigned int Read_Analog_Beacon(void){
    return AD_ReadADPin(ALOG_BEACON);
}
/**
 * Function  Read_Digital_Beacon(void)
 * @param 
 * @return High/LOW
 * @remark Returns the current reading from the Digital Beacon Detector
 * @author Amber Patino
 * @date 5/16/2022 */
char Read_Digital_Beacon(void){
    return DIG_BEACON;
}
#ifdef BEACON_TEST
    int main(void){
        
        /**
        *Description: Analog Track Wire Detectors A and B readings will be printed. The current reading
         * will be displayed on the LED banks 1 & 2 with 1 being the lowest value
        **/
        //Init Functions
        
         BOARD_Init();
         LED_Init();
         Beacon_Init();
         
         // Print out compilation statement
        printf("/r/nECE 118 Final Project Solder Slugs Beacon Detector Testing. Compiled %s, %s", __DATE__, __TIME__);
//        
//        //Adding Bank 1 to Display a scaled version of the Beacon Reading. Bank 2 will indicate whether the beacon
         //has been triggered
         LED_AddBanks(LED_BANK1 | LED_BANK2);
//        
//        //Defining variables to hold readings for A and B
//        
        int scaled_Reading, reading;
        uint16_t pattern;
        while(1){
//            //Read Analog Beacon and output the Scaled Reading to LED Bank
            reading =  Read_Analog_Beacon();
            scaled_Reading = reading *4/1023;
//            //Get Pattern for LED Bank =
            pattern = (1 << (scaled_Reading - OFFSET) ); 
//            
            //Setting Pattern for the LED 
            LED_SetBank(LED_BANK1, pattern);
//            
            printf("\r\nCurrent Reading for Analog Sensor: %d", reading);
            printf("\r\n State: %d", Read_Digital_Beacon());
            
            //Turns on all LEDs in Bank 2 when the Digital Beacon is high
            if(Read_Digital_Beacon()){
                printf("\r\n Beacon is High");
                LED_SetBank(LED_BANK2 , FULLBANK);
            }
            else{
            //Turns off all LEDs in Bank 2 when the Digital Beacon is low
                printf("\r\n Beacon is Low");
                LED_SetBank(LED_BANK2, EMPTYBANK);
            }

        }
        
        return 0;
    } 
#endif