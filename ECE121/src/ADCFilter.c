/* 
 * File:   LibraryTemplate.c
 * Author: <Your Name>
 * Brief: 
 * Created on March 3rd, 2022, 3:15 pm
 * Modified on March 3rd, 2022, 3:20 pm
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "ADCFilter.h" // The header file for this source file. 
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
 * @Function ADCFilter_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes ADC system along with naive filters 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:18pm
 */
int ADCFilter_Init(void){
    
    return ERROR;
}

/**
 * @Function ADCFilter_RawReading(short pin)
 * @param pin, which channel to return
 * @return un-filtered AD Value
 * @brief returns current reading for desired channel 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:18pm
 */
short ADCFilter_RawReading(short pin){
    
    return 0;
}

/**
 * @Function ADCFilter_FilteredReading(short pin)
 * @param pin, which channel to return
 * @return Filtered AD Value
 * @brief returns filtered signal using weights loaded for that channel 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:18pm
 */
short ADCFilter_FilteredReading(short pin){
    
    return 0;
}

/**
 * @Function short ADCFilter_ApplyFilter(short filter[], short values[], short startIndex)
 * @param filter, pointer to filter weights
 * @param values, pointer to circular buffer of values
 * @param startIndex, location of first sample so filter can be applied correctly
 * @return Filtered and Scaled Value
 * @brief returns final signal given the input arguments
 * @warning returns a short but internally calculated value should be an int 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:18pm
 */
short ADCFilter_ApplyFilter(short filter[], short values[], short startIndex){
    
    return 0;
}

/**
 * @Function ADCFilter_SetWeights(short pin, short weights[])
 * @param pin, which channel to return
 * @param pin, array of shorts to load into the filter for the channel
 * @return SUCCESS or ERROR
 * @brief loads new filter weights for selected channel 
 * @author Benjamin Vander Klay
 * @modified Benjamin Vander Klay, 2022.03.03 3:18pm
 */
int ADCFilter_SetWeights(short pin, short weights[]){
    
    return 0;
}
/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/



/**
 * @Function someFunction(void)
 * @param foo, some value
 * @return TRUE or FALSE
 * @brief 
 * @note 
 * @author <Your Name>
 * @modified <Your Name>, <year>.<month>.<day> <hour> <pm/am> */
//uint8_t someFunction(int foo);

#ifdef TEST_ADC_FILTER


int main() {
    
    // Initialize the basics
    BOARD_Init();
    Protocol_Init();
    ADCFilter_Init();
    
    
    // never exit this mf
    while(1){
        
        
        
        
        
    }
}


#endif



