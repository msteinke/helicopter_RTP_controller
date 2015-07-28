#ifndef BUTTON_H_
#define BUTTON_H_

// *******************************************************
// 
// button.h  ** Version 2 **
//
// Support for buttons on the Stellaris LM3S1968 EVK
// P.J. Bones UCECE
// Last modified:  28.2.2013
// 
// *******************************************************

// Constants for button states (order is important). "Pushed"
//  implies newly pushed.
enum but_state {BUT_INACTIVE = -1, BUT_OUT = 0, BUT_IN, BUT_PUSHED};
// Constants for debounce in msec
#define BUT_DETECT 4
#define BUT_HOLDOFF 50

// *******************************************************
// Button structure
typedef struct {
   int iState;			// Value from enum but_state
   unsigned int uiCnt;	// Counter for debouncing delay
   unsigned long ulPort;	// Base argument for GPIO port
   unsigned char ucPin;	// Pin mask for GPIO port for button
} button_t;

// *******************************************************
// init_button: Initialise the button instance for the specific button & pin.
//  Enable the port and pin for the button for polling only. Initialise state 
//  of button to 'out'.
void
initButton (button_t *button, unsigned long ulPort, unsigned char ucPin);

#endif /*BUTTON_H_*/
