/* This file contains (hopefully) correct implementations of the functions that students are 
 * expected to write.  The results of these functions can be compared to student-written functions.
 */

#include <stdio.h>
#include <math.h>

#include "MatrixMath_correct.h"

int MatrixEquals_Correct(float mat1[3][3], float mat2[3][3])
{
    int i, j;
    float tmp;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tmp = mat1[i][j] - mat2[i][j];
            if (tmp > FP_DELTA || tmp < -FP_DELTA) {
                return 0;
            }
        }
    }

    return 1;
}

void MatrixMultiply_Correct(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int r, c, i;

    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            result[r][c] = 0;
            for (i = 0; i < 3; i++)
                result[r][c] += mat1[r][i] * mat2[i][c];
        }
    }
}

void MatrixAdd_Correct(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = 0;
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void MatrixScalarMultiply_Correct(float x, float mat[3][3], float result[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = x * mat[i][j];
        }
    }
}

void MatrixScalarAdd_Correct(float x, float mat[3][3], float result[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = x + mat[i][j];
        }
    }
}

float MatrixTrace_Correct(float mat[3][3])
{
    float result = 0;
    int i;
    for (i = 0; i < 3; i++) {
        result += mat[i][i];
    }
    return result;
}

void MatrixTranspose_Correct(float mat[3][3], float result[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = mat[j][i];
        }
    }
}

void MatrixSubmatrix_Correct(int i, int j, float mat[3][3], float result[2][2])
{
    int rows_to_keep0, rows_to_keep1, cols_to_keep0, cols_to_keep1;
    if (i == 0) {
        rows_to_keep0 = 1;
    } else rows_to_keep0 = 0;
    if (i == 2) {
        rows_to_keep1 = 1;
    } else rows_to_keep1 = 2;

    if (j == 0) {
        cols_to_keep0 = 1;
    } else cols_to_keep0 = 0;
    if (j == 2) {
        cols_to_keep1 = 1;
    } else cols_to_keep1 = 2;

    result[0][0] = mat[rows_to_keep0][cols_to_keep0];
    result[0][1] = mat[rows_to_keep0][cols_to_keep1];
    result[1][0] = mat[rows_to_keep1][cols_to_keep0];
    result[1][1] = mat[rows_to_keep1][cols_to_keep1];
}

//a useful helper "function" for Determinant and Inverse:
#define Determinant2x2(m) (m[0][0]*m[1][1] - m[0][1]*m[1][0])

float MatrixDeterminant_Correct(float mat[3][3])
{
    float coefficients[3] = {mat[0][0], -mat[0][1], mat[0][2]};
    int i;
    float sub[2][2];
    float ret = 0;
    for (i = 0; i < 3; i++) {
        MatrixSubmatrix_Correct(0, i, mat, sub);
        float minor = Determinant2x2(sub);
        ret += coefficients[i] * minor;
    }
    return (ret);
}

void MatrixInverse_Correct(float mat[3][3], float result[3][3])
{
    int i, j;
    float sub[2][2];
    //first, make cofactor matrix
    float cofactor[3][3];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            MatrixSubmatrix_Correct(i, j, mat, sub);
            float minor = Determinant2x2(sub); //transpose as we record
            if ((i + j) % 2 == 0) { //i+j is even
                cofactor[j][i] = minor;
            } else cofactor[j][i] = -minor;
        }
    }
    //then, scale it by 1/determinant:
    float det = MatrixDeterminant_Correct(mat);
    MatrixScalarMultiply_Correct(1 / det, cofactor, result);
}

void MatrixPrint_Correct(float mat[3][3])
{
    int i, j;
    puts("\n   +---------+---------+---------+");
    for (i = 0; i < 3; i++) {
        printf("   | ");
        for (j = 0; j < 3; j++) {
            printf("% -7.2f | ", (double) mat[i][j]);
        }
        puts("\n   +---------+---------+---------+");
    }
}

// <editor-fold defaultstate="collapsed" desc="Adjugate Defined Here">

//
//void MatrixAdjugate_Correct(float mat[3][3], float result[3][3])
//{
//    // This variable stores the cofactor matrix of `mat`.
//    float tmp[3][3];
//
//    int i;
//    for (i = 0; i < 3; i++) {
//        // Compute the rows that contain our elements here for speed.
//        int row1 = (i + 1) % 3;
//        int row2 = (i + 2) % 3;
//        if (row2 < row1) {
//            SWAP(row2, row1);
//        }
//
//        int j;
//        for (j = 0; j < 3; j++) {
//            // Calculate the row and column indices for the 4 elements we care about. They're all
//            // the elements that don't share a row or column with the current element.
//            int col1 = (j + 1) % 3;
//            int col2 = (j + 2) % 3;
//            if (col2 < col1) {
//                SWAP(col2, col1);
//            }
//
//            // Compute whether this element needs to be negated.
//            int sign = ((i ^ j) & 1) ? -1 : 1;
//
//            // Now that we have our new 2x2 matrix, calculate the determinate for it.
//            tmp[i][j] = sign * (mat[row1][col1] * mat[row2][col2] - mat[row1][col2] * mat[row2][col1]);
//        }
//    }
//
//    MatrixTranspose(tmp, result);
//}
// </editor-fold>