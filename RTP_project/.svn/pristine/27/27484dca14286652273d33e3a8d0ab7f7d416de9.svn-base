// *******************************************************
//
// height.h
//
// Functions to set-up height measurement for a helicopter
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#ifndef HEIGHT_H_
#define HEIGHT_H_


// CONSTANTS
#define CIRCBUF_SIZE 10

// PROTOTYPES
// *******************************************************
// Initializes the ADC pins and their ISRs.
void heightInit(void);

// *******************************************************
// Takes an ADC sample. This is the location of
// the helicopter on the vertical axis.
void heightSample(void);



// *******************************************************
// Returns the height of the heli. This is the location of
// the helicopter on the vertical axis.
unsigned long heightGet(void);


// *******************************************************
// Returns the height of the heli. This is the location of
// the helicopter on the vertical axis.
unsigned long heightGetRaw(void);

// *******************************************************
// Returns the last known direction of movement of heli.
// Do we need this?
int heightGetDirection(void);


// *******************************************************
// Sets the height to a desired value (for calibration)
// Do we need this?
void heightSet(int value);

#endif /*HEIGHT_H_*/
