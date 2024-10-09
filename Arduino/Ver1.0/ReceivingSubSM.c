#include "ReceivingSubSM.h"

/*
    GLOBAL VARIABLES
*/

  static ReceivingSubState ThisSubState;

	static char ThisLength = 0; 						// length of payload in bytes
	static char ThisPayload[MAX_PAYLOAD];
	static char PayloadCount = 0; 						// number of payload bytes read
	static char ThisSum = 0;

/*
    FUNCTION DEFINITIONS
*/

void InitReceivingSubSM(void) {

    ThisSubState= ReadHead;
    ThisLength = 0;
    for (int i = 0; i < MAX_PAYLOAD; i++) {
        ThisPayload[i] = 0x0;        
    }
    PayloadCount = 0;
    ThisSum = 0;
    

}

// Runs the Receiving sub state machine
Event RunReceivingSubSM(Event ThisEvent) {

	static char thisLength = 0; 						// length of payload in bytes
	static char thisPayload[MAX_PAYLOAD];
	static char payloadCount = 0; 						// number of payload bytes read
	static char thisSum = 0;
	

	switch(ThisSubState) {
	case ReadHead:
			
			switch(ThisEvent.Type) {
			case NewByte:

				if (ThisEvent.Param1 == HEAD_BYTE){             
					ThisSubState = ReadLength; 	
					thisLength = 0;
					for (int i = 0; i < MAX_PAYLOAD; i++){
						thisPayload[i] = 0x0;        
					}
					payloadCount = 0;
					thisSum = 0;
				}
				ThisEvent.Type = noEvent;			// consume event
				break;
			default:
				break;
			}
		break;

	case ReadLength:
	
			switch(ThisEvent.Type) {
			case NewByte:

				thisLength = ThisEvent.Param1;			// store length of payload
				for(int i = 0; i < MAX_PAYLOAD; i++) {
					thisPayload[i] = 0;					// clear payload variable
				}
				ThisSubState = ReadPayload;
				ThisEvent.Type = noEvent;
				break;
                
			default:
				break;
			}
		break;

	case ReadPayload:
	
			switch(ThisEvent.Type) {
			case NewByte:
				
				thisPayload[payloadCount] = ThisEvent.Param1;
				payloadCount++;
				if (payloadCount >= thisLength) {
					ThisSubState = ReadTail;			// transition once thisLength # of bytes read
				}
				ThisEvent.Type = noEvent;
				break;

			default:
				break;
			}
		
		break;
	case ReadTail:
	
			switch(ThisEvent.Type) {
			case NewByte:
				
				if (ThisEvent.Param1 == TAIL_BYTE){
					ThisSubState = ReadSum;		
				} else {
					ThisSubState = ReadHead;
				}
				ThisEvent.Type = noEvent;
				break;

			default:
				break;
			}
		
		break;
	case ReadSum:
	
			switch(ThisEvent.Type) {
			case NewByte:
			
				thisSum = ThisEvent.Param1;
				ThisSubState = ReadEnd;
				ThisEvent.Type = noEvent;
				break;
                
			default:
				break;
			}
		
		break;
	case ReadEnd:
	
			switch(ThisEvent.Type) {
			case NewByte:
			
				if (ThisEvent.Param1 == END_BYTE){
																	// implements CompareSum "state"
					if (thisSum == CalculateChecksum(thisPayload, ARRAY_SIZE(thisPayload))){
																	// implements post "state"
						Event commandEvent;
						Event respondEvent;
			
						commandEvent.Type   = thisPayload[0];	    // payloads will be structured the same as command events
						commandEvent.Param1 = thisPayload[1];
						commandEvent.Param2 = thisPayload[2];
						commandEvent.Param3 = thisPayload[3];
						commandEvent.Param4 = thisPayload[4];
                        commandEvent.Param5 = thisPayload[5];

						respondEvent.Type = TransmitConfirm;
						respondEvent.Param1 = thisPayload[0];
			
						PostEvent(respondEvent);					// Post respond event THEN command event
						PostEvent(commandEvent);
						
					} 
				} 
				ThisSubState = ReadHead;							// Reset to ReadHead state no matter what
				ThisEvent.Type = noEvent;
				break;

			default:
				break;
			}
		break;
	default:
		break;
	}

	return ThisEvent;

}

ReceivingSubState GetReceivingSubState(void) {

    return ThisSubState;

}

// returns the bitwise NOT of the bitwise XOR of string char[]
char CalculateChecksum(char str[], char len){ 

    char sum = 0; 

	for(int i = 0; i < len; i++) {

        sum ^= str[i];

    }
    sum = ~sum;
	
	return sum;

}