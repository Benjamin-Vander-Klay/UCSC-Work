#include "Configuration.h"


/*
    GLOBAL VARIABLES
*/

  Pot PotList[NUM_POTS];
	
  SW2T SW2TList[NUM_SW2];
	
	SW3T SW3TList[NUM_SW3];
	
	SW5T SW5TList[NUM_SW5];
	
	SW7T SW7TList[NUM_SW7];
	
	SW11T SW11TList[NUM_SW11];
	
	int Voltage5Pin; 
	
	int Voltage12Pin; 
	
	int Voltage48Pin; 
	
	int Voltage310Pin; 

/*
    FUNCTION DEFINITIONS
*/

// Resets all static extern variables in Configuration.c, assigning all instantiated setting elements to an unused pin
void ResetConfig(void) {

    // clear all config data 

    for(int i = 0; i < ARRAY_SIZE(PotList); i++) {
	
		PotList[i].Pin1 = UNUSED_PIN;
		PotList[i].Pin2 = UNUSED_PIN;
		PotList[i].Pin3 = UNUSED_PIN;
	
	}
	
	for(int i = 0; i < ARRAY_SIZE(SW2TList); i++) {
	
		SW2TList[i].Pin1 = UNUSED_PIN;
		
	}
	
	for(int i = 0; i < ARRAY_SIZE(SW3TList); i++) {
	
		SW3TList[i].Pin1 = UNUSED_PIN;
		SW3TList[i].Pin2 = UNUSED_PIN;
	
	}
	
	for(int i = 0; i < ARRAY_SIZE(SW5TList); i++) {
	
		SW5TList[i].Pin1 = UNUSED_PIN;
		SW5TList[i].Pin2 = UNUSED_PIN;
		SW5TList[i].Pin3 = UNUSED_PIN;
	
	}
	
	for(int i = 0; i < ARRAY_SIZE(SW7TList); i++) {
	
		SW7TList[i].Pin1 = UNUSED_PIN;
		SW7TList[i].Pin2 = UNUSED_PIN;
		SW7TList[i].Pin3 = UNUSED_PIN;
	
	}
	
	for(int i = 0; i < ARRAY_SIZE(SW11TList); i++) {
	
		SW11TList[i].Pin1 = UNUSED_PIN;
		SW11TList[i].Pin2 = UNUSED_PIN;
		SW11TList[i].Pin3 = UNUSED_PIN;
		SW11TList[i].Pin4 = UNUSED_PIN;
	
	}
	
	Voltage5Pin = UNUSED_PIN;
	Voltage12Pin = UNUSED_PIN;
	Voltage48Pin = UNUSED_PIN;
	Voltage310Pin = UNUSED_PIN;

    // reset all outputs 
    for(int i = 0; i < 14; i++) {
        digitalWrite(i, 0);
    }
    
}

