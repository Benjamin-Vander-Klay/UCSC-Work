
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

#ifndef SimpleFunctionService_H  // <- This should be changed to your own guard on both
#define SimpleFunctionService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/
#include "TopHSM.h"
#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "Sense_EventChecker.h"
#include "ActiveSearchSubHSM.h"
#include "All_Events.h"
#include "Bumpers_Gen_v1SubHSM.h"
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
// Timers Duration List 
#define TEMP_DRIVE_DURATION 1000 // might as well use it. 
#define TEMP_DRIVE_DURATION_2 200
#define ACTIVE_DURATION 3500 //10000 // Not sure but we are using in place of FT_IDLE_DURATION to time how long we search
#define DEBOUNCE_DURATION 15 // period of sampling the bumpers (I think-BVK)
#define MIDROTATE_DURATION 850 // duration we adjust after driving straight in FindTape Idle // bvk changed from 750 to 850 to try and get out of scenarios more quickly 
#define LINE_CORRECT_LEFT_DURATION 250 // duration we tank turn left to get back on tape
#define LINE_CORRECT_RIGHT_DURATION 550
#define REVERSE_DURATION 500 
#define APPROACH_ADJUST_RIGHT 1350
#define APPROACH_ADJUST_LEFT 500 
#define BREAKOUT_DURATION 4500

#define MINOR_ALIGN_ADJUST 200 // 5-31-22 1:04 PM Timer To add a minor adjustment to realigh with the tower
//#define FT_IDLE_DURATION 3500 // duration we drive straight in FindTape Idle before adjusting
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
uint8_t InitSimpleFunctionService(uint8_t Priority);

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostSimpleFunctionService(ES_Event ThisEvent);

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunSimpleFunctionService(ES_Event ThisEvent);



#endif /* SimpleFunctionService_H */

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

#ifndef SimpleFunctionService_H  // <- This should be changed to your own guard on both
#define SimpleFunctionService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/
#include "TopHSM.h"
#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "Sense_EventChecker.h"
#include "ActiveSearchSubHSM.h"
#include "All_Events.h"
#include "Bumpers_Gen_v1SubHSM.h"
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
//#define TEMP_DRIVE_DURATION 1000 // might as well use it. 
//#define TEMP_DRIVE_DURATION_2 200
//#define ACTIVE_DURATION 3500 //10000 // Not sure but we are using in place of FT_IDLE_DURATION to time how long we search
//#define DEBOUNCE_DURATION 50 // period of sampling the bumpers (I think-BVK)
//#define MIDROTATE_DURATION 750 // duration we adjust after driving straight in FindTape Idle
//#define LINE_CORRECT_LEFT_DURATION 250 // duration we tank turn left to get back on tape
//#define LINE_CORRECT_RIGHT_DURATION 500
////#define FT_IDLE_DURATION 3500 // duration we drive straight in FindTape Idle before adjusting
//#define APPROACH_ADJUST_LEFT 200
//#define APPROACH_ADJUST_RIGHT 300
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
uint8_t InitSimpleFunctionService(uint8_t Priority);

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostSimpleFunctionService(ES_Event ThisEvent);

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunSimpleFunctionService(ES_Event ThisEvent);



#endif /* SimpleFunctionService_H */


