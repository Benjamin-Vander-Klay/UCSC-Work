/* 
 * File:   filename.h
 * Author: <Your Name>
 * Brief: 
 * Created on <month> <day>, <year>, <hour> <pm/am>
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */

#ifndef RINGBUFFER_H // Header guard
#define	RINGBUFFER_H //

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/


#include <stdlib.h>
#include "BOARD.h"
#include "Protocol.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
//(PACKETBUFFERSIZE*MAXPAYLOADLENGTH) + 1
#define BUFFER_LENGTH 641 
// note that this does include the ID
#define MAXPAYLOADLENGTH 128

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/
typedef struct {
    // buffer should be 5 * Max length
    unsigned char data[BUFFER_LENGTH]; // 641
    uint8_t head;
    uint8_t tail;
    
//    uint8_t length[(PACKETBUFFERSIZE*MAXPAYLOADLENGTH) + 1];
//    unsigned char payload[MAXPAYLOADLENGTH + 1];
//    uint8_t checksum;
    
}Circ_Buffer;    
    

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function Init_Buff(Circ_Buffer buff)
 * @param circular buffer
 * @return void
 * @brief initializes the circular buffer by setting the head and tail = 0
 * @note 
 * @author <Your Name>,
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
void Init_Buff(Circ_Buffer *Buff);

/**
 * @Function Buff_Add(Circ_Buffer, unsigned char)
 * @param circular Buffer, datum  
 * @return 1 (TRUE) if added successfully, 0 (FALSE) if unsuccessful
 * @brief Adds a datum (unsigned char to the circular buffer at the tail. 
 * @note **DEPENDENT ON Buff_Full()** -> returns ERROR (-1) if failed
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Add (Circ_Buffer *Buff, unsigned char datum);

/**
 * @Function Buff_Pull(Circ_Buffer)
 * @param Circ_Buffer
 * @return the datum at the head (unsigned char)
 * @brief 
 * @note MAXPAYLOADLENGTH defined in RingBuffer.h and is currently 128
 *          **DEPENDENT ON Buff_Empty()**  -> returns ERROR (-1) if failed
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Pull (Circ_Buffer *Buff);

/**
 * @Function Buff_Full(Circ_Buffer)
 * @param circular Buffer 
 * @return 1 (TRUE) if the buffer is Full and 0 (FALSE) if the buffer is not
 * @brief initializes circular buffer, sets head and tail = 0 
 * @note 
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Empty(Circ_Buffer *Buff);

/**
 * @Function Buff_empty(Circ_Buffer)
 * @param circular Buffer 
 * @return 1 (TRUE) if the buffer is full and 0 (FALSE) if the buffer is not
 * @brief takes into account the wrap around using the +1 % LENGTH
 * @note buffer is full when the tail is immediately behind the head
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Full(Circ_Buffer *Buff);

/**
 * @Function Buff_size(Circ_Buffer)
 * @param circular Buffer 
 * @return number of items in buffer
 * @brief 
 * @note buffer is full when the tail is immediately behind the head
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int Buff_Size(Circ_Buffer *Buff);

/**
 * @Function Buff_Length(Circ_buffer *Buff)
 * @param pointer to circular Buffer 
 * @return the length of the payload stored at head
 * @brief 
 * @note 
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Length(Circ_Buffer *Buff);



#endif	/* RINGBUFFER_H */ // End of header guard



