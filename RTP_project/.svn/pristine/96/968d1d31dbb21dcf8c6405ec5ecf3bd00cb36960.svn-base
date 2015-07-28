// *******************************************************
//
// mbutton.h
//
//  Support for buttons with integrated debouncing
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#ifndef MBUTTON_H_
#define MBUTTON_H_

// this is a simple preprocessor macro that will make
// it easy to switch between real (physical) and virtual
// buttons. Simply leave the desired button uncommented.
#define VIRTUAL_BUTTONS_
//#define REAL_BUTTONS_

// Constants for button states (order is important). "Pushed"
//  implies newly pushed.
enum but_state {BUT_INACTIVE = 0, BUT_OUT, BUT_IN, BUT_PUSHED};



// Constants for debounce in msec
#define BUT_DETECT_MS 5
#define BUT_HOLDOFF_MS 20

// systick poll rate
#define TICK_RATE_HZ 1000

// *******************************************************
// Button structure
typedef struct {
   int iState;			// Value from enum but_state
   unsigned int uiCntIn;	// Counter for debouncing delay
   unsigned int uiCntOut;	// Counter for debouncing delay
   //unsigned long ulPort;	// Base argument for GPIO port
   unsigned char ucPin;	// Pin mask for GPIO port for button
} button_t;


// Bit fields used to select which buttons are initialised in the
//  button set.  Designed to be ORed in argument to initButSet().
//#define UP_B 		0x08 // GPIO pin 3
//#define DOWN_B 	0x10 // GPIO pin 4
//#define LEFT_B 	0x20 // GPIO pin 5
//#define RIGHT_B 	0x40 // GPIO pin 6
//#define SELECT_B 	0x80 // GPIO pin 7

// Constants to identify buttons (need to be consecutive)
enum butDefs {UP = 0, DOWN, LEFT, RIGHT, SELECT};


void ButtonInit (unsigned char button);
void ButtonUpdate (void);
unsigned char ButtonCheck (unsigned char button);
void ButtonEnable (unsigned char button);
void ButtonDisable (unsigned char button);

#endif /*MBUTTON_H_*/




/*
 *
 * #include "button.h"

// Bit fields used to select which buttons are initialised in the
//  button set.  Designed to be ORed in argument to initButSet().
#define UP_B 0X01
#define DOWN_B 0X02
#define LEFT_B 0X04
#define RIGHT_B 0X08
#define SELECT_B 0X10
// Constants to identify buttons (need to be consecutive)
enum butDefs {UP = 0, DOWN, LEFT, RIGHT, SELECT};


// *******************************************************
// initButSet: Initialise the button instances for the specific
//  buttons specified.  Argument = bit pattern formed by UP_B,
//  DOWN_B, etc., ORed together.  Should only be called once the
//  SysCtlClock frequency is set.  'tickRateHz' is the rate of
//  SysTick interrupts (set externally).
void
initButSet (unsigned char buttons, unsigned int tickRateHz);


// *******************************************************
// updateButtons: Function designed to be called from the SysTick
//  interrupt handler.  It has no return type or argument list. A
//  call to initButSet() is required before the first call to this.
void
updateButtons (void);


// *******************************************************
// checkBut: Checks the specified individual button and returns true
//  (1) if the button is active and has state BUT_PUSHED (newly pushed)
//  and modifies state to BUT_IN. Returns false (0) otherwise.
unsigned char
checkBut (unsigned char button);


// *******************************************************
// anyButPushed: Checks the current set of active buttons and returns
//  true (>0) if any of them have state = BUT_PUSHED. Value returned
//  is an ORed set of the bits representing the button(s) newly pushed,
//  e.g., if "UP" and "SELECT" have been recently pushed, the
//  value returned is (UP_B | SELECT_B). Otherwise returns false (0).
//  State of any pushed button is altered to BUT_IN.
unsigned char
anyButPushed (void);


// *******************************************************
// enableBut: Alters the state of the specified button to BUT_OUT,
//  if it was previously BUT_INACTIVE, otherwise makes no change.
void
enableBut (unsigned char button);


// *******************************************************
// disableBut: Alters the state of the specified button to
//  BUT_INACTIVE.
void
enableBut (unsigned char button);


*/
