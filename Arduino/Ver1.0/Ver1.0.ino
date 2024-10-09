// Library Inclusions


// Project Inclusions
#include "Configuration.h"
#include "EventBuffer.h"
#include "ReceivingSubSM.h"
#include "TopLevelSM.h"

// Test Harness Defines, uncomment exactly one
// Uncomment MAIN to run full program

//#define EVENTS_TEST
//#define TOP_LEVEL_TEST
//#define UART_TEST
#define MAIN

/*
	HELPER FUNCTIONS FOR COMPILING C CODE IN C++ MODE
*/

// converts Serial.write method to a function usable in C mode
int SerialWriteStr(char str[], char len){
    int val = Serial.write(str, len);
    return val;
}


int ExitError(int error) {

    #ifndef MAIN                                          // if in testing mode, print an error statement, else simply exit
    Serial.print("\r\nError: ");
    switch(error) {
    case EventBufferOverflow:
        Serial.print("Event Buffer Overflow, ");
        PrintEventBuffer();        
        break;
    case EventBufferHighHead:
        Serial.print("Event Buffer Invalid Head,");
        break;
    default:
        break;
    }    
    Serial.print("\r\nExiting...\r\n");
    #endif
    delay(1000);
    exit(1);
    return 1;
}



/*
	MAIN FUNCTIONS
*/


void setup() {

    // Hardware initializations

    Serial.begin(9600);

    pinMode(2, OUTPUT);                                 // Configure all available digital pins as outputs
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    pinMode (A0, INPUT);                                // Configure all analog pins as inputs
    pinMode (A1, INPUT);
    pinMode (A2, INPUT);
    pinMode (A3, INPUT);
    pinMode (A4, INPUT);
    pinMode (A5, INPUT);

    // State machine initializations

    InitEventBuffer();
    InitTopLevelSM();
    InitReceivingSubSM();
    ResetConfig();
}


#ifdef MAIN

void loop() {

    if (!IsEventBufferEmpty()){
	
		Event ThisEvent = RunTopLevelSM(GetEvent());
		if (ThisEvent.Type != noEvent){
			PostEvent(ThisEvent);                       // re-post event if it is not consumed in that iteration of SM
		} 
	
	}
	
	// Check for events
	
	if (Serial.available()) {
		Event newEvent;
		newEvent.Type = NewByte;
		newEvent.Param1 = Serial.read();
		
		PostEvent(newEvent);
	}

}

#endif



/*******************************************************

    TEST HARNESSES

********************************************************/

/*
    HELPER FUNCTIONS FOR TESTING
*/ 

#ifndef MAIN 
extern struct EventBuffer {Event List[BUFFER_SIZE]; int Head; int Tail; } EventBuffer;
void PrintEventBuffer(void) {
    Serial.print("Printing Event Buffer...\r\n");
    for(int i = 0; i < BUFFER_SIZE; i++) {

        Serial.print("Event #");
        Serial.print(i);
        Serial.print("\r\n");   
        Serial.print("\tType: ");
        Serial.print((int)EventBuffer.List[i].Type);
        Serial.print("\tParam1: ");
        Serial.print((int)EventBuffer.List[i].Param1);
        Serial.print("\tParam2: ");
        Serial.print((int)EventBuffer.List[i].Param2);
        Serial.print("\tParam3: ");
        Serial.print((int)EventBuffer.List[i].Param3);
        Serial.print("\r\n");
    }
}
#endif

/*
    TEST HARNESS VERSIONS OF LOOP()
*/

#ifdef EVENTS_TEST
void loop(){


    // fill the event buffer to make sure order works
    Event testEvent;
    Event getEvent;
    testEvent.Type = Config_Pot;
    testEvent.Param1 = 1;
    testEvent.Param2 = 2;
    testEvent.Param3 = 3;

    PostEvent(testEvent);

    testEvent.Type = Config_Switch_2T;
    PostEvent(testEvent); 
    testEvent.Type = Config_Switch_3T;
    PostEvent(testEvent);  
    testEvent.Type = Config_Switch_5T;
    PostEvent(testEvent); 
    testEvent.Type = Config_Switch_7T;
    PostEvent(testEvent); 
    testEvent.Type = Config_Switch_11T;
    PostEvent(testEvent);
    testEvent.Type = Config_Voltage;
    PostEvent(testEvent);
    testEvent.Type = Set_Pot;
    PostEvent(testEvent);

    getEvent = GetEvent();
    getEvent = GetEvent();
    getEvent = GetEvent();
    getEvent = GetEvent();
    getEvent = GetEvent();

    testEvent.Type = Set_Switch_2T;
    PostEvent(testEvent);
    testEvent.Type = Set_Switch_3T;
    PostEvent(testEvent);
    testEvent.Type = Set_Switch_5T;
    PostEvent(testEvent);

    getEvent = GetEvent();
    getEvent = GetEvent();
    getEvent = GetEvent();
    getEvent = GetEvent();

    Serial.print("Event Gotten: \r\n");
    Serial.print("\tType: ");
    Serial.print((int)getEvent.Type);
    Serial.print("\tParam1: ");
    Serial.print((int)getEvent.Param1);
    Serial.print("\tParam2: ");
    Serial.print((int)getEvent.Param2);
    Serial.print("\tParam3: ");
    Serial.print((int)getEvent.Param3);
    Serial.print("\r\n");
    
    //Print Event Buffer to serial

    PrintEventBuffer();
    
    while(1);
}
#endif

#ifdef TOP_LEVEL_TEST
void loop(){

    Event testEvent;
    Event returnEvent;

    testEvent.Type = Connected;
    
    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");

    RunTopLevelSM(testEvent);

    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");

    testEvent.Type = TransmitConfirm;
    RunTopLevelSM(testEvent);    

    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");

    testEvent.Type = Read_Voltage;
    returnEvent = RunTopLevelSM(testEvent);

    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");    

    testEvent.Type = TransmitInfo;
    RunTopLevelSM(testEvent);
        
    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");

    testEvent.Type = Set_Pot;
    RunTopLevelSM(testEvent);
        
    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");
    

    while(1);
}
#endif 

#ifdef UART_TEST
void loop(){

    Event testEvent;
    Event returnEvent;

    returnEvent = RunTopLevelSM(testEvent);

    Serial.print("Current State: ");
    Serial.print((int)GetTopLevelState());
    Serial.print("\r\n");

    Serial.print("HEAD: ");
    Serial.print(HEAD_BYTE);
    Serial.print(" TAIL: ");
    Serial.print(TAIL_BYTE);
    Serial.print(" END: ");
    Serial.print(END_BYTE);
    Serial.print("\r\n");

    while(1) {

        if(GetTopLevelState() == Transmitting){

            Serial.print("Entered Transmitting State");  

        }

        if (!IsEventBufferEmpty()){
	
        testEvent = GetEvent();


        Serial.print("Running Top Level SM in state: ");
        Serial.print(GetTopLevelState());
        Serial.print(" with event:\r\n");
        Serial.print(" Type: ");
        Serial.print((int)testEvent.Type);
        Serial.print(" Param1: ");
        Serial.print((int)testEvent.Param1);
        Serial.print(" Param2: ");
        Serial.print((int)testEvent.Param2);
        Serial.print(" Param3: ");
        Serial.print((int)testEvent.Param3);
        Serial.print("\r\n");

		returnEvent = RunTopLevelSM(testEvent);
		if (returnEvent.Type != noEvent){
			PostEvent(returnEvent);  // re-post event if it is not consumed in that iteration of SM
		} 
	
	}
	
	// Check for events
	
	if (Serial.available()) {
		Event newEvent;
		newEvent.Type = NewByte;
		newEvent.Param1 = Serial.read();
		
		PostEvent(newEvent);
	}

    }
}

#endif









