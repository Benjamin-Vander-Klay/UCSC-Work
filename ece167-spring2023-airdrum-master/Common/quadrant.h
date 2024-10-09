
#ifndef QUADRANT_H
#define	QUADRANT_H

#include <math.h>
#include "BNO055.h"

// Every EULER_PER_DEGREES read from the BNO corresponds to
// a one degree difference in angle.
#define EULER_PER_DEGREES 16
#define EPD EULER_PER_DEGREES // abbreviate.
#define HORIZONTAL_CUTOFF_ANGLE (-15 * EPD)

int getBNOQuadrant(unsigned char addr) {
    // Quadrants: | 1 | 0 |
    //            ---------
    //            | 2 | 3 |
    int quadrant = 0;
    int yaw, pitch;
    
    if (addr == (0x28)){
        yaw = BNO055_ReadEulHeading(addr);
        pitch = BNO055_ReadEulPitch(addr);
	// roll is left unused.
//    roll = BNO055_ReadEulRoll();
    }else{
        yaw = BNO055_ReadEulHeading(addr) + 90 * EPD;
        pitch = -BNO055_ReadEulRoll(addr);
//    roll = BNO055_ReadEulPitch();        
    }
    if ((yaw <= 90 * EPD || yaw >= 180 * EPD) && yaw <= 270 * EPD && pitch <= HORIZONTAL_CUTOFF_ANGLE) quadrant = 0;
    else if ((yaw >= 270 * EPD || yaw >= 90 * EPD) && pitch <= HORIZONTAL_CUTOFF_ANGLE) quadrant = 1;
    else if (yaw >= 270 * EPD && pitch > HORIZONTAL_CUTOFF_ANGLE) quadrant = 2;
    else quadrant = 3;
    
    return quadrant;
}
    
#endif	/* QUADRANT_H */

