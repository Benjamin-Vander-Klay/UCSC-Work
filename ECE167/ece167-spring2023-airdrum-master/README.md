# Team Air Drums
## ECE 167 - Final Project
---
Josh Gamlen, Alex Swanson, Anthony Russo, Benjamin Vander Klay

Electronic percussion instrument system powered by the Microchip Uno32 microcontroller.

### Materials:

Microchip Uno32 Developement Board
Microchip ChipKit3 programmer
Adafruito QT Py development board
BNO055 orientation sensor(s)
VMPK MIDI synthesizer software

### Repository Structure
Important files written for this project.
```c
├─── Common
│   ├─── MIDI_Interface.h
│   ├─── MIDI_Interface.c
│   ├─── HitDetectorLib.h
│   ├─── MIDI_Interface.c
│   └─── quadrant.h
├─── AirDrums.X
│   ├─── airDrums.c // main
│   └─── Makefile
```

### Installation
Before installing this software to your Uno32 development board you will first need to
install MPLabX and a combatible XC32 compiler. See this guide for details.

1. Clone the repository to a known directory, hereon referred to as "~".
2. Load the MPLabX IDE.
3. Select "File > Open Project" and search for "~/AirDrum.X".
4. Right click the project in the navigator window and select "Set as Main Project".
5. Select "File > Project Properties (AirDrum)".
6. From the project properties window select "XC32 (Global Options) > xc32-gcc".
7. Change the option categories dropdown to "Preprocessing and messages".
8. Add "..\Common" to the include directories and select the "Additional warnings" option.
9. Select "XC32 (Global Options) > xc32-ld".
10. Modify the heap size to be 2048 bytes.
11. Select "OK".
12. Select the "Clean and Build" option to confirm the project compiles correctly.
13. With the Uno32 device and ChipKit3 programmer both connected properly select the
"Make and Program Device" option to install the program to your board.

