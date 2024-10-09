/* 
 * File:   RCServo.c
 * Author: Benjamin Vander Klay (bcvander)
 * Brief: 
 * Created on January 23, 2022, 8:14pm
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "RCServo.h" // The header file for this source file.
#include "Protocol.h"
#include <xc.h>
#include <sys/attribs.h>
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include "MessageIDs.h"
#include "FreeRunningTimer.h"


/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define PERIOD_T3 31250
#define RC_CENTERED_TICKS 938
// based on 1:64 prescalar. 62,500 ticks in 50ms. 50000 us in 50 ms. /100 
#define TICKS_NUM 312
#define TICKS_DENOM 500
#define START_SPOT 0
#define NOPS_FOR_100_MS 50000
#define UINT_LEN 4
/*******************************************************************************
 * PRIVATE MODULAR VARIABLES                                                           *
 ******************************************************************************/
unsigned int pulse_width_ticks, pulse_width_us;

/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

void NOP_delay_100ms ();
/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/
/**
 * @Function RCServo_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware required and set it to the CENTER PULSE */
int RCServo_Init(void){
    // init timer3
    T3CON = 0;
    T3CONbits.TCKPS = 0b110; // 1:64 -  prescalar
    // set period = 31,250 ticks.
    PR3 = PERIOD_T3;
//    T3CONbits.ON = 1;
    
    // configure Output Capture 3 -- Pin 6
    OC3CON = 0;
    // Set pin 6 as output
    TRISDbits.TRISD2 = 0;
    // Set Timer3 as clock source for OC3
    OC3CONbits.OCTSEL = 1;
    // Mode = Continuous output pulses
    OC3CONbits.OCM = 0b101;
    //start pulse at t3 = 0
    OC3R = START_SPOT;
    //set pulse width initially to centered (based on 1500 us -> ticks. 31250 * 1500 / 50,000)
    OC3RS = RC_CENTERED_TICKS + START_SPOT;
//    OC3RS = 1250 + START_SPOT;
    
    // Clear interrupt flag
    IFS0bits.OC3IF = 0;
    // Enable interrupts
    IEC0bits.OC3IE = 1;
    IPC3bits.OC3IP = 2;
    IPC3bits.OC3IS = 1;
    
    // Set modular wide varibale so ISR can set it back to center
    pulse_width_ticks = RC_CENTERED_TICKS + START_SPOT;
//    pulse_width_ticks = 1250 + START_SPOT; // 2k*.625 + 16000
    // Turn it back on
    T3CONbits.ON = 1;
    OC3CONbits.ON = 1;
    
    
    return ERROR;
}

/**
 * @Function int RCServo_SetPulse(unsigned int inPulse)
 * @param inPulse, integer representing number of microseconds
 * @return SUCCESS or ERROR
 * @brief takes in microsecond count, converts to ticks and updates the internal variables
 * @warning This will update the timing for the next pulse, not the current one */
int RCServo_SetPulse(unsigned int inPulse){
    
    
    // within bounds. so we don't break the servo
    if(RC_SERVO_MIN_PULSE <= inPulse <= RC_SERVO_MAX_PULSE ){
        // save the width in us
        pulse_width_us = inPulse;
        inPulse = (inPulse * TICKS_NUM) / TICKS_DENOM;
        // save width in ticks
        pulse_width_ticks = inPulse;
        return SUCCESS;
    }
    else
        return ERROR;
    
}

/**
 * @Function int RCServo_GetPulse(void)
 * @param None
 * @return Pulse in microseconds currently set */
unsigned int RCServo_GetPulse(void){
    
    return pulse_width_us;
}

/**
 * @Function int RCServo_GetRawTicks(void)
 * @param None
 * @return raw timer ticks required to generate current pulse. */
unsigned int RCServo_GetRawTicks(void){
    
    return pulse_width_ticks;
}
/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/

void __ISR ( _OUTPUT_COMPARE_3_VECTOR ) __OC3Interrupt ( void ) {
    // set flag low again
    IFS0bits.OC3IF = 0;
    // change pulse widths
    OC3RS = pulse_width_ticks;
//    LATEINV = 1;
    
    
}

//// borrowed from Lab0 :)
//void NOP_delay_100ms () {
//    int i;
//    for (i = 0; i < NOPS_FOR_100_MS; i++) { 
//            asm ("NOP");   
//    }
//}

/**
 * @Function someFunction(void)
 * @param foo, some value
 * @return TRUE or FALSE
 * @brief 
 * @note 
 * @author <Your Name>
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
//uint8_t someFunction(int foo);

#ifdef TEST_RC_SERVO
int main() {
    
    TRISE = 0;
    LATE = 0;
    
    BOARD_Init();
    Protocol_Init();
    RCServo_Init();
    
//    pulse_width_ticks = RC_CENTERED_TICKS + 1600;
    RCServo_SetPulse(RC_SERVO_MAX_PULSE);
//    RCServo_SetPulse(RC_SERVO_MIN_PULSE);
    
    // -------------------------------------------------------------------------
    //Send debug message about the date and time n stuff 
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    sprintf(intro_message, "RCServo.c Test Harness compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);
    LATE = 15;
    // -------------------------------------------------------------------------
    unsigned char *error = "Error in RCServo_SetPulse()";
    unsigned int new_pulse = 0;
    unsigned int old_pulse = 0;
    
    while(1){
//    if(!RCServo_SetPulse(RC_SERVO_MIN_PULSE)){
//        Protocol_SendDebugMessage(error);
//    }
//    NOP_delay_100ms();
//    if(!RCServo_SetPulse(RC_SERVO_MAX_PULSE)){
//        Protocol_SendDebugMessage(&error);
//    }
//    NOP_delay_100ms();
    
    
    // -------------------------------------------------------------------------
    // Read in a packet from the interface and send it to the RC Servo
    // Packet comes in
    // extract the unsigned int. set 
    // defined in MEssage IDs.h
    // if no packet, should b invalid ID
        
        if(Protocol_ReadNextID() == ID_COMMAND_SERVO_PULSE){
            // save the lastpulse to compare the two. 
//            old_pulse = new_pulse;
            // Get the payload -- unsigned int
            Protocol_GetPayload(&new_pulse);
            // Swap endedness
            new_pulse = Protocol_IntEndednessConversion(new_pulse);
            
            // if the new pulse > max pulse for servo, clip it to max
            if(new_pulse > RC_SERVO_MAX_PULSE){
                new_pulse = RC_SERVO_MAX_PULSE;
            }
            // same for min
            else if(new_pulse < RC_SERVO_MIN_PULSE){
                new_pulse = RC_SERVO_MIN_PULSE;
            }
            
            // if new pulse is an update, send message telling us this
            if(new_pulse != old_pulse){
                // Send message 
                // YOOO this is where we left off
                
                
            
                // Set the new pulse as modular level variable to be changed by ISR
                if(RCServo_SetPulse(new_pulse) == ERROR){
                    Protocol_SendDebugMessage(&error);
                }
                
                // save the lastpulse to compare the two. 
                old_pulse = new_pulse;
                
                new_pulse = Protocol_IntEndednessConversion(new_pulse);
                Protocol_SendMessage(UINT_LEN,ID_SERVO_RESPONSE, &new_pulse);
                
                
            }
        
        
        }
    }
    
}

#endif

