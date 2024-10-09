/* 
 * File:   RingBuffer.c
 * Author: Benjamin Vander Klay (bcvander)
 * Brief: 
 * Created on <month> <day>, <year>, <hour> <pm/am>
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "RingBuffer.h" // The header file for this source file.
#include <stdlib.h>
#include <stdio.h>
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/


/**
 * @Function Init_Buff(*Circ_Buffer)
 * @param circular Buffer 
 * @return void
 * @brief initializes circular buffer, sets head and tail = 0 
 * @note need to passs in the address of the circular buffer
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
void Init_Buff (Circ_Buffer *Buff){
    Buff->head = 0;
    Buff->tail = 0;
    
    // for RX_buffer
//    Buff->length = 0;
//    Buff->checksum = 0;
    return;
}

/**
 * @Function Buff_Add(Circ_Buffer, unsigned char)
 * @param circular Buffer, datum  
 * @return 1 (TRUE) if added successfully, 0 (FALSE) if unsuccessful
 * @brief Adds a datum (unsigned char to the circular buffer at the tail. 
 * @note **DEPENDENT ON Buff_Full()** -> returns ERROR (-1) if failed
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Add (Circ_Buffer *Buff, unsigned char datum){
    // if full is FALSE -> we can add another
    if(Buff_Full(Buff) == FALSE) {
        // if we are adding this to the length array datum is the length 
//        if(len_bool)
//            Buff->length[Buff->tail] = datum;
//            
//        else {
            Buff->data[Buff->tail] = datum;
            Buff->tail = (Buff->tail + 1) % BUFFER_LENGTH; // currently 128  
//        }
        return SUCCESS;
    }
    else 
        return ERROR; 
   
}

/**
 * @Function Buff_Pull(Circ_Buffer)
 * @param Circ_Buffer
 * @return the datum at the head (unsigned char)
 * @brief 
 * @note MAXPAYLOADLENGTH defined in RingBuffer.h and is currently 128
 *          **DEPENDENT ON Buff_Empty()** -> returns ERROR (-1) if failed
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Pull (Circ_Buffer *Buff){
//    if(Buff_Empty(Buff) == FALSE) {
    if(Buff->head == Buff->tail){
        return ERROR;
    }
    else {
        unsigned char datum = Buff->data[Buff->head];
        Buff->data[Buff->head] = '\0';
        Buff->head = (Buff->head + 1) % BUFFER_LENGTH;
        return datum;
    }    
}

/**
 * @Function Buff_Full(Circ_Buffer)
 * @param circular Buffer 
 * @return 1 (TRUE) if the buffer is Full and 0 (FALSE) if the buffer is not
 * @brief initializes circular buffer, sets head and tail = 0 
 * @note 
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Empty(Circ_Buffer *Buff){
    return Buff->head == Buff->tail;
}

/**
 * @Function Buff_empty(Circ_Buffer)
 * @param circular Buffer 
 * @return 1 (TRUE) if the buffer is full and 0 (FALSE) if the buffer is not
 * @brief takes into account the wrap around using the +1 % LENGTH
 * @note buffer is full when the tail is immediately behind the head
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int8_t Buff_Full(Circ_Buffer *Buff){
    return ((Buff->tail + 1) % BUFFER_LENGTH) == Buff->head;
}

/**
 * @Function Buff_size(Circ_Buffer)
 * @param circular Buffer 
 * @return number of items in buffer
 * @brief 
 * @note buffer is full when the tail is immediately behind the head
 * @author bcvander
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
int Buff_Size(Circ_Buffer *Buff){
    int size;
    size = Buff->tail - Buff->head;
    if(size < 0){
        return BUFFER_LENGTH + size;
    }
    else
        return size;
}


//int8_t Buff_Length(Circ_Buffer *Buff){
//    return Buff->length[Buff->head];
//    
//}


/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/
//uint8_t Is_Init()

#ifdef BUFFTEST
/*******************************************************************************
 * Test bench for RingBufferc                                          *
 ******************************************************************************/

int main (){
    // Testing variables Could use UART simulator
    // if any of these == 1, there is an error
    uint8_t init_er, add_er, pull_er, empty_er, full_er, size_er;
    init_er = add_er = pull_er = empty_er = full_er = size_er = 0;
    unsigned char test_char[MAXPAYLOADLENGTH];
    int i;
    
    // Instantiation and Initialization
    Circ_Buffer first_buff;
    Init_Buff(&first_buff);
    
    // check everything is correct
    // should == 0
    size_er = init_er = Buff_Size(&first_buff);  
    if(Buff_Empty(&first_buff)){
        empty_er = init_er = 0;
        
    }
    else
        empty_er = init_er = 1;
    full_er = init_er = Buff_Full(&first_buff);
    
    // try to pull a value when none are present:
    if(Buff_Pull(&first_buff) == 0){
        pull_er = 1;
    }
    // add some values
    
    Buff_Add(&first_buff, 'A');
    
    test_char[0] = Buff_Pull(&first_buff);
    
    for(i = 0; i<MAXPAYLOADLENGTH; i++ ){
        Buff_Add(&first_buff, 'A');
    }
    
    full_er = Buff_Full(&first_buff);
    if(Buff_Size(&first_buff) != MAXPAYLOADLENGTH) 
        size_er = 1;
//    printf('%c', test_char[0]);
}

#endif


/**
 * @Function someFunction(void)
 * @param foo, some value
 * @return TRUE or FALSE
 * @brief 
 * @note 
 * @author <Your Name>
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
//uint8_t someFunction(int foo);



