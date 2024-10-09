/* 
 * File:   RotaryEncoder.c
 * Author: Benjamin Vander Klay (bcvander)
 * Brief: 
 * Created on February 13, 2022, 5:20pm
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "RotaryEncoder.h" // The header file for this source file. 
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
//#define LATD CHIP_SELECT
#define NUM_NOPS 5
#define READ_ANGLE 0xffff
#define AMS_NOP 0xC000
#define MES_ANGLE_LENGTH 2

/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/
/**
 * @Function CalcParity(int)
 * @param parity_input
 * @return either 0 or 1 depending on parity
 * @brief calculates whether input number is odd or even number of 1's
 * @note 
 * @author Benjamin Vander Klay
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
uint16_t CalcParity(uint16_t parity_input);


/**
 * @Function Five_NOPS(void)
 * @param void
 * @return 
 * @brief runs 5 nops
 * @note dep on #define NUM_NOPS
 * @author Benjamin Vander Klay
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
void Five_NOPS(void);

//uint16_t GetAngle
/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/
/**
 * @Function RotaryEncoder_Init(char interfaceMode)
 * @param interfaceMode, one of the two #defines determining the interface
 * @return SUCCESS or ERROR
 * @brief initializes hardware in appropriate mode along with the needed interrupts */
int RotaryEncoder_Init(char interfaceMode){
    //dummy variable to empty receive buffer
    uint16_t trash;
    
    if(interfaceMode == ENCODER_BLOCKING_MODE){
        // disable interrupts from SPI
        IEC1bits.SPI2EIE = 0;
        IEC1bits.SPI2RXIE = 0;
        IEC1bits.SPI2TXIE = 0;
    
        // clear ON bit to stop & reset SPI module
        // clear control register to reset everything. now unintended stuff
        SPI2CON = 0;
    
        // clear receive buffer
        trash = SPI2BUF;
    
        // set standard SPI mode nvm doesn't exist
//    SPI2CONbits.
            
        //set BRG 
        SPI2BRG = 3;
    
        //clear receive overflow flag
        SPI2STATbits.SPIROV = 0;
    
        // configure register bits
        // PIC32 is master
        SPI2CONbits.MSTEN = 1;
        // IDLE state is low
        SPI2CONbits.CKP = 0; // should already be low. 
        // serial output changes on transition from active to idle.
        SPI2CONbits.CKE = 0;
    
        // 16 bit mode
        SPI2CONbits.MODE16 = 1;
        // set pin 9 as ss pin 9 output 
        // could also try and maintain whatever TRISD was before using some logic if it is a problem
        // set bit 3 == 0 clear it to output
        TRISDCLR = 8;
        // perhaps double check this bvk 0x0008 is the 3210(bits) => 1000 = 8
        // should set slave select high. 
        LATD |= 8; 
    
        // turn spi back on
        SPI2CONbits.ON = 1;
    
    
    }
    
    return 0;
}

/**
 * @Function int RotaryEncoder_ReadRawAngle(void)
 * @param None
 * @return 14-bit number representing the raw encoder angle (0-16384) */
unsigned short RotaryEncoder_ReadRawAngle(void){
    unsigned short trash;
    
    // Set CSn low - notify that we're sending a signal
    LATDINV = 0x0008; 
    // maybe some no ops
    Five_NOPS();
    // send spi message (1 1 3fff) 3fff => 0011 1111 1111 1111 // and we read = 1 
    //                                     0111 1111 1111 1111 // need parity bit == 1
    SPI2BUF = READ_ANGLE;
    // maybe some more no ops so encoder can catch up? 
    Five_NOPS();
    // Set CSn high again so we can get the response in the second transfer
    LATDINV = 0x0008;
    // discard stuff in buffer
    trash = SPI2BUF;
    // think we need at least 18 nops (350ns before set it back)
    Five_NOPS();
    Five_NOPS();
    Five_NOPS();
    Five_NOPS();
    
    //set CSn low to receive info. send NOPS
    LATDINV = 0x0008;
    // f it, nops
    Five_NOPS();
    
    SPI2BUF = AMS_NOP;
    
    Five_NOPS();
    // high again
    LATDINV = 0x0008;
    
    // SPI buffer now holds the desired angle
    return SPI2BUF & 0x3FFF;
    
    // need 
    
//    return 0;
}


/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/

/**
 * @Function CalcParity(int)
 * @param parity_input
 * @return either 0 or 1 depending on parity
 * @brief calculates whether input number is odd or even number of 1's
 * @note 
 * @author Benjamin Vander Klay
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
uint16_t CalcParity(uint16_t parity_input){
    uint16_t p = 0;
    int i;
    
    // for each bit in input, if it is a 1, add to parity
    // and eventually should have an even number of ones
    
    for(i = 1; i < 0x8000;){
        if(parity_input & i){
            p++;
        }
        // shift left by one so we 
        i = i << 1;
        
    }
    p = p%2;
    
    return p;
}

/**
 * @Function Five_NOPS(void)
 * @param void
 * @return 
 * @brief runs 5 nops
 * @note dep on #define NUM_NOPS
 * @author Benjamin Vander Klay
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
void Five_NOPS(void){
    uint8_t i;
    for(i = 0; i < NUM_NOPS; i++){
        asm("NOP");
    }
    return;
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


#ifdef TEST_RE

int main(){
    uint16_t test_parity;
    uint16_t test_16;
    unsigned short raw_angle;
    
    
    
    char mode = 'a';
    
    // init the stuff
    BOARD_Init();
    RotaryEncoder_Init(ENCODER_BLOCKING_MODE);
    Protocol_Init();
    FreeRunningTimer_Init();
    
    // -------------------------------------------------------------------------
    //Send debug message about the date and time n stuff 
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    sprintf(intro_message, "RotaryEncoder.c Test Harness compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);
    // -------------------------------------------------------------------------
    
//    // test a couple values for the parity
//    test_parity = CalcParity(0x0000);
//    // should return 1
//    test_parity = CalcParity(0x0001);
//    // should return 0
//    test_parity = CalcParity(0x000f);
//    test_parity = CalcParity(0x001f);
//    test_parity = CalcParity(0x0002);
    
    raw_angle = RotaryEncoder_ReadRawAngle();
    
    Protocol_SendMessage(MES_ANGLE_LENGTH, ID_ROTARY_ANGLE, &raw_angle);
    
    unsigned int target = FreeRunningTimer_GetMilliSeconds() + 500;
    while(1){
//        banana
//        // SPI testing w O scope!! :) ----------------------------------------
//        test_16 = 0x01AA;
//        // get parity bit
//        test_parity = CalcParity(test_16);
//        //insert parity bit
//        test_16 = test_16|(test_parity<<15);
//    
//        // set slave select low / chip select
//        LATDINV = 0x0008;
//        
//        SPI2BUF = test_16;
//        // keep MISO high! // this kinda works
////        LATGSET = 0x0080;
//        
//    
////        while(SPI2BUF != 0);
//        while(SPI2STATbits.SPIBUSY);
//        
//        // set chip select high again // should turn off the 
//        LATDINV = 0x0008;
        
        // Lets f Go. Rot Enc Testing ------------------------------------------
        
        // some rate of some hertz :)
        if(target <= FreeRunningTimer_GetMilliSeconds()) {
            
            raw_angle = RotaryEncoder_ReadRawAngle();
            
//            raw_angle = 0xA2FE;
            
            // fuckin uh gotta do an endianness swap on this mf
            raw_angle = Protocol_ShortEndednessConversion(raw_angle);
            // send this shit out
            Protocol_SendMessage(MES_ANGLE_LENGTH, ID_ROTARY_ANGLE, &raw_angle);
            
            // add 50 ms to the target 
            target = FreeRunningTimer_GetMilliSeconds() + 500;
                    
        }
    }
}



#endif
