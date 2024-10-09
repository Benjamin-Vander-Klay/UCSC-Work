#include <Arduino.h>

#include "EventBuffer.h"
#include "Configuration.h"

/*
    GLOBAL VARIABLES
*/

 struct EventBuffer {
  Event List[BUFFER_SIZE];

  int Head;
  int Tail;
} EventBuffer;

/*
    FUNCTION DEFINITIONS
*/

// Initialize Event Buffer, set head and tail to, set all events to noEvent, all params to 0
void InitEventBuffer(void) {

  EventBuffer.Head = 0;
	EventBuffer.Tail = 0;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		EventBuffer.List[i].Type = noEvent;
		EventBuffer.List[i].Param1 = 0;
		EventBuffer.List[i].Param2 = 0;
		EventBuffer.List[i].Param3 = 0;
	}

}

// add an event to the head of EventBuffer
int PostEvent(Event ThisEvent) {

    if (!IsEventBufferFull()){
		if( EventBuffer.Head < BUFFER_SIZE) {
			EventBuffer.List[EventBuffer.Head] = ThisEvent;     // add event to lowest open slot
			if (EventBuffer.Head == BUFFER_SIZE - 1){
				EventBuffer.Head = 0;                           // reset head to 0 if it wraps back around
			} else {
				EventBuffer.Head++;                             // increment head otherwise
			}
        } else {
            ExitError(EventBufferHighHead);   
        }
     } else {
		ExitError(EventBufferOverflow);
	}

}

// return the oldest event in EventBuffer
Event GetEvent(void) {

    if (!IsEventBufferEmpty()){
		Event ThisEvent = EventBuffer.List[EventBuffer.Tail];
		
		EventBuffer.List[EventBuffer.Tail].Type = noEvent;      // clear buffer entry
		EventBuffer.List[EventBuffer.Tail].Param1 = 0;
		EventBuffer.List[EventBuffer.Tail].Param2 = 0;
		EventBuffer.List[EventBuffer.Tail].Param3 = 0;
		
		if (EventBuffer.Tail == BUFFER_SIZE - 1) {
			EventBuffer.Tail = 0;                               // reset tail to 0 if it wraps back around
		} else {
			EventBuffer.Tail++;                                 // increment tail otherwise
		}		

		return ThisEvent;
	}	else {
        
		EventBuffer.Head = 0;
		EventBuffer.Tail = 0;                                   // Reset head and tail if buffer is empty
		Event ThisEvent;
        ThisEvent.Type = noEvent;
        return ThisEvent;
	}

}

// Return TRUE is Event Buffer is Full and FALSE if it is not
unsigned char IsEventBufferFull(void) {

    char isFull = TRUE;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		
		if (EventBuffer.List[i].Type == noEvent) {
			isFull = FALSE;
		}
	}
	
	return isFull;

}

// Return TRUE is Event Buffer is Empty and FALSE if it is not
unsigned char IsEventBufferEmpty(void) {

    char isEmpty = TRUE;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		
		if (EventBuffer.List[i].Type != noEvent) {
			isEmpty = FALSE;
		}
	}
	
	return isEmpty;

}

