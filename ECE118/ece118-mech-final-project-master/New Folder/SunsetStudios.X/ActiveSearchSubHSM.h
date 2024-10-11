/*
 * File: TemplateSubHSM.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical SubState Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that 
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * Make sure each SubState machine has a unique name and is #include in the
 * higher level state machine using it
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 16/Sep/2013
 */

#ifndef ACTIVE_SEARCH_SUB_HSM_H  // <- This should be changed to your own guard on both
#define ACTIVE_SEARCH_SUB_HSM_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
/*Tape Sensor to Bot Placement Key 
 * TS_A ->Rear Right Tape Sensor
 * TS_D -> Front Right Tape Sensor
 * TS_E -> Front Center Tape Sensor 
 */
//Currently Making Changes to Sense Event Checker 5/28/22
//Using Defines for EventParameter conditions that trigger state transitions
//CHANGE THIS! THIS IS ONLY LIKE THIS WHILE THE BIT MANIPULATION I WROTE IS BUSTED !!!!!!!!!!!!!!!!!!!!!!!!! {Amber}
//5/30/22// NVM I'm actually using these as is 
// 5/29/22 This is where exit/entry conditions for the state machine are defined
//         They are designed to be OR'd then xor'd with the event parameter for the CHANGE_IN_LIGHT_STATE event
#define SR_ENTRY (A_TS_MASK | D_TS_MASK | E_TS_MASK ) // Right to Quarner? Rotate to Face Quatrant (x11xx1)
#define MAR_ENTRY_1 (NOT_TS_MASK_A & NOT_TS_MASK_E & NOT_TS_MASK_D)  // Mid Adjust Rotate (x00xx0) 
#define MAR_ENTRY_2 (NOT_TS_MASK_E & NOT_TS_MASK_D) //(x00xx1)
#define MAR_ENTRY_3 (NOT_TS_MASK_E & NOT_TS_MASK_A) //(x01xx0)
#define FT_ENTRY (NOT_TS_MASK_E) // Follow tape?  (x01xx1)
#define RAFC_ENTRY (NOT_TS_MASK_A)
#define DANGER_ZONE (E_TS_MASK | F_TS_MASK) 
#define RR_ONLY_ADJUST ()
#define FR_ONLY_ADJUST ()

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(void)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitActiveSearchSubHSM(void);

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunActiveSearchSubHSM(ES_Event ThisEvent);

#endif /* TAPE_HANDLER_SUB_HSM_H */

