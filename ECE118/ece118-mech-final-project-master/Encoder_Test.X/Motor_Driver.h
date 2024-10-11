/* 
 * File:   Motor_Driver.h
 * Author: bcvander
 *
 * 
 * *** SPEED MIN IS CURRENTLY 300 PWM*** 5/15/2022
 * Created on May 12, 2022, 7:05 PM
 */

#ifndef MOTOR_DRIVER_H
#define	MOTOR_DRIVER_H
#include <xc.h>
#include "BOARD.h"
#include "AD.h"
#include "pwm.h"
#include "IO_Ports.h"
#include "ES_Configure.h"
#include "EncoderService.h"
// Public Includes

#define DRIVE_HYPERSPEED_MAX_PLUS 1000 // the forbidden drive speed. Use with Caution * Jokes aside 
#define DRIVE_MAX 900
#define DRIVE_HIGH 750
#define DRIVE_MED 500
#define DRIVE_LOW 450 // may need to raise this to ~300

// Define Ports for Motor
// right motor
#define EN_A PWM_PORTX11
// left motor
#define EN_B PWM_PORTY12

#define IN_1_LAT PORTZ03_LAT 
#define IN_1_TRIS PORTZ03_TRIS

#define IN_2_LAT PORTZ04_LAT
#define IN_2_TRIS PORTZ04_TRIS

#define IN_3_LAT PORTZ05_LAT
#define IN_3_TRIS PORTZ05_TRIS

#define IN_4_LAT PORTZ07_LAT
#define IN_4_TRIS PORTZ07_TRIS

// For Toggling Bits
#define PORT_IN_1_2 PORTZ
#define PIN_IN_1 PIN3

// we need to toggle them at the same time. These should be on the same port!!!
//#define PORT_IN_2 PORTZ
#define PIN_IN_2 PIN4

#define PORT_IN_3_4 PORTZ
#define PIN_IN_3 PIN5
#define PIN_IN_4 PIN7

// Encoder MACROS // The PORT to be read from 
#define HALL_IN_RA PORTX05_BIT
#define HALL_IN_LA PORTX06_BIT

// Encoder B sides
#define HALL_IN_RB PORTX03_BIT
#define HALL_IN_LB PORTX04_BIT

#define HALL_IN_PORT PORTX
#define HALL_IN_PIN_RA PIN5
#define HALL_IN_PIN_LA PIN6
#define HALL_IN_PIN_RB PIN3
#define HALL_IN_PIN_LB PIN4

// basically an enum but can't b fucked to google that syntax rn :/ nvm bits r cooler
#define LEFT 1
#define RIGHT 2
#define BOTH 4
#define BOTH_NO_RESET 8
/**
 * Function Drive_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark sets up PWM and pins to be used to drive two motor. Uses pins:
 * 
 * 
 *  Z03 - In 1 high -> forward
 *  Z04 - In 2 high -> REVERSE
 *  Z06 - PWM 1 (ENA)
 * 
 *  Z05 - In 3 high -> forward
 *  Z07 - In 4 high -> REVERSE
 *  Y12 - PWM 2 (ENB)
 * 
 *  *** SPEED MIN IS CURRENTLY 300 PWM*** 5/15/2022
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Init();

/**
 * Function  Drive_Init
 * @param void
 * @param takes in the pwm value bn 0 - 1000 to set the motor to. outside these bounds
 *  the motor sets as max or min
 * 
 *  if input is NEGATIVE then ensures 
 *  
 *   In 1 LOW 
 *   In 2 High -> REVERSE
 * 
 *  if input is Positive then ensures
 * 
 *   In 1 High -> forward
 *   In 2 Low 
 * 
 * 
 * *** SPEED MIN IS CURRENTLY 300 PWM*** 5/15/2022
 * @return SUCCESS or ERROR
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Right_Motor(int pwm_to_set);

/**
 * Function  Drive_Init
 * @param void
 * @param takes in the pwm value bn 0 - 1000 to set the motor to. outside these bounds
 *  the motor sets as max or min
 * 
 *  if input is NEGATIVE then ensures 
 *  
 *   In 3 LOW 
 *   In 4 High -> REVERSE
 * 
 *  if input is Positive then ensures
 * 
 *   In 3 High -> forward
 *   In 4 Low 
 * 
 * 
 * *** SPEED MIN IS CURRENTLY 300 PWM*** 5/15/2022
 * 
 * 
 * @return SUCCESS or ERROR
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Left_Motor(int pwm_to_set);

/**
 * Function  Drive_Init
 * @param void
 * @param speed - negative -> REVERSE. 
 *              - positive -> FORWARD
 * @return SUCCESS or ERROR
 * @remark Sets both left and right motor to the same speed, either positive or negative
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Straight(int speed);

/**
 * Function  Drive_Init
 * @param MACRO of left, right, both, to stop either motor or both motors. 
 * @param 
 * @return SUCCESS or ERROR
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Stop(uint8_t which_motor);

/**
 * Function  Drive_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark 
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Tank_Turn_Left(int speed);

/**
 * Function  Drive_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark 
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Tank_Turn_Right(int speed);

/**
 * Function  Drive_Pivot_Right
 * @param int speed - positive for pivoting forward, negative for pivoting back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn much below 300. 
 * @param 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Drive_Pivot_Right(int speed);



/**
 * Function  Drive_Pivot_Left
 * @param int speed - positive for pivoting forward, negative for pivoting back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn much below 300. 
 * @param 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Drive_Pivot_Left(int speed);

/**
 * Gradual_Turn_Right(int speed):
 * @param speed - positive for turning forward, negative for turning back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn below 300. 
 * 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Gradual_Turn_Right(int speed);

/**
 * Gradual_Turn_Left(int speed):
 * @param speed - positive for turning forward, negative for turning back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn below 300. 
 * 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Gradual_Turn_Left(int speed);


/**
 * Hard_Turn_Right(int speed):
 * @param speed - positive for turning forward, negative for turning back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn below 300. 
 * 
 *  Right Wheel turns at -speed 
 *  Left Wheel turns at speed - HARD_TURN_CONST 
 *  this is a constant defined in the .c file (motor driver.c) 
 *  this constant determines how hard we turn. if this constant increases, 
 *  there is a greater difference between the wheel speeds. This also changes 
 *  the maximum value we can input to here and still turn the wheels  
 * 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Hard_Turn_Right(int speed);

/**
 * Hard_Turn_Left(int speed):
 * @param speed - positive for turning forward, negative for turning back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn below 300. 
 * 
 *  Left Wheel turns at -speed 
 *  Right Wheel turns at speed - HARD_TURN_CONST 
 *  this is a constant defined in the .c file (motor driver.c) 
 *  this constant determines how hard we turn. if this constant increases, 
 *  there is a greater difference between the wheel speeds. This also changes 
 *  the maximum value we can input to here and still turn the wheels  
 * 
 *
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Hard_Turn_Left(int speed);

/**
 * converts the desired number of ticks for each side into the 8 msb for the left side
 *  and the 8 lsb for the right side 
 * @param left_ticks, right_ticks. Max tick count is max of uint8_t
 * @return Error or Success depending on turn function and EncoderServicer function 
 */

int16_t Encoder_Tick_Converter(uint16_t left_ticks, uint16_t right_ticks);

/**
 * Drives straight at desired speed for half a wheel rotation. Recommend Med or High 
 * @param speed
 * @return Error or Success depending on turn function and EncoderServicer function 
 */
int8_t Enc_Drive_Straight_Half_Rot(int speed);


/**
 * Drives straight at desired speed for full a wheel rotation. Recommend Med or High 
 * @param speed
 * @return Error or Success depending on turn function and EncoderServicer function 
 */

int8_t Enc_Drive_Straight_Full_Rot(int speed);

/**
 * Drives straight at desired speed for 2 feet (Quarter of field length) Recommend Med or High 
 * We will likely need to readjust while driving along the tape
 * @param speed
 * @return Error or Success depending on turn function and EncoderServicer function 
 */

int8_t Enc_Drive_Straight_Two_Feet(int speed);

/**
 * Tank Turn Left at preset speed for when we find a corner on the tape 
 * @param speed
 * @return Error or Success depending on turn function and EncoderServicer function 
 */

int8_t Enc_Drive_Tank_Turn_90Left(void);



/**
 * Pivots Left for ~300 Degrees to navigate tower corners (equalatial trianlge is 60 deg side)
 * @param speed
 * @return Error or Success depending on turn function and EncoderServicer function 
 */

int8_t Enc_Pivot_Left_Corner(int speed);





#endif	/* MOTOR_DRIVER_H */

