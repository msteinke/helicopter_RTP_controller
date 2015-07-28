//*****************************************************************************
//
// yaw_test.c Simple test file to test the yaw module.
//*****************************************************************************

//*****************************************************************************
//
//! Simple interrupt driven program:
//!   Pin config on the stellaris EVk is:
//!       ORANGE: PF5
//!       RED:    PF7
//!
//*****************************************************************************


// API Peripheral Modules
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/timer.h"
#include "drivers/rit128x96x4.h"

// C Modules
#include <stdio.h>

// Program specific modules
#include "mbutton.h"
#include "mdisplay.h"
#include "yaw.h"


///////////////////////////////////////////////////////////////////////////////
////////////////////////////////    MAIN    ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*
int main(void)
{
	IntMasterDisable();

	mButtonInit(SELECT);
	mButtonInit(DOWN);
	//decoder_pins_init ();
	yawInit();

    mDisplayInit(10000000);
    mDisplayLine("Press DOWN to reset", 0, 8, 4);
    unsigned short selectBut = 0;
    //g_uiYaw_clicks = 0;

    //
    // Enable interrupts to the processor.
    IntMasterEnable();



	while (1)
	{

		if (mButtonCheck(SELECT))
		{
			selectBut++;
		}
		if (mButtonCheck(DOWN))
		{
			yawSetClicks(0);
		}
		mDisplayLine("selectBut  = %.5u  ", selectBut, 1, 4);
		mDisplayLine("Yaw clicks = %.4d  ", yawGetClicks() , 3, 15);
		mDisplayLine("Yaw angle  = %.4d  ", yawGetAngle() , 4, 15);

		if (yawIsCW())
		{
			mDisplayLine("Direction =  CW   ", 0, 5, 15);
		}
		else
		{
			mDisplayLine("Direction =  CCW  ", 0, 5, 15);
		}


	}
}
*/


