#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Bumpers.h"
#include "Beacon_Detector.h"
#include "Motor_Driver.h"
#include "Solenoid_Driver.h"
#include "Tape_Sensors.h"
#include "Track_Wire_Sensor.h"
#include "Sense_EventChecker.h"
#include "TopHSM.h"
#include "All_Events.h"
#include "Bumpers_Gen_v1SubHSM.h"
#include "ActiveSearchSubHSM.h"

void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();

    printf("Starting ES Framework Template\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");


    // Your hardware initialization function calls go here
    
    Drive_Init();
    Tape_Init();
    Beacon_Init();
    Solenoid_Init();
    Bumper_Init();
    LED_Init();
    LED_AddBanks(LED_BANK2);
    
    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d", ErrorType);
        break;
    }
    for (;;)
        ;

};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
