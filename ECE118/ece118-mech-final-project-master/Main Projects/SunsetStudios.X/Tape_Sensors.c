/*
 * File:   TapeSensor.c
 * Author: abner
 *
 * Created on May 16, 2022
 */

#include "Tape_Sensors.h"
//TIP 120 Pin
#define SWITCH_PORT PORTY
#define SWITCH_PIN PIN3


//Ports for Sensors Change as needed



//Digital States
#define LOW 0
#define HIGH 1


//#define TAPE_TEST
//Names of Digital Tape Sensors
/*---------------------
 *|Fill in here Later* |
 * --------------------*/
//6/1/22 Amber -- Was not previously using defines for some reason

/**
 * Function  Tape_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Initialize AD pins for Tape Sensors, PWM Signal for swtich 
 * @author Amber Patino
 * @date 5/16/2022 */

char Tape_Init(void) {
    char returnVal = 0;
    //    returnVal = AD_Init();
    //Initializes Tape Sensor 
    AD_AddPins(A_TS | B_TS | C_TS | D_TS | E_TS | F_TS);
    //Sets Switch to an Output 
    IO_PortsSetPortOutputs(SWITCH_PORT, SWITCH_PIN);
    //Sets switch to High (Default state)
    IO_PortsSetPortBits(SWITCH_PORT, SWITCH_PIN);

    //Set Port Direction for Digital Tape Sensors 
    //    TS_Front_TRIS = INPUT; 6/6/22 Changing to AD
    //    TS_Mid_TRIS = INPUT;  6/6/22 Changing to AD
    //    TS_Rear_TRIS = INPUT;  6/6/22 Changing to AD
    // BVK added 5/19/2022
    AD_AddPins(TS_FRONT_AD | TS_MID_AD | TS_REAR_AD);

    return returnVal;
}

/**
 * Function  Read_Bottom_Tape(char)
 * @param Name of Tape Sensor that you are trying to read 
 * @return 10-bit value corresponding to the light level from the sensor 
 * @remark Returns the light level from specified sensor 
 * @author Amber Patino
 * @date 5/16/2022 */

unsigned int Read_Bottom_Tape(unsigned int TapeSensor) {
    return AD_ReadADPin(TapeSensor);
}

/**
 * Function  Read_Top_Tape(void)
 * @param n/a
 * @return State of Top Tape Sensors, 
 * @author Amber Patino
 * @date 5/16/2022 */



char Read_Top_Tape(void) {
    char currentState;
    //    currentState = TS_Front | (TS_Mid << 1) | (TS_Rear << 2);  6/6/22 Not being Used
    return currentState;
}

unsigned int Read_Top_Tape_AD(unsigned int TapeSensor) {
    return AD_ReadADPin(TapeSensor);
}

/**
 * Function  Set_IR_LED(char State)
 * @param HIGH or LOW
 * @return SUCCESS or ERROR
 * @remark Sets the State of the IR LED to ON/OFF. For Use for detecting current light conditions 
 * @author Amber Patino
 * @date 5/16/2022 */
char Set_IR_LED(char State) {
    return 0;
}
/**
 * Function  Get_IR_LED(char State)
 * @param HIGH or LOW
 * @remark Returns Current State of IR LEDS 
 * @author Amber Patino
 * @date 5/16/2022 */

//Not implemented yet

char Get_IR_LED(void) {
    return 0;
}


#ifdef TAPE_TEST

int main(void) {
    BOARD_Init();

    Tape_Init();

    // Print out compilation statement
    printf("/r/nECE 118 Final Project Solder Slugs Tape Sensor Testing. Compiled %s, %s", __DATE__, __TIME__);

    if (Tape_Init()) {
        printf("\r\n Tape Sensors Initialized");
    } else {
        printf("\r\nFailed to Initialize Tape Sensor");
    }

    // BVK added 5/19/2022
    unsigned int tapeReading;
    char TopTapeState;
    tapeReading = Read_Bottom_Tape(B_TS);
    printf("\r\n ////////////////////////////////////////");

    tapeReading = Read_Bottom_Tape(A_TS);
    printf("\r\n Tape Reading A: %d", tapeReading);

    tapeReading = Read_Bottom_Tape(B_TS);
    printf("\r\n Tape Reading B: %d", tapeReading);

    tapeReading = Read_Bottom_Tape(C_TS);
    printf("\r\n Tape Reading C: %d", tapeReading);

    tapeReading = Read_Bottom_Tape(D_TS);
    printf("\r\n Tape Reading D: %d", tapeReading);

    tapeReading = Read_Bottom_Tape(E_TS);
    printf("\r\n Tape Reading E: %d", tapeReading);

    tapeReading = Read_Bottom_Tape(F_TS);
    printf("\r\n Tape Reading F: %d", tapeReading);

    tapeReading = AD_ReadADPin(TS_FRONT_AD); //Read_Bottom_Tape(B_TS);
                printf("\r\n Tape Reading Front: %d", tapeReading);
    tapeReading = AD_ReadADPin(TS_MID_AD); //Read_Bottom_Tape(B_TS);
                printf("\r\n Tape Reading Mid: %d", tapeReading);
    tapeReading = AD_ReadADPin(TS_REAR_AD); //Read_Bottom_Tape(B_TS);
                printf("\r\n Tape Reading Rear: %d", tapeReading);
    if (Read_Top_Tape()) {
        printf("\r\n Both Tape Sensors High");
    } else {
        printf("\r\n Both Tape Sensors are not High");
    }
    while (1) {
        //        TopTapeState = Read_Top_Tape();
        //        printf("\r\n Current State for Top Tape Sensors: %d", TopTapeState);

        tapeReading = AD_ReadADPin(TS_FRONT_AD); //Read_Bottom_Tape(B_TS);
        //            printf("\r\n Tape Reading Front: %d", tapeReading);
        tapeReading = AD_ReadADPin(TS_MID_AD); //Read_Bottom_Tape(B_TS);
        //            printf("\r\n Tape Reading Mid: %d", tapeReading);
        tapeReading = AD_ReadADPin(TS_REAR_AD); //Read_Bottom_Tape(B_TS);
        //            printf("\r\n Tape Reading Rear: %d", tapeReading);

    }
}

#endif
