/* 
 * File:   BNO055.h
 * Author: Aaron Hunter
 * 
 * Software module to communicate with the IMU over I2C.
 * Provides access to each raw sensor axis along with raw temperature
 *
 * Created on April 11, 2022, 8:58 AM
 */

#ifndef BNO055_H
#define	BNO055_H

#define GYRO_CALIB_STAT 0b00110000
#define ACCEL_CALIB_STAT 0b00001100

/**
 * @Function BNO055_Init(Rate)

 * @return 0 if error, 1 if succeeded
 * @brief  Initializes the BNO055 for usage.
 * @author Aaron Hunter */
char BNO055_Init(unsigned char addr);

unsigned char BNO055_ReadCalibStat(unsigned char addr);

int BNO055_ReadEulHeading(unsigned char addr);
int BNO055_ReadEulPitch(unsigned char addr);
int BNO055_ReadEulRoll(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadAccelX(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadAccelY(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadAccelZ(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadGyroX(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadGyroY(unsigned char addr);


/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadGyroZ(unsigned char addr);



/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadMagX(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadMagY(unsigned char addr);

/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadMagZ(unsigned char addr);


/**
 * @Function BNO055_Read*()
 * @param None
 * @return Returns raw sensor reading
 * @brief reads sensor axis as given by name
 * @author Aaron Hunter*/
int BNO055_ReadTemp(unsigned char addr);

#endif

