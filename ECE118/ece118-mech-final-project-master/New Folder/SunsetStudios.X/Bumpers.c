/*
 * File:   Bumpers.c
 * Author: abner
 *
 * Created on May 16, 2022
 */

#include "Bumpers.h"



/*

*/

//Digital States
#define LOW 0
#define HIGH 1

#define INPUT 1

#define NUM_BUMPERS 4

//Bumper Masks
#define FL_MASK 0x01
#define FR_MASK 0X02
#define RL_MASK 0x04
#define RR_MASK 0X08

//Test Harness for Bump Sensor
//#define BUMP_TEST

char Bumper_Init(void){
    //Assigning Digital Port Direction for Port X Pins 9:12
    FR_TRIS = INPUT;
    FL_TRIS = INPUT;
    RR_TRIS = INPUT;
    RL_TRIS = INPUT;
    return SUCCESS;        
//    IO_PortsSetPortInputs(BUMP_PORT, BUMP_PINS);
    
}
unsigned char Read_FR_Bumper(void){
    //Reading/Inverting bits from port X09
    return !FR;
}
unsigned char Read_FL_Bumper(void){
    return !FL;
}
unsigned char Read_RR_Bumper(void){
    return !RR;
}
unsigned char Read_RL_Bumper(void){
    return !RL;
}
 int16_t Read_All_Bumpers(void){
     
     int16_t portReading;
     //Use Defined Masks to Get Specific Bumper Values
     portReading = !FL | (!FR<<1) | (!RL <<2) | (!RR <<3);
    return portReading;
}

#ifdef BUMP_TEST
    int main(void){
        BOARD_Init();
        Bumper_Init();
        int16_t bumpState;
        
        // Print out compilation statement
        printf("/r/nECE 118 Final Project Solder Slugs Bumper Testing. Compiled %s, %s", __DATE__, __TIME__);
        if(Bumper_Init()){
                printf("\r\n *****Welcome To the Bumper Test: Bumpers Successfully Initialized****");
            }
            else{
                printf("\r\nFailed to Initialize Bumpers");
            }
                
            
                bumpState = Read_FL_Bumper();
                printf("\r\n Current State of Front Left Bumper: %d", bumpState);
                bumpState = Read_FR_Bumper();
                printf("\r\n Current State of Front Right Bumper: %d", bumpState);
                bumpState = Read_RL_Bumper();
                printf("\r\n Current State of Rear Left Bumper: %d", bumpState);
                bumpState = Read_RR_Bumper();
                printf("\r\n Current State of Rear RightBumper: %d", bumpState);
                bumpState = Read_All_Bumpers();
                printf("\r\n Current State of all Bumpers: %d", bumpState);
        while(1){
                ;
        }
                return 0;
    }
    
#endif