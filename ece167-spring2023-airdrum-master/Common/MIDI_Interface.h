#ifndef MIDI_INTERFACE_H
#define MIDI_INTERFACE_H

#include "BOARD.h"


#define BAUD_RATE 115200

#define NOTE_ON 0x9
#define NOTE_OFF 0x8

#define DRUM_CHANNEL 9

#define DRUM_KICK 35
#define DRUM_SNARE 38
#define DRUM_HIHAT 42
#define DRUM_COWBELL 56
#define DRUM_CRASH1 49




typedef union MIDI_Packet{
    uint8_t message[3];
    struct fields{
        uint8_t channel : 4;
        uint8_t command : 4;
        uint8_t note : 8;
        uint8_t velocity : 8;
    }fields;
    
}MIDI_Packet;

/**
 * Initialize the UART2 (TX pin 40) that the MIDI will be transmitted 
 * on with the set baudrate (115200)
 */
void MIDI_Init();

/**
 * Send a MIDI packet
 * @param packet
 */
void MIDI_send_packet(MIDI_Packet packet);

/**
 * Generate a packet with argument data
 * @param command - NOTE_ON, NOTE_OFF, other MIDI functions
 * @param channel - MIDI channel to use
 * @param note - The note to command
 * @param velocity - The loudness of the note
 * @return 
 */
MIDI_Packet MIDI_build_packet(uint8_t command, uint8_t channel, uint8_t note, uint8_t velocity);


/**
 * Send a string (can be formatted) over the MIDI Uart
 * @param string - String to send
 * @param args - Formatting params, NULL if none
 */
void MIDI_send_string(char* string, void* args);

#endif