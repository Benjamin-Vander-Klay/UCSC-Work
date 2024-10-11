/* 
 * File:   Lab2_pt3_2_main.c
 * Author: bcvander
 *
 * Created on April 26, 2023, 8:23 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "BOARD.h"
#include "timers.h"
#include "AD.h"

#define POLL_PERIOD 5 // ms
#define LOW_BOUND_HIST 200
#define HIGH_BOUND_HIST 300
#define MIN_CHANGE 5  
#define GARBAGE_VALUES 20
#define ELEMENTS_IN_MOVING_AVG 7
#define DEFAULT_VALUE 0
#define AD_PIN_USED AD_A4

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    SERIAL_Init();
    AD_Init();
    TIMERS_Init();

    AD_AddPins(AD_PIN_USED); // ensure this pin works oml 
    int poll_timer = 0;

    printf("\r\nLab2 part 3.2 Main compiled on %s, at %s", __DATE__, __TIME__);

    uint16_t raw_ad = 0;
    //    uint16_t old_ad = 0;
    uint8_t touch = 0; // o is low, 1 is high
    volatile int run_sum = DEFAULT_VALUE * ELEMENTS_IN_MOVING_AVG;
    volatile int run_avg = DEFAULT_VALUE;
    //     need array for moving AVG
    uint16_t mov_avg[ELEMENTS_IN_MOVING_AVG];

    for (uint8_t i = 0; i < ELEMENTS_IN_MOVING_AVG; i++) {
        mov_avg[i] = DEFAULT_VALUE;
    }
    printf("\r\n Active AD pins are: %d", AD_ActivePins());

    poll_timer = TIMERS_GetMilliSeconds() + POLL_PERIOD;

    while (1) {

        if (/*AD_IsNewDataReady() && */TIMERS_GetMilliSeconds() >= poll_timer) {
            raw_ad = AD_ReadADPin(AD_PIN_USED);
            //            printf("\r\n Active AD pins are: %d", AD_ActivePins());
            //            printf("\r\nraw_ad = %d", raw_ad);
            // try to dump some zeros // need moving average
            if (raw_ad <= GARBAGE_VALUES) {
                raw_ad = mov_avg[0];
            }
            // may need historisissdfsd
            // the most recent old value
            if (abs(raw_ad - mov_avg[0]) >= MIN_CHANGE) {
                //                old_ad = raw_ad;
                //
                //        
                // track the oldest
                run_sum = 0;
                //                old_ad = mov_avg[ELEMENTS_IN_MOVING_AVG - 1];

//                printf("\r\n running average below:\r\n");
                for (int i = ELEMENTS_IN_MOVING_AVG - 1; i >= 0; i--) {
                    if (i <= 0) {
                        mov_avg[0] = raw_ad;
                        run_sum += raw_ad;
                        break; // clean up those off by one's
                    } else {
                        // shuffle them up
                        mov_avg[i] = mov_avg[i - 1];
                        run_sum += mov_avg[i];
//                        printf("\r\nmov_avg i = %d", mov_avg[i]);
                    }

                }

                // set the 0th to be the new value
                //                mov_avg[0] = raw_ad;
                //                run_sum += raw_ad;
                //                printf("\r\n running sum is: %d", run_sum);
                run_avg = run_sum / ELEMENTS_IN_MOVING_AVG;


                //                printf("\r\nad reading: %d\r\nstate is:%d", raw_ad, touch);
                printf("\r\n average is now: %d", run_avg);
                if (touch == TRUE) {
                    printf("\r\nTouch Detected! :))");
                    if (run_avg < LOW_BOUND_HIST) {
                        // state goes low:
                        touch = FALSE;
//                        printf("\r\nTouch Detected! :))");
                    }
                } else { // touch is false

                    printf("\r\nNo Touch Detected! ://////");

                    if (run_avg > HIGH_BOUND_HIST) { // touch is false && we get high average

                        // state goes high
                        touch = TRUE;
//                        printf("\r\nNo Touch Detected! ://////");
                    }

                }
            }
            //            


            //            
            poll_timer = TIMERS_GetMilliSeconds() + POLL_PERIOD;
        }

    }

    //    return (EXIT_SUCCESS);
}

