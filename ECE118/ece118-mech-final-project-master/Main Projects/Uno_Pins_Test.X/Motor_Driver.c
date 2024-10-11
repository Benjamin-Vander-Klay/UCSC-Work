/*
 * File:   motor_driver.c
 * Author: bcvander
 *
 * Created on May 12, 2022, 4:11 PM
 */

// File includes maybe should be in .h
#include <stdlib.h>
#include <stdio.h>
#include "BOARD.h"
#include "xc.h"
#include "AD.h"
#include "pwm.h"
#include "LED.h"
#include "serial.h"
#include "IO_Ports.h"

#include "Motor_Driver.h"
#include "ES_Events.h"

//UNCOMMENT TO TEST MOTOR LIB // also can do in the project properties like dunne would want
//#define MOTOR_TEST
// ****

// Private MACROS
// Macros so christian doesnt yell at me
#define PWM_SPEED 900
#define MIN_SPEED 300


#define FORWARD 1
#define REVERSE 0

#define GRADUAL_TURN_CONST 200 // difference btn wheel speeds for Gradual Turn
#define GRADUAL_TURN_MIN GRADUAL_TURN_CONST + MIN_SPEED

#define HARD_TURN_CONST 400 // difference btn wheel speeds (direction of turn is -speed))
#define HARD_TURN_MIN HARD_TURN_CONST + MIN_SPEED
#define ON 1
#define OFF 0

#define OUTPUT 0  // for TRIS values

// Module level Variables. Consider using Static if actually use these
unsigned int pwm_input = 0;
unsigned int prev_pwm = 0;


// -----------------------------------------------------------------------------

/**
 * Function Drive_Init()
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
 *  EN_B
 *  
 * sets inputs for the Hall Sensors to the UNO 32
 * 
 * 
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Init() {

    // Init PWM
    if (PWM_Init() == ERROR) {
        printf("\r\nERROR in Drive_Init() calling PWM_Init()");
        return ERROR;
    }

    // Set up pins as outputs 
    //ENA and ENB 
    if (PWM_AddPins(EN_A | EN_B) == ERROR) {// Pin Z6 on I/O shield
        printf("\r\nERROR in in Drive_Init() calling PWM_AddPins(PWM_PORTY12 | PWM_PORTZ06)");
        return ERROR;
    }

    // outputs and set to init direction
    //In1
    IN_1_TRIS = OUTPUT;
    IN_1_LAT = 0;
    // In2
    IN_2_TRIS = OUTPUT;
    IN_2_LAT = 1;

    // In3
    IN_3_TRIS = OUTPUT;
    IN_3_LAT = 1;
    // In4
    IN_4_TRIS = OUTPUT;
    IN_4_LAT = 0;
    
    if (IO_PortsSetPortInputs(PORTX, PIN5 | PIN6) == ERROR) {// Pin X3 on I/O shield
        printf("ERROR in PWM Add pins\n");
        return ERROR;
    }
    
}

/**
 * Function  Drive_Right_Motor
 * @param void
 * @param takes in the pwm value bn 0 - 1000 to set the motor to. outside these bounds
 *  the motor sets as max or min
 * 
 *      Z06 - PWM 1 (ENA)
 *      EN_A
 *  
 * if input is NEGATIVE then ensures 
 * 
 *   In 1 High -> REVERSE
 *   In 2 Low 
 * 
 *  if input is Positive then ensures
 *  
 *   In 1 LOW 
 *   In 2 High -> forward
 * 
 * 
 *  Z03 - In 1 high -> forward
 *  Z04 - In 2 high -> REVERSE
 *  Z06 - PWM 1 (ENA)
 *  
 * @return SUCCESS or ERROR
 * @remark ** forward is Clockwise on the right and CCW on the left motor. The log\
 *         ** LOGIC IS INVERTED TO ACCOUNT FOR THIS. FORWARD IS 
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Right_Motor(int pwm_w_dir) {

    // Ensure not out of bounds
    unsigned int pwm_to_set = abs(pwm_w_dir);
    if (pwm_to_set > MAX_PWM) {
        pwm_to_set = MAX_PWM;
    } else if (pwm_to_set < MIN_PWM) {
        pwm_to_set = MIN_PWM;
    }
    // if pwm_to_set is negative we make sure the values are negative
    // negative but currently set to drive right wheel forward
    if ((pwm_w_dir < 0) && (IN_1_LAT == OFF) && (IN_2_LAT == ON)) {
        // change direction
        IO_PortsTogglePortBits(PORT_IN_1_2, PIN_IN_1 | PIN_IN_2);
    }// Converse... Switch to Forward
    else if ((pwm_w_dir > 0) && (IN_1_LAT == ON) && (IN_2_LAT == OFF)) {
        // change direction
        IO_PortsTogglePortBits(PORT_IN_1_2, PIN_IN_1 | PIN_IN_2);
    }

    unsigned int curr_DC = PWM_GetDutyCycle(EN_A);
    if (curr_DC == ERROR) {
        printf("ERROR in Drive_Right_Motor calling PWM_GetDutyCycle(PWM_PORTZ06)\n");
        return ERROR;
    } else if (curr_DC != pwm_to_set) {
        // set new pwm
        if (PWM_SetDutyCycle(EN_A, pwm_to_set) == ERROR) {// Pin Z6 on I/O shield
            printf("ERROR in Drive_Right_Motor calling PWM_SetDutyCycle(PWM_PORTZ06, pwm_input)\n");
            return ERROR;
        }
    }
    return SUCCESS;



}

/**
 * Function  Drive_Left_Motor
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
 *  Z05 - In 3 high -> forward
 *  Z07 - In 4 high -> REVERSE
 *  Y12 - PWM 2 (ENB)
 * 
 * 
 * @return SUCCESS or ERROR
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Left_Motor(int pwm_w_dir) {
    // Ensure not out of bounds
    unsigned int pwm_to_set = abs(pwm_w_dir);
    if (pwm_to_set > MAX_PWM) {
        pwm_to_set = MAX_PWM;
    } else if (pwm_to_set < MIN_PWM) {
        pwm_to_set = MIN_PWM;
    }
    // if pwm_to_set is negative we make sure the values are negative
    // negative but currently set to drive right wheel forward
    if ((pwm_w_dir < 0) && (IN_3_LAT == ON) && (IN_4_LAT == OFF)) {
        // change direction
        IO_PortsTogglePortBits(PORT_IN_3_4, PIN_IN_3 | PIN_IN_4);
    }// Converse... Switch to Forward
    else if ((pwm_w_dir > 0) && (IN_3_LAT == OFF) && (IN_4_LAT == ON)) {
        // change direction
        IO_PortsTogglePortBits(PORT_IN_3_4, PIN_IN_3 | PIN_IN_4);
    }

    unsigned int curr_DC = PWM_GetDutyCycle(EN_B);
    if (curr_DC == ERROR) {
        printf("ERROR in Drive_Right_Motor calling PWM_GetDutyCycle(PWM_PORTZ06)\n");
        return ERROR;
    } else if (curr_DC != pwm_to_set) {
        // set new pwm
        if (PWM_SetDutyCycle(EN_B, pwm_to_set) == ERROR) {// Pin Y12 on I/O shield
            printf("ERROR in Drive_Right_Motor calling PWM_SetDutyCycle(PWM_PORTZ06, pwm_input)\n");
            return ERROR;
        }
    }
    return SUCCESS;
}
// ------------------------------------------------------------------------------

/**
 * Function  Drive_Init
 * @param void
 * @param speed - negative -> REVERSE. 
 *              - positive -> FORWARD
 * @return SUCCESS or ERROR
 * @remark Sets both left and right motor to the same speed, either positive or negative
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Straight(int speed) {

    // minimum pwm where the motor still turns
    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }
    if (Drive_Right_Motor(speed) == ERROR || Drive_Left_Motor(speed) == ERROR) {
        printf("ERROR in Drive_Straight calling Drive_Right/Left_Motor()\n");
        return ERROR;
    }
    return SUCCESS;

}

/**
 * Function  Drive_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Stops motors by setting both ENA and ENB to 0
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Stop(uint8_t which_motor) {
    // these r bits my friend OR logic for the win 
    if(which_motor == RIGHT | BOTH){
        // right motor 
        if (PWM_SetDutyCycle(PWM_PORTZ06, MIN_PWM) == ERROR) {// Pin Z6 on I/O shield
            printf("ERROR in Drive_Right_Motor calling PWM_SetDutyCycle(PWM_PORTZ06, pwm_input)\n");
            return ERROR;
        }
    }
    if(which_motor == LEFT | BOTH){
        // left motor
        if (PWM_SetDutyCycle(PWM_PORTY12, MIN_PWM) == ERROR) {// Pin Y12 on I/O shield
            printf("ERROR in Drive_Right_Motor calling PWM_SetDutyCycle(PWM_PORTZ06, pwm_input)\n");
            return ERROR;
        } 
    }
    
    return SUCCESS;
}

//------------------------------------------------------------------------------
// TANK TURN
// no reverse tank direction 

/**
 * Function  Drive_Init
 * @param void
 * @param 
 * @return SUCCESS or ERROR
 * @remark Stops motors by setting both ENA and ENB to 0
 * @author Benjamin Vander Klay
 * @date 5/12/2022  */
char Drive_Tank_Turn_Right(int speed) {
    //    motorSpeedLeft = HIGH;
    //    motorSpeedRight = MED;
    char error = SUCCESS;
    // minimum pwm where the motor still turns

    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }
    if (Drive_Right_Motor(-speed) == ERROR) {
        error = ERROR;
    }
    if (Drive_Left_Motor(speed) == ERROR) {
        error = ERROR;
    }
    return error;
}

char Drive_Tank_Turn_Left(int speed) {

    int8_t error = SUCCESS;
    // minimum pwm where the motor still turns
    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }
    if (Drive_Right_Motor(speed) == ERROR) {
        error = ERROR;
    }
    if (Drive_Left_Motor(-speed) == ERROR) {
        error = ERROR;
    }

    return error;
}
//------------------------------------------------------------------------------

/**
 * Function  Drive_Pivot_Right
 * @param int speed - positive for pivoting forward, negative for pivoting back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn much below 300. 
 * @param 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Drive_Pivot_Right(int speed) {
    char error = SUCCESS;

    // minimum pwm where the motor still turns
    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }

    if (Drive_Left_Motor(speed) == ERROR) {
        error = ERROR;
    }
    if (Drive_Right_Motor(OFF) == ERROR) {
        error = ERROR;
    }

    return error;
}

/**
 * Function  Drive_Pivot_Left
 * @param int speed - positive for pivoting forward, negative for pivoting back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn much below 300. 
 * @param 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @remark
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Drive_Pivot_Left(int speed) {
    char error = SUCCESS;

    // minimum pwm where the motor still turns
    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }

    if (Drive_Left_Motor(OFF) == ERROR) {
        error = ERROR;
    }
    if (Drive_Right_Motor(speed) == ERROR) {
        error = ERROR;
    }

    return error;
}
//------------------------------------------------------------------------------

char Gradual_Turn_Right(int speed) {
    char error = SUCCESS;

    // minimum pwm where the motor still turns
    if (speed < GRADUAL_TURN_MIN) {
        speed = GRADUAL_TURN_MIN;
    }

    if (Drive_Left_Motor(speed - GRADUAL_TURN_CONST) == ERROR) {
        error = ERROR;
    }
    if (Drive_Right_Motor(speed) == ERROR) {
        error = ERROR;
    }
    return error;
}

char Gradual_Turn_Left(int speed) {
    char error = SUCCESS;

    // minimum pwm where the motor still turns
    if (speed < GRADUAL_TURN_MIN) {
        speed = GRADUAL_TURN_MIN;
    }

    if (Drive_Left_Motor(speed) == ERROR) {
        error = ERROR;
    }
    if (Drive_Right_Motor(speed - GRADUAL_TURN_CONST) == ERROR) {
        error = ERROR;
    }
    return error;
}
//------------------------------------------------------------------------------

// HARD TURN
// High speed right, med speed left

/**
 * Hard_Turn_Right(int speed):
 * @param speed - positive for turning forward, negative for turning back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn below 300. 
 * 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Hard_Turn_Right(int speed) {
    int8_t error = SUCCESS;

    // ensure we don't mess up the arithmatic
    // needs to be at least min speed (300 right now) + HARD_TURN_CONST
    // so that we don't set Drive_Left_Motor to less than 300. 
    
    if (speed < HARD_TURN_MIN) {
        speed = HARD_TURN_MIN;
    }
    if (Drive_Left_Motor(speed - HARD_TURN_CONST) == ERROR) {
        error = ERROR;
    }
    if (Drive_Right_Motor(-speed) == ERROR) {
        error = ERROR;
    }

    return error;
}

/**
 * Hard_Turn_Left(int speed):
 * @param speed - positive for turning forward, negative for turning back
 *          PWM usable range ~300 - 1000 (MAX)... Wheels don't turn below 300. 
 * 
 * @return SUCCESS or ERROR depending on Drive_..._Motor functions
 * @author Benjamin Vander Klay
 * @date 5/15/2022 */
char Hard_Turn_Left(int speed) {

    int8_t error = SUCCESS;
    // ensure we don't mess up the arithmatic
    // needs to be at least min speed (300 right now) + HARD_TURN_CONST
    // so that we don't set Drive_Right_Motor to less than 300. 
    
    if (speed < HARD_TURN_MIN) {
        speed = HARD_TURN_MIN;
    }
    if (Drive_Left_Motor(-speed) == ERROR) {
        error = ERROR;
    }
    if (Drive_Right_Motor(speed - HARD_TURN_CONST) == ERROR) {
        error = ERROR;
    }
    return error;
}

//------------------------------------------------------------------------------
// ROTARY ENCODER PRE DETERMINED MOVEMENTS
//
///**
// * converts the desired number of ticks for each side into the 8 msb for the left side
// *  and the 8 lsb for the right side ** MAX IS 1020 (255 * 4 = 1020) THIS IS ROUGHLY 2 WHEEL ROTATIONS
// * @param left_ticks, right_ticks
// * @return Error or Success depending on turn function and EncoderServicer function 
// */
//
//int16_t Encoder_Tick_Converter(uint16_t left_ticks, uint16_t right_ticks){
//    
//    uint8_t scaled_left = left_ticks / ENCODER_SCALER;
//    uint8_t scaled_right = right_ticks / ENCODER_SCALER;
//    uint16_t shifted_left = (uint16_t) scaled_left << 8;
//    printf("shifted left = %d", shifted_left);
//    uint16_t combined = shifted_left | ((uint16_t) scaled_right);
//    return combined;
//}
//
//int8_t Drive_Straight_Half_Rot(int speed){
//    
//    // Event to send to the Rotary Encoder Servicer
//    ES_Event DriveEvent;
//    DriveEvent.EventType = ENCODER_SET_TICKS;
////    DriveEvent.EventParam = 
//    
//    return SUCCESS;
//}
//
///**
// * Drives straight at desired speed for half a wheel rotation. Recommend Med or High 
// * @param speed
// * @return Error or Success depending on turn function and EncoderServicer function 
// */
//
//int8_t Enc_Drive_Straight_Half_Rot(int speed){
//    
//}
//
//
///**
// * Drives straight at desired speed for full a wheel rotation. Recommend Med or High 
// * @param speed
// * @return Error or Success depending on turn function and EncoderServicer function 
// */
//
//int8_t Enc_Drive_Straight_Full_Rot(int speed){
//    
//}
//
//
///**
// * Drives straight at desired speed for 2 feet (Quarter of field length) Recommend Med or High 
// * We will likely need to readjust while driving along the tape
// * @param speed
// * @return Error or Success depending on turn function and EncoderServicer function 
// */
//
//int8_t Enc_Drive_Straight_Two_Feet(int speed){
//    
//}
//
///**
// * Tank Turn Left at preset speed for when we find a corner on the tape 
// * @param speed
// * @return Error or Success depending on turn function and EncoderServicer function 
// */
//
//int8_t Enc_Drive_Tank_Turn_90Left(void){
//    
//}
//
//
//
///**
// * Pivots Left for ~300 Degrees to navigate tower corners (equalatial trianlge is 60 deg side)
// * @param speed
// * @return Error or Success depending on turn function and EncoderServicer function 
// */
//
//int8_t Enc_Pivot_Left_Corner(int speed){
//    
//}

#ifdef MOTOR_TEST

int main(void) {
    // Taken from my lab3 
    // Init required Modules
    BOARD_Init();
    AD_Init();
    //    PWM_Init();
    LED_Init();
    Drive_Init();

    //--------------------------------------------------------------------------
    // Variables
    //    unsigned int ad_value = 0;
    //    unsigned int prev_ad = 0;
    //    unsigned int led_value = 0;
    //    unsigned char led_b1, led_b2, led_b3;
    unsigned int pwm_input = 0;
    unsigned int prev_pwm = 0;
    uint16_t switch_input = 0;
    uint16_t prev_switch = 0;
    int16_t count = 0;
    int16_t y_8, prev_y8;
    uint16_t left_ticks = 400;
    uint16_t right_ticks = 200;
    
    // --------------------------------------------------------------------------
//    // test encoder libraries
//    uint16_t ticks = Encoder_Tick_Converter(left_ticks, right_ticks);
//    printf("\r\nticks encoded to 16bits = %d", ticks);
//    uint16_t ticks_left_mtr = (ticks | LEFT_MTR_TICKS) >> 7 * 4;
//    printf("\r\nticks decoded left motor(400) = %d", ticks_left_mtr);
//    uint16_t ticks_right_mtr = (ticks | RIGHT_MTR_TICKS) * 4;
//    printf("\r\nticks decoded riht motor(200) = %d", ticks_right_mtr);
    
    //    //--------------------------------------------------------------------------
    //    // Add Pins / Set-up
    //    // Add pins -- PWM outputs and AD inputs 
    //
    //    if(PWM_AddPins(PWM_PORTY10) == ERROR){// Pin Z6 on I/O shield
    //        printf("ERROR in PWM Add pins\n");
    //    }
    //    
    //
    //    
    //    
    if (IO_PortsSetPortInputs(PORTX, PIN3) == ERROR) {// Pin X3 on I/O shield
        printf("ERROR in PWM Add pins\n");
    }
    //    
    //    PORTY07_TRIS = 0;
    //    PORTY06_TRIS = 0;
    //    
    //    PORTY07_LAT = 0;
    //    PORTY06_LAT = 1;

    //    
    //    if(IO_PortsSetPortOutputs(PORTY, PIN5 | PIN6) == ERROR){// Pin X5 & X6 on I/O shield
    //        printf("ERROR in PWM Add pins\n");
    //    }

    //--------------------------------------------------------------------------
    // Print out compilation statement
    printf("\r\nECE 118 Final Project Motors driver. Compiled %s, %s\n", __DATE__, __TIME__);


    // Switching Directions
    //IO_PortsTogglePortBits(PORTY, PIN7 | PIN6);

    // set pwm 
//    pwm_input = PWM_SPEED;
    //    Drive_Right_Motor(PWM_SPEED);
    //    Drive_Left_Motor(PWM_SPEED);
//    Drive_Tank_Turn_Right(-PWM_SPEED);
    Drive_Straight(PWM_SPEED);
    printf("\r\nDuty Cycle = %d\n", PWM_GetDutyCycle(PWM_PORTY12));
//    if (IO_PortsReadPort(PORTY08_BIT) == ERROR) {
//        printf("\r\nPort reads ERROR");
//    }
    //--------------------------------------------------------------------------
    // Never exit on embedded. Turns out nbd actually but 

    while (1) {

        // Set duty cycle              
        //        if(PWM_SetDutyCycle(PWM_PORTY10, pwm_input) == ERROR){// Pin Z6 on I/O shield
        //        printf("ERROR in PWM Set Duty Cycle\n");
        //        }

        //        printf("count = %d", count);
//        prev_y8 = y_8;
//        y_8 = PORTY08_BIT;
//
//        // count rising edges
//        if ((PORTY08_BIT) == TRUE && prev_y8 == FALSE) {
//            //            printf("Port reads True");
//            count++;
//        }
//        if ((PORTY08_BIT) == ERROR) {
//            printf("\r\nPort reads ERROR");
//        }
//        if (count > 509) {
//            count = 0;
//            Drive_Stop();
//            printf("\r\ncompleted 1 full rotation\r\n");
//            // and stop motor?
//
//        }

    }

    return 0;
}

#endif
