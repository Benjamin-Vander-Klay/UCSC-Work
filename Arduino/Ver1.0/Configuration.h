#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#ifdef __cplusplus
 extern "C" {
#endif


/*
    LIBRARY DEFINES, ENUMS, STRUCTS
*/

    typedef enum {
        EventBufferOverflow = 0,
        EventBufferHighHead
    } ErrorCode;

	#define FIRST_BIT  0b0001
	#define SECOND_BIT 0b0010
	#define THIRD_BIT  0b0100
	#define FOURTH_BIT 0b1000
	
	#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))          // Calculates the number of elements in an array
	
	#define UNUSED_PIN 100                                      // Set this to any pin that is unused in the given implmentation

    #define NUM_POTS 2                                        // Number of each setting element emulation to be instantiated
    #define NUM_SW2  3                                        // Modify depending on how many of each the hardware has 
    #define NUM_SW3  3
    #define NUM_SW5  3
    #define NUM_SW7  2
    #define NUM_SW11 3

	typedef struct {
		int Pin1;
		int Pin2;
		int Pin3;
	} Pot;
	
	typedef struct {
		int Pin1;
	} SW2T;
	
	typedef struct {
		int Pin1;
		int Pin2;
	} SW3T;
	
	typedef struct {
		int Pin1;
		int Pin2;
		int Pin3;
	} SW5T;
	
	typedef struct {
		int Pin1;
		int Pin2;
		int Pin3;
	} SW7T;
	
	typedef struct {
		int Pin1;
		int Pin2;
		int Pin3;
		int Pin4;
	} SW11T;
	
	
  extern Pot PotList[NUM_POTS];
	
	extern SW2T SW2TList[NUM_SW2];
	
	extern SW3T SW3TList[NUM_SW3];
	
	extern SW5T SW5TList[NUM_SW5];
	
	extern SW7T SW7TList[NUM_SW7];
	
	extern SW11T SW11TList[NUM_SW11];
	
	extern int Voltage5Pin; 
	
	extern int Voltage12Pin; 
	
	extern int Voltage48Pin; 
	
	extern int Voltage310Pin; 

/*
    FUNCTION PROTOTYPES
*/

// Resets all static extern variables in Configuration.c, assigning all instantiated setting elements to an unused pin
void ResetConfig(void);


#ifdef __cplusplus
}
#endif

#endif