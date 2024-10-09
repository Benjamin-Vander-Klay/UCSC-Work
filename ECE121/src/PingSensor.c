/* 
 * File:   PingSensor.c
 * Author: Benjamin Vander Klay (bcvander)
 * Brief: 
 * Created on February 13, 2022, 5:47pm
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "PingSensor.h" // The header file for this source file. 
#include <proc/p32mx340f512h.h> // ?
#include <xc.h>
#include <sys/attribs.h>
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include "Protocol.h"
#include "MessageIDs.h"
#include "FreeRunningTimer.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
// 7 ticks is 11.2 us
#define PERIOD_10_US 8
// 37500 ticks is 60 ms 
#define PERIOD_60_MS 37500
// 60k ticks is 12ms when ps = 8
#define PERIOD_T2 60000
#define NOPS_FOR_100_MS 50000
#define SHORT_LEN 2


/*******************************************************************************
 * PRIVATE Module Level Variables                                                            *
 ******************************************************************************/
unsigned short up_time, down_time, save_time;
uint8_t rising_bool, wait_12ms;

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
 * @Function PingSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for PingSensor with the needed interrupts */
int PingSensor_Init(void){
    
    // Using pin5 as Trigger
    TRISFbits.TRISF1 = 0; // clear bit 1 of Reg D -> output
    LATFbits.LATF1 = 0; // set bit 1 as 0 -> initialize to 0. triggers starts low.
    
//    TRISE = 0;
//    LATE = 0;
//    LATEbits.LATE0 = 1;
//    LATESET = 1;  
    
    // Setup timer4 
    T4CON = 0;
    // prescalar = 1:64
    T4CONbits.TCKPS = 0b110;
    // period = 60 ms to start
    // 2^16 is 65k. this is 300k hm...
    PR4 = PERIOD_60_MS;
    // turn timer on
    T4CONbits.ON = 1;
    
    // Enable timer4 interrupts
    IEC0bits.T4IE = 1;
    IPC4bits.T4IP = 2;
    IPC4bits.T4IS = 2;
    
        
    // timer2 Init
    T2CON = 0;
    // PreScalar = 1:16
    T2CONbits.TCKPS = 0b011;
    // Period is 12ms > 11.68ms from lab manual
    // period is 12.8ms > 11.68
    // this is 60k ticks
    PR2 = PERIOD_T2;
    
    
    //IC3 Setup
    TRISDbits.TRISD10 = 1; // Set as input
    
    IC3CON = 0;
    // Send signal on every edge after starting edge - defined below
    IC3CONbits.ICM = 0b110;
    // capture rising edge first
    IC3CONbits.FEDGE = 1; 
    // Timer 2 is counter source
    IC3CONbits.ICTMR = 1; 
    
    // Enable IC3 Interrupts ** might want to double check interrupt priorities n shit
    IEC0bits.IC3IE = 1;
    IFS0bits.IC3IF = 0;
    IPC3bits.IC3IP = 2;
    IPC3bits.IC3IS = 3;
    
    // Turn it back on 
    // timer 2
    T2CONbits.ON = 1;
    // IC3
    IC3CONbits.ON = 1;
    
    // just make sure we don't start doing weird arthimatic at the beginning
    up_time = down_time = save_time = 0;
    rising_bool = TRUE;
    return SUCCESS;
}

/**
 * @Function int PingSensor_GetDistance(void)
 * @param None
 * @return Unsigned Short corresponding to distance in millimeters */
unsigned short PingSensor_GetDistance(void){
    
    if(wait_12ms){
//      // come back in 12ms bc we have to wait until the interrupt triggers on the falling edge 
//      // use T4?
        // send back the previously calculated distance
        return save_time;
    }
    else {
        // 10^-6(us in seconds) * 10^6(meters in mm)
//    Protocol_SendMessage(SHORT_LEN, ID_DEBUG, &up_time);
//    Protocol_SendMessage(SHORT_LEN, ID_DEBUG, &down_time);
        // only calculate the time when we know the up/down times have correct polarity
//        save_time = ((down_time - up_time) * 340 / 2);
        save_time = ((down_time - up_time) / 58);
        return save_time; // or something idk look at this
    }    
        
}

/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/

void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void){
    
    // Set INT flag low again.
    IFS0bits.T4IF = 0;
    
    // if trigger pin is high
    if(LATFbits.LATF1){
        // Set pin low again
        LATFINV = 2; // This might do nothing... lol 
        LATFbits.LATF1 = 0;
        
        // Set period back to 60ms
        PR4 = PERIOD_60_MS;
//        LATEINV = 2;
//        rising_bool = FALSE;
    }
    else{
        // Set trigger pin high
//        LATFINV = 2;
        LATFbits.LATF1 = 1;
        // Set period to 10us
        PR4 = PERIOD_10_US;
//        LATEINV = 1;
    }
        
    
    
    return;
}

void __ISR ( _INPUT_CAPTURE_3_VECTOR ) __IC3Interrupt ( void ) {
    
//    LATEbits.LATE3 = 1;
    // Set interrupt flag low again -- should be at the end of the ISR
    IFS0bits.IC3IF = 0;
    
    // only get the bottom 16 bits of the buffer -> weird hardware error where its 32 bits long or smtg
    //save_time = 0xffff & IC3BUF;
    
//    LATEbits.LATE3 = 1;
    if(rising_bool & PORTDbits.RD10){  // Should be && but I guess this works too. 
        // save time at rising edge
        while(IC3CONbits.ICBNE){
            up_time = (0xffff & IC3BUF);
//            LATEbits.LATE4 = 1;
        }    
        // don't compute distance between interrupts, the number will be incorrect
        wait_12ms = TRUE;
        rising_bool = FALSE;
    }
    else if((rising_bool == FALSE) && (PORTDbits.RD10 == 0)){
        // save time at falling edge
        while(IC3CONbits.ICBNE){
            down_time = (0xffff & IC3BUF);
//            LATEbits.LATE5 = 1;
        }    
        // can safely compute the distance
        wait_12ms = FALSE;
        rising_bool = TRUE;
    }
    else{
        // polarity is wrong, reset 
        up_time = down_time = 0;
        rising_bool = TRUE;
        wait_12ms = FALSE;
    }
    
    
}

// borrowed from Lab0 :)
void NOP_delay_100ms () {
    int i;
    for (i = 0; i < NOPS_FOR_100_MS; i++) { 
            asm ("NOP");   
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


#ifdef TEST_PING_SENSOR

int main(){
    unsigned short trash, distance;
    int i;
    
    // init some stuff 
    BOARD_Init();
    PingSensor_Init();
    Protocol_Init();
    
//    LATFbits.LATF1 = 1;
    // clear the IC3BUF as asked in Lab manual
    while(IC3CONbits.ICBNE){
            trash = 0xffff & IC3BUF;
        }
    
//    TRISFCLR = 2; // clear bit 1 of Reg D 
//    LATFSET = 2;
    
//    LATF &= 2;
    
    // -------------------------------------------------------------------------
    //Send debug message about the date and time n stuff 
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    sprintf(intro_message, "PingSensor.c Test Harness compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);
    // -------------------------------------------------------------------------
    
    
    
    while(1){
//        wait.. nops... and then poll 
        // once every 100 ms is every 10 Hz
        NOP_delay_100ms();
        // poll the Ping Sensor
        distance = PingSensor_GetDistance();
        // swap endedness of the distance * maybe need maybe no?*
        distance = Protocol_ShortEndednessConversion(distance);
        // throw it to the Interface
        Protocol_SendMessage(SHORT_LEN, ID_PING_DISTANCE, &distance);
        
        if(PORTDbits.RD10){
            LATEbits.LATE6 = 1;
        }
        else{
            LATEbits.LATE7 = 1;
        }
    }
}


#endif

