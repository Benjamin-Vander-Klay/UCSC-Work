/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

#ifndef EncoderService_H  // <- This should be changed to your own guard on both
#define EncoderService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "ES_Framework.h"
#include "BOARD.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define NO_TICK 0
#define RIGHT_TICK 1
#define LEFT_TICK  2
#define BOTH_TICK RIGHT_TICK | LEFT_TICK
// since event param is uint16_t, each motor gets half so that we can set both, simultaneously
// this means each gets 255. we just scale the number of ticks down by a factor of 4 in the motor lib
// and scale it back up to 4 in the service. 
// This gives a max resolution of 4. 1 rotation is ~508. 
// factor of 4 gives whole number for this value. Unfortunately it isn't perfect but its alright
// we're not doing surgery. 
// ** 
#define ENCODER_SCALER 4 
#define LEFT_MTR_TICKS  0xFF00
#define RIGHT_MTR_TICKS 0x00FF
/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

 
/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitEncoderService(uint8_t Priority);

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostEncoderService(ES_Event ThisEvent);

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunEncoderService(ES_Event ThisEvent);



#endif /* EncoderService_H */

