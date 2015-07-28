// *******************************************************
//
// mbutton.c
//
// Support for buttons
//  Stellaris LM3S1968 EVK
//
// *******************************************************

#include "mbutton.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#ifdef REAL_BUTTONS_
	// Bit fields used to select which buttons are initialised in the
	//  button set.  Designed to be ORed in argument to initButSet().
	#define PORT_BASE				GPIO_PORTG_BASE
	#define SYSCTL_PERIPH_GPIO	 	SYSCTL_PERIPH_GPIOG

	#define UP_B 			0x08 // GPIO pin 3
	#define DOWN_B 			0x10 // GPIO pin 4
	#define LEFT_B 			0x20 // GPIO pin 5
	#define RIGHT_B 		0x40 // GPIO pin 6
	#define SELECT_B 		0x80 // GPIO pin 7
#elif defined VIRTUAL_BUTTONS_
	// Bit fields used to select which buttons are initialised in the
	//  button set.  Designed to be ORed in argument to initButSet().
	#define PORT_BASE				GPIO_PORTB_BASE
	#define SYSCTL_PERIPH_GPIO	 	SYSCTL_PERIPH_GPIOB

	//#define RESET_B 		0x02 // GPIO pin 1
	#define LEFT_B 			0x04 // GPIO pin 2
	#define RIGHT_B			0x08 // GPIO pin 3
	#define SELECT_B		0x10 // GPIO pin 4
	#define UP_B			0x20 // GPIO pin 5
	#define DOWN_B			0x40 // GPIO pin 6
#else
	#error "Virtual or real buttons have not been defined. Check mbutton.h for VIRTUAL_BUTTONS_or REAL_BUTTONS_"
#endif



//
// a list of button types, one for each button on port G
static volatile button_t buttonPointer[7];

// *******************************************************
// SysTickIntHandler: Poll the buttons and determines if
// there has been a button press.
/*void SysTickIntHandler(void)
{
    //
    // Poll the buttons
    mButtonUpdate();
}*/

// *******************************************************
// initClock: Sets up the clock so that systick polls at TICK_RATE_HZ
/*void initClock (void)
{
  //
  // Set the clock rate. From Section 19.1 in stellaris_peripheral_lib_UG.doc:
  //  "In order to use the ADC, the PLL must be used; the PLL output will be
  //  used to create the clock required by the ADC." ADC rate = 8 MHz / 10.
  SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);
  //
  // Set up the period for the SysTick timer.  The SysTick timer period is
  // set as a function of the system clock.
  SysTickPeriodSet(SysCtlClockGet() / TICK_RATE_HZ);
  //
  // Register the interrupt handler
  SysTickIntRegister(SysTickIntHandler);
  //
  // Enable interrupt and device
  SysTickIntEnable();
  SysTickEnable();
}*/

// *******************************************************
// mButtonInit: Sets up a button.
void ButtonInit (unsigned char buttonPin)
{

	unsigned char ucPin;// = 1 << (buttonPin + 3);
	switch(buttonPin)
	{
	    case UP:
	        ucPin = UP_B;
	        break;
	    case DOWN:
	    	ucPin = DOWN_B;
	    	break;
	    case LEFT:
	    	ucPin = LEFT_B;
	    	break;
	    case RIGHT:
	    	ucPin = RIGHT_B;
	    	break;
	    case SELECT:
	    	ucPin = SELECT_B;
	    	break;
	}
	button_t* button = &buttonPointer[buttonPin];

	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIO);

    // Initialize button pins
    GPIOPinTypeGPIOInput (PORT_BASE, ucPin);

    // Enable internal pullups on button pins
    GPIOPadConfigSet(PORT_BASE,  ucPin, GPIO_STRENGTH_8MA,
                     GPIO_PIN_TYPE_STD_WPU);

    // Set the button_t values
    button->iState = BUT_OUT; // enable button
    button->uiCntIn = 0;
    button->uiCntOut = 0;
    button->ucPin = ucPin;

    //buttonPointer = button;
}




// *******************************************************
// mButtonUpdate: This goes into systickinthandler and polls
// each button to determine if was a button push.
void ButtonUpdate (void)
{

	button_t* button;

	// Read the pin's digital state
	//long rawPinData = GPIOPinRead(button->ulPort, button->ucPin);
	long rawPinData = GPIOPinRead(PORT_BASE,
			UP_B | DOWN_B | LEFT_B | RIGHT_B | SELECT_B);

	int pinState;

	long currentPin;  // loop through all the pins
	for (currentPin = UP; currentPin <= SELECT; currentPin++)
	{
		button = &buttonPointer[currentPin];

		//transfer the current pin read to a more meaningful variable
		unsigned char ucPin;// = 1 << (buttonPin + 3);
		switch(currentPin)
		{
		    case UP:
		        ucPin = UP_B;
		        break;
		    case DOWN:
		    	ucPin = DOWN_B;
		    	break;
		    case LEFT:
		    	ucPin = LEFT_B;
		    	break;
		    case RIGHT:
		    	ucPin = RIGHT_B;
		    	break;
		    case SELECT:
		    	ucPin = SELECT_B;
		    	break;
		}
		//if (rawPinData & (1 << (currentPin + 3)) )
		if (rawPinData & ucPin)
		{
			pinState = BUT_OUT;
		}
		else
		{
			pinState = BUT_IN;
		}

		// Don't do anything until pushed button has
		// been serviced by checkBut().
		if ((button->iState == BUT_PUSHED) || (button->iState == BUT_INACTIVE))
		{
			// Do nothing
		}
		else
		{
			// check for a button press.
			if ((button->uiCntIn >= BUT_DETECT_MS)
					&& (button->uiCntOut >= BUT_HOLDOFF_MS))
			{
				//
				button->iState = BUT_PUSHED;
				button->uiCntIn = 0;
				button->uiCntOut = 0;
			}
			else if ((button->iState == pinState) && (pinState == BUT_IN))
			{
				//
				button->iState = pinState;
				button->uiCntIn += 1;
				button->uiCntOut = 0;
			}
			else if ((button->iState == pinState) && (pinState == BUT_OUT)
					&& (button->uiCntIn >= BUT_DETECT_MS))
			{
				//
				button->iState = pinState;
				//button->uiCntIn = 0;
				button->uiCntOut += 1;
			}
			else
			{
				//button->uiCntIn = 0;
				//button->uiCntOut = 0;
				button->iState = pinState;
			}
		}
	}
}


// *******************************************************
// checkBut: Checks the specified individual button and returns true
//  (1) if the button is active and has state BUT_PUSHED (newly pushed)
//  and modifies state to BUT_IN. Returns false (0) otherwise.
unsigned char ButtonCheck (unsigned char button)
{
	//
	if (buttonPointer[button].iState == BUT_PUSHED)
	{
		buttonPointer[button].iState = BUT_IN; // modify state In or OUT??
		return true;
	}
	else
	{
		return false;
	}

}

// *******************************************************
// enableBut: Alters the state of the specified button to BUT_OUT,
//  if it was previously BUT_INACTIVE, otherwise makes no change.
void ButtonEnable (unsigned char button)
{
	//
	if (buttonPointer[button].iState == BUT_INACTIVE)
	{
		buttonPointer[button].iState = BUT_OUT;
	}
}

// *******************************************************
// disableBut: Alters the state of the specified button to
//  BUT_INACTIVE.
void ButtonDisable (unsigned char button)
{
	buttonPointer[button].iState = BUT_INACTIVE;
}



