/* 
 * File:   FreeRunningTimer.c
 * Author: Benjamin Vander Klay
 * Brief: 
 * Created on February 8, 2022, 3:08 pm
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "FreeRunningTimer.h" // The header file for this source file. 
#include <proc/p32mx340f512h.h> // ?
#include <xc.h>
#include <sys/attribs.h>
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include "Protocol.h"
#include "MessageIDs.h"



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define TICKS_PER_PERIOD 5000
#define UNINT_LENGTH 4

// for nop delays 
#define NOPS_FOR_5_MS 250 // 
#define NOPS_FOR_250_MS 12500
/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/
void NOP_delay_5ms ();
/*******************************************************************************
 * PRIVATE Modular Variables                                                           *
 ******************************************************************************/
unsigned int ms, us;

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/
/**
 * @Function FreeRunningTimer_Init(void)
 * @param none
 * @return None.
 * @brief  Initializes the timer module */
void FreeRunningTimer_Init(void){
    // set everything to 0
    // this also sets TCS(clock source) to 0, 
    // meaning the source is internal peripheral clocj
    T5CON = 0;
    // set Pre-scaler to 8
    T5CONbits.TCKPS = 0b011;
    //set the Period Register to 5000 ticks
    PR5 = TICKS_PER_PERIOD;
    
    // enable interrupts.
    IEC0bits.T5IE = 1;
    // set priority
    IPC5bits.T5IP = 3;
    IPC5bits.T5IS = 2;
    
    // can now turn timer ON
    T5CONbits.ON = 1;
    
    return;
}

/**
 * Function: FreeRunningTimer_GetMilliSeconds
 * @param None
 * @return the current MilliSecond Count
   */
unsigned int FreeRunningTimer_GetMilliSeconds(void){
    
    return ms;
}

/**
 * Function: FreeRunningTimer_GetMicroSeconds
 * @param None
 * @return the current MicroSecond Count
   */
unsigned int FreeRunningTimer_GetMicroSeconds(void){
    unsigned int current_timer = TMR5;
    return (us + (current_timer / TICKS_PER_PERIOD));
}

/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/
//uint8_t led;
void __ISR(_TIMER_5_VECTOR, ipl3auto) Timer5IntHandler(void) {
    //check that the correct interrupt flag has been raised
    if(IFS0bits.T5IF){
        IFS0bits.T5IF = 0;
        // TICKS_PER_PERIOD have passed, equal to one ms passing
        ms++;
        // one ms == 1000 us
        us += 1000;
        // toggle LED 1
//        led = LATE;
        
    }
}

/**
 * @Function someFunction(void)
 * @param foo, some value
 * @return TRUE or FALSE
 * @brief 
 * @note 
 * @author <Your Name>
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
//uint8_t someFunction(int foo);

#ifdef TEST_FRT
int main (){
    
    // Init board and protocol -------------------------------------------------
    BOARD_Init();
    Protocol_Init();

    // init LEDS
    TRISE = 0;
    LATE = 0;
    LATE = 0x02;     
    // init FRT
    FreeRunningTimer_Init();
    
    
    
    // Variable Definitions ----------------------------------------------------
    unsigned int micro_s, milli_s;
    
    // -------------------------------------------------------------------------
    //Send debug message about the date and time n stuff 
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    sprintf(intro_message, "FreeRunningTimer.c Test Harness compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);
    
    // -------------------------------------------------------------------------
//     Sending out the modular varibles compared to the values returned by functions
    unsigned char five_ms[MAXPAYLOADLENGTH + 1];
    // delay for 5 ms
    NOP_delay_5ms ();
    
    // hopefully this all happens within a millisecod. 
    milli_s = FreeRunningTimer_GetMilliSeconds();
    Protocol_SendMessage(UNINT_LENGTH, ID_DEBUG, &milli_s);
    Protocol_SendMessage(UNINT_LENGTH, ID_DEBUG, &ms);
    
    // same but for microsecond. Not guessing this will suceed in less than a us
    micro_s = FreeRunningTimer_GetMicroSeconds();
    Protocol_SendMessage(UNINT_LENGTH, ID_DEBUG, &micro_s);
    Protocol_SendMessage(UNINT_LENGTH, ID_DEBUG, &us);
    
    
//    Protocol_SendMessage(UNINT_LENGTH, ms, );
//    FreeRunningTimer_GetMilliSeconds();
    while(1){
        // print out every 2 seconds, 2000 ms
        if(ms % 2000 == 0) {
            Protocol_SendDebugMessage("Every two seconds"); // we'll see if this works or not lol
            
            // 0.5 Hz is a period of 2 seconds. 
            //toggle LED. lets do LED8
            if(LATE != 0x80){
                LATE = 0x80;
            }
            else{
                LATE == 0x00;
            }    
            
        }
        
            
            
    }
}

// borrowed from Lab0 :)
void NOP_delay_5ms () {
    int i;
    for (i = 0; i < NOPS_FOR_5_MS; i++) { 
            asm ("NOP");   
    }
}

#endif


