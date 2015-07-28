// *******************************************************
//
// vbutton.h
//
//  Support for buttons with integrated debouncing
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#ifndef VBUTTON_H_
#define VBUTTON_H_

// this is a simple preprocessor macro that will make
// it easy to switch between real (physical) and virtual
// buttons. Simply leave the desired button uncommented.
#define VIRTUAL_BUTTONS_
//#define REAL_BUTTONS_

// Constants for button states (order is important). "Pushed"
//  implies newly pushed.
enum but_state {BUT_INACTIVE = 0, BUT_OUT, BUT_IN, BUT_PUSHED};


// *******************************************************
// Button structure
typedef struct {
   int iState;			// Value from enum but_state
   //unsigned int uiCntIn;	// Counter for debouncing delay
   //unsigned int uiCntOut;	// Counter for debouncing delay
   //unsigned long ulPort;	// Base argument for GPIO port
   unsigned char ucPin;	// Pin mask for GPIO port for button
} button_t;


// Constants to identify buttons (need to be consecutive)
enum butDefs {UP = 0, DOWN, LEFT, RIGHT, SELECT};


void ButtonInit (void);
//void ButtonInit (unsigned char button);
void ButtonUpdate (void);
unsigned char ButtonCheck (unsigned char button);
void ButtonEnable (unsigned char button);
void ButtonDisable (unsigned char button);

#endif /*VBUTTON_H_*/


