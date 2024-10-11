/*
 * File:   QEI.c
 * Author: Benjamin Vander Klay bcvander
 * ECE 167
 * 
 * Created on April 17, 2023, 8:21 PM 
 */
#include "QEI.h"

#include <xc.h>
#include <sys/attribs.h>
#include <BOARD.h>
#include <AD.h>
#include "PWM.h"
#include <serial.h>
#include <stdio.h>
#include <stdlib.h>
#include "timers.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define QEI_TEST
#define ENCODER_MIN   -96 // 24 ticks in 360 degrees in 2pi * counts per tick
#define ENCODER_MAX    96 // ^^
#define SAMPLE_PERIOD  100
#define ENCODER_RATIO  1
#define TICK_PER_REV   96 //
#define ONE_REVOLUTION 360 // degrees
#define DEG_MARGIN     0
#define DEG_RGB        120 // changed to be 120. split into 3 and center at offset of 60 degrees

// from splitting 360 degrees into 7 segments. 3 per R G B with G sharing two and having one on its own. 

#define R_DEG_MIN 300
#define R_DEG_CENTER 60
#define R_DEG_MAX 180
#define G_DEG_MIN 180
#define G_DEG_CENTER 300
#define G_DEG_MAX 60
#define B_DEG_MIN 60
#define B_DEG_CENTER 180
#define B_DEG_MAX 300
/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/
static int8_t encoder_count;
static volatile uint8_t prev_A;
static volatile uint8_t prev_B;
static volatile char A = 0;
static volatile char B = 0;

//static char isr_flag = 0;

typedef enum state {
    S0,
    S1,
    S2,
    S3
} ROT_STATE;


uint8_t cur_state;
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @function QEI_Init(void)
 * @param none
 * @brief  Enables the Change Notify peripheral and sets up the interrupt, anything
 *         else that needs to be done to initialize the module. 
 *         Ues pins 36 and 37 (RD6 and RD7)
 * @return SUCCESS or ERROR (as defined in BOARD.h)
 */
char QEI_Init(void) {
    // INIT Change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN15 = 1; //enable one phase
    CNENbits.CNEN16 = 1; //enable other phase

    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    // we then read the port again in the interrupt



    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; // set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify

    // define as inputs
    TRISDbits.TRISD6 = 1; // input!
    TRISDbits.TRISD7 = 1; // input!

    //Note: PORTZ06 is OC1, PORTY12, 10, 4 are OC2, OC3, OC4 respectively.
    //PORTX11 is OC5. Use pins 3 (OC1), 5 (OC2), and 9 (OC4) for your RGB encoder.

    temp++;
    // the rest of the function goes here
    // temporarily here
    prev_A = PORTDbits.RD6; // pin 36
    prev_B = PORTDbits.RD7; // pin 37
    cur_state = 0; // reset cur_state

    if (prev_A == 1) { // A is MSB, and we are in case S2 or S3
        cur_state += 2; // S1
    }
    if (prev_B == 1) { // B is LSB, and we are in case S1 or S3
        cur_state += 1; // S2
    }
    // if both were false, cur_state == 0!
    return EXIT_SUCCESS;
}

/**
 * @function QEI_GetPosition(void) 
 * @param none
 * @brief This function returns the current count of the Quadrature Encoder in ticks.      
 */
int QEI_GetPosition(void) {
    // gets the current count
    int8_t round_count = encoder_count;
    if (round_count > 94 && round_count < ENCODER_MAX) { // round up to 24
        round_count = ENCODER_MAX;
    } else if (round_count < -94 && round_count > ENCODER_MIN) { // or -24
        round_count = ENCODER_MIN;
    }
    return round_count / ENCODER_RATIO; // initially divided by 4 to get down to +/- 24. Changed. keep MACRO 
}

/**
 * @Function QEI_ResetPosition(void) 
 * @param  none
 * @return none
 * @brief  Resets the encoder such that it starts counting from 0.
 */
void QEI_ResetPosition(void) {
    //    resets the count    
    encoder_count = 0;
    cur_state = S0;

    return;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0; // only reads 8 of the bits


    readPort = PORTD; // this read is required to make the interrupt work
    readPort++; // just to get ride of warning. delete if not necessary and need to increase speed
    //anything else that needs to happen goes here

    // now we need to read it to determine which pin changed. decipher the register


    // ports 6 and 7 used right now. could bit mask bits 6 and 7
    A = PORTDbits.RD6;
    B = PORTDbits.RD7;

    switch (cur_state) {
        case(S0): // Previously A == 0, B == 0
            if (A == 0 && B == 1) { // B comes first, that means we are going CCW

                encoder_count++;
                if (encoder_count > ENCODER_MAX) { // watch your off-by-one's MF
                    encoder_count = ENCODER_MIN;

                }
                cur_state = S1;

            } else if (A == 1 && B == 0) { // back to 
                encoder_count--; // if you have speed issues combine these into one ***
                if (encoder_count < ENCODER_MIN) { // see above note about being a dumbass
                    encoder_count = ENCODER_MAX;
                }
                cur_state = S2;

            }
            break;
        case(S1): // Previously A == 0, B == 1
            if (A == 1 && B == 1) { // B came first, CCW, dec

                encoder_count++;
                if (encoder_count > ENCODER_MAX) { // watch your off-by-one's MF
                    encoder_count = ENCODER_MIN;

                }
                cur_state = S3;

            } else if (A == 0 && B == 0) { // back to S0 , A came first, CW, inc
                encoder_count--; // if you have speed issues combine these into one ***
                if (encoder_count < ENCODER_MIN) { // see above note about being a dumbass
                    encoder_count = ENCODER_MAX;
                }
                cur_state = S0;
            }
            break;

        case(S2): // Previously A == 1, B == 0
            if (A == 1 && B == 1) { // A came fist, inc, CW

                encoder_count--; // if you have speed issues combine these into one ***
                if (encoder_count < ENCODER_MIN) { // see above note about being a dumbass
                    encoder_count = ENCODER_MAX;
                }
                cur_state = S3;

            } else if (A == 0 && B == 0) { // back to S0, CCW, dec
                encoder_count++;
                if (encoder_count > ENCODER_MAX) { // watch your off-by-one's MF
                    encoder_count = ENCODER_MIN;

                }
                cur_state = S0;
            }
            break;

        case(S3): // Previously A == 1, B == 1
            if (A == 0 && B == 1) { // A went down first, CW, inc
                encoder_count--; // if you have speed issues combine these into one ***
                if (encoder_count < ENCODER_MIN) { // see above note about being a dumbass
                    encoder_count = ENCODER_MAX;
                }
                cur_state = S1;

            } else if (A == 1 && B == 0) { // to S3, we are going CCW, dec
                encoder_count++;
                if (encoder_count > ENCODER_MAX) { // watch your off-by-one's MF
                    encoder_count = ENCODER_MIN;

                }
                cur_state = S2;
            }

            break;

    }



    IFS1bits.CNIF = 0; // set IF back low. Can re-generate an interrupt now
}

// Main function for testing
#ifdef QEI_TEST

int main(void) {
    BOARD_Init();
    SERIAL_Init();

    QEI_Init();
    TIMERS_Init();
    PWM_Init();

    PWM_AddPins(PWM_PORTZ06); // R pin 3
    PWM_AddPins(PWM_PORTY12); // G pin 5
    PWM_AddPins(PWM_PORTY04); // B pin 9


    PWM_SetFrequency(PWM_DEFAULT_FREQUENCY);

    //    PWM_SetDutyCycle(PWM_PORTZ06, 500);


    //    int prev_pos = 0;
    int cur_pos = 0;
    int wait_ms;

    int16_t degrees = 0;
    int16_t degrees_prev = 0;
    int16_t degrees_R = 0;
    int16_t degrees_G = 0;
    int16_t degrees_B = 0;
    // never exit on embedded
    printf("\r\nLab2 QEI Main compiled on %s, at %s", __DATE__, __TIME__);
    printf("\r\nInitial state: %d", cur_state);

    printf("\r\nActive PWM pins %x", PWM_ListPins());


    wait_ms = TIMERS_GetMilliSeconds() + SAMPLE_PERIOD;
    //    PWM_SetDutyCycle(PWM_PORTZ06, MAX_PWM);
    //    PWM_SetDutyCycle(PWM_PORTY12, 500); /// just for testing 
    //    PWM_SetDutyCycle(PWM_PORTY04, 500);


    while (1) {
        cur_pos = QEI_GetPosition();
        //        printf("\r\ncurrent position is: %d", cur_pos);


        if (TIMERS_GetMilliSeconds() >= wait_ms) {

            //            printf("\r\nA value: %d", A);
            //            printf("\r\nprevA value: %d", prev_A);
            //            printf("\r\nB value: %d", B);
            //            printf("\r\nprevB value: %d", prev_B);

            //            printf("\r\ncurrent position is: %d", cur_pos);
            //            printf("interrupt triggered %d many times\r\n", isr_flag); // ISR triggering
            //            printf("\r\ncurrent state: %d", cur_state);
            wait_ms = TIMERS_GetMilliSeconds() + SAMPLE_PERIOD;


            // degree conversion is current tick value * degrees per tick. but careful w integer divison
            degrees = (cur_pos * ONE_REVOLUTION) / TICK_PER_REV;



            // only change  PWM if something actually changed. Reduce flickering
            if (degrees != degrees_prev) {
                printf("\r\ncurrent position is: %d", cur_pos);
                printf("\r\ndegrees = %d", degrees);
                degrees_prev = degrees;
                // want to simplify things. this might be counterproductive. overlay -360 onto 360. 
                if (degrees < 0) {
                    degrees = degrees + ONE_REVOLUTION;
                }
                // Map QEI to color:
                // Red --------------------------------------------------------------------------------------------------------------------
                if (degrees > R_DEG_MIN || degrees < R_DEG_MAX) { // 300 to 180. total range is 240 degrees. 120 on each side. 

                    // we still can't change the degreees 
                    //                    degrees_R = (degrees * DEG_RGB / 360);
                    //                    degrees_R = DEG_RGB - degrees; // 153 - x in range (0 to 153)
                    if (degrees >= R_DEG_MIN) {
                        // puts at negative -60 to 0. degrees can be negative. 
                        degrees_R = degrees - 360;
                    } else {
                        // will set up degrees R to be - 60 to + 180
                        degrees_R = degrees;
                    }
                    // intentionally not else if. ^^ brings it to less than 60. Below sets PWM
                    if (degrees_R <= R_DEG_CENTER) {// -60  to 60 degrees 
                        // shift up to be in range 0 to 120. 
                        degrees_R = degrees_R + R_DEG_CENTER;
                        //                        printf("\r\ndegrees R = %d", degrees_R);
                        PWM_SetDutyCycle(PWM_PORTZ06, (-MAX_PWM * (degrees_R)) / DEG_RGB + MAX_PWM);
                        //                        printf("duty cycle is: %d", PWM_GetDutyCycle(PWM_PORTZ06));

                    } else { //if (degrees_R > R_DEG_CENTER) { // 60 deg to 180 degrees
                        // can likely be simple else
                        // scale 60 -> 180 to 0 -> 120
                        // 1000 * deg - 60 ( to bring into range) / 120. Scales 0 to 1000 to 0 to 120. 
                        // we want total 
                        //                        printf("\r\ndegrees R = %d", degrees_R);
                        PWM_SetDutyCycle(PWM_PORTZ06, (MAX_PWM * (degrees_R - R_DEG_CENTER)) / DEG_RGB);
                        //                        printf("duty cycle is: %d", PWM_GetDutyCycle(PWM_PORTZ06));
                    }
                } else {
                    PWM_SetDutyCycle(PWM_PORTZ06, MAX_PWM);
                }


                //                    printf("\r\ndegrees R = %d", degrees_R);
                //                    PWM_SetDutyCycle(PWM_PORTZ06, (((-MAX_PWM * degrees_R) / DEG_RGB) + MAX_PWM)); // will prob not zero out? idk man DEG_RGB is 153 here
                //                    PWM_SetDutyCycle(PWM_PORTZ06, 100);
                //                    PWM_SetDutyCycle(PWM_PORTY12,MAX_PWM); /// just for testing 
                //                    PWM_SetDutyCycle(PWM_PORTY04,MAX_PWM);

                // Green --------------------------------------------------------------------------------------------------------------------
                if (degrees > G_DEG_MIN || degrees < G_DEG_MAX) {
                    if (degrees < G_DEG_MAX) {// 0 to 60 degrees
                        degrees_G = degrees + 360;
                    } else {
                        degrees_G = degrees; // case of 180 to 360
                    }
                    //                    printf("\r\ndegrees G = %d", degrees_G);
                    if (degrees_G >= G_DEG_CENTER) { // 300 to 420
                        PWM_SetDutyCycle(PWM_PORTY12, ((MAX_PWM * (degrees_G - G_DEG_CENTER)) / DEG_RGB));
                        //                        printf("\r\ndegrees G = %d", degrees_G);
                        //                        printf("duty cycle is: %d", PWM_GetDutyCycle(PWM_PORTY12));
                    } else {
                        PWM_SetDutyCycle(PWM_PORTY12, ((-MAX_PWM * (degrees_G - G_DEG_MIN)) / DEG_RGB) + MAX_PWM);
                        //                        printf("\r\ndegrees G = %d", degrees_G);
                        //                        printf("duty cycle is: %d", PWM_GetDutyCycle(PWM_PORTY12));
                    }

                    //                    degrees_G = (degrees * DEG_RGB / 360);
                    //                    degrees_G = DEG_RGB - (degrees - G_DEG_MIN);
                    //                    //                    printf("\r\ndegrees G = %d", degrees_G);
                    //                    PWM_SetDutyCycle(PWM_PORTY12, (((-MAX_PWM * degrees_G) / DEG_RGB) + MAX_PWM)); // Max PWM currently 1k. will turn LED OFF!!
                } else {
                    PWM_SetDutyCycle(PWM_PORTY12, MAX_PWM);
                }

                // Blue --------------------------------------------------------------------------------------------------------------------
                if (degrees > B_DEG_MIN && degrees <= B_DEG_MAX) {
                    degrees_B = degrees;
                    //                    printf("\r\ndegrees B = %d", degrees_B);
                    // 
                    if (degrees < B_DEG_CENTER) { // CASE A greater than 60 
                        // decreasinggree
                        PWM_SetDutyCycle(PWM_PORTY04, ((-MAX_PWM * (degrees_B - B_DEG_MIN)) / DEG_RGB) + MAX_PWM);
                    } else { // CASE B less than 300
                        PWM_SetDutyCycle(PWM_PORTY04, ((MAX_PWM * (degrees_B - B_DEG_CENTER)) / DEG_RGB));
                    }
                    //                    printf("duty cycle is: %d", PWM_GetDutyCycle(PWM_PORTY04));
                    //                    degrees_B = (degrees * DEG_RGB / 360);
                    //                    //                    printf("\r\ndegrees B = %d", degrees_B);
                    //                    PWM_SetDutyCycle(PWM_PORTY04, (((-MAX_PWM * degrees_B) / DEG_RGB) + MAX_PWM));
                } else {
                    PWM_SetDutyCycle(PWM_PORTY04, MAX_PWM);
                }

            }
        }



    }
}



#endif
