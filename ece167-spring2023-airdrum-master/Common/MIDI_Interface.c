#include "MIDI_Interface.h"
#include "Uart2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Initialize the UART2 (TX pin 40) that the MIDI will be transmitted 
 * on with the set baudrate (115200)
 */
void MIDI_Init(){
    Uart2Init(0);
    Uart2ChangeBaudRate(BAUD_RATE);
}

void MIDI_send_packet(MIDI_Packet packet){
    Uart2WriteData(packet.message, sizeof(packet));
}

MIDI_Packet MIDI_build_packet(uint8_t command, uint8_t channel, uint8_t note, uint8_t velocity){
    MIDI_Packet result;
    result.fields.channel= channel;
    result.fields.command= command;
    result.fields.note = note;
    result.fields.velocity = velocity;
    return result;
}

void MIDI_send_string(char* string, void* args){
    char* temp = malloc(strlen(string));
    sprintf(temp, string, args);
    Uart2WriteData(temp, strlen(temp));
    free(temp);
}