
#include <Arduino.h>

#include "TopLevelSM.h"
#include "Configuration.h"


/*
    GLOBAL VARIABLES
*/

	static TopLevelState ThisState;

/*
    FUNCTION DEFINITIONS
*/

void InitTopLevelSM(void) {

    ThisState = InitTop;

}

Event RunTopLevelSM(Event ThisEvent) {

    // Local Variable Declarations
    char responsePacket[RESPONSE_STR_LEN];  // belongs to Transmitting > TransmitConfirm
    char infoPacket[AREAD_STR_LEN];         // belongs to Transmitting > TransmitInfo
    char thisPayload2[2];                   // belongs to Transmitting > TransmitConfirm
    char thisPayload3[3];                   // belongs to Transmitting > TransmitInfo
    Event newEvent;
    int thisVoltage = 0;                    // belongs to Executing > Read_Voltage

    switch(ThisState) {
	case InitTop:
		ThisState = Receiving;
		break;
	case Receiving:
			ThisEvent = RunReceivingSubSM(ThisEvent);
			if (ThisEvent.Type == TransmitConfirm) {
				ThisState = Transmitting;
				ThisEvent = RunTopLevelSM(ThisEvent);			    // transition when transmit event is found
			}
		break;
	case Transmitting:
	
		switch (ThisEvent.Type) {
		case TransmitConfirm:
    
                                                                    // Define string char by char because C is annoying
            thisPayload2[0] = ThisEvent.Type;
            thisPayload2[1] = ThisEvent.Param1;
            responsePacket[0] = HEAD_BYTE;
            responsePacket[1] = 2;
            responsePacket[2] = ThisEvent.Type;
            responsePacket[3] = ThisEvent.Param1;
            responsePacket[4] = TAIL_BYTE;
            responsePacket[5] = CalculateChecksum(thisPayload2, ARRAY_SIZE(thisPayload2));
            responsePacket[6] = END_BYTE;
			
			                                                        // send message and verify it sent before transition
			if (SerialWriteStr(responsePacket, RESPONSE_STR_LEN) == RESPONSE_STR_LEN) {
				ThisState = Executing;	
				ThisEvent.Type = noEvent;
			} else {
				PostEvent(ThisEvent);                               // if message fails to send, try to send it again
			}
	    break;
		case TransmitInfo:

            thisPayload3[0] = ThisEvent.Type;
            thisPayload3[1] = ThisEvent.Param1;
            thisPayload3[2] = ThisEvent.Param2;
			infoPacket[0] = HEAD_BYTE;
            infoPacket[1] = 3;
            infoPacket[2] = ThisEvent.Type;
            infoPacket[3] = ThisEvent.Param1;
            infoPacket[4] = ThisEvent.Param2;
            infoPacket[5] = TAIL_BYTE;
            infoPacket[6] = CalculateChecksum(thisPayload3, ARRAY_SIZE(thisPayload3));
            infoPacket[7] = END_BYTE;
			
			                                                        // send message and verify it sent before transition
			if (SerialWriteStr(infoPacket, AREAD_STR_LEN) == AREAD_STR_LEN) {
				ThisState = Receiving;		
				ThisEvent.Type = noEvent;
			} else {
				PostEvent(ThisEvent);                               // if message fails to send, try and send it again
			}
			
		break;
			default:
		break;	
		}
	
		break;
	case Executing:
	
		switch(ThisEvent.Type) {
		case Connected:
            ThisState = Receiving;
            ThisEvent.Type = noEvent;                   
			break;
		case Reset:
			ResetConfig();
            ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Pot:
			PotList[ThisEvent.Param1].Pin1 = ThisEvent.Param2;
			PotList[ThisEvent.Param1].Pin2 = ThisEvent.Param3;
			PotList[ThisEvent.Param1].Pin3 = ThisEvent.Param4;
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Switch_2T:
			SW2TList[ThisEvent.Param1].Pin1 = ThisEvent.Param2;
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Switch_3T:
			SW3TList[ThisEvent.Param1].Pin1 = ThisEvent.Param2;
			SW3TList[ThisEvent.Param1].Pin2 = ThisEvent.Param3;
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Switch_5T:
			SW5TList[ThisEvent.Param1].Pin1 = ThisEvent.Param2;
			SW5TList[ThisEvent.Param1].Pin2 = ThisEvent.Param3;
			SW5TList[ThisEvent.Param1].Pin3 = ThisEvent.Param4;
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Switch_7T:
			SW7TList[ThisEvent.Param1].Pin1 = ThisEvent.Param2;
			SW7TList[ThisEvent.Param1].Pin2 = ThisEvent.Param3;
			SW7TList[ThisEvent.Param1].Pin3 = ThisEvent.Param4;
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Switch_11T:
			SW11TList[ThisEvent.Param1].Pin1 = ThisEvent.Param2;
			SW11TList[ThisEvent.Param1].Pin2 = ThisEvent.Param3;
			SW11TList[ThisEvent.Param1].Pin3 = ThisEvent.Param4;
			SW11TList[ThisEvent.Param1].Pin4 = ThisEvent.Param5;
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Config_Voltage:
			switch(ThisEvent.Param1) {
			case Voltage5:
				Voltage5Pin = ThisEvent.Param2;
				break;
			case Voltage12:
				Voltage12Pin = ThisEvent.Param2;
				break;
			case Voltage48:
				Voltage48Pin = ThisEvent.Param2;
				break;
			case Voltage310:
				Voltage310Pin = ThisEvent.Param2;
				break;
			}
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Set_Pot:
			digitalWrite(PotList[ThisEvent.Param1].Pin1, ThisEvent.Param2 & FIRST_BIT);
			digitalWrite(PotList[ThisEvent.Param1].Pin2, ThisEvent.Param2 & SECOND_BIT);
			digitalWrite(PotList[ThisEvent.Param1].Pin3, ThisEvent.Param2 & THIRD_BIT);
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Set_Switch_2T:
			digitalWrite(SW2TList[ThisEvent.Param1].Pin1, ThisEvent.Param2 & FIRST_BIT);
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Set_Switch_3T:
			digitalWrite(SW3TList[ThisEvent.Param1].Pin1, ThisEvent.Param2 & FIRST_BIT);
			digitalWrite(SW3TList[ThisEvent.Param1].Pin2, ThisEvent.Param2 & SECOND_BIT);
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Set_Switch_5T:
			digitalWrite(SW5TList[ThisEvent.Param1].Pin1, ThisEvent.Param2 & FIRST_BIT);
			digitalWrite(SW5TList[ThisEvent.Param1].Pin2, ThisEvent.Param2 & SECOND_BIT);
			digitalWrite(SW5TList[ThisEvent.Param1].Pin3, ThisEvent.Param2 & THIRD_BIT);
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Set_Switch_7T:
			digitalWrite(SW7TList[ThisEvent.Param1].Pin1, ThisEvent.Param2 & FIRST_BIT);
			digitalWrite(SW7TList[ThisEvent.Param1].Pin2, ThisEvent.Param2 & SECOND_BIT);
			digitalWrite(SW7TList[ThisEvent.Param1].Pin3, ThisEvent.Param2 & THIRD_BIT);
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
		case Set_Switch_11T:
			digitalWrite(SW11TList[ThisEvent.Param1].Pin1, ThisEvent.Param2 & FIRST_BIT);
			digitalWrite(SW11TList[ThisEvent.Param1].Pin2, ThisEvent.Param2 & SECOND_BIT);
			digitalWrite(SW11TList[ThisEvent.Param1].Pin3, ThisEvent.Param2 & THIRD_BIT);
			digitalWrite(SW11TList[ThisEvent.Param1].Pin4, ThisEvent.Param2 & FOURTH_BIT);
			ThisState = Receiving;
            ThisEvent.Type = noEvent;
			break;
			
		case Read_Voltage:
			
			newEvent.Type = TransmitInfo;
			switch(ThisEvent.Param1) {
			case Voltage5:
                newEvent.Param1 = Voltage5;
				thisVoltage = analogRead(Voltage5Pin) >> 2;                     // reduce max from 1023 to 255
				break;
			case Voltage12:
            newEvent.Param1 = Voltage12;
				thisVoltage = analogRead(Voltage12Pin) >> 2;
				break;
			case Voltage48:
                newEvent.Param1 = Voltage48;
				thisVoltage = analogRead(Voltage48Pin) >> 2;
				break;
			case Voltage310:
                newEvent.Param1 = Voltage310;
				thisVoltage = analogRead(Voltage310Pin) >> 2;
				break;
			}
			if (thisVoltage > ThisEvent.Param2) {
				newEvent.Param2 = PASSED;
			} else {
				newEvent.Param2 = FAILED;
			}
			PostEvent(newEvent);
            ThisEvent.Type = noEvent;
			ThisState = Transmitting;
		break;
		default:
			break;
		}
	
		break;
	deafault:
		break;
	}
	
	return ThisEvent;

}

TopLevelState GetTopLevelState(void) {

    return ThisState;

}