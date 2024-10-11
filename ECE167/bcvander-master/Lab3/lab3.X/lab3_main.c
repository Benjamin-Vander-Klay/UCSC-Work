/* 
 * File:   lab3_main.c
 * Author: bcvander
 *
 * Created on May 2, 2023, 4:23 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "SERIAL.h"
#include "BNO055.h"
#include "AD.h"
#include "TIMERS.h"

#define POLL_PERIOD 15// gyro I think is 64 hz acc to .C // 16 -> 62.5 Hz? gyro 

// from matlab averaged data
//#define XGYRO_BIAS -11526 //-11.526 6 // Getting - 10 
//#define YGYRO_BIAS -39925 //-39.925 7 // 
//#define ZGYRO_BIAS 16255  //16.255 6

// from sampling as I go 
// keeping matlab one
//#define XGYRO_BIAS -11526 //-11.526 6 // Getting - 10 
//#define YGYRO_BIAS -18500 //-39.925 7 // 
//#define ZGYRO_BIAS  15500 

//
#define XGYRO_BIAS -19000//-11.526 6 // Getting - 10 
#define YGYRO_BIAS -18500 //-39.925 7 // 
#define ZGYRO_BIAS  15500 

// found from hour long test
#define XGYRO_DRIFT -1573 // 1.573 degrees per second
#define YGYRO_DRIFT 10204 // 10.2039 deg /s
#define ZGYRO_DRIFT 19678 // 19.6786 deg/s



//Getting - 10 
//#define ACCEL 
//#define MAG
#define GYRO
//#define GYRO_CALI



// not sure what these do, use 
//#define POWERPIN_LAT LATFbits.LATF1
//#define POWERPIN_TRIS TRISFbits.TRISF1

/*
 * 
 */
int main(int argc, char** argv) {
    BOARD_Init();
    SERIAL_Init();
    //    AD_Init();
    if (BNO055_Init() == FALSE) { // defined as 0 in GenTpeDefs. .h just says 0
        fprintf(stderr, "BNO055_Init() returned failure");
    }

    //    POWERPIN_LAT = 0;
    //    POWERPIN_TRIS = 0;
    //    POWERPIN_LAT = 1;


    TIMERS_Init();

    printf("\r\nBVK's Lab3 IMU Main compiled on %s, at %s", __DATE__, __TIME__);
#ifdef ACCEL 
    int xAccel = 0;
    int yAccel = 0;
    int zAccel = 0;
#endif
    // Magnetomiter 
#ifdef MAG
    int xMag = 0;
    int yMag = 0;
    int zMag = 0;

#endif
#ifdef GYRO
    int xGyro = 0;
    int yGyro = 0;
    int zGyro = 0;
    
    int xGyro_post_bias = 0;
    int yGyro_post_bias = 0;
    int zGyro_post_bias = 0;

    int xGyro_angle = 0;
    int yGyro_angle = 0;
    int zGyro_angle = 0;

    int xGyro_ang_per_sec = 0;
    int yGyro_ang_per_sec = 0;
    int zGyro_ang_per_sec = 0;

#endif 

#ifdef GYRO_CALI
    
    int xGyro = 0;
    int yGyro = 0;
    int zGyro = 0;
    
    int sample_count = 0;
    
    int xGyro_Bias = 0;
    int yGyro_Bias = 0;
    int zGyro_Bias = 0;

    int xGyro_sum = 0;
    int yGyro_sum = 0;
    int zGyro_sum = 0;
#endif
    unsigned int polling_count = TIMERS_GetMilliSeconds() + POLL_PERIOD;
    // clear buffer
    while (!IsTransmitEmpty());
    // yessir never exit
    while (1) {
        // 50 Hz is .. every 0.02 seconds. that is .020 sec or 20 ms

        if (TIMERS_GetMilliSeconds() >= polling_count) { // &&IsTransmitEmpty())
            // read the pins I2C !
#ifdef ACCEL           
            xAccel = BNO055_ReadAccelX();
            yAccel = BNO055_ReadAccelY();
            zAccel = BNO055_ReadAccelZ();

            printf("%d ", xAccel);
            printf("%d ", yAccel);
            printf("%d\r\n", zAccel);

            if (xAccel > 0) {
                xAccel = (xAccel + 40) / 1000;

            } else {
                xAccel = (xAccel) / 1000;
            }
            //            printf("%d\r\n", xAccel);


            if (yAccel > 0) {
                yAccel = (yAccel + 90) / 1000;

            } else {
                yAccel = (yAccel - 50) / 1000;
            }

            if (zAccel > 0) {
                zAccel = (BNO055_ReadAccelZ() + 50) / 1000; // shift up to over 1000
            } else {
                zAccel = (BNO055_ReadAccelZ() - 30) / 1000; // shift 
            }

            //            printf("X: %d\r\n", xAccel);
            //            printf("Y: %d\r\n", yAccel);
            //            printf("Z: %d\r\n", zAccel);

#endif
#ifdef MAG

            xMag = BNO055_ReadMagX();
            yMag = BNO055_ReadMagY();
            zMag = BNO055_ReadMagZ();
            printf("%+06d %+06d %+06d\r\n", xMag, yMag, zMag);

#endif
#ifdef GYRO_CALI
            // read the raw values
            xGyro = BNO055_ReadGyroX();
            yGyro = BNO055_ReadGyroY();
            zGyro = BNO055_ReadGyroZ();
            
            
            xGyro_sum += xGyro;
            yGyro_sum += yGyro;
            zGyro_sum += zGyro;
            sample_count++;

            xGyro_Bias = xGyro_sum / sample_count;
            yGyro_Bias = yGyro_sum / sample_count;
            zGyro_Bias = zGyro_sum / sample_count;
            printf("%+06d, %+06d, %+06d\r\n", xGyro_Bias, yGyro_Bias, zGyro_Bias);
#endif
#ifdef GYRO

            xGyro = BNO055_ReadGyroX();
            yGyro = BNO055_ReadGyroY();
            zGyro = BNO055_ReadGyroZ();
            //            printf("%+06d %+06d %+06d\r\n", xGyro, yGyro, zGyro);



            // Calibrate the data
            // subtract the bias,
            xGyro_post_bias = (1000 * xGyro) - XGYRO_BIAS;
            yGyro_post_bias = (1000 * yGyro) - YGYRO_BIAS;
            zGyro_post_bias = (1000 * zGyro) - ZGYRO_BIAS;

            // scale the data into angle per second // 4 was ok at first, but doubled. 180 instead of 90.
            // Then Alex suggested I incrase the sample speed to be maxed at 62.5 Hz acc to .C file thats for acc. Gyro i think is 65 hz
            xGyro_ang_per_sec = xGyro_post_bias * 17 / 1000;              // / 131 / 35; // was * 1000 / / 131  4
            yGyro_ang_per_sec = yGyro_post_bias * 14 / 1000;  // / 131 / 28; // guess and check on these
            zGyro_ang_per_sec = zGyro_post_bias * 16 / 1000;             // / 131 / 35; // 45 would be 

                                                //15
            // sum the change of angle to be 
            xGyro_angle += xGyro_ang_per_sec / 1000;
            yGyro_angle += yGyro_ang_per_sec / 1000;
            zGyro_angle += zGyro_ang_per_sec / 1000;


//            printf("%+06d\r\n", yGyro_angle);
            
//              printf("X: %5.2f degrees\r\n", ((float) xGyro_angle / 100));
//              printf("Y: %5.2f degrees\r\n", ((float) yGyro_angle / 100));
              printf("Z: %5.2f degrees\r\n", ((float) zGyro_angle / 100));

#endif 

            polling_count = TIMERS_GetMilliSeconds() + POLL_PERIOD;

        }



    }

    // nope never exit
    //    return (EXIT_SUCCESS);
}
//
//#include "serial.h"
//#define POWERPIN_LAT LATFbits.LATF1
//#define POWERPIN_TRIS TRISFbits.TRISF1
//
//int main(void) {
//    char initResult;
//    BOARD_Init();
//
//    printf("Welcome to the BNO055 test compiled at " __DATE__ " " __TIME__ ". Sensor will be brought up and then values displayed\r\n");
//    while (!IsTransmitEmpty());
//    POWERPIN_LAT = 0;
//    POWERPIN_TRIS = 0;
//    POWERPIN_LAT = 1;
//
//    DelayMicros(100000);
//    initResult = BNO055_Init();
//    if (initResult != TRUE) {
//        printf("Initialization of IMU failed, stopping here\r\n");
//    } else {
//        printf("Initialization succeeded\r\n");
//        while (1) {
//            if (IsTransmitEmpty()) {
//                printf("Gyro: (%+06d, %+06d, %+06d)   ", BNO055_ReadGyroX(), BNO055_ReadGyroY(), BNO055_ReadGyroZ());
//                printf("Accel: (%+06d, %+06d, %+06d)   ", BNO055_ReadAccelX(), BNO055_ReadAccelY(), BNO055_ReadAccelZ());
//                printf("Mag: (%+06d, %+06d, %+06d)   ", BNO055_ReadMagX(), BNO055_ReadMagY(), BNO055_ReadMagZ());
//                printf("Temp: %+06d", BNO055_ReadTemp());
//                printf("\r\n");
//                DelayMicros(100000);
//            }
//        }
//    }
//    while (1);
//}