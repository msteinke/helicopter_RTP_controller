//*****************************************************************************
//
// music1.c - Example program for ENCE361 - intro to interrupts.
//          - Also used in preparation for ENCE463 Project #1 2013.
//
//  P.J. Bones	UCECE
//  Last modified:  26.6.2013
//*****************************************************************************

//*****************************************************************************
//
//! Simple interrupt driven program:
//!   samples with ADC0 (Pin 62 on board header)
//!   reference high voltage on PF7 (Pin 29)
//!  Based on 'convertV1.c'
//!
//*****************************************************************************


// API Peripheral Modules
#include "inc/hw_types.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"

#include "mdisplay.h"
#include "mRTC.h"

// C Modules
#include <stdio.h>

// Program specific modules
//#include "circBuf.h"
//#include "mbutton.h"
//#include "heliDisplay.h"
//#include "decoder.h"




//*****************************************************************************
// Constants
//*****************************************************************************

//#define PERIOD_CIRBUFF_SIZE 5

//#define SYSTICK_RATE_HZ 1000	//Real Time clock tick rate

//#define BUTTON_POLL_RATE 1000



//#define DISPLAY_REFRESH_RATE 5

//#define BUTTON_PINS  GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7



//*****************************************************************************
// Globals
//*****************************************************************************

//static circBuf_t g_inBuffer;		// Buffer of size BUF_SIZE integers (sample values)
//static volatile unsigned long long g_ulSampCnt;	// Counter for the interrupts
//static volatile unsigned long long g_ulRTCTicks; // Ticks since program initialization
//static volatile unsigned long g_ulButtonPolls; // Counts button polling events

// Global circular buffer for storing period times
//static circBuf_t g_cBPeriodTimes;

// Global for holding decoder state, to be moved to decoder module
//	NOT NAMED USING THE STANDARD CONVENTION INTENTIONALLY
//static volatile unsigned char decoderStateLast;
// Global for encoder heading (in encoder clicks not degrees)
//static volatile unsigned short g_uiYaw_clicks;

// Global for storing period, used by the pin interupt handler

// Global for storing state of portG 												//DEBUG VARIABLE, REMOVE
//static volatile long g_ucPortG;

// Global button instance
//static button_t g_bUp;



//*****************************************************************************
//
// Main module prototypes
// (For functions used by interrupt handlers)
//*****************************************************************************



//  CONFIGURE BUTTON PINS AND SET UP INTERRUPTS FOR DEBOUNCING

/*void
initButtonPins (void)
{	
    //
    // Enable and configure the port and pins used for output with 8 mA
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);

    // Initialize button pins
    GPIOPinTypeGPIOInput (GPIO_PORTG_BASE,  GPIO_PIN_3 | GPIO_PIN_4 |
    		GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 );

    // Enable internal pullups on button pins
    GPIOPadConfigSet(GPIO_PORTG_BASE,  GPIO_PIN_3 | GPIO_PIN_4 |
    		GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_8MA,
                     GPIO_PIN_TYPE_STD_WPU);

}*/








//*****************************************************************************
//
// Main module functions
//
//*****************************************************************************

// Returns number of Systick interrupts
/*unsigned long long RTCGet(void)
{
	IntMasterDisable();
	unsigned long ticks = g_ulRTCTicks;
	IntMasterEnable();
	return ticks;
}*/

// Returns uS since program startup
/*unsigned long long RTCGetuS(void)
{
	unsigned long long ticks = RTCGet();

	// !! CONVERT TICKS INTO uS !!

	return ticks;
}*/










//*****************************************************************************
//
// Debug main loop and associated functions
//
//*****************************************************************************


/*
// Debugging display function
void updateDisplayDebug(unsigned short button_pushes)
{
	displayClear();
	displayClock(RTCGet() / SYSTICK_RATE);

	char string[100];

    sprintf(string, "%u", button_pushes);
    RIT128x96x4StringDraw(string, 5, 35, 15);
}*/

/*
void mainLoopDebug(void)
{

	buttonInit(&g_bUp, GPIO_PORTG_BASE, GPIO_PIN_3);

	unsigned short button_push_count = 0;

	unsigned short ticks = 0;

	while(1)
	{
		IntMasterDisable();
		ticks = g_ulRTCTicks;
		if(buttonPushed(&g_bUp))
			button_push_count++;
		IntMasterEnable();

		if (ticks % (SYSTICK_RATE/5) == 0)
		{
			updateDisplayDebug( buttonDown(&g_bUp) );
		}

	}
}*/

///////////////////////////////////////////////////////////////////////////////

////////////////////////////////    MAIN    ///////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

int
main(void)
{
	IntMasterDisable();

	unsigned long ticks;
	
	mRTCInit();

	// intialise the OLED display
	displayInit(10000000);

    //
    // Enable interrupts to the processor.
    IntMasterEnable();



	while (1)
	{

		ticks = (unsigned long)mRTCGetSeconds();

		//ticks = (unsigned long)RTCGet();
		displayText("ticks (S): %u", (int)ticks, 1);
		displayText("%u", mRTCGetMicroSeconds(), 2);

	}
}
