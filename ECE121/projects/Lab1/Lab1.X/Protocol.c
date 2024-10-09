/* 
 * File:   Protocol.c
 * Author: Benjamin Vander Klay bcvander
 * Brief: Contains library for the 
 * Created on January 21st, 2022, 8:46pm 
 * Modified on January 24th, 2022, 3:55pm
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "BOARD.h"
#include "Protocol.h" // The header file for this source file.
#include "RingBuffer.h"
#include "MessageIDs.h"
#include <xc.h>
#include <sys/attribs.h>
#include <string.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
*******************************************************************************/
#define END_D 0x0D
#define END_A 0x0A

//#define ADD_LENGTH TRUE
//#define ADD_DATA FALSE

typedef enum {
    WAIT_HEAD,
//    GET_LENGTH,
    STORE_LENGTH,
    GET_PAYLOAD,
    COMP_CHECKSUM,
    EXPORT_PACKET
               
}RX_STATE;

/*******************************************************************************
 * PRIVATE Structs                                                            *
 ******************************************************************************/


typedef struct {
    uint8_t length, ID, complete;
    unsigned char payload[MAXPAYLOADLENGTH + 1];
}Receive_Buffer;


/*******************************************************************************
 * PRIVATE Module Variables                                                            *
 ******************************************************************************/
Circ_Buffer TX_buffer;
Receive_Buffer RX_buffer;
RX_STATE state;


unsigned char state_length, state_checksum;
// going to end up overwriting this every time 
unsigned char state_payload [MAXPAYLOADLENGTH + 1];
uint8_t state_i = 0;
unsigned char led_status;

char error;




/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

//int8_t RX_Add (Receive_Buffer *Buff, unsigned char datum);
//int8_t RX_Pull (Receive_Buffer *Buff);

int8_t PingPong(unsigned int);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                               *
 ******************************************************************************/

/**
 * @Function Protocol_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief 
 * @author bcvander */
int Protocol_Init(void){
    // Clear control Register
    U1STA = 0;
    // Set Baud Rate Generator
    U1BRG = 21;
    // Baud rate generator should be 21 given that this is set to 0 ? right?
    U1MODEbits.BRGH = 0; // ** MIGHT NEED TO CHECK THIS **
    //set 8 data bits, no parity, 1 stop bit
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;
    // Enable UART 1
    U1MODEbits.ON = 1;
    // Enable transmission
    U1STAbits.UTXEN = 1;
    // Enable Reception
    U1STAbits.URXEN = 1;
    // Enable Tramsitting interrupts thru UART1
    IEC0bits.U1TXIE = 1;
    // Enable Receiving interrupts thru UART1
    IEC0bits.U1RXIE = 1;
    
    IPC6bits.U1IP = 3;
    
    U1STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;
    // set interrupt flag to low
        
    // set initial state
    state = WAIT_HEAD;

    // init buffers 
    Init_Buff(&TX_buffer);
//    Init_Buff(&RX_buffer);
    
    
    return SUCCESS;
}

/**
 * @Function int Protocol_SendMessage(unsigned char len, void *Payload)
 * @param len, length of full <b>Payload</b> variable
 * @param Payload, pointer to data, will be copied in during the function
 * @return SUCCESS or ERROR
 * @brief 
 * @author bcvander */
int Protocol_SendMessage(unsigned char len, unsigned char ID, void *Payload){
    unsigned char checksum;
    uint8_t i;
    unsigned char next_char;
    
    PutChar(HEAD);
    PutChar(len + 1); // definition does not include the ID
    checksum = 0;
    
    // Start checksum and payload transmission with messageID
    checksum = Protocol_CalcIterativeChecksum(ID, checksum);
    PutChar(ID);
    
    // do the rest of the checksum and the putchar
    for(i = 0; i < len; i++){
        next_char = ((unsigned char*)Payload)[i];
        checksum = Protocol_CalcIterativeChecksum(next_char, checksum);
        PutChar(next_char);
    }
    
    // add tail
    PutChar(TAIL);
    
    // add checksum
    PutChar(checksum);
    
    // add end (Both)
    PutChar(END_D);
    PutChar(END_A);
    
    return SUCCESS;
}


/**
 * @Function int Protocol_SendDebugMessage(char *Message)
 * @param Message, Proper C string to send out
 * @return SUCCESS or ERROR
 * @brief Takes in a proper C-formatted string and sends it out using ID_DEBUG
 * @warning this takes an array, do <b>NOT</b> call sprintf as an argument.
 * @author bcvander */
int Protocol_SendDebugMessage(char *Message){
    unsigned char loc_length = 0;
    while(Message[loc_length] != '\0'){
        loc_length++;
    }
    // if this returns SUCCESS(==1) then return success, ERROR == -1
    if(Protocol_SendMessage(loc_length, ID_DEBUG, Message)){
        return SUCCESS;
    }
    else 
        return ERROR;
    
}


/**
 * @Function unsigned char Protocol_ReadNextID(void)
 * @param None
 * @return Reads ID of next Packet
 * @brief Returns ID_INVALID if no packets are available
 * @author bcvander */
unsigned char Protocol_ReadNextID(void){
    // assumes we dont include ID in Get_Payload
    // RX buff is empty, no packets availible
    // assuming nothing in RX_buffer.payload besides payloads
    // which there shouldnt be...
    if(RX_buffer.complete == FALSE)
        return ID_INVALID;       
    else 
        return RX_buffer.ID;
    
}

/**
 * @Function int Protocol_GetPayload(void* payload)
 * @param payload, Memory location to put payload
 * @return SUCCESS or ERROR
 * @brief sets = NUL after you get it. Can only read once
 * @author bcvander */
int Protocol_GetPayload(void* payload){
    // assuming we extract payload from RX_buffer and put it at this location
    // Extract from RX buffer
    uint8_t i;
    // ensure we dont read none existent message
    if(RX_buffer.complete == FALSE)
        return ERROR;
    
   
    unsigned char length = RX_buffer.length;

    unsigned char payload_char;
    for(i = 0; i < length; i++){
        
        // 
        payload_char = RX_buffer.payload[i];
        ((unsigned char*)payload)[i] = payload_char;
               
        
        
        if(((unsigned char*)payload)[i] != RX_buffer.payload[i])
            return ERROR;
        
        // perhaps set = \0 after we read it?
        RX_buffer.payload[i] = '\0';
        
    }
    
    // reset buffer fields so we don't read out of date data
    RX_buffer.length = '\0';
    RX_buffer.ID = '\0';
    RX_buffer.complete = FALSE;
    return SUCCESS;
}

/**
 * @Function char Protocol_IsMessageAvailable(void)
 * @param None
 * @return TRUE if Queue is not Empty
 * @brief 
 * @author bcvander */
char Protocol_IsMessageAvailable(void){
//    if(Buff_Empty)
    return RX_buffer.complete;
}

/**
 * @Function char Protocol_IsQueueFull(void)
 * @param None
 * @return TRUE is QUEUE is Full
 * @brief 
 * @author bcvander */
char Protocol_IsQueueFull(void){
    return Buff_Full(&TX_buffer);
}
    

/**
 * @Function char Protocol_IsError(void)
 * @param None
 * @return TRUE if error
 * @brief Returns if error has occurred in processing, clears on read
 * @author bcvander */
char Protocol_IsError(void){
    char loc_error;
    loc_error = error;
    error = FALSE;
    return loc_error;
}

/**
 * @Function char Protocol_ShortEndednessConversion(unsigned short inVariable)
 * @param inVariable, short to convert endedness
 * @return converted short
 * @brief Converts endedness of a short. This is a bi-directional operation so only one function is needed
 * @author bcvander */
unsigned short Protocol_ShortEndednessConversion(unsigned short inVariable){
    
    return (inVariable << 8) + (inVariable >> 8);
}

/**
 * @Function char Protocol_IntEndednessConversion(unsigned int inVariable)
 * @param inVariable, int to convert endedness
 * @return converted short
 * @brief Converts endedness of a int. This is a bi-directional operation so only one function is needed
 * @author bcvander */
unsigned int Protocol_IntEndednessConversion(unsigned int inVariable){
    // could j use short endedness conv twice and swap em
    // might b harder to split into shorts than j iterate it...
    unsigned int inv_0, inv_1, inv_2, inv_3;
    inv_0 = ((inVariable << 8) & 0x00ff0000);
    inv_1 = ((inVariable >> 8) & 0x0000ff00);
    inv_2 = (inVariable << 24);
    inv_3 = (inVariable >> 24);
    
    return inv_0 + inv_1 + inv_2 + inv_3;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS
 * generally these functions would not be exposed but due to the learning nature of the class they
 * are to give you a theory of how to organize the code internal to the module
 ******************************************************************************/

/**
 * @Function char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum)
 * @param charIn, new char to add to the checksum
 * @param curChecksum, current checksum, most likely the last return of this function, can use 0 to reset
 * @return the new checksum value
 * @brief Returns the BSD checksum of the char stream given the curChecksum and the new char
 * @author bcvander */
unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum){
    curChecksum = (curChecksum >> 1) + (curChecksum << 7); // circular rotation to the right by 1
    curChecksum += charIn;
    return curChecksum;
}

/**
 * @Function void Protocol_runReceiveStateMachine(unsigned char charIn)
 * @param charIn, next character to process
 * @return None
 * @brief Runs the protocol state machine for receiving characters, it should be called from 
 * within the interrupt and process the current character
 * @author bcvander */
void Protocol_RunReceiveStateMachine(unsigned char charIn){
    
    // variables are module wide so they can be edited between FN calls
    // for transfering payload to RX_buffer
    uint8_t i;
    switch(state) {
        
    case(WAIT_HEAD):
        // reset the counters and variables
        state_length = 0;
        state_checksum = 0;
        state_i = 0;
        
        if(charIn == HEAD)
            state = STORE_LENGTH;
        
        break;
        
    case(STORE_LENGTH):
        //make sure we don't read packet before we've stored it all
        RX_buffer.complete = FALSE;
        
        // store length
        state_length = charIn;
        state = GET_PAYLOAD;
        break;
               
    case(GET_PAYLOAD):
        // we go through this length number of times
        // assuming ID included in the length
        if(state_i < state_length){
            
            // calculate checksum. first char is the ID,
            state_checksum = Protocol_CalcIterativeChecksum(charIn, state_checksum);
            state_payload[state_i] = charIn;
            state_i++;
        }
        //
        else if(charIn != TAIL){
            // return to beginning
            state = WAIT_HEAD;
            error = TRUE;
        }
        else{
            // go to checksum after getting the tail
            state = COMP_CHECKSUM;
        }
        
        break;
        
    case(COMP_CHECKSUM):
        // checksum should be next char after tail
        // if the checksum matches the next
        if(state_checksum != charIn){
            error = TRUE;
            state = WAIT_HEAD;
        }
        else {
            state = EXPORT_PACKET;
        }
        
        break;
        
    case(EXPORT_PACKET):
        
        // LED_SET case
        if(state_payload[0] == ID_LEDS_SET){
            LATE = state_payload[1];
            
        }
        else if(state_payload[0] == ID_LEDS_GET){
            led_status = LATE;
            Protocol_SendMessage(1, ID_LEDS_STATE, &led_status);
        }
        else {
            // add to RX_buffer. Single packet long
            // don't include ID
            RX_buffer.length = state_length - 1;
            
            // 
            RX_buffer.ID = state_payload[0];
            for(i = 0; i < state_length; i++){
                // shifts it so that 1st byte in RX is not ID
                RX_buffer.payload[i] =  state_payload[i+1];
                
            }
        
            
            RX_buffer.complete = TRUE;
        }
        state = WAIT_HEAD;
           
    }       
    return;
}

/**
 * @Function char PutChar(char ch)
 * @param ch, new char to add to the circular buffer
 * @return SUCCESS or ERROR
 * @brief adds to circular buffer if space exists, if not returns ERROR
 * @author bcvander */
int PutChar(char ch){
    
    if(Buff_Full(&TX_buffer) == TRUE){
        error = TRUE;
        return ERROR;
    }    
    else {
//         add the desired character to the input buffer
        // don't add to length array
        // add to the Data array
        Buff_Add(&TX_buffer, ch);   
         
        // if UART is idle, give it a kickstart        
        if(U1STAbits.TRMT == 1) {
            IFS0bits.U1TXIF = 1;
        }        
        return SUCCESS;
    
    }
}

/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/


uint8_t string_index;
unsigned char test_str[50];
unsigned char incoming_char;

void __ISR(_UART1_VECTOR) IntUart1Handler(void) {

    unsigned char next_char;
    
    // first check that the receive flag is raise
    if(IFS0bits.U1RXIF){
        //if the receive interrupt flag has been raised
        //copy the char into a variable and lower the flag, 
        
        while(U1STAbits.URXDA){
            incoming_char = U1RXREG;
            Protocol_RunReceiveStateMachine(incoming_char);
//            if(incoming_char == END_D)
//                break;
//            PutChar('G');
        }
//        else 
        IFS0bits.U1RXIF = 0;
        
    }
    // then check that the transmitting flag is raised
    else if(IFS0bits.U1TXIF){
        
        // get the next character and ensure that we didnt pull from empty buffer
        while((U1STAbits.UTXBF != 1) && (Buff_Empty(&TX_buffer) == FALSE)) {
            
            next_char = Buff_Pull(&TX_buffer);
            // set the next byte and increment the index
//            while(U1STAbits.UTXBF == 1);
            U1TXREG = next_char;
            
        }
        IFS0bits.U1TXIF = 0;
    }
    
    
    return;
}

//int8_t PingPong(unsigned int ping) {
//    // convert to little endian
//    // shift right by one
//    // convert back to big endian
//    // send it back thru protocol
//    
////    unsigned int temp = Protocol_IntEndednessConversion(ping);
//    ping = ping >> 1;
//    unsigned int pong = Protocol_IntEndednessConversion(ping);
//    
//    // needs to be a string! int is size of 32 which is 4 chars
////    unsigned char pong_message[MAXPAYLOADLENGTH + 1];
////    sprintf(pong_message, "%u", pong);
//    
//    // len (not including ID), ID, payload
//    Protocol_SendMessage(4, ID_PONG, &ping);
//    return SUCCESS;
//}


#ifdef TEST_PROTOCOL


int main () {
    
    // Initialize the LEDS
    TRISE = 0x00;
    LATE = 0x00;
    
    // can set LATE to be a bit pattern and ask the interface ID_LED_GET to verify functionality. 
    
    // will be in any main that uses protocol.h
    BOARD_Init();
    Protocol_Init();
    
    // -------------------------------------------------------------------------
    // Test message send and receive
    unsigned char len = 3;
    unsigned char intro_message[MAXPAYLOADLENGTH + 1];
    
//    unsigned char * date = __DATE__;
 
    sprintf(intro_message, "Protocol.c Test Harness compiled on %s, at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(intro_message);
    
//    const unsigned char * message = "Benjamin Vander Klay \0";
//    const unsigned char * message_1 = "My middle name is carter\0";
//    
//    Protocol_SendDebugMessage(message);
//    Protocol_SendDebugMessage(message_1);
    
    unsigned char message_2[MAXPAYLOADLENGTH + 1];
    sprintf(message_2, "Clear for Take off");
    Protocol_SendDebugMessage(message_2);
    
    
    const unsigned char * response = "G\0";
//    unsigned char received[MAXPAYLOADLENGTH + 1];
    const unsigned char * error_ID = "error in getID :(\0";
    const unsigned char * no_ID_error = "NO error in getID :)\0";
    const unsigned char * error_pay = "error in getPay :(\0";
    const unsigned char * no_pay_error = "NO error in getPay :)\0";
    
    // -------------------------------------------------------------------------
    // test endian conversion SHORT
    
//    unsigned short short_test_0, short_test_1;
//    unsigned short short_0_big = 0x1234;
//    unsigned short short_0_lit = 0x3412;
//    
//    short_test_0 = Protocol_ShortEndednessConversion(short_0_big);
//    short_test_1 = Protocol_ShortEndednessConversion(short_0_lit);
//    
//    unsigned char message_baseline_0[MAXPAYLOADLENGTH + 1];
//    unsigned char message_baseline_1[MAXPAYLOADLENGTH + 1];
//    unsigned char message_endy[MAXPAYLOADLENGTH + 1];
//    unsigned char message_endy_1[MAXPAYLOADLENGTH + 1];
//    
//    while(Protocol_IsQueueFull());
//    sprintf(message_baseline_0, "short_0 before: %u\0", short_0_big);
//    sprintf(message_endy, "big -> little conversion: %u\0", short_test_0);
//    sprintf(message_baseline_1, "short_1 before: %u\0", short_0_lit);
//    sprintf(message_endy_1, "little -> big conversion: %u\0", short_test_1);
//    
//    Protocol_SendDebugMessage(message_baseline_0);
//    Protocol_SendDebugMessage(message_endy);
//    Protocol_SendDebugMessage(message_baseline_1);
//    Protocol_SendDebugMessage(message_endy_1);
//    
    // -------------------------------------------------------------------------
    // test endian conversion INT 
    
//    unsigned int int_test_0;
//    unsigned int int_test_1;
//    unsigned int int_0_big = 0xefbeadde;
//    unsigned int int_1_lit = 0xdeadbeef;
//    
//    int_test_0 = Protocol_IntEndednessConversion(int_0_big);
//    int_test_1 = Protocol_IntEndednessConversion(int_1_lit);
//    
//    unsigned char message_endy_int[MAXPAYLOADLENGTH + 1];
//    unsigned char message_endy_1_int[MAXPAYLOADLENGTH + 1];
//    
//    sprintf(message_baseline_0, "int_0 before: %u\0", int_0_big);
//    sprintf(message_endy_int, "INT! big -> little conversion: %u\0", int_test_0);
//    sprintf(message_baseline_1, "int_1 before: %u\0", int_1_lit);
//    sprintf(message_endy_1_int, "INT! little -> big conversion: %u\0", int_test_1);
//    
//    Protocol_SendDebugMessage(message_baseline_0);
//    Protocol_SendDebugMessage(message_endy_int);
//    Protocol_SendDebugMessage(message_baseline_1);
//    Protocol_SendDebugMessage(message_endy_1_int);
//   
    // -------------------------------------------------------------------------
    // Test PING / PONG
    
    unsigned int ping_0 = 2880416474;
    unsigned int ping_1 = 1688069936;
    unsigned int ping_2 = 1910713426;
    
    unsigned int pong_0 = 144020837;
    unsigned int pong_1 = 844034968;
    unsigned int pong_2 = 955356713;
    
//    PingPong(ping_0);
//    PingPong(ping_1);
//    PingPong()
    
    
    // -------------------------------------------------------------------------
    // never exit
    while(1){
        // continuously poll the UART1 for a received character        
        
        if(Protocol_IsMessageAvailable()){
            // generate packet and send it back
//            sprintf(respond, "%c", )
//            Protocol_SendMessage(RX_buffer.length, RX_buffer.payload[0], message);
//            unsigned char * message = "BEn VK!?";
//            Protocol_SendMessage(len, ID_DEBUG, response);
//            if(!count){
//                Protocol_SendDebugMessage(response);
 
////            }
            unsigned char id = Protocol_ReadNextID();
            if(id == ID_INVALID){
                Protocol_SendDebugMessage(error_ID);
            }
//            else if(id == ID_PING){
////                PingPong(RX_buffer.payload);
////            }
//            else
//                Protocol_SendDebugMessage(no_ID_error);
//               
//            if(Protocol_GetPayload(received) != SUCCESS){
//                Protocol_SendDebugMessage(error_pay);
//            }
//            else{
//                Protocol_SendDebugMessage(no_pay_error);
//            }
             
            if(id == ID_PING){
//                PingPong(*received);
                unsigned int pong;
                Protocol_GetPayload(&pong);
                pong = Protocol_IntEndednessConversion(pong);
                pong = pong >> 1;
                pong = Protocol_IntEndednessConversion(pong);
                Protocol_SendMessage(4, ID_PONG, &pong);
                
            }

        }     
        
    }
    
}

#endif
