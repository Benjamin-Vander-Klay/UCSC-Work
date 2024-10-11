/*
    ECE 167 Lab4 Euler angle extraction
    BVK
    5/20/23

 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "MatrixMath_correct.h"
#include "Lab4_Lib_BVK.h"
#include "BOARD.h"
#include "serial.h"
#include "Oled.h"
#include "BNO055.h"
#include "I2C.h"
#define LAB4_TEST





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

/*
     * omega cross matrix
     * we get the [p q r]' matrix and we need to output the wx matrix
     * [0 -r  q
     *  r  0 -p
     *  -q p  0]
     *  Right now I'm thinking we pass in the [p q r] and return a [3][3]
     *  Actually following matrixMath, makes more sense to put it in a matrix 
     *  that we prevemptively pass a pointer to
     * 
     *  return: success or failuer?
     */
int Omega_Cross(float w_in[3], float w_x_out[3][3]){
    // May need to 
    // Just hard code it whatever
    // Zeros on Diagonal
    w_x_out[1][1] = 0;
    w_x_out[2][2] = 0;
    w_x_out[3][3] = 0;
    
    // top half
    w_x_out[1][2] = -w_in[3]; // -r
    w_x_out[1][3] = w_in[2];  //  q
    w_x_out[2][3] = -w_in[1]; // -p
    
    
    // bottom half
    w_x_out[2][1] = w_in[3];  //  r
    w_x_out[3][1] = -w_in[2]; // -q
    w_x_out[3][2] = w_in[1];  //  p
    
    return SUCCESS; // might need to check in the future
}

/*
     *DCM differential exn
     * partial w respect to time of R is defined as:
     *       R_dot = - [w_x] * R 
     * Again pass in matrix for solution
     * Return: Success for now. no err check yet? 
 * q    Takes w_x as input. 
 * Uses Matrix Multiply Correct:
     mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
     */
    
    int DCM_diff_R_dot(float w_x[3][3], float R[3][3], float R_dot[3][3]){
        
//        float temp_mat [3][3] = 
        MatrixMultiply_Correct(w_x,R,R_dot);
        MatrixScalarMultiply_Correct(-1.0,R_dot,R_dot); // may not work. Could use an intermed matrix which goes away at end of function call.  
                
        return SUCCESS;
    }

     /*
     * Forward integration by BVK
     * Naive solution, we will improve in a bit.
     * R_k+1 = R_k + -w_x*R_k*delta_time 
     * @param: R_k -- pointer to current DCM matrix, 
     * @param: R_dot, pointer to current R_dot matrix -- DCM diff eq
     * @param: delta_t -- scalar constant being the time step we are using
     * @param: R_k_plusone - our output, pointer to next DCM after we apply forward integration
     */
    int DCM_update_naive(float R_k[3][3], float R_dot[3][3], float delta_t, float R_k_plusone[3][3]){
        // if we get R_dot, then we get -w_x*R_k
        // scalar multiply delta_t and R_dot,
        // and we add R_k to that
        // and return
        float temp_mat[3][3];
        MatrixScalarMultiply_Correct(delta_t, R_dot, temp_mat);
        MatrixAdd_Correct(R_k, temp_mat, R_k_plusone);   
        return SUCCESS;
    }
    
    /*
     * returns the matrix exponetial using the closed form solution from the Attitude Cheat Sheet
     * BVK
     * 
     * returns 1 why not
     * should include some case checking when w is close to zero
     * *** MAKE SURE TO CHANGE UNITS TO RAD/S
     */
    int DCM_matrixExp(float w[3], float delta_t, float w_x[3][3], float matrixExp[3][3]){
        // find magnitude of omega
        float w_mag = sqrt((w[1]*w[1]) + (w[2]*w[2]) + (w[3]*w[3]));
        // get magnitude squared... just no sqrt
        float w_mag_2 = (w[1]*w[1]) + (w[2]*w[2]) + (w[3]*w[3]);
        // Not sure if there's a math.h macro
        float I[3][3] = {
            {1,0,0},
            {0,1,0},
            {0,0,1}
        }
        
        // determine first term 
        float sine_term = -1 * sin(w_mag*delta_t) / w_mag;
        float first_term[3][3];
        MatrixScalarMultiply_Correct(sine_term, w_x, first_term);
        
        // determine second term
        // get omega cross squared
        float w_x_2[3][3];
        MatrixMultiply_Correct(w_x, w_x, w_x_2);
        
        // get 
        // get cosine term
        float cosine_term = (1 - cos(w_mag*delta_t)) / w_mag_2;
        float second_term[3][3];
        
        MatrixScalarMultiply_Correct(cosine_term, w_x_2, second_term);
        
        
        // put them all together
        
        float add_two_three[3][3];
        MatrixAdd_Correct(first_term, second_term, add_two_three);
        MatrixAdd_Correct(I, add_two_three, R_k_plusone);
        
        return SUCCESS;
    }
    

#ifdef LAB4_TEST
// Test some shit

int main(void) {

    BOARD_Init();
    SERIAL_Init();
    BNO055_Init();
    float m[3][3] = {
        {0, 1, 2},
        {4, 5, 6},
        {8, 9, 10}
    };


    // never exit
    while (1) {
        // printf();
    }
}

#endif