/*
    ECE 167 Lab4 Euler angle extraction
    BVK
    5/20/23


 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "MatrixMath_correct.h"
#include "Euler_Extraction_BVK.h"
#include "BOARD.h"
#include "serial.h"
#include "Oled.h"







//#define EULER_TEST

// We need to extract the angles for a given rotation matrix
// input to this is a pointer to a 3x3 rotation matrix (stored in floats)
// and the return should be the angles in degrees (not radians). 
// Use the matrix lib from ECE13 as refernce. 
// The matrix lib I see passes entire 3x3 matriceis. 
// But moral of the story is we need to extract the pitch, yaw, and roll


// refering to Part 1 of the lab manual, we need to go from the Direct Cosine Mattrix (DCM)
// To Euler Angles. The DCM takes Euler Angles and goes from the Inertial frame to the Body frame
// DCM : Inertial -> Body
// if we want Body-> Inertial, we need to do other stuff.
// but since we have a DCM, we can extract the Euler, bc the DCM uses the Euler
//  Google says we compare the DCM angles to the angles from the combined 123 euler sequence

/*
    BVK 
 * psi Yaw = atan(C12 / C11)
 * Theta Pitch = - asin(C13) 
 * Phi Roll = atan(C23 / C33)
 * could also use the one in the ECE163 attitude cheat sheet, which uses 
 * psi (yaw) = atan2(R[1][2],R[1][1])
 */
float EulerAngleYaw(float mat[3][3]) {
    // extract the above using math.h functions
    // Check that the ratios are within +/- 1

    if (abs(mat[1][2]) > 1) {
        return ERROR; // This is weird. 
        // maybe just modulus by pi or smtg
        // maybe isnan() in math.h
    }

    return atanf(mat[1][2] / mat[1][1]);
}


//Theta Pitch = - asin(C13) 

float EulerAnglePitch(float mat[3][3]) {

    // extract the above using math.h functions

    // Check that the ratios are within +/- 1
    if(mat[1][3] > 1.0) {
        mat[1][3] = 1.0;
    }
    else if(mat[1][3] < -1.0){
        mat[1][3] = -1.0;
    }

    return -asinf(mat[1][3]);
}


//Phi Roll = atan(C23 / C33)
// could similarly use the atan2(R[2][3],R[3][3]) as for Psi

float EulerAngleRoll(float mat[3][3]) {

    // extract the above using math.h functions

    return atanf(mat[2][3] / mat[3][3]);
}






#ifdef EULER_TEST
// Test some shit

int main(void) {

    BOARD_Init();
    SERIAL_Init();
    BNO055_Init();
    float m[3][3] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 12}
    };


    // never exit
    while (1) {
        // printf();
    }
}

#endif
