/* 
 * File:   NonVolatileMemory.c
 * Author: Benjamin Vander Klay
 * Brief: 
 * Created on March 3rd, 2022, 3:08 pm
 * Modified on March 9th, 2022, 4:56 pm
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "NonVolatileMemory.h" // The header file for this source file. 
// Headers for the rest of the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "BOARD.h"
#include "MessageIDs.h"
#include "Protocol.h"
// ones we maybe need
//#include "FreeRunningTimer.h"
//#include "RotaryEncoder.h"
//#include "PingSensor.h"
//#include "RCServo.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define NOPS_FOR_100_MS 50000
// R/~W
#define DEVICE_ADDY_WRITE 0b10100000
#define DEVICE_ADDY_READ  0b10100001
#define UPPER_8_MASK 0x0000ff00
#define LOWER_8_MASK 0x000000ff
#define BYTE_LEN 1



/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/
int8_t Send_Byte(uint8_t byte);
int8_t Send_START(void);
int8_t Send_STOP(void);
int8_t Send_RESTART(void);

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/
/**
 * @Function NonVolatileMemory_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes I2C for usage
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.09 4:29pm
 */
int NonVolatileMemory_Init(void){
    // Init the I2C on PIC32
    // turn I2C1 off
    I2C1CON = 0;
    // Set the BRG from table. 100kHz
    I2C1BRG = 0x0C2;
    // turn it back on I guess
    I2C1CONbits.ON = 1;
    
    
    
    return 0;
}

/**
 * @Function NonVolatileMemory_ReadByte(int address)
 * @param address, device address to read from
 * @return value at said address
 * @brief reads one byte from device
 * @warning Default value for this EEPROM is 0xFF
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:13pm
 */
unsigned char NonVolatileMemory_ReadByte(int address){
    uint8_t upper = (address & UPPER_8_MASK) >> 8;
    uint8_t lower = address & LOWER_8_MASK;
    
    // Make sure line is idle I2C1STATbits.TRSTAT -> currently transmitting
    // I2C1CONbits.SEN -> stop bit is over
    if(I2C1STATbits.TRSTAT){
        return ERROR;
//        LATESET = 1;
    } 
    
    // Send Start -- waits for it to end before returning. might be a timing issue?
    if(Send_START() == ERROR){
        return ERROR;
    }
    
    // send address, write register address
    if(Send_Byte(DEVICE_ADDY_WRITE) == ERROR){
        return ERROR;
    }
    
    // Send Top 8 bits of ADDRESS // Assume only using lower 2 bytes of int
    if(Send_Byte(upper) == ERROR){
        return ERROR;
    }
           
    // Send Btm 8 bits of ADDRESS // Assume only using lower 2 bytes of int
    if(Send_Byte(lower) == ERROR){
        return ERROR;
    }
    
    // Send Re-Start -- waits for it to end before returning. might be a timing issue?
    if(Send_RESTART() == ERROR){
        return ERROR;
    }
    // Send new device address but with read
    if(Send_Byte(DEVICE_ADDY_READ) == ERROR){
        return ERROR;
    }
    
    // could be its own lil function
    // Enable Master Reception
    I2C1CONbits.RCEN = 1;
    
    // Wait for reception to finish
    while(I2C1CONbits.RCEN);
    
    // Set NACK in data bit
    I2C1CONbits.ACKDT = 1;
    
    // Enable NACK to be sent
    I2C1CONbits.ACKEN = 1; 
    
    // Wait for NACK to finish *Blocking*
    while(I2C1CONbits.ACKEN);
    
    // Send stop
    if(Send_STOP() == ERROR){
        return ERROR;
    }
    // Save the received char // this way we always read it and dont get buffer overflow errors
    unsigned char data = I2C1RCV;
          
    return data;
}

/**
 * @Function char NonVolatileMemory_WriteByte(int address, unsigned char data)
 * @param address, device address to write to
 * @param data, value to write at said address
 * @return SUCCESS or ERROR
 * @brief writes one byte to device 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.10 3:16pm 
 */
char NonVolatileMemory_WriteByte(int address, unsigned char data){
    // temp variables
    uint8_t upper = (address & UPPER_8_MASK) >> 8;
    uint8_t lower = address & LOWER_8_MASK;
    
    // Make sure line is idle I2C1STATbits.TRSTAT -> currently transmitting
    // I2C1CONbits.SEN -> stop bit is over
    if(I2C1STATbits.TRSTAT){
        return ERROR;
//        LATESET = 1;
        
    } 
    
    // Send Start -- waits for it to end before returning. might be a timing issue?
    if(Send_START() == ERROR){
        return ERROR;
    }
    
    // send address
    if(Send_Byte(DEVICE_ADDY_WRITE) == ERROR){
        return ERROR;
    }
        
    // Send Top 8 bits of ADDRESS // Assume only using lower 2 bytes of int
    if(Send_Byte(upper) == ERROR){
        return ERROR;
    }
           
    // Send Btm 8 bits of ADDRESS // Assume only using lower 2 bytes of int
    if(Send_Byte(lower) == ERROR){
        return ERROR;
    }
        
    // Send actual Data (WRITE) -- R/~W
    if(Send_Byte(data) == ERROR){
        return ERROR;
    }
    
    // Check that no collisons happened
    // Send STOP -- waits for it to end before returning. might be a timing issue?
    if(Send_STOP() == ERROR){
        return ERROR;
    }
    
    
    
    return SUCCESS;
}




/**
 * @Function int NonVolatileMemory_ReadPage(int page, char length, unsigned char data[])
 * @param page, page value to read from
 * @param length, value between 1 and 64 bytes to read
 * @param data, array to store values into
 * @return SUCCESS or ERROR
 * @brief reads bytes in page mode, up to 64 at once
 * @warning Default value for this EEPROM is 0xFF
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:13pm
 */
int NonVolatileMemory_ReadPage(int page, char length, unsigned char data[]){
    
    return 0;
}

/**
 * @Function char int NonVolatileMemory_WritePage(int page, char length, unsigned char data[])
 * @param address, device address to write to
 * @param data, value to write at said address
 * @return SUCCESS or ERROR
 * @brief writes one byte to device 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:13pm
 */
int NonVolatileMemory_WritePage(int page, char length, unsigned char data[]){
    
    return 0;
}
/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/


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
 * @return SUCCESS or ERROR
 * @brief just sets the I2C1TRN register and returns T/F if the 
 * @note blocking code
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.10 3:16pm 
 */
int8_t Send_Byte(uint8_t byte){
    
    I2C1TRN = byte;
    // wait for this to finish
    while(I2C1STATbits.TRSTAT);
    // if NACK is sent -> return ERROR
    if(I2C1STATbits.ACKSTAT){
        LATE = 1;
        return ERROR;
        
    }
    // check for collisions
    if(I2C1STATbits.IWCOL){
        I2C1STATbits.IWCOL = 0;
//        LATESET = 2;
        return ERROR;
    }
    return SUCCESS;
}

/**
 * @Function Send_START(void)
 * @param 
 * @return SUCCESS or ERROR
 * @brief Sets the SEN bit and waits for it to clear. if a collision happened return error
 * @note blocking code
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.10 3:16pm 
 */
int8_t Send_START(){
    // Send Start
    I2C1CONbits.SEN = 1;
   // wait for it to finish START
    while(I2C1CONbits.SEN);
    // if collision occured, clear bit and return error
    if(I2C1STATbits.IWCOL){
        I2C1STATbits.IWCOL = 0;
//        LATESET = 1;
        return ERROR;
    }
    return SUCCESS;
}
/**
 * @Function Send_START(void)
 * @param 
 * @return SUCCESS or ERROR
 * @brief Sets the PEN bit and waits for it to clear. if a collision happened return error
 * @note blocking code
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.10 3:16pm 
 */
int8_t Send_STOP(){
    // Send Start
    I2C1CONbits.PEN = 1;
   // wait for it to finish START
    while(I2C1CONbits.PEN);
    // if collision occured, clear bit and return error 
    if(I2C1STATbits.IWCOL){
        I2C1STATbits.IWCOL = 0;
//        LATESET = 128;
        return ERROR;
    }
    return SUCCESS;
}

/**
 * @Function Send_START(void)
 * @param 
 * @return SUCCESS or ERROR
 * @brief Sets the PEN bit and waits for it to clear. if a collision happened return error
 * @note blocking code
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.10 3:16pm 
 */
int8_t Send_RESTART(){
    // Send Start
    I2C1CONbits.RSEN = 1;
   // wait for it to finish START
    while(I2C1CONbits.RSEN);
    // if collision occured, clear bit and return error 
    if(I2C1STATbits.IWCOL){
        I2C1STATbits.IWCOL = 0;
//        LATESET = 128;
        return ERROR;
    }
    return SUCCESS;
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

#ifdef TEST_NVM
int main() {
    
    // Initialize the basics
    BOARD_Init();
    Protocol_Init();
    NonVolatileMemory_Init();
    
    // -------------------------------------------------------------------------
    //Send debug message about the date and time n stuff 
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    sprintf(intro_message, "NonVolatileMemory.c Test Harness compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);   
    
    // -------------------------------------------------------------------------
    // Error messages for Protocol Debug
    static char *error_message_read_byte = "ERROR in NVM_ReadByte()";
    static char *error_message_write_byte = "ERROR in NVM_WriteByte()";
    static char *error_message_read_page = "ERROR in NVM_ReadPage()";
    static char *error_message_write_page = "ERROR in NVM_WritePage()";
    
    // -------------------------------------------------------------------------
    TRISE = 0;
    LATE = 0;
    unsigned char test_char;
    uint8_t transmit_data = 0;
    
    uint8_t data = 0;
    int8_t ack;
    int read_payload = 0;
    int address = 0;
    long write_byte_payload = 0;
    
    
    // never exit this mf
    while(1){
        
        //Sending Address to see on O-Scope 
//// ---------------------------------------------------------------------------

        // Send Start Sign 
//        I2C1CONbits.SEN = 1;
//        while(I2C1CONbits.SEN);
//        if(I2C1STATbits.IWCOL){
//            I2C1STATbits.IWCOL = 0;
//            LATE = 1;
//        }
//
//        
//        // Send Device Address
//        transmit_data = 0b10100000;
//        I2C1TRN = transmit_data;
//        
//        if(I2C1STATbits.IWCOL){
//            I2C1STATbits.IWCOL = 0;
//            LATE = 2;
//        }
//        while(I2C1STATbits.TRSTAT);
//        
//        
////        asm("NOP");
//        I2C1CONbits.PEN = 1;
////        I2C1TRN = 0x;
//        if(I2C1STATbits.IWCOL){
//            I2C1STATbits.IWCOL = 0;
//            LATE = 3;
//        }
//        while(I2C1CONbits.PEN);
//        NOP_delay_100ms();
        
//        if(NonVolatileMemory_WriteByte(0xffffffff, 'A') == ERROR)
//                LATESET = 4;
        
//        if((test_char = NonVolatileMemory_ReadByte(0xffffffff)) == ERROR)
//                LATESET = 8;
//        if(test_char == 'A'){
//            LATESET = 64;
//        }
//        
//        if(I2C1STATbits.IWCOL){
//            I2C1STATbits.IWCOL = 0;
//            LATE = 3;
//        }
//        Send_START();
//        Send_Byte(0b10100000);
//        I2C1TRN = 0b10100000;
//        while(I2C1STATbits.TRSTAT);
//        Send_STOP();
        
//// ---------------------------------------------------------------------------            
        // Sending and writing bytes Thru the protocol   
        if(Protocol_IsMessageAvailable()){
            // if the message ID is READ
            if(Protocol_ReadNextID() == ID_NVM_READ_BYTE){
                // Extract the Address we want to read from
                Protocol_GetPayload(&address);
                // Endedness Conversion before using NVM modules
                address = Protocol_IntEndednessConversion(address);
                // 1 byte long don't need endedness conversion
                data = NonVolatileMemory_ReadByte(address);
                if(data == ERROR){
                    Protocol_SendDebugMessage(error_message_read_byte);
                }
                // Possibly not an Else situation. Maybe want to know what it is anyways? NVM- its just ERROR ==  -1
                else{
                    Protocol_SendMessage(BYTE_LEN, ID_NVM_READ_BYTE_RESP, &data);
                    
                }
                 
            }
            else if(Protocol_ReadNextID() == ID_NVM_WRITE_BYTE){
                Protocol_GetPayload(&write_byte_payload);
                // This might be wrong. Double check. Need top 4 bytes
                address = write_byte_payload >> 8;
                // need bottom 1 byte
                data = write_byte_payload && 0xff;
                
                ack = NonVolatileMemory_WriteByte(address, data);
                if(ack == ERROR){
                    Protocol_SendDebugMessage(error_message_write_byte);
                }
                else{
                    Protocol_SendMessage(BYTE_LEN, ID_NVM_WRITE_BYTE_ACK, &ack);
                }
                
                
                
            }
            
        }
        
        
        
    }
}


#endif

