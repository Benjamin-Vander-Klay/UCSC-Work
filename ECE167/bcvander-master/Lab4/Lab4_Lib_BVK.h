/* 
 * File:   Lab4_Lib_BVK.h
 * Author: bcvander
 *
 * Created on May 25, 2023, 11:10 AM
 */

#ifndef LAB4_LIB_BVK_H
#define	LAB4_LIB_BVK_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*
     * Uses the equations found on vectornav Attitude transformations page
     * COuld also use the equations found in the ECE163 Attitude cheat sheet
     */
    
    float EulerAngleYaw(float mat[3][3]);
    /*
     * Uses the equations found on vectornav Attitude transformations page
     * COuld also use the equations found in the ECE163 Attitude cheat sheet
     */
    
    float EulerAnglePitch(float mat[3][3]);
    /*
     * Uses the equations found on vectornav Attitude transformations page
     * COuld also use the equations found in the ECE163 Attitude cheat sheet
     */
    float EulerAngleRoll(float mat[3][3]);
    

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
    
    int Omega_Cross(float w_in[3], float w_x_out[3][3]);


    
    /*
     *DCM differential exn
     * partial w respect to time of R is defined as:
     *       R_dot = - [w_x] * R 
     * Again pass in matrix for solution
     * Return: Success for now. no err check yet? 
     
     */
    
    int DCM_diff_R_dot(float w_x[3][3], float R[3][3], float R_dot[3][3]);
    
    
    /*
     * Forward integration by BVK
     * Naive solution, we will improve in a bit.
     * R_k+1 = R_k + -w_x*R_k*delta_time 
     * @param: R_k -- pointer to current DCM matrix, 
     * @param: R_dot, pointer to current R_dot matrix -- DCM diff eq
     * @param: delta_t -- scalar constant being the time step we are using
     * @param: R_k_plusone - our output, pointer to next DCM after we apply forward integration
     */
    int DCM_update_naive(float R_k[3][3], float R_dot[3][3], float delta_t, float R_k_plusone[3][3]);
    
    /*
     * returns the matrix exponetial using the closed form solution from the Attitude Cheat Sheet
     * BVK
     * 
     * 
     */
    int DCM_matrixExp(float w[3], float delta_t, float w_x[3][3], float matrixExp[3][3]);
#ifdef	__cplusplus
}
#endif

#endif	/* LAB4_LIB_BVK_H */

